#pragma once

#ifndef _SDLWRAPPER_H_
#define _SDLWRAPPER_H_

// Geometry
//
#include "IncludeGL.hpp"

// SDL
//
#include <SDL/SDL.h>

// STL
//
#include <iostream>
#include <string>

namespace Geometry
{
    class TimeManager;
    class SDLWrapper
    {
    public:
        /* =============================================================
         * ENUMS
         * ============================================================= */
        struct SimulationState
        {
            enum State
            {                
                RUNNING = 1,
                PAUSED  = 2,
                QUIT    = 4
            };
        };

        /* =============================================================
         * CTOR
         * ============================================================= */

        SDLWrapper( const std::string& title, const int& width, const int& height );

        /* =============================================================
         * DTOR
         * ============================================================= */
        ~SDLWrapper( );

        /* =============================================================
         * PUBLIC FUNCTIONS
         * ============================================================= */

        // SDL
        //        
        bool OnInit                 ( );
        void OnCleanup              ( );
        void OnResize               ( int width, int height );
        void OnExit                 ( );

        //////////////////////////////////////////
        // Simulation
        //////////////////////////////////////////

        // Heartbeat
        //
        void OnExecute              ( );
        void OnLoop                 ( );

        /* =============================================================
         * INLINE FUNCTIONS
         * ============================================================= */

        inline const bool IsRunning ( ) const { return m_state == SimulationState::RUNNING; }

    private:
        /* =============================================================
         * MEMBERS
         * ============================================================= */

        std::string                 m_title;
        int                         m_width;
        int                         m_height;
        unsigned int                m_nUpdates;
        double                      m_deltaTime;
        SimulationState::State            m_state;

        // SDL
        //
        SDL_Surface*                m_mainwindow;

        // Utilities
        //
        TimeManager*                m_timer;

        /* =============================================================
         * PRIVATE FUNCTIONS
         * ============================================================= */

        void OnUpdate               ( );
        void OnRender               ( );
        void OnInput                ( );

        /* =============================================================
         * SDL INPUT HANDLING FUNCTIONS
         * ============================================================= */

        // Handlers
        void HandleMouseButtonDownEvents    ( SDL_Event* event );
        void HandleMouseButtonUpEvents      ( SDL_Event* event );

        // Keyboard
        //
        void OnKeyDown              ( SDL_KeyboardEvent keyBoardEvent );
        void OnKeyUp                ( SDL_KeyboardEvent keyBoardEvent );  

        // Touch
        //
        void OnFingerDown           ( SDL_Event* touchFingerEvent );
        void OnFingerUp             ( SDL_Event* touchFingerEvent );
        void OnFingerMotion         ( SDL_Event* touchFingerEvent );

        // Mouse
        //

        // Move
        void OnMouseMove            ( int x, int y, int relx, int rely, bool left, bool right, bool middle );

        // Button down
        void OnLButtonDown          ( int x, int y);
        void OnRButtonDown          ( int x, int y);
        void OnMButtonDown          ( int x, int y);

        // Button up
        void OnLButtonUp            ( int x, int y);        
        void OnRButtonUp            ( int x, int y);        
        void OnMButtonUp            ( int x, int y);
    };
}

#endif // _SDLWRAPPER_H_