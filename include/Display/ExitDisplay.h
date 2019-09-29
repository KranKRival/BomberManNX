#ifndef EXITDISPLAY_H
#define EXITDISPLAY_H

/**
 *  \file ExitDisplay.h
 *
 *  Defines class ExitDisplay which represents special type of Display that
 *  has a special purpose of signaling that the program should quit.
 *
 */

#include "Display/Display.h"

/** \class ExitDisplay
 *
 * \brief Class which represents special type of Display that signals the
 *        program when it should quit
 * \details Class ExitDisplay is a special type of Display that has a special
 *          purpose of signaling that the program should quit. It does not have
 *          the usual Update() and Draw() methods as it does not need to update
 *          or draw anything.
 *
 */
class ExitDisplay : public Display
{
    public:
        /**
         *  \brief Constructor for ExitDisplay
         *
         *  Makes the special ExitDisplay with the given boolean pointer so that
         *  it can signal the program when it should quit
         *  \param running pointer to boolean values which represents whether
         *         the program should still be running or not
         *
         */
        ExitDisplay(bool* running = nullptr);
        ~ExitDisplay(); /**< \brief Default destructor */
        ExitDisplay(const ExitDisplay& other) = delete; /**< \brief Default copy constructor is disabled */
        ExitDisplay& operator=(const ExitDisplay&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Enter method for ExitDisplay
         *
         *  When called signals that the program should quit
         *  \param mode this parameter is ignored in this Display
         *  \return void
         *
         */
        void Enter(int mode = 0);

        /**
         *  \brief Update method for ExitDisplay
         *
         *  When called signals that the program should quit.
         *  \return void
         *
         */
        void Update();
        /**
         *  \brief Draw method for ExitDisplay
         *
         *  Empty method because this Display has nothing to draw
         *  \param renderer this parameter can be ignored
         *  \return void
         *
         */
        void Draw(SDL_Renderer* renderer = nullptr) const;

    protected:

    private:
        bool*   m_running;
};

#endif // EXITDISPLAY_H
