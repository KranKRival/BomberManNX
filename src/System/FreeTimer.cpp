#include "System/FreeTimer.h"
#include <SDL2/SDL.h>

FreeTimer::FreeTimer()
    : m_past_ticks(SDL_GetTicks()),
      m_paused_ticks(m_past_ticks),
      m_paused(false)
{
}

void FreeTimer::ResetTimer()
{
    m_past_ticks = SDL_GetTicks();
}

void FreeTimer::DecreaseTimer(unsigned long interval)
{
    m_past_ticks += interval;
}

unsigned long FreeTimer::GetTimeElapsed() const
{
    if (m_paused)
        return m_paused_ticks - m_past_ticks;
    else
        return SDL_GetTicks() - m_past_ticks;
}

void FreeTimer::Pause()
{
    if (!m_paused)
    {
        m_paused_ticks = SDL_GetTicks();
        m_paused = true;
    }
}

void FreeTimer::Unpause()
{
    if (m_paused)
    {
        m_past_ticks = SDL_GetTicks() - (m_paused_ticks - m_past_ticks);
        m_paused = false;
    }
}

bool FreeTimer::IsPaused() const
{
    return m_paused;
}
