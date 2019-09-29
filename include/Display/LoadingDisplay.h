#ifndef LOADINGDISPLAY_H
#define LOADINGDISPLAY_H

/**
 *  \file LoadingDisplay.h
 *
 *  Defines class LoadingDisplay which represents the Display that is seen
 *  between levels when the game is loading
 *
 */

#include "Display/Display.h"
#include "System/FreeTimer.h"
#include <SDL2/SDL.h>
#include <vector>

/** \class LoadingDisplay
 *
 * \brief Class which represents the Display that is seen between levels the
 *        the game is loading
 * \details Class LoadingDisplay only contains simple texture that represents
 *          the text which tells on what level the player currently is or in
 *          special cases the game over of game completed messages. This class
 *          is in charge of making GameDisplay object with the proper parameters
 *          one of which is the number of the current level.
 *
 */
class LoadingDisplay : public Display
{
    public:
        /**
         *  \brief Constructor for LoadingDisplay
         *
         *  Makes the LoadingDisplay with the given parameters
         *  \param texture pointer to SDL_Texture from which the various game
         *         assets will be drawn and will be passed on to GameDisplay
         *  \param renderer represents the SDL_Renderer on which the Display
         *         will be drawn on.
         *  \param window_width width of the program's window in pixels
         *  \param window_height height of the program's window in pixels
         *  \param players_number number of players that will be in the game
         *  \param max_level number of levels the game has
         *
         */
        LoadingDisplay(SDL_Texture* texture,
                       SDL_Renderer* renderer,
                       unsigned int window_width,
                       unsigned int window_height,
                       unsigned int players_number,
                       unsigned int max_level);
        /**
         *  \brief Destructor for WelcomeDisplay
         *
         *  Destroys all textures that were used for displaying loading message
         *
         */
        ~LoadingDisplay();
        LoadingDisplay(const LoadingDisplay& other) = delete; /**< \brief Default copy constructor is disabled */
        LoadingDisplay& operator=(const LoadingDisplay&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Init method for LoadingDisplay
         *
         *  Play the appropriate music for LoadingDisplay
         *  \return void
         *
         */
        void Init();
        /**
         *  \brief Enter method for LoadingDisplay
         *
         *  Play the appropriate music for LoadingDisplay and creates the
         *  texture for displaying correct text message
         *  \param mode represents the number of the level that should be loaded
         *         or 0 if the game should be over
         *  \return void
         *
         */
        void Enter(int mode);
        /**
         *  \brief Leave method for LoadingDisplay
         *
         *  Stops the music and destroys the textures which represent text
         *  message
         *  \return void
         *
         */
        void Leave();
        /**
         *  \brief Destroy method for LoadingDisplay
         *
         *  Destroys the music and textures.
         *  \return returns 0 on success
         *
         */
        int Destroy();

        /**
         *  \brief Update method for LoadingDisplay
         *
         *  Makes new GameDisplay if needed. Checks to see if the music finished
         *  and modifies its own state so that ShouldLeaveToPrevious() or
         *  ShouldLeaveToPrevious() return true on next call.
         *  \return void
         *
         */
        void Update();
        /**
         *  \brief Draw method for LoadingDisplay
         *
         *  Draws the text message
         *  \return void
         *
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

        /**
         *  \brief Make new texture of the given text
         *
         *  Makes a texture that is the image of the text given by the string
         *  parameter
         *  \param text std::string from which the texture will be made
         *  \return void
         *
         */
        void MakeTexture(std::string text);
        /**
         *  \brief Destroys the textures previously made
         *
         *  Destroys all the textures (if any) that this object keeps track off
         *  \return void
         *
         */
        void DestroyTextures();

    private:
        SDL_Texture*                m_texture;
        SDL_Renderer*               m_renderer;
        std::vector<SDL_Texture*>   m_textures;
        std::vector<SDL_Rect>       m_textures_draw_src;
        std::vector<SDL_Rect>       m_textures_draw_dest;
        unsigned int                m_window_width;
        unsigned int                m_window_height;
        unsigned int                m_players_number;
        unsigned int                m_current_level;
        const unsigned int          m_max_level;
        FreeTimer                   m_timer;
        bool                        m_game_over;
        Mix_Music*                  m_music;
        unsigned int                m_music_wait;

};

#endif // LOADINGDISPLAY_H
