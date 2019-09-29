#ifndef ENEMYTHREE_H
#define ENEMYTHREE_H

/**
 *  \file EnemyThree.h
 *
 *  Defines class EnemyThree which represents an type of enemy.
 *
 */

#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include "Utility/Relay.h"
#include "Utility/Timer.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"

/** \class EnemyThree
 *  \brief class which represents an type of enemy and inherits class Enemy
 *  \details This class contains all properties of an enemy like its
 *           coordinates on a map, its size, direction where its going
 *           as well as its speed. Also contains a method Draw()
 *           which draws him on a proper place on map and inherited methods
 *           like  EnemyMove() for moving around the map and Update() for
 *           refreshing its position.
 */

class EnemyThree : public Enemy
{
    public:
        /**
         *  \brief Constructor for EnemyThree.
         *
         *  Makes an object of class EnemyThree according to given parameters.
         *  \param tex pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param tile_size size of one tile on map
         *  \param val_x x coordinate of the enemy on the map
         *  \param val_y y coordinate of the enemy on the map
         *
         */
        EnemyThree(SDL_Texture* tex, unsigned int tile_size, unsigned int val_x = 1, unsigned int val_y = 1);

        /**
         *  \brief Draws the enemy on given SDL_Renderer.
         *
         *  Draws the enemy on the map according to its coordinates.
         *  \param renderer represents SDL_Renderer on which the enemy
         *  will be drawn on
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer);

        /**
         *  \brief Updates enemy's position on map.
         *
         *  Calculates where enemy should go with ChasePlayer() method
         *  and checks for collision with player and updates enemy's position
         *  on map accordingly and calls appropriate actions.
         *
         *  \param relay pointer to Relay object of the game
         *
         *  \return void
         */
        void Update(Relay *relay);

        /**
         *  \brief Calculate in what direction enemy should go.
         *
         *  Calculates in what direction enemy should go to chase player,
         *  checks with DirectionCheck() method if direction is available
         *  and sends enemy in that direction.
         *
         *  \param player pointer to Player object of the game
         *  \param relay pointer to Relay object of the game
         *
         *  \return void
         */
        void ChasePlayer(Player * player, Relay *relay);

        /**
         *  \brief Checks if given direction is available.
         *
         *  Calculates if given direction is available on map.
         *
         *  \param d direction that needs to be checked
         *  \param relay pointer to Relay object of the game
         *
         *  \return bool
         */
        bool DirectionCheck(Direction d, Relay *relay);
    protected:

    private:
        bool m_chase = false;
};

#endif // ENEMYTHREE_H
