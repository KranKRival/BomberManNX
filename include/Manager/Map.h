#ifndef MAP_H
#define MAP_H

/**
 *  \file Map.h
 *
 *  Defines class Map which represents one map.
 *
 */

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Display/DisplayElement.h"
#include "Utility/Relay.h"
#include "Entity/MapObject.h"

/** \class Map
 *  \brief Class which represents one level of the game.
 *  \details This class keeps the current layout of the map in the game. It can
 *           make the layout using given text file, it can draw it on the given
 *           renderer as well make changes to itself by destroying wall that are
 *           specified as destructible.
 */
class Map : public DisplayElement
{
    public:
        /**
         *  \brief Constructor for Map
         *
         *  Makes an object of class Map according to given parameters
         *  \param path_to_file string which represent relative path to .txt
         *         map's properties needed for making a layout, such as height,
         *         width and layout of MapObjects
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param tile_size pixel size of one tile which will be used for
         *         method Draw()
         *  \param relay pointer to the relay object which is used to
         *         communicate with other game objects
         */
        Map(std::string path_to_file, SDL_Texture* texture, unsigned int tile_size, Relay* relay);
        /**
         *  \brief Destructor for Map
         *
         *  Destroys all MapObjects on the map before deleting itself.
         */
        ~Map();
        Map(const Map& other) = delete; /**< \brief Default copy constructor is disabled */
        Map& operator=(const Map&) = delete; /**< \brief Default operator = is disabled */

        unsigned int GetHeight() const { return m_height; } /**< \brief Gives height of map in tiles */
        unsigned int GetWidth() const { return m_width; } /**< \brief Gives width of map in tiles */
        unsigned int GetTileSize() const { return m_tile_size; } /**< \brief Gives size of a tile in pixels */

        /**
         *  \brief Tells if the tile at given coordinates is walkable on
         *
         *  Specifically it checks if the MapObject on given coordinates is of
         *  type MapObject::EMPTY and return true if it is.
         *  \param i row coordinate of the map
         *  \param j column coordinate of the map
         *  \return true if the tile at the given coordinates is empty
         */
        bool Walkable(unsigned int i,unsigned int j) const;
        /**
         *  \brief Draw the map's current layout on the given renderer
         *
         *  Calls MapObject::Draw() methods for all the MapObject in it's layout
         *  and draws them on the given renderer.
         *  \param renderer represents the SDL_Renderer on which the map will be
         *         drawn on.
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer) const;
        /**
         *  \brief Destroys wall on given coordinates
         *
         *  Checks if the wall on the given coordinates id of type
         *  MapObject::DESTRUCTABLE_WALL and swaps it with object of type
         *  MapObject::EMPTY
         *  \param i row coordinate of the map
         *  \param j column coordinate of the map
         *  \param damage value in percent that the bomb should do to a wall
         *
         *  \return void
         */
        void DestroyWall(unsigned int i, unsigned int j, unsigned int damage);
        /**
         *  \brief Checks the type of MapObject on given coordinates
         *
         *  Checks the value of type MapObject::Tile on the given coordinates
         *  and returns the appropriate tile id int the form of MapObject::Tile
         *  \param i row coordinate of the map
         *  \param j column coordinate of the map
         *
         *  \return MapObject::Tile which represents the type of object
         */
        MapObject::Tile GetTileType(unsigned int i, unsigned int j) const;
        /**
         *  \brief Update method for Map
         *
         *  Empty method since there are no periodical changes on the map.
         *
         *  \return void
         */
        void Update() {}

    protected:

        /**
         *  \brief Places PickUp::EXIT on the given map tile
         *
         *  \param i row coordinate of the map
         *  \param j row coordinate of the map
         *  \return void
         *
         */
        void PlaceExit(unsigned int i, unsigned int j);
        /**
         *  \brief Calculates chance of PickUp appearing and places it on the
         *         map
         *
         *  \param i row coordinate of the map
         *  \param j row coordinate of the map
         *  \return void
         *
         */
         void TryPlacePickUp(unsigned int i, unsigned int j);

    private:
        unsigned int                            m_height;
        unsigned int                            m_width;
        std::vector<std::vector<MapObject*>>    m_layout;
        const int                               m_tile_size;
        Relay*                                  m_relay;
        unsigned int                            m_wall_count;
};

#endif // MAP_H
