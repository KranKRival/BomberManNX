#include "game.h"

void game::Cleanup()
{
    for (int i = 0; i < 2; i++) 
    {
        SDL_Joystick *joys = SDL_JoystickOpen(i);
        SDL_JoystickClose(joys);
    }
    delete display_manager;
    Mix_CloseAudio();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
