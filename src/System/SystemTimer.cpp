#include "System/SystemTimer.h"
#include <SDL2/SDL.h>

SystemTimer* SystemTimer::s_instance;

SystemTimer::SystemTimer()
    : m_past_ticks(SDL_GetTicks()),
      m_paused_ticks(m_past_ticks),
      m_paused(false)
{
}

SystemTimer* SystemTimer::Instance()
{
    if (s_instance == 0) {
        s_instance = new SystemTimer();
    }
    return s_instance;
}

void SystemTimer::ResetTimer()
{
    m_past_ticks = SDL_GetTicks();
}

void SystemTimer::DecreaseTimer(unsigned long interval)
{
    m_past_ticks += interval;
}

unsigned long SystemTimer::GetTimeElapsed() const
{
    if (m_paused)
        return m_paused_ticks - m_past_ticks;
    else
        return SDL_GetTicks() - m_past_ticks;
}

void SystemTimer::Pause()
{
    if (!m_paused)
    {
        m_paused_ticks = SDL_GetTicks();
        m_paused = true;
    }
}

void SystemTimer::Unpause()
{
    if (m_paused)
    {
        m_past_ticks = SDL_GetTicks() - (m_paused_ticks - m_past_ticks);
        m_paused = false;
    }
}

bool SystemTimer::IsPaused() const
{
    return m_paused;
}
