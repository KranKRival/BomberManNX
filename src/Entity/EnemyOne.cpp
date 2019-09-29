#include "Entity/EnemyOne.h"
#include "Manager/Map.h"
#include "Constants/TextureEnemyConstants.h"

EnemyOne::EnemyOne(SDL_Texture* tex, unsigned int tile_size, unsigned int val_x, unsigned int val_y)
 : Enemy(tex, tile_size, val_x, val_y)
{
    m_speed = 100; //timer speed
    m_move_speed = m_move_speed *m_tile_size/32; //speed according to 32px tile size

    m_rotation_const = TEXTURE_ENEMY_ONE_COUNT;
    m_enemy_size_w = TEXTURE_ENEMY_ONE_SIZE_W *tile_size/32;
    m_enemy_size_h = TEXTURE_ENEMY_ONE_SIZE_H *tile_size/32; //size according to 32px tile size
}

void EnemyOne::Draw(SDL_Renderer *renderer)
{
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = TEXTURE_ENEMY_ONE_X + (m_status % m_rotation_const) * TEXTURE_ENEMY_ONE_TEXTURE_OFFSET;
    SrcR.y = TEXTURE_ENEMY_ONE_Y;
    SrcR.w = TEXTURE_ENEMY_ONE_SOURCE_W;
    SrcR.h = TEXTURE_ENEMY_ONE_SOURCE_H;

    DestR.x = m_x;
    DestR.y = m_y;
    DestR.w = m_enemy_size_w;
    DestR.h = m_enemy_size_h;

    SDL_RenderCopy(renderer, m_tex, &SrcR, &DestR);
}
