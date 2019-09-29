#include "game.h"
#include "Constants/WindowConstants.h"

game::game()
    : Running(true),
      window(nullptr),
      renderer(nullptr),
      Event(),
      keyboard_input(KeyboardInput::Instance()),
      texture(nullptr),
      display_manager(nullptr),
      window_width(WINDOW_WIDTH),
      window_height(WINDOW_HEIGHT)
{
}

int game::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }

    if (LoadContent() == false)
    {
        return -1;
    }

    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    Cleanup();

    return 0;
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) 
        {
            printf("SDL_JoystickOpen: %s\n", SDL_GetError());
        }
        else
        {
            printf("SDL_JoystickOpen: OK\n");
        }
    } 
    
    game theGame;

    return theGame.OnExecute();
}
