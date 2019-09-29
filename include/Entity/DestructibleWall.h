#ifndef DESTRUCTIBLEWALL_H
#define DESTRUCTIBLEWALL_H

/**
 *  \file DestructibleWall.h
 *
 *  Defines class DestructibleWall which represents MapObject which is of type
 *  MapObject::DESTRUCTIBLE_WALL
 *
 */

#include "Entity/MapObject.h"

/** \class DestructibleWall
 *  \brief class which represents an MapObject which is a destructible wall.
 *  \details This class inherits class MapObject and adds functionalities for
 *           keeping track of damage done to a wall.
 */
class DestructibleWall : public MapObject
{
    public:
        /**
         *  \brief Constructor for DestructibleWall.
         *
         *  Makes an object of class DestructibleWall according to given
         *  parameters.
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param kind represents kind of texture that will be used for Draw()
         */
        DestructibleWall(SDL_Texture *texture, unsigned int kind);
        /**
         *  \brief Destructor for DestructibleWall.
         *
         *  Basic destructor for DestructibleWall.
         */
        virtual ~DestructibleWall() { };
        DestructibleWall(const DestructibleWall& other) = delete; /**< \brief Default copy constructor is disabled */
        DestructibleWall& operator=(const DestructibleWall&) = delete; /**< \brief Default operator = is disabled */
        /**
         *  \brief Tells if the wall is destroyed
         *
         *  If the integrity of wall is at 0 the it returns true which means
         *  that this object should be deleted.
         *  \return true if the wall should be destroyed
         */
        bool IsDestroyed() const;
        /**
         *  \brief Decreases the integrity of the wall according to damage taken
         *
         *  Given parameter represents the damage in percentages to the wall
         *  that it should take. Percentages given represents a portion of
         *  maximum integrity not current.
         *  \return void
         */
        void DecreaseIntegrity(int value);
        /**
         *  \brief Draws a DestructibleWall tile on given SDL_Renderer.
         *
         *  Draws a tile on the map according to it's coordinates.
         *  \param renderer represents SDL_Renderer on which a tile will be
         *         drawn on
         *  \param DestR location and size of renderer where should texture be
         *         drawn
         *
         *  \return void
         */
        virtual void Draw(SDL_Renderer* renderer, const SDL_Rect *DestR);

    protected:

    private:
        int                 m_integrity;
        static const int    S_MAX_INTEGRITY = 100; /**< number represents percentage */

        inline unsigned int min2(unsigned int a, unsigned int b)
        {
            return a*(a<b) + b*(a>=b);
        }

};

#endif // DESTRUCTIBLEWALL_H
