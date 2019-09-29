#include "Display/ExitDisplay.h"

ExitDisplay::ExitDisplay(bool* running)
    : Display(), m_running(running)
{
}

ExitDisplay::~ExitDisplay()
{
}

void ExitDisplay::Enter(int mode)
{
    if (m_running == nullptr)
        SDL_Quit();
    else
        *m_running = false;
}

void ExitDisplay::Update()
{
    if (m_running == nullptr)
        SDL_Quit();
    else
        *m_running = false;
}

void ExitDisplay::Draw(SDL_Renderer* renderer) const
{
}
