#ifndef EXPLOSION_H
#define EXPLOSION_H

// in Explosion.h Explosion.cpp ExplosionManager.h ExplosionManager.cpp
//#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
#include<iostream>
#endif // DEBUG_OUTPUT

/**
 *  \file Explosion.h
 *
 *  Defines class Explosion which represents one explosion of the bomb.
 *
 */

#include <SDL2/SDL.h>
#include "Utility/Timer.h"

/** \class Explosion
 *  \brief Class which represents visual effect of one explosion of the bomb
 *  \details This class is used only for visual representation of the explosion
 *           and does not affect any of the game's other objects such as map,
             player or enemies.
             This class contains all properties of an explosion such as it's
 *           coordinates on the map, the duration of the explosion, intensity
 *           of the explosion. Also contains a method Draw() which draws it on a
 *           proper place on the map.
 */
class Explosion
{
    public:
        /**
         *  \brief Constructor for Explosion
         *
         *  Makes an object of class Explosion according to given
         *  parameters
         *  \param duration duration of the explosion in milliseconds
         *  \param x_center x coordinate of the center of explosion on the map
         *  \param y_center y coordinate of the center of explosion on the map
         *  \param intensity real value of explosion's visual size (1.0 is
         *         radius of one tile size of the map
         *  \param tile_size pixel size of one tile of the map (used for Draw())
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *
         */
        Explosion(unsigned int duration,
                  unsigned int x_center,
                  unsigned int y_center,
                  double intensity,
                  unsigned int tile_size,
                  SDL_Texture* texture);

        /**
         *  \brief Update function for class Explosion
         *
         *  Updates the values in class according to it's internal timer.
         *  Specifically, it checks the explosion's duration and updates it
         *  phase number which is used to draw the correct texture of the
         *  explosion in method Draw(). Sets the appropriate value so that the
         *  call of method Explode() returns true if the explosion has ended.
         *
         *  \return void
         */
        void Update();
        /**
         *  \brief Tells if the exploding animation has ended
         *
         *  Returns true if the explosion has gone through all the phases of
         *  drawing and should be deleted.
         *
         *  \return true if the explosion has ended, else false
         */
        bool IsExploding() const;
        /**
         *  \brief Draws the explosion on given SDL_Renderer
         *
         *  Draws the explosion on the map according to it's coordinates and
         *  size.
         *  \param renderer represents the SDL_Renderer on which the explosion
         *         will be drawn on.
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        Timer           m_timer;
        unsigned int    m_duration;
        bool            m_exploding;
        unsigned int    m_x_center;
        unsigned int    m_y_center;
        double          m_intensity;
        unsigned int    m_tile_size;
        SDL_Texture*    m_texture;
        unsigned int    m_phase_number;

        inline unsigned int min2(unsigned int a, unsigned int b)
        {
            return a*(a<b) + b*(a>=b);
        }

};

#endif // EXPLOSION_H
