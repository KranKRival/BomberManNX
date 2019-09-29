#ifndef MAINMENUDISPLAY_H
#define MAINMENUDISPLAY_H

/**
 *  \file MainMenuDisplay.h
 *
 *  Defines class MainMenuDisplay which represents the Display that contains
 *  main menus that a user can access
 *
 */

#include "Display/Display.h"
#include <vector>

/** \class MainMenuDisplay
 *
 * \brief Class which represents the Display that shows the main menu.
 * \details Class MainMenuDisplay draws a menu that is interactive. User can
 *          navigate through its options and run the one that is selected with
 *          the keyboard.
 *
 */
class MainMenuDisplay : public Display
{
    public:
        /**
         *  \brief Constructor for MainMenuDisplay
         *
         *  Makes the MainMenuDisplay with the given parameters
         *  \param texture pointer to SDL_Texture from which the various game
         *         assets will be drawn and will be passed on to GameDisplay
         *  \param renderer represents the SDL_Renderer on which the Display
         *         will be drawn on.
         *  \param window_width width of the program's window in pixels
         *  \param window_height height of the program's window in pixels
         *
         */
        MainMenuDisplay(SDL_Texture* texture,
                        SDL_Renderer* renderer,
                        unsigned int window_width,
                        unsigned int window_height);
        /**
         *  \brief Destructor for WelcomeDisplay
         *
         *  Destroys all textures that were used for displaying menu options
         *
         */
        ~MainMenuDisplay();
        MainMenuDisplay(const MainMenuDisplay& other) = delete; /**< \brief Default copy constructor is disabled */
        MainMenuDisplay& operator=(const MainMenuDisplay&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Init method for MainMenuDisplay
         *
         *  Play the appropriate music for MainMenuDisplay and resets certain
         *  values for menus.
         *  \return void
         *
         */
        void Init();
        /**
         *  \brief Enter method for MainMenuDisplay
         *
         *  Play the appropriate music for MainMenuDisplay and resets certain
         *  values for menus.
         *  \param mode this parameter can be ignored for this Display
         *  \return void
         *
         */
        void Enter(int mode = 0);
        /**
         *  \brief Leave method for MainMenuDisplay
         *
         *  Pauses the music.
         *  \return void
         *
         */
        void Leave();
        /**
         *  \brief Destroy method for MainMenuDisplay
         *
         *  Destroys the music and textures used for displaying options
         *  \return returns 0 on success
         *
         */
        int Destroy();

        /**
         *  \brief Update method for MainMenuDisplay
         *
         *  Reads user's input and runs appropriate action which can be either
         *  navigating the menu or running the selected menu option.
         *  \return void
         *
         */
        void Update();
        /**
         *  \brief Draw method for MainMenuDisplay
         *
         *  Draws the menu options as well as arrow that points to the currently
         *  selected option.
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
        SDL_Texture*                m_arrow_texture;
        int                         m_arrow_height;
        int                         m_arrow_width;
        int                         m_arrow;
        bool                        m_button_pressed_down;
        bool                        m_button_pressed_up;
        bool                        m_button_pressed_enter;
        unsigned int                m_window_width;
        unsigned int                m_window_height;
        unsigned int                m_players_number;
        Mix_Music*                  m_music;
        bool                        m_in_options;

};

#endif // MAINMENUDISPLAY_H
