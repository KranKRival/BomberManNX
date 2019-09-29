#ifndef RELAY_H
#define RELAY_H

/** \class Relay
 *  \brief class which represents a relay between manager classes
 *  \details This class contains pointers to all manager classes and class Map
 *           and its purpose is to make communication between them better.
 *           Also contains setters and getters for all objects for easy access.
 */

class ExplosionManager;
class BombManager;
class PlayerManager;
class EnemyManager;
class Map;
class PickUpManager;

class Relay
{
    public:
        /**
         *  \brief Constructor for Relay.
         *
         *  Makes an object of class Relay.
         *
         */
        Relay();

        /**
         *  \brief Constructor for Relay.
         *
         *  Makes an object of class Relay according to given attributes.
         *
         *  \param explosion_manager pointer to ExplosionManager object of the game
         *  \param bomb_manager pointer to BombManager object of the game
         *  \param player_manager pointer to PlayerManager object of the game
         *  \param enemy_manager pointer to EnemyManager object of the game
         *  \param map_level pointer to Map object of the game
         *  \param pickup_manager pointer to PickUpManager object of the game
         *
         */
        Relay(ExplosionManager *explosion_manager,
              BombManager *bomb_manager,
              PlayerManager *player_manager,
              EnemyManager *enemy_manager,
              Map* map_level,
              PickUpManager* pickup_manager);

        ExplosionManager* GetExplosionManager() const;
        void SetExplosionManager(ExplosionManager* val);

        BombManager* GetBombManager() const;
        void SetBombManager(BombManager* val);

        PlayerManager* GetPlayerManager() const;
        void SetPlayerManager(PlayerManager* val);

        EnemyManager* GetEnemyManager() const;
        void SetEnemyManager(EnemyManager* val);

        Map* GetMap() const;
        void SetMap(Map* val);

        PickUpManager* GetPickUpManager() const;
        void SetPickUpManager(PickUpManager* val);

        /**
         *  \brief Tells if all player are dead
         *
         *  Reads values from PlayerManager to determine whether all player have
         *  died in which case returns true, otherwise returns false.
         *  \return true if all players are dead
         *
         */
        bool PlayersDead() const;
        /**
         *  \brief Tell if the level was completed successfully
         *
         *  Reads values from PlayerManager to determine whether the players
         *  have completed level successfully in which case returns true,
         *  otherwise returns false.
         * \return true if level was completed successfully, otherwise false
         *
         */
        bool LevelCompleted() const;

    protected:

    private:
        ExplosionManager* m_explosion_manager;
        BombManager*      m_bomb_manager;
        PlayerManager*    m_player_manager;
        EnemyManager*     m_enemy_manager;
        Map*              m_map;
        PickUpManager*    m_pickup_manager;

};

#endif // RELAY_H
