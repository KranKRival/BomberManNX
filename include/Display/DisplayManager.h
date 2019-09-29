#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

/**
 *  \file DisplayManager.h
 *
 *  Defines class DisplayManager which contains the mechanics for controlling
 *  multiple displays in a single window.
 *
 */

#include "Display/Display.h"
#include <SDL2/SDL.h>
#include <stack>

/** \class DisplayManager
 *
 * \brief Class which contains mechanics for displaying and swapping between
 *        multiple Displays
 * \details DisplayManager keeps track of already opened Displays and can go
 *          back to any of them when necessary. Contains method for going back
 *          to previous display or moving to a new one. Methods Update() and
 *          Draw() call the appropriate methods of current Display.
 *
 */
class DisplayManager
{
    public:
        /**
         *  \brief Constructor for DisplayManager
         *
         *  Constructor is used for initializing base elements of DisplayManager
         *  as well as making special ExitDisplay for signaling when the program
         *  should end and the first proper Display, the WelcomeDisplay.
         *
         */
        DisplayManager(SDL_Texture* texture,
                       SDL_Renderer* renderer,
                       bool* running,
                       unsigned int window_width,
                       unsigned int window_height);
        /**
         *  \brief Destructor for DisplayManager
         *
         *  Deletes all remaining Display it keeps track of before deleting
         *  itself.
         *
         */
        ~DisplayManager();
        DisplayManager(const DisplayManager& other) = delete; /**< \brief Default copy constructor is disabled */
        DisplayManager& operator=(const DisplayManager&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Updates the DisplayManager
         *
         *  Checks whether the current Display says if it should swap it with
         *  another one, either previous one or a new one, and acts accordingly
         *  If the current Display should not be changed then it updates it by
         *  calling Display::Update() method of current Display.
         *
         *  \return void
         */
        void Update();
        /**
         *  \brief Draws the current Display
         *
         *  Calls the Display::Draw() method of the current Display with the
         *  given SDL_Renderer as parameter.
         *  \param renderer represents the SDL_Renderer on which the current
         *         Display will be drawn on.
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer);

    protected:

        /**
         *  \brief Swaps the current Display with the given one
         *
         *  Uses the Display given as parameter and makes it the current Display
         *  Previous Display is not discarded but is still being kept on in
         *  DisplayManager for when the program returns to it.
         *  \param display pointer to Display which the program should make
         *         current
         *  \return void
         *
         */
        void EnterDisplay(Display* display);
        /**
         *  \brief Destroys the current Display and goes back to the previous.
         *
         *  Destroys the Display that is marked as current and in its place puts
         *  the Display from which the program originally changed to that one
         *  \return void
         *
         */
        void LeaveDisplay();
        /**
         *  \brief Returns pointer to the current Display
         *
         *  Gives a pointer that is marked as current and under normal
         *  circumstances will be updated and drawn.
         *  \return pointer to the current Display
         *
         */
        Display* CurrentDisplay();

    private:
        std::stack<Display*> m_displays;
        SDL_Renderer*        m_renderer;

        unsigned int         m_window_width;
        unsigned int         m_window_height;
};

#endif // DISPLAYMANAGER_H
