#ifndef FREETIMER_H
#define FREETIMER_H

/**
 *  \file FreeTimer.h
 *
 *  Defines class FreeTimer which is used to calculate elapsed time
 */

/** \class FreeTimer
 *  \brief class for measuring time
 *  \details This is an utility class for measuring time which can be used for
 *           properly timing events.
 */
class FreeTimer
{
    public:
        /**
         *  \brief Make new timer and set it to 0.
         *
         *  Basic constructor which makes new Timer object and sets it's value
         *  to 0.
         */
        FreeTimer();
        /**
         *  \brief Resets the timer
         *
         *  Resets the time elapsed so that the next call of GetTimeElapsed()
         *  gives the number of milliseconds since the last reset.
         *
         *  \return void
         */
        void ResetTimer();
        /**
         *  \brief Decreases timer by the given interval
         *
         *  Decreases the timer by the given number of millisecond so that the
         *  next call of GetTimeElapsed() will give number of milliseconds
         *  lessened by the interval.
         *  \param interval number of milliseconds to decrease
         *  \return void
         */
        void DecreaseTimer(unsigned long interval);
        /**
         *  \brief Gives time elapsed in milliseconds
         *
         *  Value returned is unsigned long which represents time in
         *  milliseconds since last time the timer was reset or since it was
         *  created.
         *
         *  \return number of milliseconds since last reset
         */
        unsigned long GetTimeElapsed() const;
        /**
         *  \brief Pauses the timer
         *
         * Stops measuring the time. Each consecutive call of the
         * GetTimeElapsed() will always give the same time until Unpause() is
         * called. Also IsPaused() will now return true;
         * \return void
         */
        void Pause();
        /**
         *  \brief Unpauses the timer
         *
         *  Resumes measuring the time if it was paused. Timer will continue to
         *  measure the normally in either case.
         *  \return void
         */
        void Unpause();
        /**
         *  \brief Tells if the timer is paused
         *
         *  Return true if timer is currently not measuring time that passes.
         *  \return true if the timer is paused and not measuring time.
         */
        bool IsPaused() const;

    protected:

    private:
        unsigned long    m_past_ticks;
        unsigned long    m_paused_ticks;
        bool             m_paused;

};

#endif // FREETIMER_H
