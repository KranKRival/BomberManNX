#ifndef DISPLAYELEMENT_H
#define DISPLAYELEMENT_H

/**
 *  \file DisplayElement.h
 *
 *  Defines abstract class DisplayElement which is basis for a single
 *  displayable element of GameDisplay.
 *
 */

#include <SDL2/SDL.h>
//#include "Utility/Relay.h"

/** \class DisplayElement
 *
 * \brief Abstract class which represents a single displayable element
 *        of GameDisplay
 * \details Defines basic behavior for every displayable element in GameDisplay.
 *          Includes methods Update() and Draw() which every display element
 *          must redefine. This class should be inherited by every manager
 *          class.
 *
 */
class DisplayElement
{
    public:
        /**
         *  \brief Constructor for DisplayElement
         *
         *  Class DisplayElement is abstract. Constructor is used for
         *  initializing base elements of every class that inherits
         *  DisplayElement.
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *
         */
        DisplayElement(SDL_Texture* texture);
        /**
         *  \brief Destructor for DisplayElement
         *
         *  Default destructor for DisplayElement
         *
         */
        virtual ~DisplayElement() = 0;
        DisplayElement(const DisplayElement& other) = delete; /**< \brief Default copy constructor is disabled */
        DisplayElement& operator=(const DisplayElement&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Updates the DisplayElement
         *
         *  Abstract method. This method should be redefined so that a
         *  DisplayElement acts according to user input or makes changes that
         *  need to be done periodically, whatever the DisplayElement needs.
         *
         *  \return void
         */
        virtual void Update() = 0;
        /**
         *  \brief Draws the DisplayElement
         *
         *  Abstract method. This method should be redefined so that the
         *  DisplayElement draws all its elements.
         *  \param renderer represents the SDL_Renderer on which the object
         *         will draw its elements.
         *
         *  \return void
         */
        virtual void Draw(SDL_Renderer* renderer) const = 0;

    protected:
        SDL_Texture*    m_texture;
        //Relay*          m_relay;

    private:
};

#endif // DISPLAYELEMENT_H
