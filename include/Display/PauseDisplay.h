#ifndef PAUSEDISPLAY_H
#define PAUSEDISPLAY_H

/**
 *  \file PauseDisplay.h
 *
 *  Defines class PauseDisplay which represents the Display that contains
 *  pause display that a user can access by pausing the game
 *
 */

#include "Display/Display.h"
#include <SDL2/SDL.h>
#include <vector>

/** \class PauseDisplay
 *
 * \brief Class which represents the Display that shows the pause screen and its
 *        options
 * \details Class PauseDisplay represents the pause display that appears when
 *          the user pauses the GameDisplay. Draws a menu that is interactive.
 *          User can navigate through its options and run the one that is
 *          selected with the keyboard.
 *
 */
class PauseDisplay : public Display
{
    public:
        /**
         *  \brief Constructor for PauseDisplay
         *
         *  Makes the PauseDisplay with the given parameters
         *  \param renderer represents the SDL_Renderer on which the Display
         *         will be drawn on.
         *  \param window_width width of the program's window in pixels
         *  \param window_height height of the program's window in pixels
         *  \param previous_display pointer to Display that will be used as a
         *         background for drawing or it can be ignored
         *
         */
        PauseDisplay(SDL_Renderer* renderer,
                     unsigned int window_width,
                     unsigned int window_height,
                     Display* previous_display = nullptr);
        /**
         *  \brief Destructor for PauseDisplay
         *
         *  Destroys all textures that were used for displaying pause menu
         *  options
         *
         */
        ~PauseDisplay();
        PauseDisplay(const PauseDisplay& other) = delete; /**< \brief Default copy constructor is disabled */
        PauseDisplay& operator=(const PauseDisplay&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Init method for PauseDisplay
         *
         *  Resets certain values for pause menus.
         *  \return void
         *
         */
        void Init();
        /**
         *  \brief Enter method for PauseDisplay
         *
         *  Resets certain values for pause menus.
         *  \param mode this parameter can be ignored for this Display
         *  \return void
         *
         */
        void Enter(int mode = 0);
        /**
         *  \brief Leave method for PauseDisplay
         *
         *  Empty method since the PauseDisplay cannot make another Display
         *  \return void
         *
         */
        void Leave();
        /**
         *  \brief Destroy method for PauseDisplay
         *
         *  Destroys the textures used for displaying pause menu options.
         *  Checks whether option for quiting the game was selected and returns
         *  0 for signaling the game should end. Otherwise the game should
         *  continue and return 1.
         *  \return returns 0 option quit was selected, else returns 1 if the
         *          game should continue
         *
         */
        int Destroy();

        /**
         *  \brief Update method for PauseDisplay
         *
         *  Reads user's input and runs appropriate action which can be either
         *  navigating the pause menu or running the selected pause menu option.
         *  \return void
         *
         */
        void Update();
        /**
         *  \brief Draw method for PauseDisplay
         *
         *  Draws the pause menu options as well as arrow that points to the
         *  currently selected option.
         *  \return void
         *
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        SDL_Renderer*               m_renderer;
        std::vector<SDL_Texture*>   m_textures;
        std::vector<SDL_Rect>       m_textures_draw_src;
        std::vector<SDL_Rect>       m_textures_draw_dest;
        SDL_Texture*                m_arrow_texture;
        int                         m_arrow_height;
        int                         m_arrow_width;
        int                         m_arrow;
        bool                        m_button_pressed_down;
        bool                        m_button_pressed_up;
        bool                        m_button_pressed_enter;
        unsigned int                m_window_width;
        unsigned int                m_window_height;
        bool                        m_quit;
        Display*                    m_previous_display;

};

#endif // PAUSEDISPLAY_H
