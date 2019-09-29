#include "Manager/Map.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>      /* fstream open close */
#include "Constants/TextureMapObjectConstants.h"
#include "Constants/PickUpConstants.h"
#include "Entity/PickUp.h"
#include "Manager/PickUpManager.h"
#include "Entity/DestructibleWall.h"

//#define DEBUG_OUTPUT_MAP

#ifdef DEBUG_OUTPUT_MAP
#include <iostream>
#endif // DEBUG_OUTPUT_MAP

Map::Map(std::string path_to_file,
         SDL_Texture* texture,
         unsigned int tile_size,
         Relay* relay)
    : DisplayElement(texture),
      m_tile_size(tile_size),
      m_relay(relay),
      m_wall_count(0)
{
    std::fstream fs;
    fs.open (path_to_file, std::fstream::in);

    if (!fs.is_open())
    {
        #ifdef DEBUG_OUTPUT_MAP
        std::cout << "Error opening file " << path_to_file << std::endl;
        #endif // DEBUG_OUTPUT_MAP
        exit(EXIT_FAILURE);
    }

    fs >> m_height >> m_width;

    m_layout.resize(m_height);
    for (unsigned i=0; i<m_height; ++i)
        m_layout[i].resize(m_width);

    srand(time(nullptr));
    for (unsigned i=0; i<m_height; ++i)
        for (unsigned j=0; j<m_width; ++j)
        {
            int id;
            fs >> id;
            //MapObject::Tile tile;
            switch(id)
            {
            case 0:
                //tile = MapObject::EMPTY;
                m_layout[i][j] = new MapObject(MapObject::EMPTY, m_texture, rand() % TEXTURE_MAP_EMPTY_KIND_COUNT);
                break;
            case 1:
                //tile = MapObject::DESTRUCTIBLE_WALL;
                m_layout[i][j] = new DestructibleWall(m_texture, rand() % TEXTURE_MAP_DESTRUCTIBLE_KIND_COUNT);
                ++m_wall_count;
                break;
            case 2:
                //tile = MapObject::INDESTRUCTIBLE_WALL;
                m_layout[i][j] = new MapObject(MapObject::INDESTRUCTIBLE_WALL, m_texture, rand() % TEXTURE_MAP_INDESTRUCTIBLE_KIND_COUNT);
                break;
            default:
                //tile = MapObject::EMPTY;
                m_layout[i][j] = new MapObject(MapObject::EMPTY, m_texture);
                break;
            }
        }
    #ifdef DEBUG_OUTPUT_MAP
    std::cout << "WALL COUNT: " << m_wall_count << std::endl;
    #endif // DEBUG_OUTPUT_MAP
    fs.close();
    srand(time(NULL));
}

Map::~Map()
{
    for (unsigned i = 0; i < m_height; ++i)
    {
        for (unsigned j = 0; j < m_width; ++j)
        {
            delete m_layout[i][j];
        }
    }
}

bool Map::Walkable(unsigned int i,unsigned int j) const
{
    if (m_layout[i][j]->GetId() == MapObject::EMPTY)
        return true;
    else
        return false;
}


void Map::Draw(SDL_Renderer* renderer) const
{
    SDL_Rect DestR;
    int tile_size = m_tile_size;

    DestR.x = 0;
    DestR.y = 0;
    DestR.w = tile_size;
    DestR.h = tile_size;

    for (unsigned i = 0; i < m_height; ++i)
    {
        for (unsigned j = 0; j < m_width; ++j)
        {
            DestR.y = tile_size*i;
            DestR.x = tile_size*j;
            m_layout[i][j]->Draw(renderer, &DestR);
        }
    }
}

