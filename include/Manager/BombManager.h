#ifndef BOMBMANAGER_H
#define BOMBMANAGER_H

/**
 *  \file BombManager.h
 *
 *  Defines class BombManger which is used for keeping track on all bombs in
 *  the game
 *
 */

#include <list>
#include <SDL2/SDL_mixer.h>
#include "Display/DisplayElement.h"
#include "Entity/Bomb.h"
#include "Utility/Relay.h"

/** \class BombManager
 *  \brief Class which is used for keeping track of all bombs in the game.
 *  \details This class contains the list of all bombs which are placed by the
 *           player. Has appropriate methods for adding bombs and drawing them.
 *           Also has an update method which calls the appropriate update method
 *           for all bombs. Also keeps reference to Relay which it uses to
 *           communicate to other game objects.
 */
class BombManager : public DisplayElement
{
    public:
        /**
         *  \brief Constructor for BombManager
         *
         *  Makes an object of class BombManager according to given
         *  parameters
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param tile_size represents the size of one tile of the map in
         *         pixels (which is required for proper implementation of method
         *         Draw())
         *  \param relay pointer to the relay object which is used to
         *         communicate with other game objects
         */
        BombManager(SDL_Texture* texture, unsigned int tile_size, Relay* relay);
        /**
         *  \brief Destructor for BombManager
         *
         *  Destroys all bombs it keeps track of before deleting itself.
         */
        ~BombManager();
        BombManager(const BombManager& other) = delete; /**< \brief Default copy constructor is disabled */
        BombManager& operator=(const BombManager&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Adds new Bomb to the list of bombs.
         *
         *  Adds new Bomb to the list of bombs so that it will be periodically
         *  updated and destroyed when it's fuse runs out. Will also make new
         *  Explosion and possibly destroy walls on the map or enemies or player
         *
         *  \param bomb pointer to object Bomb which will be added to the list
         *  \return void
         */
        void AddBomb(Bomb *bomb);
        /**
         *  \brief Makes new Bomb according to given parameters and adds it to
         *         the list of bombs.
         *
         *  Uses the given parameters and makes a new Bomb object and adds it to
         *  the list of bombs same as method AddBomb(Bomb* bomb). The bomb will
         *  be periodically updated and destroyed when it's fuse runs out.
         *
         *  \param fuse_duration duration of bombs fuse in millisecond
         *  \param x top left x coordinate of the bomb on the map
         *  \param y top left y coordinate of the bomb on the map
         *  \param player_id id of the player that placed the bomb
         *  \param intensity real value which represents the intensity of the
         *         bombs explosion after it's fuses burns out
         *  \param damage value in percents that the bomb will do to a wall
         *  \return void
         */
        void MakeBomb(unsigned int fuse_duration,
                      unsigned int x,
                      unsigned int y,
                      unsigned int player_id,
                      double intensity = 1.0,
                      unsigned int damage = 25);
        /**
         *  \brief Update function for class BombManager
         *
         *  Calls the update methods of all the bombs it keeps track of.
         *
         *  \return void
         */
        void Update();
        /**
         *  \brief Draw all the bombs it keeps track of on given SLD_Renderer
         *
         *  Calls Bomb::Draw() method for all the bombs it keeps track of with
         *  the given SLD_Renderer as parameter so it will draw them on that
         *  same renderer.
         *  \param renderer represents the SDL_Renderer on which the bombs
         *         will be drawn on.
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        std::list<Bomb*>        m_bombs;
        unsigned int            m_bomb_size;
        unsigned int            m_tile_size;
        Relay*                  m_relay;
        Mix_Chunk*              m_bomb_sound_effect;
};

#endif // BOMBMANAGER_H
