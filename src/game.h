#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

//#define DEBUG_OUTPUT_GAME

/**
 *  \file Bomb.h
 *
 *  Defines class game which represents is the main class of the program.
 *
 */

#include "includes.h"
#include "System/KeyboardInput.h"
#include "Display/DisplayManager.h"

/** \class game
 *  \brief Class which represents the game
 *  \details This class all the basic methods of an SDL program.
 *           Also keeps track of all the objects in the game such as map,
 *           player, enemies, bombs, etc. and updates them periodically and
 *           draws them when needed.
 */
class game
{
    public:
        /**
         *  \brief Constructor for game
         *
         *  Makes an instance of the game
         */
        game();
        /** \brief Calls for initialization and enters the main loop of the game
         *
         *  First method to call. Initializes the game objects and then enters
         *  the main loop the game which reads keyboard input, updates game
         *  objects that need it and draws one that should be drawn.
         * \return -1 if an error occurred, otherwise returns 0
         *
         */
        int OnExecute();
        /** \brief Initializes main parts of the SDL library needed to run the
         *         game
         *
         *  Initializes window and renderer needed for SDL
         * \return false if there was an error initializing, otherwise true
         *
         */
        bool OnInit();
        /** \brief Loads textures and initializes main game objects
         *
         * Loads .bmp files that represents and makes textures. Also loads .txt
         * files and loads up level data. Then it initializes main objects of
         * the game, such as map, player, enemies, manager classes that keep t
         * track of the game and so on.
         * \return false if there was an error initializing, otherwise true
         *
         */
        bool LoadContent();
        /** \brief Reads input from the user and processes it.
         *
         * Read all input given by the user and processes it so that the object
         * that are affected by user input can act according to it in OnLoop()
         * \param Event SDL_Event* type object that keeps track of user input
         * \return void
         *
         */
        void OnEvent(SDL_Event* Event);
        /** \brief Calls update methods on object that need to be updated
         *         periodically
         *
         * Calls update method individually for each of the game object that
         * needs to be updated whether they need to act according to user input
         * or by some timer.
         * \return void
         *
         */
        void OnLoop();
        /** \brief Draws all game object that need to be drawn.
         *
         * Calls render method individually for each of the game object that
         * can and need to be draw so that the user has full output needed in
         * the game.
         * \return void
         *
         */
        void OnRender();
        /** \brief Cleans up game object, deletes object, destroys window
         *
         * Frees up memory that was taken by all object that remain at the end
         * of the game so that the program can be more easily closed.
         * \return void
         *
         */
        void Cleanup();

    protected:

    private:
        bool                Running;
        SDL_Window*         window;
        SDL_Renderer*       renderer;
        SDL_Event           Event;
        KeyboardInput*      keyboard_input;
        SDL_Texture*        texture;
        DisplayManager*     display_manager;

        unsigned int        window_width;
        unsigned int        window_height;

};
#endif // GAME_H_INCLUDED
