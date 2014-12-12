#include "SDLWrapper.hpp"
//#include <iostream>

#if EMSCRIPTEN
    #include <emscripten.h>
#endif

// Game Window Size
//
const int WIDTH         = 1136;
const int HEIGHT        = 640;

// Game obj
//
Geometry::SDLWrapper * game   = 0;

void step () 
{
    game->OnExecute( );
}

void channelDone(int channel) {
    printf("channel %d finished playback.\n",channel);
}


int main()
{        
    game = new Geometry::SDLWrapper( "Geometry Wars Clone", WIDTH, HEIGHT );

    game->OnInit( );

    #if EMSCRIPTEN
        emscripten_set_main_loop( step, 0, 0 );
    #else
        while( game->IsRunning( ))
        {            
            step( );
        }
    #endif
    
    delete game;

    return 0;
}