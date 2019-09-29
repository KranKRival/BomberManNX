#include "Entity/Bomb.h"
#include "Constants/TextureBombConstants.h"

#ifdef DEBUG_OUTPUT_BOMB
#include <iostream>
#endif // DEBUG_OUTPUT_BOMB

Bomb::Bomb(unsigned int fuse_duration,
           SDL_Texture* texture,
           unsigned int x,
           unsigned int y,
           unsigned int bomb_size,
           unsigned int player_id,
           double intensity,
           unsigned int damage)
    :   m_timer(),
        m_fuse_duration(fuse_duration),
        m_texture(texture),
        m_explode(false),
        m_x(x),
        m_y(y),
        m_draw_size(bomb_size),
        m_player_id(player_id),
        m_intensity(intensity),
        m_damage(damage),
        m_phase_number(0)
{
    #ifdef DEBUG_OUTPUT_BOMB
    std::cout << "Bomb placed: X:" << m_x << " Y:" << m_y << " fuse:" << m_fuse_duration << " intesity:" << m_intensity << std::endl;
    #endif // DEBUG_OUTPUT_BOMB
}

#ifdef DEBUG_OUTPUT_BOMB
Bomb::~Bomb()
{
    std::cout << "Bomb destroyed: X:" << m_x << " Y:" << m_y << " fuse:" << m_fuse_duration << " intesity:" << m_intensity << std::endl;
}
#endif // DEBUG_OUTPUT_BOMB

void Bomb::Update()
{
    if (m_timer.GetTimeElapsed() > m_fuse_duration)
        m_explode = true;
    else
    {
        m_phase_number =  m_timer.GetTimeElapsed() / (m_fuse_duration / TEXTURE_BOMB_COUNT); // Time elapsed / Phase length
        #ifdef DEBUG_OUTPUT_BOMB
        std::cout << "Bomb: X:" << m_x << " Y:" << m_y << " Phase:" << m_phase_number << std::endl;
        #endif // DEBUG_OUTPUT_BOMB
    }
}

bool Bomb::Explode() const
{
    return m_explode;
}

void Bomb::Draw(SDL_Renderer* renderer) const
{
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.h = TEXTURE_BOMB_H;
    SrcR.w = TEXTURE_BOMB_W;
    SrcR.x = TEXTURE_BOMB_X + m_phase_number * TEXTURE_BOMB_OFFSET_X;
    SrcR.y = TEXTURE_BOMB_Y + m_phase_number * TEXTURE_BOMB_OFFSET_Y;

    DestR.h = m_draw_size;
    DestR.w = m_draw_size;
    DestR.x = m_x - m_draw_size / 2;
    DestR.y = m_y - m_draw_size / 2;

    SDL_RenderCopy(renderer, m_texture, &SrcR, &DestR);
}
