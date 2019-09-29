#include "Entity/Enemy.h"
#include "Manager/Map.h"
#include "Manager/PlayerManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(SDL_Texture* tex, unsigned int tile_size, unsigned int val_x, unsigned int val_y)
{
    this->m_x = val_x*tile_size;
    this->m_y = val_y*tile_size;

    srand(time(NULL));
    m_timer.ResetTimer();
    this->m_tex = tex;
    this->m_tile_size = tile_size;
    this->m_direction = RIGHT;
}

Enemy::~Enemy()
{

}

bool Enemy::Touch(unsigned int player_x, unsigned int player_y)
{
    if(player_x >= m_x && player_y >= m_y && player_x <= m_x+m_enemy_size_w
       && player_y <= m_y+m_enemy_size_h)
    {
        return true;
    }
    return false;
}

void Enemy::Update(Relay *relay)
{
    for(PlayerManager::Iterator it(relay->GetPlayerManager()); !it.Finished(); ++it)
    {
        Player& player = it.GetPlayer();
        unsigned int player_x = player.GetX();
        unsigned int player_y = player.GetY();
        unsigned int player_w = player.GetSizeW();
        unsigned int player_h = player.GetSizeH();

        //Setting coordinates for better collision
        player_x = player_x + m_tile_size/6;
        player_y = player_y + m_tile_size/6;
        player_w = player_w - m_tile_size/3;
        player_h = player_h - m_tile_size/4;
        //----------------------------------------

        if(Touch(player_x, player_y))
        {
            player.SetHealth(0);
        }
        else if(Touch(player_x+player_w, player_y))
            {
                player.SetHealth(0);
            }
            else if(Touch(player_x, player_y+player_h))
                {
                    player.SetHealth(0);
                }
                else if(Touch(player_x+player_w, player_y+player_h))
                    {
                        player.SetHealth(0);
                    }
    }

    int r;

        if(m_walk_len <= 0)
        {

            m_walk_len = rand()%5 + 10;
            r = rand()%4;
            switch(r)
            {
                case 0:
                    m_direction = LEFT;
                    break;
                case 1:
                    m_direction = RIGHT;
                    break;
                case 2:
                    m_direction = UP;
                    break;
                case 3:
                    m_direction = DOWN;
                    break;
                default:
                    m_direction = DOWN;
            }
        }

    if(m_timer.GetTimeElapsed() > m_speed)
    {
        m_walk_len--;
        this->EnemyMove(relay);
        m_timer.ResetTimer();
    }

}

void Enemy::EnemyMove(Relay *relay)
{
    unsigned int field_size = m_tile_size;

    if(m_direction == RIGHT) // MOVE RIGHT ------------
    {

        if( relay->GetMap()->Walkable( m_y/field_size, (m_x+m_enemy_size_w+m_move_speed)/field_size )
                && relay->GetMap()->Walkable( (m_y+m_enemy_size_h)/field_size, (m_x+m_enemy_size_w+m_move_speed)/field_size) )
        {
            m_x = m_x + m_move_speed;
        }
    }
    else if (m_direction == LEFT) // MOVE LEFT ------------
        {
            if(relay->GetMap()->Walkable( m_y/field_size, (m_x-m_move_speed)/field_size )
                    && relay->GetMap()->Walkable( (m_y+m_enemy_size_h)/field_size, (m_x-m_move_speed)/field_size) )
            {
                m_x = m_x - m_move_speed;
            }
        }
        else if(m_direction == DOWN) // MOVE DOWN ------------
            {

                if(relay->GetMap()->Walkable( (m_y+m_enemy_size_h+m_move_speed)/field_size, m_x/field_size )
                    && relay->GetMap()->Walkable( (m_y+m_enemy_size_h+m_move_speed)/field_size, (m_x+m_enemy_size_w)/field_size ) )
                {
                    m_y = m_y + m_move_speed;
                }
            }
            else if(m_direction == UP) // MOVE UP ------------
                {

                    if(relay->GetMap()->Walkable( (m_y - m_move_speed)/field_size, m_x/field_size )
                        &&  relay->GetMap()->Walkable( (m_y - m_move_speed)/field_size, (m_x+m_enemy_size_w)/field_size) )
                    {
                        m_y = m_y - m_move_speed;
                    }
                }
    m_status++;
    if(m_status >= m_rotation_const)
        m_status = 0;
}

unsigned int Enemy::GetX() const
{
    return m_x;
}

void Enemy::SetX(unsigned int val)
{
    m_x = val;
}

unsigned int Enemy::GetY() const
{
    return m_y;
}

void Enemy::SetY(unsigned int val)
{
    m_y = val;
}

unsigned int Enemy::GetSizeW() const
{
    return m_enemy_size_w;
}

unsigned int Enemy::GetSizeH() const
{
    return m_enemy_size_h;
}

unsigned int Enemy::GetStatus() const
{
    return m_status;
}

void Enemy::SetStatus(int s)
{
    m_status = s;
}

unsigned int Enemy::GetHealth() const
{
    return m_health;
}

void Enemy::SetHealth(int h)
{
    m_health = h;
}
