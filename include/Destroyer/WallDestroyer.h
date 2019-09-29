#ifndef WALLDESTROYER_H
#define WALLDESTROYER_H

/**
 *  \file WallDestroyer.h
 *
 *  Defines class WallDestroyer which is used to calculate the effects of bomb
 *  explosions and makes changes to the map.
 */

#include "Manager/Map.h"

/** \class WallDestroyer
 *  \brief class for destroying walls on the map
 *  \details This class is used to calculate the effects of bomb explosions and
 *           makes changes to the map in the game.
 *           Contains an algorithm for traversing the map and making required
 *           changes.
 */
class WallDestroyer
{
    public:
        /**
         *  \brief Constructor for WallDestroyer
         *
         *  Makes an object of class WallDestroyer according to given attributes
         *  \param level pointer to object Map to which it will make changes
         *  \param start_x x coordinate of explosion
         *  \param start_y y coordinate of explosion
         *  \param tile_size pixel size of one tile on the map
         *  \param intensity real value of explosion's size and effect it will
         *         make (1.0 is radius of one tile size of the map)
         *  \param damage value in percent that the bomb will do to a wall
         */
        WallDestroyer(Map* level,
                      unsigned int start_x,
                      unsigned int start_y,
                      unsigned int tile_size,
                      double intensity,
                      unsigned int damage);

    protected:

        /**
         *  \brief Spreads the explosion to given tile of the map
         *
         *  Calculates whether the explosion will reach the adjacent tiles of
         *  the given tile in the given direction
         *  \param row id of row from which the explosion will spread
         *  \param col id of column from which the explosion will spread
         *  \param direction_row vertical direction of explosion (down=1, up=-1)
         *  \param direction_col horizontal direction of explosion (right=1,
         *         left=-1)
         *  \return void
         */
        void Spread(int row, int col, int direction_row, int direction_col) const;
        /**
         *  \brief Calculates the damage of explosion on given tile
         *
         *  Calculates the damage the explosion should do to the given tile and
         *  applies the changes to the tile. Should only be called on MapObject
         *  of type MapObject::DESTRUCTIBLE_WALL
         *  \param row id of row for which the damage will be calculated
         *  \param col id of column for which the damage will be calculated
         *  \return void
         */
        void Destroy(int row, int col) const;
        /**
         *  \brief Calculates the distance to center of given tile from the
         *         point of origin of explosion
         *
         *  Calculates the distance from the center of the tile given by the
         *  parameters to the point of origin of explosion.
         *  \param row id of row for which the distance will be calculated
         *  \param col id of column for which the distance will be calculated
         *  \return void
         */
        double DistanceToCenter(int row, int col) const;
        /**
         *  \brief Return squared value of given integer value
         *
         *  Squares the given integer. Multiplies it by itself.
         *  \param x number which will be squared
         *  \return values that is squared
         */
        int Square(int x) const { return x*x; }
        /**
         *  \brief Checks whether the explosion should spread to the given tile
         *         and if it does then spreads it.
         *
         *  First it determines whether the explosion reaches the given tile and
         *  then based on the type of the tile calls either Spread() or
         *  Destroy() with the same parameters it received.
         *  \param new_row id of row for which the conditions will be calculated
         *  \param new_col id of column for which the conditions will be
         *         calculated
         *  \param direction_row vertical direction of explosion (down=1, up=-1)
         *  \param direction_col horizontal direction of explosion (right=1,
         *         left=-1)
         *  \return void
         */
        void CheckAndCall(int new_row, int new_col, int direction_row, int direction_col) const;

    private:
        Map*            m_level;
        unsigned int    m_start_x;
        unsigned int    m_start_y;
        unsigned int    m_tile_size;
        double          m_intensity;
        unsigned int    m_damage;

};

#endif // WALLDESTROYER_H
