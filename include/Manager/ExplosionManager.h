#ifndef EXPLOSIONMANAGER_H
#define EXPLOSIONMANAGER_H

/**
 *  \file ExplosionManager.h
 *
 *  Defines class ExplosionManager which is used for keeping track on all
 *  explosions in the game
 *
 */

#include <list>
#include "Display/DisplayElement.h"
#include "Entity/Explosion.h"

/** \class ExplosionManager
 *  \brief Class which is used for keeping track of all the explosions in the
 *         game.
 *  \details This class contains the list of all explosions which are made by
 *           the bombs that have burned out their fuses. Has appropriate methods
 *           for adding explosions and drawing them. Also has an update method
 *           in the form of Update() which calls the appropriate update method
 *           for all explosions it keeps track off.
 */
class ExplosionManager : public DisplayElement
{
    public:
        /**
         *  \brief Constructor for ExplosionManager
         *
         *  Makes an object of class ExplosionManager according to given
         *  parameters
         *  \param texture pointer to SDL_texture object from which the texture
         *         will be taken for method Draw()
         *  \param tile_size represents the size of one tile of the map in
         *         pixels (which is required for proper implementation of method
         *         Draw())
         */
        ExplosionManager(SDL_Texture* texture, unsigned int tile_size);
        /**
         *  \brief Destructor for ExplosionManager
         *
         *  Deletes all objects of Explosion it keeps track off.
         */
        ~ExplosionManager();
        ExplosionManager(const ExplosionManager& other) = delete; /**< \brief Default copy constructor is disabled */
        ExplosionManager& operator=(const ExplosionManager&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Adds new Explosion to the list of explosions.
         *
         *  Adds new Explosion to the list of explosions so that it will be
         *  periodically updated and destroyed when it's animation plays out.
         *
         *  \param explosion pointer to object Explosion which will be added to
         *         the list
         *  \return void
         */
        void AddExplosion(Explosion *explosion);
        /**
         *  \brief Makes new Explosion according to given parameters and adds it
         *         to the list of explosions.
         *
         *  Uses the given parameters and makes a new Explosion object and adds
         *  it to the list of explosions same as method
         *  AddExplosion(Explosion *explosion). The explosion will be
         *  periodically updated and destroyed when it's animation plays out.
         *
         *  \param duration duration of explosion's animation in milliseconds
         *  \param x_center center x coordinate of the explosion on the map
         *  \param y_center center y coordinate of the explosion on the map
         *  \param intensity real value of explosion's visual size (1.0 is
         *         radius of one tile size of the map)
         *  \return void
         */
        void MakeExplosion(unsigned int duration,
                           unsigned int x_center,
                           unsigned int y_center,
                           double intensity);
        /**
         *  \brief Update function for class ExplosionManager
         *
         *  Calls the update methods of all the explosions it keeps track of.
         *
         *  \return void
         */
        void Update();
        /**
         *  \brief Draw all the explosion it keeps track of on given
         *         SLD_Renderer
         *
         *  Calls Explosion::Draw() methods for all the explosions it keeps
         *  track of with the given SLD_Renderer so it will draw them on that
         *  same renderer.
         *  \param renderer represents the SDL_Renderer on which the bombs
         *         will be drawn on.
         *
         *  \return void
         */
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        std::list<Explosion*>   m_explosions;
        unsigned int            m_tile_size;
};

#endif // EXPLOSIONMANAGER_H
