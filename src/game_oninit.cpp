#include "game.h"

//#define DEBUG_OUTPUT_GAME

#ifdef DEBUG_OUTPUT_GAME
#include <iostream>
#endif // DEBUG_OUTPUT_GAME

bool game::OnInit()
{
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO  | SDL_INIT_JOYSTICK) < 0)
    {
        #ifdef DEBUG_OUTPUT_GAME
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_GAME
        return false;
    }
    int result = 0;
    int flags = MIX_INIT_MP3;
    if (flags != (result = Mix_Init(flags)))
    {
        //std::cout<<"Could not initialize mixer "<<result<< std::endl;
        //std::cout<<"Mix_Init: "<<Mix_GetError()<< std::endl;
        return false;
    }

    if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        #ifdef DEBUG_OUTPUT_GAME
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_GAME
        return false;
    }

    /* TTF Init */
    if (TTF_Init() != 0){
        #ifdef DEBUG_OUTPUT_GAME
		std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_GAME
		SDL_Quit();
		return 1;
	}
    /* SDL Window */
    if((window = SDL_CreateWindow("Bombermaniac!",50,50, window_width, window_height, SDL_WINDOW_SHOWN)) == NULL)
    {
        #ifdef DEBUG_OUTPUT_GAME
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_GAME
        //SDL_Quit();
        return false;
    }
    /* SDL Renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL){
        #ifdef DEBUG_OUTPUT_GAME
        std::cout << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_GAME
        return false;
    }

    return true;
}
