#ifndef DESTROYER_H
#define DESTROYER_H

/**
 *  \file Destroyer.h
 *
 *  Defines class EnemyDestroyer which is used to calculate the effects of
 *  Bomb's explosion on an Enemy or Player.
 *
 */

#include "Entity/Enemy.h"
#include "Entity/Player.h"

/** \class Destroyer
 *  \brief class for killing enemies and players
 *  \details This class is used to calculate the effects of Bomb's explosion on
 *           an Enemy or Player and decreases their health if necessary.
 */
class Destroyer
{
    public:

        /** \brief Calculates the effect of a Bomb on an Enemy
         *
         * According to given parameters which represent center point of bomb's
         * explosion and intensity determines whether it should damage the Enemy
         * \param enemy pointer to Enemy for which the effect is calculated
         * \param start_x x coordinate of explosion's point of origin
         * \param start_y y coordinate of explosion's point of origin
         * \param tile_size represents the size of one tile of the map in
         *        pixels
         * \param intensity real value which represents the intensity of the
         *        bomb's explosion
         * \return void
         *
         */
        static void DestroyEnemy(Enemy* enemy,
                                 unsigned int start_x,
                                 unsigned int start_y,
                                 unsigned int tile_size,
                                 double intensity);

        /** \brief Calculates the effect of a Bomb on a Player
         *
         * According to given parameters which represent center point of bomb's
         * explosion and intensity determines whether it should damage the
         * Player
         * \param player pointer to Player for which the effect is calculated
         * \param start_x x coordinate of explosion's point of origin
         * \param start_y y coordinate of explosion's point of origin
         * \param tile_size represents the size of one tile of the map in
         *        pixels
         * \param intensity real value which represents the intensity of the
         *        bomb's explosion
         * \return void
         *
         */
        static void DestroyPlayer(Player* player,
                                  unsigned int start_x,
                                  unsigned int start_y,
                                  unsigned int tile_size,
                                  double intensity);

    protected:

        /**
         *  \brief Return squared value of given integer value
         *
         *  Squares the given integer. Multiplies it by itself.
         *  \param x number which will be squared
         *  \return values that is squared
         */
        static int Square(int x) { return x*x; }

    private:

        Destroyer();
};

#endif // ENEMYDESTROYER_H
