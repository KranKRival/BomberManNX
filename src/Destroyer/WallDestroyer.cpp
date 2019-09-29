#include "Destroyer/WallDestroyer.h"

//#define DEBUG_OUTPUT_WALLDESTROYER

#ifdef DEBUG_OUTPUT_WALLDESTROYER
#include<iostream>
#endif // DEBUG_OUTPUT_WALLDESTROYER

#include<cmath>

WallDestroyer::WallDestroyer(Map* level,
                             unsigned int start_x,
                             unsigned int start_y,
                             unsigned int tile_size,
                             double intensity,
                             unsigned int damage)
    :   m_level(level),
        m_start_x(start_x),
        m_start_y(start_y),
        m_tile_size(tile_size),
        m_intensity(intensity/2),
        m_damage(damage)
{
    int i = m_start_y / tile_size; // row number
    int j = m_start_x / tile_size; // column number
    #ifdef DEBUG_OUTPUT_WALLDESTROYER
    std::cout << "WallDestroyer Start at: (i,j)=" << i << "," << j << std::endl;
    #endif // DEBUG_OUTPUT_WALLDESTROYER
    CheckAndCall(i-1,j,-1,0);       //UP
    CheckAndCall(i+1,j,1,0);        //DOWN
    CheckAndCall(i,j-1,0,-1);       //LEFT
    CheckAndCall(i,j+1,0,1);        //RIGHT
    CheckAndCall(i-1,j-1,-1,-1);    //UP LEFT
    CheckAndCall(i-1,j+1,-1,1);     //UP RIGHT
    CheckAndCall(i+1,j-1,1,-1);     //DOWN LEFT
    CheckAndCall(i+1,j+1,1,1);      //DOWN RIGHT
}

void WallDestroyer::Spread(int row, int col, int direction_row, int direction_col) const
{
    #ifdef DEBUG_OUTPUT_WALLDESTROYER
    std::cout << "WallDestroyer Explosion spread to: (i,j)=" << row << "," << col << std::endl;
    #endif // DEBUG_OUTPUT_WALLDESTROYER
    if ((direction_row != 0))
        CheckAndCall(row+direction_row,col              ,direction_row,direction_col);
    if ((direction_col != 0))
        CheckAndCall(row              ,col+direction_col,direction_row,direction_col);
    if ((direction_row != 0) && (direction_col != 0))
        CheckAndCall(row+direction_row,col+direction_col,direction_row,direction_col);
}

void WallDestroyer::Destroy(int row, int col) const
{
    double distance = DistanceToCenter(row,col);
    #ifdef DEBUG_OUTPUT_WALLDESTROYER
    std::cout << "WallDestroyer Destroy: distance=" << distance << ", reach=" << m_intensity * m_tile_size << std::endl;
    #endif // DEBUG_OUTPUT_WALLDESTROYER
    if (distance < m_intensity * m_tile_size)
    {
        #ifdef DEBUG_OUTPUT_WALLDESTROYER
        std::cout << "WallDestroyer Destroying wall: (i,j)=" << row << "," << col << std::endl;
        #endif // DEBUG_OUTPUT_WALLDESTROYER
        m_level->DestroyWall(row,col,m_damage);
    }
}

double WallDestroyer::DistanceToCenter(int row, int col) const
{
    int wall_center_x = col * m_tile_size + m_tile_size / 2;
    int wall_center_y = row * m_tile_size + m_tile_size / 2;
    return std::sqrt( Square(m_start_x-wall_center_x) + Square(m_start_y-wall_center_y) );
}

void WallDestroyer::CheckAndCall(int new_row, int new_col, int direction_row, int direction_col) const
{
    if (DistanceToCenter(new_row,new_col) < m_intensity * m_tile_size)
    {
        MapObject::Tile tile = m_level->GetTileType(new_row,new_col);
        if (tile == MapObject::EMPTY)
            Spread(new_row,new_col,direction_row,direction_col);
        else if (tile == MapObject::DESTRUCTIBLE_WALL)
            Destroy(new_row,new_col);
    }
}
