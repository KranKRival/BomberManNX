#ifndef PICKUPMANAGER_H
#define PICKUPMANAGER_H

/**
 *  \file PickUpManager.h
 *
 *  Defines class PickUpManager which is used for keeping track on all pickups
 *  in the game
 *
 */

#include "Display/DisplayElement.h"
#include "Utility/Relay.h"
#include "Entity/PickUp.h"
#include <list>

/** \class PickUpManager
 *  \brief Class which is used for keeping track of all pickups in the game.
 *  \details This class contains the list of all pickups which can be found in
 *           the level and have appeared randomly after wall have been
 *           destroyed. Has appropriate methods for adding pickups and drawing
 *           them. Also has an update method check whether any of the pickup
 *           have already been used and deletes them if they have. Also keeps
 *           reference to Relay which it uses to communicate to other game
 *           objects.
 */
class PickUpManager : public DisplayElement
{
    public:
        /**
         *  \brief Constructor for PickUpManager
         *
         *  Makes an object of class PickUpManager according to given
         *  parameters.
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param tile_size represents the size of one tile of the map in
         *         pixels (which is required for proper implementation of method
         *         Draw())
         *  \param relay pointer to the relay object which is used to
         *         communicate with other game objects
         */
        PickUpManager(SDL_Texture* texture, unsigned int tile_size, Relay* relay);
        /**
         *  \brief Destructor for PickUpManager
         *
         *  Destroys all pickups it keeps track of before deleting itself.
         */
        ~PickUpManager();
        PickUpManager(const PickUpManager& other) = delete; /**< \brief Default copy constructor is disabled */
        PickUpManager& operator=(const PickUpManager&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Adds new PickUp to the list of pickups.
         *
         *  Adds new PickUp to the list of pickups so that it will be
         *  periodically updated and destroyed when it has been used.
         *
         *  \param pickup pointer to object PickUp which will be added to the
         *         list
         *  \return void
         */
        void AddPickUp(PickUp* pickup);
        /**
         *  \brief Makes new PickUp according to given parameters and adds it to
         *         the list of pickups.
         *
         *  Uses the given parameters and makes a new PickUp object and adds it
         *  to the list of pickups same as method AddPickUp(PickUp* pickup). The
         *  PickUp will be periodically updated and destroyed when it has been
         *  used.
         *
         *  \param type describes type of PickUp to be made
         *  \param x center x coordinate of the PickUp on the map
         *  \param y center y coordinate of the PickUp on the map
         *  \param value numerical value that the PickUp will give to player
         *         when used
         *  \return void
         */
        void MakePickUp(PickUp::PickUpType type, int x, int y, int value = 0);

        /**
         *  \brief Update function for class PickUpManager
         *
         *  Checks whether any pickup has been used by a player and removes it
         *  from the list of the pickups it keeps track of.
         *
         *  \return void
         */
        void Update();
        /**
         *  \brief Draw all the pickups it keeps track of on given SLD_Renderer
         *
         *  Calls PickUp::Draw() method for all the pickups it keeps track of
         *  with the given SLD_Renderer as parameter so it will draw them on
         *  that same renderer.
         *  \param renderer represents the SDL_Renderer on which the pickups
         *         will be drawn on.
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer) const;

        /** \class PickUpManager::Iterator
         *  \brief Class which is used for iterating through list of PickUp
         *         objects that PickUpManager keeps track off.
         *  \details This is an embedded class inside of PickUpManager that is
         *           used for iterating the list of PickUp objects (that a
         *           PickUpManager is keeping track of) and is meant to be used
         *           by an outside class effectively keeping internal structure
         *           of the class hidden.
         */
        class Iterator
        {
        public:
            /**
             *  \brief Constructor for PickUpManager::Iterator
             *
             *  Makes an iterator for PickUp objects inside given PickUpManager
             *  and sets it to first element.
             *  \param pickup_manager pointer to PickUpManager through which it
             *         will iterate.
             *
             */
            Iterator(PickUpManager* pickup_manager);
            /**
             *  \brief Resets the iterator to the first element.
             *
             *  \return void
             */
            void Reset();
            /**
             *  \brief Tells if all elements have been iterated
             *
             *  \return true if iterator has passed last element
             */
            bool Finished() const;
            /**
             *  \brief Returns reference to the current PickUp object in the
             *         iterator
             *
             *  \return reference to PickUp object
             */
            PickUp& GetPickUp() const;
            /**
             *  \brief Increments the iterator, moves onto the next element.
             *
             *  \return reference to Iterator class
             */
            Iterator& operator++ ();

        private:
            std::list<PickUp*>* m_pickups_pointer;
            std::list<PickUp*>::iterator it;

            inline std::list<PickUp*>::iterator Begin() const;
            inline std::list<PickUp*>::iterator End() const;
            inline std::list<PickUp*>::iterator Current() const;
            inline std::list<PickUp*>::iterator Next();
        };

    protected:

    private:
        std::list<PickUp*>      m_pickups;
        unsigned int            m_tile_size;
        unsigned int            m_draw_size;
        Relay*                  m_relay;
        //Iterator                m_iterator;
};

#endif // PICKUPMANAGER_H
