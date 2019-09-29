#include "Destroyer/Destroyer.h"
#include <cmath>

Destroyer::Destroyer()
{
}

void Destroyer::DestroyEnemy(Enemy* enemy,
                                  unsigned int start_x,
                                  unsigned int start_y,
                                  unsigned int tile_size,
                                  double intensity)
{
    unsigned int enemy_center_x = enemy->GetX() + enemy->GetSizeW() / 2;
    unsigned int enemy_center_y = enemy->GetY() + enemy->GetSizeH() / 2;
    double distance = std::sqrt( Square(start_x-enemy_center_x) + Square(start_y-enemy_center_y) );

    if (distance < tile_size * intensity / 2)
        enemy->SetHealth(0);
}

void Destroyer::DestroyPlayer(Player* player,
                                  unsigned int start_x,
                                  unsigned int start_y,
                                  unsigned int tile_size,
                                  double intensity)
{
    unsigned int player_center_x = player->GetX() + player->GetSizeW() / 2;
    unsigned int player_center_y = player->GetY() + player->GetSizeH() / 2;
    double distance = std::sqrt( Square(start_x-player_center_x) + Square(start_y-player_center_y) );

    if (distance < tile_size * intensity / 2)
        player->SetHealth(0);
}