void Map::DestroyWall(unsigned int i, unsigned int j, unsigned int damage)
{
    if (m_layout[i][j]->GetId() == MapObject::DESTRUCTIBLE_WALL)
    {
        DestructibleWall* wall = (DestructibleWall*)m_layout[i][j];
        wall->DecreaseIntegrity(damage);
        if (wall->IsDestroyed())
        {
            delete m_layout[i][j];
            m_layout[i][j] = new MapObject(MapObject::EMPTY, m_texture);
            --m_wall_count;
            #ifdef DEBUG_OUTPUT_MAP
            std::cout << "MapObject at X:" << j << " Y:" << i << " is replaced with EMPTY. Wall count:" << m_wall_count << std::endl;
            #endif // DEBUG_OUTPUT_MAP
            if (m_wall_count == 0)
                PlaceExit(i,j);
            else
                TryPlacePickUp(i,j);
        }
    }
    #ifdef DEBUG_OUTPUT_MAP
    else
    {
        std::cout << "MapObject at X:" << j << " Y:" << i << " is not DESTRUCTABLE_WALL." << std::endl;
    }
    #endif // DEBUG_OUTPUT_MAP
}

MapObject::Tile Map::GetTileType(unsigned int i, unsigned int j) const
{
    return m_layout[i][j]->GetId();
}

void Map::PlaceExit(unsigned int i, unsigned int j)
{
    unsigned int x = j*m_tile_size+m_tile_size/2;
    unsigned int y = i*m_tile_size+m_tile_size/2;
    m_relay->GetPickUpManager()->MakePickUp(PickUp::EXIT,x,y);
    #ifdef DEBUG_OUTPUT_MAP
    std::cout << "Made PickUp::EXIT at: (i,j)=(" << i << "," << j << ") (x,y)=(" << x << "," << y << ")" << std::endl;
    #endif // DEBUG_OUTPUT_MAP
}

void Map::TryPlacePickUp(unsigned int i, unsigned int j)
{
    unsigned int x = j*m_tile_size+m_tile_size/2;
    unsigned int y = i*m_tile_size+m_tile_size/2;
    #ifdef DEBUG_OUTPUT_MAP
    std::cout << "Map::TryPlacePickUp at: (i,j)=(" << i << "," << j << ") (x,y)=(" << x << "," << y << ")" << std::endl;
    #endif // DEBUG_OUTPUT_MAP
    unsigned int chance = rand() % 100;
    unsigned int type = rand() % NUMBER_OF_PICKUPS;
    #ifdef DEBUG_OUTPUT_MAP
    std::cout << "Chance: " << chance << ", Type:" << type << std::endl;
    #endif // DEBUG_OUTPUT_MAP
    switch(type)
    {
        case 0:
            if (chance < CHANCE_PICKUP_EXIT)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::EXIT,x,y);
            break;
        case 1:
            if (chance < CHANCE_PICKUP_SPEED)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::SPEED,x,y,VALUE_PICKUP_SPEED);
            break;
        case 2:
            if (chance < CHANCE_PICKUP_BOMB)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::BOMB,x,y,VALUE_PICKUP_BOMB);
            break;
        case 3:
            if (chance < CHANCE_PICKUP_DAMAGE)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::DAMAGE,x,y,VALUE_PICKUP_DAMAGE);
            break;
        case 4:
            if (chance < CHANCE_PICKUP_LIFE)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::LIFE,x,y,VALUE_PICKUP_LIFE);
            break;
        case 5:
            if (chance < CHANCE_PICKUP_SPEED_DECREASE)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::SPEED_DECREASE,x,y,VALUE_PICKUP_SPEED_DECREASE);
            break;
        case 6:
            if (chance < CHANCE_PICKUP_BOMB_DECREASE)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::BOMB_DECREASE,x,y,VALUE_PICKUP_BOMB_DECREASE);
            break;
        case 7:
            if (chance < CHANCE_PICKUP_DAMAGE_DECREASE)
                m_relay->GetPickUpManager()->MakePickUp(PickUp::DAMAGE_DECREASE,x,y,VALUE_PICKUP_DAMAGE_DECREASE);
            break;
        default:
            break;
    }

}
