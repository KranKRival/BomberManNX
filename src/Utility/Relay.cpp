#include "Utility/Relay.h"
//#include "Manager/ExplosionManager.h"
//#include "Manager/BombManager.h"
#include "Manager/PlayerManager.h"
//#include "Manager/EnemyManager.h"
//#include "Manager/Map.h"
//#include "Manager/PickUpManager.h"

Relay::Relay()
    : m_explosion_manager(nullptr),
      m_bomb_manager(nullptr),
      m_player_manager(nullptr),
      m_enemy_manager(nullptr),
      m_map(nullptr),
      m_pickup_manager(nullptr)
{
}

Relay::Relay(ExplosionManager *explosion_manager,
             BombManager *bomb_manager,
             PlayerManager *player_manager,
             EnemyManager *enemy_manager,
             Map* map_level,
             PickUpManager* pickup_manager)
    : m_explosion_manager(explosion_manager),
      m_bomb_manager(bomb_manager),
      m_player_manager(player_manager),
      m_enemy_manager(enemy_manager),
      m_map(map_level),
      m_pickup_manager(pickup_manager)
{
}

ExplosionManager* Relay::GetExplosionManager() const
{
    return m_explosion_manager;
}

void Relay::SetExplosionManager(ExplosionManager* val)
{
    m_explosion_manager = val;
}

BombManager* Relay::GetBombManager() const
{
    return m_bomb_manager;
}

void Relay::SetBombManager(BombManager* val)
{
    m_bomb_manager = val;
}

PlayerManager* Relay::GetPlayerManager() const
{
    return m_player_manager;
}

void Relay::SetPlayerManager(PlayerManager* val)
{
    m_player_manager = val;
}

EnemyManager* Relay::GetEnemyManager() const
{
    return m_enemy_manager;
}

void Relay::SetEnemyManager(EnemyManager* val)
{
    m_enemy_manager = val;
}

Map* Relay::GetMap() const
{
    return m_map;
}

void Relay::SetMap(Map* val)
{
    m_map = val;
}

PickUpManager* Relay::GetPickUpManager() const
{
    return m_pickup_manager;
}

void Relay::SetPickUpManager(PickUpManager* val)
{
    m_pickup_manager = val;
}

bool Relay::PlayersDead() const
{
    return m_player_manager->AreAllDead();
}

bool Relay::LevelCompleted() const
{
    return m_player_manager->AreAllCompleted();
}
