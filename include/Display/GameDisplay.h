#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

/**
 *  \file GameDisplay.h
 *
 *  Defines class GameDisplay which represents the main game Display that
 *  contains all objects of the game such as manager classes and Relay for
 *  communicating between classes
 *
 */

#include "Display/Display.h"
#include "Display/DisplayElement.h"
#include "Utility/Relay.h"
#include <vector>

/** \class GameDisplay
 *
 * \brief Class which represents the main game Display that contains all objects
 *        of the game.
 * \details Class GameDisplay represents the main game Display. It contains all
 *          objects of the game such as manager classes which are
 *          specializations of DisplayElement class as well as Relay which is
 *          used for communicating between managers as well as being used by
 *          GameDisplay for reading current state of the game. GameDisplay has
 *          Update() and Draw() methods which periodically update all managers
 *          and draw them. Also keeps track whether this Display should be
 *          changed because of a specific user input such as quiting or pausing
 *          the game.
 *
 */
 class GameDisplay : public Display
{
    public:
        /**
         *  \brief Constructor for GameDisplay
         *
         *  Makes the PauseDisplay with the given parameters
         *  \param texture pointer to SDL_Texture from which the various game
         *         assets will be drawn and will be passed on to DisplayElement
         *         objects within GameDisplay
         *  \param renderer represents the SDL_Renderer on which the Display as
         *         well as all of its DisplayElements will be drawn on.
         *  \param window_width width of the program's window in pixels
         *  \param window_height height of the program's window in pixels
         *  \param players_number number of players that will be in the game
         *  \param current_level number of the level that is currently being
         *         played
         *  \param number_of_screen_elements number of object of DisplayElement
         *         that the GameDisplay will have (used only for reserving the
         *         number elements and does not strictly limit the GameDisplay
         *         for using more or less)
         */
        GameDisplay(SDL_Texture* texture,
                    SDL_Renderer* renderer,
                    unsigned int window_width,
                    unsigned int window_height,
                    unsigned int players_number,
                    unsigned int current_level,
                    unsigned int number_of_screen_elements = 6);
        /**
         *  \brief Destructor for GameDisplay
         *
         *  Destroys all DisplayElements that it was keeping track of as well
         *  as Relay used for communicating between objects
         *
         */
        ~GameDisplay();
        GameDisplay(const GameDisplay& other) = delete; /**< \brief Default copy constructor is disabled */
        GameDisplay& operator=(const GameDisplay&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Adds a DisplayElement to the list of currently tracked
         *         elements
         *
         *  DisplayElement added to this list will be periodically updated in
         *  the Update() method. It will also be drawn by the Draw() method.
         * \param display_element pointer of the element that will be tracked
         * \return void
         *
         */
        void AddDisplayElement(DisplayElement* display_element);

        /**
         *  \brief Init method for GameDisplay
         *
         *  Initializes the manager classes and adds the to the list of
         *  DisplayElement object that are tracked. Initializes a Relay object
         *  and passes it to all manager classes that need it. Plays the game's
         *  music.
         *  \return void
         *
         */
        void Init();
        /**
         *  \brief Enter method for GameDisplay
         *
         *  Unpauses the SystemTimer which is the main game timer. Unpauses the
         *  music. Checks mode to see if it should immediately
         *  \param mode
         *  \return void
         *
         */
        void Enter(int mode = 0);
        /**
         *  \brief Leave method for GameDisplay
         *
         *  Pauses the SystemTimer which is the main game timer. Pauses the
         *  music.
         *  \return void
         *
         */
        void Leave();
        /**
         *  \brief Destroy method for GameDisplay
         *
         *  Destroys the textures used for displaying pause menu options. Also
         *  destroys music used in the game. Checks to see if the level was
         *  completed. If it was the it returns the number of the next level,
         *  otherwise if player failed or the game was quit return 0
         *  \return returns 0 if game was quit or player failed, else returns
         *          number of the next level
         *
         */
        int Destroy();

        /**
         *  \brief Update method for GameDisplay
         *
         *  Checks whether any conditions for ending the game are met and takes
         *  appropriate action (level completed, game over, etc.). If not the
         *  checks the user's input to see if any special key was pressed for
         *  quiting or pausing current display. If none of the previous
         *  conditions were met then it updates all of its DisplayElements.
         *  \return void
         *
         */
        void Update();
        /**
         *  \brief Draw method for GameDisplay
         *
         *  Draws all of GameDisplay's DisplayElement objects.
         *  \return void
         *
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        std::vector<DisplayElement*>    m_display_elements;
        Relay*                          m_relay;
        SDL_Texture*                    m_texture;
        SDL_Renderer*                   m_renderer;
        unsigned int                    m_window_width;
        unsigned int                    m_window_height;
        unsigned int                    m_players_number;
        unsigned int                    m_current_level;
        bool                            m_level_completed;
        bool                            m_play_music = true;
        Mix_Music*                      m_music;
};

#endif // GAMEDISPLAY_H
