#include "Manager/ExplosionManager.h"

ExplosionManager::ExplosionManager(SDL_Texture* texture, unsigned int tile_size)
    : DisplayElement(texture), m_tile_size(tile_size)
{
}

ExplosionManager::~ExplosionManager()
{
    for(auto i = m_explosions.begin(); i != m_explosions.end(); ++i)
    {
        delete (*i);
        #ifdef DEBUG_OUTPUT
        std::cout << "Explosion deleted" << std::endl;
        #endif // DEBUG_OUTPUT
    }

}

void ExplosionManager::AddExplosion(Explosion *explosion)
{
    m_explosions.push_back(explosion);
}

void ExplosionManager::MakeExplosion(unsigned int duration,
                                     unsigned int x_center,
                                     unsigned int y_center,
                                     double intensity)
{
    Explosion* e = new Explosion(duration,x_center,y_center,intensity,m_tile_size,m_texture);
    AddExplosion(e);
}

void ExplosionManager::Update()
{
    for(auto i = m_explosions.begin(); i != m_explosions.end();)
    {
        (*i)->Update();
        if(!((*i)->IsExploding())) // if not exploding then delete object
        {
            delete (*i);
            i = m_explosions.erase(i);
        }
        else
            ++i;
    }
}

void ExplosionManager::Draw(SDL_Renderer* renderer) const
{
    for(auto i = m_explosions.begin(); i != m_explosions.end(); ++i)
    {
        (*i)->Draw(renderer);
    }

}
