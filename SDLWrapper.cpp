#include "SDLWrapper.hpp"
#include "TimeManager.hpp"

#include "package.h"

// Constants
//
const float DESIRED_FRAME_RATE = 60.0f;
const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;

namespace Geometry
{
    SDLWrapper::SDLWrapper( const std::string& title, const int& width, const int& height )
        : m_title       ( title )
        , m_width       ( width )
        , m_height      ( height )
        , m_nUpdates    ( 0 )
        , m_deltaTime   ( 0.0 )
    {
        // Initializing the main window pointer
        //
        m_mainwindow = 0;

        // Setting the Simulation state
        //
        m_state = SimulationState::RUNNING;

        // Initializing members
        //
        m_timer = new TimeManager;
    }

    SDLWrapper::~SDLWrapper( )
    {        
        OnCleanup( );
    }

    bool SDLWrapper::OnInit( )
    {
        if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) 
        {            
            return false;
        }

        // Setting the windows title
        //
        SDL_WM_SetCaption( m_title.c_str(), "icon goes here." );

        // Setting GL attributes
        //
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE,            8 );
        SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,          8 );
        SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,           8 );
        SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,          8 );
        
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,          16 );
        SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE,         32 );

        SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE,      8 );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE,    8 );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE,     8 );
        SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE,    8 );

        /*
         * There's something about multi-sampling that my VM doesn't like
         * SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS,  1 );
         * SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES,  2 );
         */ 

        // Creating the drawing canvas and GL context at the same time
        // got to admit even though is a simple function call to the API
        // this feels very, very, very, very weird. Like 1990's weird.
        // http://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlsetvideomode.html
        //

        /*
            SDL_HWSURFACE - Create the video surface in video memory
            SDL_GL_DOUBLEBUFFER - Enable hardware double buffering; only valid with SDL_HWSURFACE
            SDL_OPENGL - Create an OpenGL rendering context.
        */

        if(( m_mainwindow = SDL_SetVideoMode( m_width, m_height, 32, 
            SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) 
        {
            std::cerr << "Unable to set video mode: " << SDL_GetError() << std::endl;

            return false;
        }

        GLenum glew_status = glewInit();
        if (GLEW_OK != glew_status) {
            std::cerr  << stderr, "Error: %s\n", glewGetErrorString(glew_status);
            return false;
        }

        if (!GLEW_VERSION_2_0) {
            std::cerr  << stderr, "No support for OpenGL 2.0 found\n";
            return false;
        }

        GameRoot::getInstance()->onInitView();

        return true;
    }

    void SDLWrapper::OnCleanup( )
    {
        // SDL Cleanup
        //
        SDL_FreeSurface( m_mainwindow );
        SDL_Quit( );
    }

    void SDLWrapper::OnResize( int width, int height )
    {
        m_width = width;
        m_height = height;
    }

    void SDLWrapper::OnExit( )
    {
        m_state = SimulationState::QUIT;
    }

    void SDLWrapper::OnExecute( )
    {        
        // Frame starts
        //
        double startTime = m_timer->GetElapsedTime( );

        // Input
        //
        OnInput( );

        // Update
        //
        OnUpdate( );

        // Draw
        //
        OnRender( );

        
        // Time Management
        //
        double endTime = m_timer->GetElapsedTime( );
        double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

        while( endTime < nextTimeFrame )
        {
            // Spin lock
            //
            endTime = m_timer->GetElapsedTime( );
        }

        // Frame ends
        //
        ++m_nUpdates;
        m_deltaTime = m_nUpdates / static_cast< double >( DESIRED_FRAME_RATE );        
    }

    void SDLWrapper::OnInput( )
    {
        SDL_Event event;

        if( SDL_PollEvent( &event ))
        {
            // Clean exit if window is closed
            //
            if( event.type == SDL_QUIT ) 
            {
                OnExit( );
            }

            switch( event.type )
            {
                case SDL_KEYDOWN:            
                    OnKeyDown( event.key );
                    break;            

                case SDL_KEYUP:
                    OnKeyUp( event.key );                
                    break;

                case SDL_MOUSEMOTION:
                    OnMouseMove( event.motion.x,
                                 event.motion.y,
                                 event.motion.xrel,
                                 event.motion.yrel,
                                 ( event.motion.state & SDL_BUTTON( SDL_BUTTON_LEFT   )) != 0,   // Left button clicked
                                 ( event.motion.state & SDL_BUTTON( SDL_BUTTON_RIGHT  )) != 0,   // Right button clicked
                                 ( event.motion.state & SDL_BUTTON( SDL_BUTTON_MIDDLE )) != 0 ); // Middle button clicked
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    HandleMouseButtonDownEvents( &event );
                    break;

                case SDL_MOUSEBUTTONUP:
                    HandleMouseButtonUpEvents( &event );
                    break;

                #if EMSCRIPTEN
                case SDL_FINGERMOTION:
                    OnFingerMotion( &event );
                    break;

                case SDL_FINGERDOWN:
                    OnFingerDown( &event );
                    break;

                case SDL_FINGERUP:
                    OnFingerUp( &event );
                    break;
                #endif
            }
        }
    }

    void SDLWrapper::HandleMouseButtonDownEvents( SDL_Event* event )
    {
        switch( event->button.button ) 
        {
            case SDL_BUTTON_LEFT:
                OnLButtonDown( event->button.x, event->button.y );
                break;

            case SDL_BUTTON_RIGHT:
                OnRButtonDown( event->button.x, event->button.y );
                break;
            
            case SDL_BUTTON_MIDDLE:
                OnMButtonDown( event->button.x, event->button.y );
                break;            
        }
    }

    void SDLWrapper::HandleMouseButtonUpEvents( SDL_Event* event )
    {
        switch( event->button.button )
        {
            case SDL_BUTTON_LEFT:
                OnLButtonUp( event->button.x, event->button.y );
                break;
            
            case SDL_BUTTON_RIGHT:
                OnRButtonUp(event->button.x, event->button.y);
                break;
            
            case SDL_BUTTON_MIDDLE:
                OnMButtonUp(event->button.x, event->button.y);
                break;            
        }
    }

    void SDLWrapper::OnMouseMove( int x, int y, int relx, int rely, bool left, bool right, bool middle )
    {
        //std::cout << "motion: " << x << ", " << y << " " << relx << ", " << rely << "\n";
        //std::cout << "buttons: left: " << left << ", right: " << right << " middle: " << middle << "\n";
    }

    void SDLWrapper::OnLButtonDown( int x, int y)
    {
        std::cout << "Left button down: " << x << ", " << y << "\n";
        Input::getInstance()->onTouch(tTouchEvent(tTouchEvent::kTouchBegin,
                tPoint2f(x, y), 0));
    }

    void SDLWrapper::OnRButtonDown( int x, int y )
    {
        std::cout << "Right button down: " << x << ", " << y << "\n";
    }

    void SDLWrapper::OnMButtonDown( int x, int y )
    {
        std::cout << "Middle button down: " << x << ", " << y << "\n";
    }

    void SDLWrapper::OnLButtonUp( int x, int y )
    {
        std::cout << "Left button Up: " << x << ", " << y << "\n";
        Input::getInstance()->onTouch(tTouchEvent(tTouchEvent::kTouchEnd,
                tPoint2f(x, y), 0));
    }

    void SDLWrapper::OnRButtonUp( int x, int y )
    {
        std::cout << "Right button Up: " << x << ", " << y << "\n";
    }

    void SDLWrapper::OnMButtonUp( int x, int y )
    {
        std::cout << "Middle button Up: " << x << ", " << y << "\n";
    }

    void SDLWrapper::OnFingerDown( SDL_Event* touchFingerEvent )
    {
        #if EMSCRIPTEN
        SDL_TouchFingerEvent *t = (SDL_TouchFingerEvent*)touchFingerEvent;
        std::cout << "Finger Down! " << t->touchId << "\n";
        #endif
    }

    void SDLWrapper::OnFingerUp( SDL_Event* touchFingerEvent )
    {
        #if EMSCRIPTEN
        SDL_TouchFingerEvent *t = (SDL_TouchFingerEvent*)touchFingerEvent;
        std::cout << "Finger Up! " << t->touchId << "\n";
        #endif
    }

    void SDLWrapper::OnFingerMotion( SDL_Event* touchFingerEvent )
    {
        #if EMSCRIPTEN
        SDL_TouchFingerEvent *t = (SDL_TouchFingerEvent*)touchFingerEvent;
        std::cout << "Finger Motion! " << t->touchId << "\n";
        #endif
    }


    void SDLWrapper::OnLoop( )
    {

    }

    void SDLWrapper::OnUpdate( )
    {

    }

    void SDLWrapper::OnKeyDown( SDL_KeyboardEvent keyBoardEvent )
    {
        Input::getInstance()->onKeyboard(tKeyboardEvent(tKeyboardEvent::kKeyDown, keyBoardEvent.keysym.sym ));
    }

    void SDLWrapper::OnKeyUp( SDL_KeyboardEvent keyBoardEvent )
    {
        if( keyBoardEvent.keysym.sym == SDLK_ESCAPE )
        {            
            OnExit( );
        }

        Input::getInstance()->onKeyboard(tKeyboardEvent(tKeyboardEvent::kKeyUp, keyBoardEvent.keysym.sym ));
    }

    void SDLWrapper::OnRender( )
    {
        // TODO: Should this be set per render call?
        //
        //glViewport( 0, 0, m_width, m_height );

        // Clear buffer
        //
        //glClearColor( 0.1f, 0.1f, 0.15f, 1.0f );
        //glClear( GL_COLOR_BUFFER_BIT );
        GameRoot::getInstance()->onRedrawView(0);

        // Bringing the back buffer to the front
        //
        SDL_GL_SwapBuffers();   
    }
}