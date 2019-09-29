#ifndef WELCOMEDISPLAY_H
#define WELCOMEDISPLAY_H

/**
 *  \file WelcomeDisplay.h
 *
 *  Defines class WelcomeDisplay which represents the first Display that is seen
 *  by the user.
 *
 */

#include "Display/Display.h"
#include <SDL2/SDL.h>
#include <vector>

/** \class WelcomeDisplay
 *
 * \brief Class which represents the first Display that is seen by user
 * \details Class WelcomeDisplay only contains simple texture that represents
 *          the welcoming text to the user and wait for user input in order to
 *          go the the MainMenuDisplay
 *
 */
class WelcomeDisplay : public Display
{
    public:
        /**
         *  \brief Constructor for WelcomeDisplay
         *
         *  Makes the WelcomeDisplay with the given parameters
         *  \param texture pointer to SDL_Texture from which the various game
         *         assets will be drawn and will be passed on to GameDisplay
         *  \param renderer represents the SDL_Renderer on which the Display
         *         will be drawn on.
         *  \param window_width width of the program's window in pixels
         *  \param window_height height of the program's window in pixels
         *
         */
         WelcomeDisplay(SDL_Texture* texture,
                       SDL_Renderer* renderer,
                       unsigned int window_width,
                       unsigned int window_height);
        /**
         *  \brief Destructor for WelcomeDisplay
         *
         *  Destroys all textures that were used for displaying welcoming
         *  message
         *
         */
        ~WelcomeDisplay();
        WelcomeDisplay(const WelcomeDisplay& other) = delete; /**< \brief Default copy constructor is disabled */
        WelcomeDisplay& operator=(const WelcomeDisplay&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Enter method for WelcomeDisplay
         *
         *  When called it modifies its state so that ShouldLeaveToPrevious()
         *  returns true because returning to this Display means that the user
         *  wants to quit the program.
         *  \param mode this parameter is ignored in this Display
         *  \return void
         *
         */
        void Enter(int mode = 0);
        /**
         *  \brief Leave method for WelcomeDisplay
         *
         *  Calls Destroy method because the after this Display is left for
         *  another the welcoming text will never be needed again.
         *  \return void
         *
         */
        void Leave();
        /**
         *  \brief Destroy method for WelcomeDisplay
         *
         *  Destroys all textures it used for displaying welcoming message
         *  \return returns 0 on success
         *
         */
        int Destroy();

        /**
         *  \brief Update method for WelcomeDisplay
         *
         *  Checks user's input and acts accordingly
         *  \return void
         *
         */
        void Update();
        /**
         *  \brief Draw method for WelcomeDisplay
         *
         *  Draws the welcoming text
         *  \return void
         *
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        SDL_Texture*                m_texture;
        SDL_Renderer*               m_renderer;
        std::vector<SDL_Texture*>   m_textures;
        std::vector<SDL_Rect>       m_textures_draw_src;
        std::vector<SDL_Rect>       m_textures_draw_dest;

        bool                        m_pressed_next;
        bool                        m_pressed_previous;
        unsigned int                m_window_width;
        unsigned int                m_window_height;
};

#endif // WELCOMEDISPLAY_H
