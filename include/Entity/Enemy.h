#ifndef ENEMY_H
#define ENEMY_H

/**
 *  \file Enemy.h
 *
 *  Defines class Enemy which represents an enemy.
 *
 */

#include <SDL2/SDL.h>
#include "Utility/Timer.h"
#include "Entity/Player.h"

/** \class Enemy
 *  \brief Abstract class which represents an enemy.
 *  \details This class contains all properties of an enemy like its
 *           coordinates on a map, its size, direction where its going
 *           as well as its speed. Also contains a method Draw() which is
 *           abstract and draws Enemy on a proper place on map,
 *           method EnemyMove() for moving around the map and Update() for
 *           refreshing its position.
 */

class Enemy
{
    public:
        /**
         *  \brief Constructor for Enemy.
         *
         *  Makes an object of class Enemy according to given parameters.
         *  \param tex pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param tile_size size of one tile on map
         *  \param val_x x coordinate of the enemy on the map
         *  \param val_y y coordinate of the enemy on the map
         *
         */
        Enemy(SDL_Texture* tex, unsigned int tile_size, unsigned int val_x = 1, unsigned int val_y = 1);
        virtual ~Enemy();
        Enemy(const Enemy& other) = delete; /**< \brief Default copy constructor is disabled */
        Enemy& operator=(const Enemy&) = delete; /**< \brief Default operator = is disabled */

        unsigned int GetX() const;
        void SetX(unsigned int val);
        unsigned int GetY() const;
        void SetY(unsigned int val);

        unsigned int GetSizeW() const;
        unsigned int GetSizeH() const;

        unsigned int GetStatus() const;
        void SetStatus(int s);

        unsigned int GetDirection() const;
        void SetDirection(int d);

        unsigned int GetHealth() const;
        void SetHealth(int h);

        /**
        *  \brief Function that implements movement for enemy.
        *
        *  Updates the position of enemy on the map according to
        *  method Update().
        *
        *  \param relay pointer to Relay object of the game
        *
        *  \return void
        */
        void EnemyMove(Relay *relay);

        /**
         *  \brief Draws the enemy on given SDL_Renderer.
         *
         *  Draws the enemy on the map according to its coordinates.
         *
         *  \param renderer represents SDL_Renderer on which the enemy
         *  will be drawn on
         *
         *  \return void
         */
        virtual void Draw(SDL_Renderer* renderer) = 0;

        /**
         *  \brief Updates enemy's position on map.
         *
         *  Calculates where enemy should go and updates enemy's position
         *  on map accordingly and calls appropriate actions.
         *
         *  \param relay pointer to Relay object of the game
         *
         *  \return void
         */
        virtual void Update(Relay *relay);

         /**
         *  \brief Checks if enemy touched player.
         *
         *  Calculates if there was a collision between
         *  enemy and player.
         *
         *  \param player_x x coordinate of the player
         *  \param player_y y coordinate of the player
         *
         *  \return bool
         */
        bool Touch(unsigned int player_x, unsigned int player_y);

    protected:
        enum Direction
        {
              LEFT = 0,
              RIGHT = 1,
              UP = 2,
              DOWN = 3
        };
        Direction    m_direction;
        int          m_walk_len = 0;
        Timer        m_timer;
        unsigned int m_speed;
        unsigned int m_rotation_const;
        unsigned int m_status = 0;
        unsigned int m_health = 100; //percent
        unsigned int m_x;
        unsigned int m_y;
        unsigned int m_move_speed = 4;
        unsigned int m_enemy_size_w;
        unsigned int m_enemy_size_h;
        SDL_Texture* m_tex;
        unsigned int m_tile_size;
    private:

};

#endif // ENEMY_H
