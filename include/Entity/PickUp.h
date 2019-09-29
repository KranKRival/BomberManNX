#ifndef PICKUP_H
#define PICKUP_H

/**
 *  \file PickUp.h
 *
 *  Defines class PickUp which represents one pickup.
 *
 */

#include <SDL2/SDL.h>

/** \class PickUp
 *  \brief Class which represents one pickup
 *  \details This class contains all properties of a pickup like it's
 *           coordinates on a map, it's size, type of pickup and value for that
 *           type. Also contains a method Draw() which draws it on a proper
 *           place on the map.
 */
class PickUp
{
    public:
        /**
         * \brief Enum for representing different types of pickups
         */
        enum PickUpType
        {
            EXIT, /**< special pickup that makes the player instantly finish the level */
            SPEED, /**< increases the movement of the player */
            BOMB, /**< increases the number of bomb the player can place at once */
            DAMAGE, /**< increases the damage and range of the bombs */
            LIFE, /**< increases the number of lives of the player  */
            SPEED_DECREASE, /**< opposite of SPEED, decreases the movement of the player */
            BOMB_DECREASE, /**< opposite of BOMB, decreases the number of bomb the player can place at once */
            DAMAGE_DECREASE /**< opposite of DAMAGE, decreases the damage and range of the bombs */
        };

        /**
         *  \brief Constructor for PickUp
         *
         *  Makes an object of class PickUp according to given parameters
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param type type of the PickUp that will be created
         *  \param value numerical value of that the pickup holds and will give
         *         to player when it is picked up
         *  \param x coordinate of the PickUp on the map
         *  \param y coordinate of the PickUp on the map
         *  \param draw_size drawing size of the pickup
         *
         */
        PickUp(SDL_Texture* texture,
               PickUpType type,
               int value,
               unsigned int x,
               unsigned int y,
               unsigned int draw_size);

        PickUpType GetType() const { return m_type; } /**< \brief Gives the type of the PickUp */
        int GetValue() const { return m_value; } /**< \brief Gives the value of the PickUp */
        unsigned int GetX() const { return m_x; } /**< \brief Gives the x coordinate of the PickUp */
        unsigned int GetY() const { return m_y; } /**< \brief Gives the y coordinate of the PickUp */
        unsigned int GetSize() const { return m_draw_size; } /**< \brief Gives the drawing size of the PickUp */

        /**
         *  \brief Tells if the PickUp has already been used
         *
         *  Returns true if the PickUp has already been used. Otherwise returns
         *  false. If it was used that the object of PickUp can be destroyed as
         *  it no longer has any purpose of being drawn on the map.
         *
         *  \return true if the PickUp has been used, else false.
         */
        bool IsUsed() const;
        /**
         *  \brief Marks the pickup as used
         *
         *  Marks the pickup as used so that the next call of IsUsed() returns
         *  true.
         *
         *  \return void
         */
        void Use();
        /**
         *  \brief Draws the pickup on given SDL_Renderer
         *
         *  Draws the pickup on the map according to it's coordinates.
         *  \param renderer represents the SDL_Renderer on which the pickup
         *         will be drawn on.
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        SDL_Texture*    m_texture;
        PickUpType      m_type;
        int             m_value;
        unsigned int    m_x;
        unsigned int    m_y;
        unsigned int    m_draw_size;
        bool            m_used;

};

#endif // PICKUP_H
