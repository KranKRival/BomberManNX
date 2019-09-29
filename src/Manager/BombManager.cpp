#include "Manager/BombManager.h"

#ifdef DEBUG_OUTPUT_BOMB
#include <iostream>
#endif // DEBUG_OUTPUT_BOMB

#include "Destroyer/WallDestroyer.h"
#include "Manager/ExplosionManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/PlayerManager.h"
#include "Constants/ResourcesConstants.h"
#include "Constants/TextureExplosionConstants.h"
#include "Constants/TextureBombConstants.h"

BombManager::BombManager(SDL_Texture* texture,
                         unsigned int tile_size,
                         Relay* relay)
    : DisplayElement(texture),
      m_bomb_size(tile_size * BOMB_SIZE_RELATIVE_TO_TILE_SIZE),
      m_tile_size(tile_size),
      m_relay(relay)
{
    std::string path_music = RESOURCES_BASE_PATH + RESOURCES_EXPLOSION_LOAD;
    m_bomb_sound_effect = Mix_LoadWAV(path_music.c_str());
}

BombManager::~BombManager()
{
    Mix_FreeChunk(m_bomb_sound_effect);

    for(auto i = m_bombs.begin(); i != m_bombs.end(); ++i)
    {
        delete (*i);
        #ifdef DEBUG_OUTPUT_BOMB
        std::cout << "Bomb deleted" << std::endl;
        #endif // DEBUG_OUTPUT_BOMB
    }
}

void BombManager::AddBomb(Bomb *bomb)
{
    m_bombs.push_back(bomb);
}

void BombManager::MakeBomb(unsigned int fuse_duration,
                           unsigned int x,
                           unsigned int y,
                           unsigned int player_id,
                           double intensity,
                           unsigned int damage)
{
    Bomb* b = new Bomb(fuse_duration,m_texture,x,y,m_bomb_size,player_id,intensity,damage);
    AddBomb(b);
}

void BombManager::Update()
{
    for(auto i = m_bombs.begin(); i != m_bombs.end();)
    {
        (*i)->Update();
        if((*i)->Explode())
        {
            Mix_PlayChannel(-1, m_bomb_sound_effect, 0);
            m_relay->GetExplosionManager()->MakeExplosion(EXPLOSION_ANIMATION_LENGTH, (*i)->GetX(), (*i)->GetY(), (*i)->GetIntensity());
            WallDestroyer wd(m_relay->GetMap(), (*i)->GetX(), (*i)->GetY(), m_tile_size, (*i)->GetIntensity(), (*i)->GetDamage());
            m_relay->GetEnemyManager()->KillEnemies((*i)->GetX(), (*i)->GetY(), (*i)->GetIntensity());
            m_relay->GetPlayerManager()->KillPlayer((*i)->GetX(), (*i)->GetY(), (*i)->GetIntensity());
            m_relay->GetPlayerManager()->GetPlayerById((*i)->GetPlayerId())->DecreaseTempBombNumber();
            delete (*i);
            i = m_bombs.erase(i);
        }
        else
            ++i;
    }
}

void BombManager::Draw(SDL_Renderer* renderer) const
{
    for(auto i = m_bombs.begin(); i != m_bombs.end(); ++i)
    {
        (*i)->Draw(renderer);
    }
}
