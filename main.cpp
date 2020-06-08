#include "SDLWrapper.hpp"
#include <SDL/SDL_mixer.h>
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

bool initAudio()
{
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	{
		printf("Unable to open audio!\n");
        return false;
	}
    return true;
}

int main()
{        
    game = new Geometry::SDLWrapper( "Geometry Wars Clone", WIDTH, HEIGHT );

    game->OnInit( );

    #if EMSCRIPTEN
        emscripten_set_main_loop( step, 0, 0 );
    #else
    	Mix_Music* music = nullptr;
        if(initAudio())
        {
            music = Mix_LoadMUS("./Resources/Sounds/music.wav");
            if(music)
                Mix_PlayMusic(music, -1);
        }

        while( game->IsRunning( ))
        {            
            step( );
        }
    #endif
    
    delete game;
    Mix_FreeMusic(music);
    return 0;
}