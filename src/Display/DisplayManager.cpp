#include "Display/DisplayManager.h"

#include "Display/ExitDisplay.h"
#include "Display/WelcomeDisplay.h"

DisplayManager::DisplayManager(SDL_Texture* texture,
                               SDL_Renderer* renderer,
                               bool* running,
                               unsigned int window_width,
                               unsigned int window_height)
    : m_renderer(renderer),
      m_window_width(window_width),
      m_window_height(window_height)
{
    m_displays.push(new ExitDisplay(running));
    m_displays.push(new WelcomeDisplay(texture,renderer,window_width,window_height));
}

DisplayManager::~DisplayManager()
{
    while (!m_displays.empty())
    {
        delete m_displays.top();
        m_displays.pop();
    }
}

void DisplayManager::EnterDisplay(Display* display)
{
    m_displays.top()->Leave();
    m_displays.push(display);
    m_displays.top()->Init();
}

void DisplayManager::LeaveDisplay()
{
    int mode = m_displays.top()->Destroy();
    delete m_displays.top();
    m_displays.pop();
    m_displays.top()->Enter(mode);
}

Display* DisplayManager::CurrentDisplay()
{
    return m_displays.top();
}

void DisplayManager::Update()
{
    if (CurrentDisplay()->ShouldLeaveToNext())
        EnterDisplay(CurrentDisplay()->NextDisplay());
    else if (CurrentDisplay()->ShouldLeaveToPrevious())
    {
        LeaveDisplay();
        Update();
    }
    else
        CurrentDisplay()->Update();
}

void DisplayManager::Draw(SDL_Renderer* renderer)
{
    CurrentDisplay()->Draw(renderer);
}
