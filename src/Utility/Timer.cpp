#include "Utility/Timer.h"
#include <SDL2/SDL.h>

Timer::Timer()
    : m_system_timer(SystemTimer::Instance()),
      m_past_ticks(m_system_timer->GetTimeElapsed()),
      m_paused_ticks(m_past_ticks),
      m_paused(false)
{
}

Timer::Timer(SystemTimer* system_timer)
    : m_system_timer(system_timer),
      m_past_ticks(m_system_timer->GetTimeElapsed()),
      m_paused_ticks(m_past_ticks),
      m_paused(false)
{
}

void Timer::ResetTimer()
{
    m_past_ticks = m_system_timer->GetTimeElapsed();
}

void Timer::DecreaseTimer(unsigned long interval)
{
    m_past_ticks += interval;
}

unsigned long Timer::GetTimeElapsed() const
{
    if (m_paused)
        return m_paused_ticks - m_past_ticks;
    else
        return m_system_timer->GetTimeElapsed() - m_past_ticks;
}

void Timer::Pause()
{
    if (!m_paused)
    {
        m_paused_ticks = m_system_timer->GetTimeElapsed();
        m_paused = true;
    }
}

void Timer::Unpause()
{
    if (m_paused)
    {
        m_past_ticks = m_system_timer->GetTimeElapsed() -
                       (m_paused_ticks - m_past_ticks);
        m_paused = false;
    }
}

bool Timer::IsPaused() const
{
    return m_paused;
}
