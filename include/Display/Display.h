#ifndef DISPLAY_H
#define DISPLAY_H

/**
 *  \file Display.h
 *
 *  Defines abstract class Display which is basis for a single display or screen
 *  in the game
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "System/KeyboardInput.h"

/** \class Display
 *
 * \brief Abstract class which represents a single Display or screen in the game
 * \details Defines basic behavior for every Display in the game. Includes
 *          methods Update() and Draw() which every screen must define. Methods
 *          Init() Enter() Leave() Destroy() define behavior of a Display when
 *          it becomes active or inactive.
 *
 */
class Display
{
    public:
        /**
         *  \brief Constructor for Display
         *
         *  Class Display is abstract. Constructor is used for initializing
         *  base elements of every class that inherits Display
         *
         */
        Display();
        virtual ~Display() = 0; /**< \brief Default destructor */
        Display(const Display& other) = delete; /**< \brief Default copy constructor is disabled */
        Display& operator=(const Display&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Initializes elements of Display
         *
         *  Method that is automatically called by DisplayManager the first time
         *  the Display becomes active. Every class that inherits Display should
         *  redefine this method if it has elements that need to be initialized
         *  before they can be used.
         *
         *  \return void
         */
        virtual void Init();
        /**
         *  \brief Resets certain values of Display. Starts background elements.
         *
         *  Method that is automatically called by DisplayManager every time the
         *  Display becomes active. Every class that inherits Display should
         *  redefine this method if it has elements that need to be reset or
         *  or reinitialized when the Display comes back into use.
         *  \param mode represents id of mode the Display should run
         *
         *  \return void
         */
        virtual void Enter(int mode = 0);
        /**
         *  \brief Pauses the Display. Stops background elements.
         *
         *  Method that is automatically called by DisplayManager every time
         *  this Display is used to switch to the next Display (not counting
         *  going back). Every class that inherits Display should redefine this
         *  method if it has elements that need to are need disabled until
         *  Display becomes active again or are working in the background but
         *  are not used in other displays.
         *
         *  \return void
         */
        virtual void Leave();
        /**
         *  \brief Destroys the Display.
         *
         *  Method that is automatically called by DisplayManager the last time
         *  the Display is used. Destroys elements of Display and frees up the
         *  memory if it was using any. Every class that inherits Display should
         *  redefine this method if it has elements that need to freed or
         *  destroyed after the Display is no longer needed.
         *
         *  \return integer which represents mode the previous screen should
         *          run; default return value is 0
         */
        virtual int Destroy();

        /**
         *  \brief Updates the Display
         *
         *  Abstract method. This method should be redefined so that a Display
         *  acts according to user input or makes changes that need to be done
         *  periodically, whatever the Display needs. Also when the Display
         *  needs to be swapped with another either because of user input or
         *  some other reason it should change its internal state, specifically
         *  values m_leave_previous and m_leave_next so that methods
         *  ShouldLeaveToPrevious() or ShouldLeaveToNext() return true if the
         *  game should go the previous or next Display respectively. In the
         *  case of ShouldLeaveToNext() it should make an object of appropriate
         *  class that inherits Display and place its pointer into
         *  m_next_display so that the next call of method NextDisplay() returns
         *  pointer to it.
         *
         *  \return void
         */
        virtual void Update() = 0;
        /**
         *  \brief Draws the Display
         *
         *  Abstract method. This method should be redefined so that the Display
         *  draws all its elements.
         *  \param renderer represents the SDL_Renderer on which the Display
         *         will be drawn on.
         *
         *  \return void
         */
        virtual void Draw(SDL_Renderer* renderer) const = 0;

        /**
         *  \brief Tells if the game should return to previous Display
         *
         *  Used by DisplayManager to see if the Display is done and should be
         *  destroyed, after which the game will go back to previous Display.
         *
         *  \return true if the game should go to next Display, false otherwise
         */
        bool ShouldLeaveToPrevious() { return m_leave_previous; }
        /**
         *  \brief Tells if the game should go to next Display
         *
         *  Used by DisplayManager to see if the Display is done and the game
         *  should move to next Display which can be obtained with method
         *  NextDisplay().
         *
         *  \return true if the game should return to previous Display, false
         *          otherwise
         */
        bool ShouldLeaveToNext() { return m_leave_next; }
        /**
         *  \brief Returns pointer to Display the game should change to if going
         *         to next Display
         *
         *  Used by DisplayManager to see obtain the Display it should go to if
         *  ShouldLeaveToNext() returns true
         *
         *  \return pointer to Display of the Display the game should change to
         */
        Display* NextDisplay() { return m_next_display; }

    protected:
        bool            m_leave_previous; /**< tells if the game should go back to previous Display */
        bool            m_leave_next; /**< tells if the game should go to next Display */
        Display*        m_next_display; /**< pointer of next Display if the game should go to next Display */
        KeyboardInput*  m_keyboard_input; /**< pointer to KeyboardInput from which the user's input is read */

    private:

};

#endif // DISPLAY_H
