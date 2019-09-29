#include "game.h"

void game::OnRender()
{
    //Clear the renderer
    SDL_RenderClear(renderer);

    //Draw
    display_manager->Draw(renderer);

    //Update the screen
    SDL_RenderPresent(renderer);
}

