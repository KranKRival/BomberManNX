#ifndef MAPOBJECT_H
#define MAPOBJECT_H

// in MapObject.h MapObject.cpp Map.h Map.cpp WallDestroyer.h WallDestroyer.cpp
//#define DEBUG_OUTPUT

/**
 *  \file MapObject.h
 *
 *  Defines class MapObject which represents a object on map.
 *
 */

#include <SDL2/SDL.h>

/** \class MapObject
 *  \brief class which represents an object on map
 *  \details This class contains all properties for describing a type of tile
 *           that can be placed on map like tile ID and texture on which should
 *           be placed. Also contains a method Draw() which draws it on a map.
 */
class MapObject
{
    public:
        /**
         * \brief Enum for representing different types of tiles on the map
         */
        enum Tile
        {
              EMPTY = 0, /**< Empty space on which the players and enemies can walk */
              DESTRUCTIBLE_WALL = 1, /**< Wall that can be destroyed with a bomb */
              INDESTRUCTIBLE_WALL = 2/**< Wall that cannot be destroyed by any means */
        };

        /**
         *  \brief Constructor for MapObject.
         *
         *  Makes an object of class MapObject according to given parameters.
         *  \param id describes type of tile on map
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param kind variation of texture for given type of Tile
         *
         */
        MapObject(Tile id, SDL_Texture *texture, unsigned int kind = 0);
         /**
         *  \brief Destructor for MapObject
         *
         *  Basic destructor for MapObject. Destructor is virtual so that the
         *  inherited classes from this can be destroyed via this destructor.
         */
        virtual ~MapObject() { };
        MapObject(const MapObject& other) = delete; /**< \brief Default copy constructor is disabled */
        MapObject& operator=(const MapObject&) = delete; /**< \brief Default operator = is disabled */
        /** \brief Returns id of the tile
         *
         * Value returned is of type MapObject::Tile and represents id of this
         * tile
         * \return value of type MapObject::Tile of this tile
         */
        Tile GetId() const { return m_id; }
        /**
         *  \brief Draws a tile on given SDL_Renderer.
         *
         *  Draws a tile on the map according to it's coordinates.
         *  \param renderer represents SDL_Renderer on which a tile will be
         *         drawn on
         *  \param DestR location and size of renderer where should texture be
         *         drawn
         *  \return void
         */
        virtual void Draw(SDL_Renderer* renderer, const SDL_Rect *DestR);

    protected:
        Tile            m_id;
        SDL_Texture*    m_texture;
        unsigned int    m_kind;

    private:
};

#endif // MAPOBJECT_H
