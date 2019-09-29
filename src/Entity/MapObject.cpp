#include "Entity/MapObject.h"
#include "Constants/TextureMapObjectConstants.h"

MapObject::MapObject(Tile id, SDL_Texture *texture, unsigned int kind)
    : m_id(id), m_texture(texture), m_kind(kind)
{
}

void MapObject::Draw(SDL_Renderer* renderer, const SDL_Rect *DestR)
{
    SDL_Rect SrcR;
    if (m_id == EMPTY)
    {
        SrcR.h = TEXTURE_MAP_EMPTY_H;
        SrcR.w = TEXTURE_MAP_EMPTY_W;
        SrcR.x = TEXTURE_MAP_EMPTY_X + TEXTURE_MAP_EMPTY_KIND_OFFSET_X * m_kind;
        SrcR.y = TEXTURE_MAP_EMPTY_Y + TEXTURE_MAP_EMPTY_KIND_OFFSET_Y * m_kind;
    }
    else //if (m_id == INDESTRUCTIBLE_WALL)
    {
        SrcR.h = TEXTURE_MAP_INDESTRUCTIBLE_H;
        SrcR.w = TEXTURE_MAP_INDESTRUCTIBLE_W;
        SrcR.x = TEXTURE_MAP_INDESTRUCTIBLE_X + TEXTURE_MAP_INDESTRUCTIBLE_KIND_OFFSET_X * m_kind;
        SrcR.y = TEXTURE_MAP_INDESTRUCTIBLE_Y + TEXTURE_MAP_INDESTRUCTIBLE_KIND_OFFSET_Y * m_kind;
    }

    SDL_RenderCopy(renderer, m_texture, &SrcR, DestR);
}
