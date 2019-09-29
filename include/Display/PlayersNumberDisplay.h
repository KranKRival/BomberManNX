#ifndef PLAYERSNUMBERDISPLAY_H
#define PLAYERSNUMBERDISPLAY_H

/**
 *  \file PlayersNumberDisplay.h
 *
 *  Defines class PlayersNumberDisplay which represents the Display that
 *  gives the options for choosing number of players.
 *
 */

#include "Display/Display.h"
#include <vector>

/** \class PlayersNumberDisplay
 *
 * \brief Class which represents the Display lets the user pick number of
 *        players
 * \details Class PlayersNumberDisplay draws a menu that is interactive. User
 *          can navigate through its options and run the one that is selected
 *          with the keyboard.
 *
 */
class PlayersNumberDisplay : public Display
{
    public:
        /**
         *  \brief Constructor for PlayersNumberDisplay
         *
         *  Makes the PlayersNumberDisplay with the given parameters
         *  \param renderer represents the SDL_Renderer on which the Display
         *         will be drawn on.
         *  \param window_width width of the program's window in pixels
         *  \param window_height height of the program's window in pixels
         *
         */
        PlayersNumberDisplay(SDL_Renderer* renderer,
                             unsigned int window_width,
                             unsigned int window_height);
        /**
         *  \brief Destructor for PlayersNumberDisplay
         *
         *  Destroys all textures that were used for displaying menu options
         *
         */
        ~PlayersNumberDisplay();
        PlayersNumberDisplay(const PlayersNumberDisplay& other) = delete; /**< \brief Default copy constructor is disabled */
        PlayersNumberDisplay& operator=(const PlayersNumberDisplay&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Init method for PlayersNumberDisplay
         *
         *  Resets certain values for menus
         *  \return void
         *
         */
        void Init();
        /**
         *  \brief Enter method for PlayersNumberDisplay
         *
         *  Resets certain values for menus
         *  \param mode this parameter can be ignored for this Display
         *  \return void
         *
         */
        void Enter(int mode = 0);
        /**
         *  \brief Leave method for PlayersNumberDisplay
         *
         *  This menu does not have any submenus so this method is empty
         *  \return void
         *
         */
        void Leave();
        /**
         *  \brief Destroy method for PlayersNumberDisplay
         *
         *  Destroys the textures used for displaying options and returns
         *  number of players the user selected
         *  \return returns number of players user selected
         *
         */
        int Destroy();

        /**
         *  \brief Update method for PlayersNumberDisplay
         *
         *  Reads user's input and runs appropriate action which can be either
         *  navigating the menu or running the selected menu option.
         *  \return void
         *
         */
        void Update();
        /**
         *  \brief Draw method for PlayersNumberDisplay
         *
         *  Draws the menu options as well as arrow that points to the currently
         *  selected option.
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
        unsigned int                m_players_selected;
};

#endif // PLAYERSNUMBERDISPLAY_H
