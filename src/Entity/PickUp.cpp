#include "Entity/PickUp.h"
#include "Constants/TexturePickUpConstants.h"

PickUp::PickUp(SDL_Texture* texture,
               PickUpType type,
               int value,
               unsigned int x,
               unsigned int y,
               unsigned int draw_size)
    : m_texture(texture),
      m_type(type),
      m_value(value),
      m_x(x),
      m_y(y),
      m_draw_size(draw_size),
      m_used(false)
{
}

bool PickUp::IsUsed() const
{
    return m_used;
}

void PickUp::Use()
{
    m_used = true;
}

void PickUp::Draw(SDL_Renderer* renderer) const
{
    SDL_Rect SrcR, DestR;
    switch(m_type)
    {
        case EXIT:
            SrcR.h = TEXTURE_PICKUP_EXIT_H;
            SrcR.w = TEXTURE_PICKUP_EXIT_W;
            SrcR.x = TEXTURE_PICKUP_EXIT_X;
            SrcR.y = TEXTURE_PICKUP_EXIT_Y;
            break;
        case SPEED:
            SrcR.h = TEXTURE_PICKUP_SPEED_H;
            SrcR.w = TEXTURE_PICKUP_SPEED_W;
            SrcR.x = TEXTURE_PICKUP_SPEED_X;
            SrcR.y = TEXTURE_PICKUP_SPEED_Y;
            break;
        case BOMB:
            SrcR.h = TEXTURE_PICKUP_BOMB_H;
            SrcR.w = TEXTURE_PICKUP_BOMB_W;
            SrcR.x = TEXTURE_PICKUP_BOMB_X;
            SrcR.y = TEXTURE_PICKUP_BOMB_Y;
            break;
        case DAMAGE:
            SrcR.h = TEXTURE_PICKUP_DAMAGE_H;
            SrcR.w = TEXTURE_PICKUP_DAMAGE_W;
            SrcR.x = TEXTURE_PICKUP_DAMAGE_X;
            SrcR.y = TEXTURE_PICKUP_DAMAGE_Y;
            break;
        case LIFE:
            SrcR.h = TEXTURE_PICKUP_LIFE_H;
            SrcR.w = TEXTURE_PICKUP_LIFE_W;
            SrcR.x = TEXTURE_PICKUP_LIFE_X;
            SrcR.y = TEXTURE_PICKUP_LIFE_Y;
            break;
        case SPEED_DECREASE:
            SrcR.h = TEXTURE_PICKUP_SPEED_DECREASE_H;
            SrcR.w = TEXTURE_PICKUP_SPEED_DECREASE_W;
            SrcR.x = TEXTURE_PICKUP_SPEED_DECREASE_X;
            SrcR.y = TEXTURE_PICKUP_SPEED_DECREASE_Y;
            break;
        case BOMB_DECREASE:
            SrcR.h = TEXTURE_PICKUP_BOMB_DECREASE_H;
            SrcR.w = TEXTURE_PICKUP_BOMB_DECREASE_W;
            SrcR.x = TEXTURE_PICKUP_BOMB_DECREASE_X;
            SrcR.y = TEXTURE_PICKUP_BOMB_DECREASE_Y;
            break;
        case DAMAGE_DECREASE:
            SrcR.h = TEXTURE_PICKUP_DAMAGE_DECREASE_H;
            SrcR.w = TEXTURE_PICKUP_DAMAGE_DECREASE_W;
            SrcR.x = TEXTURE_PICKUP_DAMAGE_DECREASE_X;
            SrcR.y = TEXTURE_PICKUP_DAMAGE_DECREASE_Y;
            break;
        default:
            break;
    }
    DestR.h = m_draw_size;
    DestR.w = m_draw_size;
    DestR.x = m_x-m_draw_size/2;
    DestR.y = m_y-m_draw_size/2;
    SDL_RenderCopy(renderer,m_texture,&SrcR,&DestR);
}
