#include "Display/GameDisplay.h"
#include "Display/PauseDisplay.h"
#include "System/SystemTimer.h"

#include "Utility/Relay.h"
#include "Manager/Map.h"
#include "Manager/BombManager.h"
#include "Manager/ExplosionManager.h"
#include "Manager/PlayerManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/PickUpManager.h"

#include "Constants/ResourcesConstants.h"
#include "Constants/WindowConstants.h"

#include <string>
#include <sstream>

GameDisplay::GameDisplay(SDL_Texture* texture,
                         SDL_Renderer* renderer,
                         unsigned int window_width,
                         unsigned int window_height,
                         unsigned int players_number,
                         unsigned int current_level,
                         unsigned int number_of_screen_elements)
    : Display(),
      m_texture(texture),
      m_renderer(renderer),
      m_window_width(window_width),
      m_window_height(window_height),
      m_players_number(players_number),
      m_current_level(current_level),
      m_level_completed(false),
      m_music(nullptr)
{
    m_display_elements.reserve(number_of_screen_elements);
    SystemTimer::Instance()->Pause();

    unsigned int tile_size = MAP_TILE_SIZE;
    m_relay = new Relay();

    std::string level_num;
    std::stringstream convert;
    convert << m_current_level;
    level_num = convert.str();

    std::string path_level = RESOURCES_LEVELS_PATH + RESOURCES_LEVEL_MAP + level_num + RESOURCES_LEVEL_MAP_EXT;
    std::string path_player = RESOURCES_LEVELS_PATH + RESOURCES_LEVEL_PLAYER + level_num + RESOURCES_LEVEL_PLAYER_EXT;
    std::string path_enemy = RESOURCES_LEVELS_PATH + RESOURCES_LEVEL_ENEMY + level_num + RESOURCES_LEVEL_ENEMY_EXT;

    Map* level = new Map(path_level, m_texture, tile_size, m_relay);
    ExplosionManager* explosion_manager = new ExplosionManager(m_texture, tile_size);
    BombManager* bomb_manager = new BombManager(m_texture, tile_size, m_relay);
    PlayerManager* player_manager = new PlayerManager(path_player, m_texture, tile_size, m_relay, m_players_number);
    if (m_players_number>1)
        player_manager->GetPlayerById(1)->SetKeycodes(SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_g);
    EnemyManager* enemy_manager = new EnemyManager(path_enemy, m_texture, tile_size, m_relay);
    PickUpManager* pickup_manager = new PickUpManager(m_texture,tile_size,m_relay);

    m_relay->SetExplosionManager(explosion_manager);
    m_relay->SetBombManager(bomb_manager);
    m_relay->SetPlayerManager(player_manager);
    m_relay->SetEnemyManager(enemy_manager);
    m_relay->SetMap(level);
    m_relay->SetPickUpManager(pickup_manager);

    AddDisplayElement(level);
    AddDisplayElement(pickup_manager);
    AddDisplayElement(bomb_manager);
    AddDisplayElement(player_manager);
    AddDisplayElement(enemy_manager);
    AddDisplayElement(explosion_manager);

    std::string path_music = RESOURCES_BASE_PATH + RESOURCES_MUSIC_GAME;
    m_music = Mix_LoadMUS(path_music.c_str());
}

GameDisplay::~GameDisplay()
{
    for (auto i = m_display_elements.begin(); i != m_display_elements.end(); ++i)
    {
        delete (*i);
    }
    m_display_elements.clear();
    delete m_relay;
}

void GameDisplay::AddDisplayElement(DisplayElement* display_element)
{
    m_display_elements.push_back(display_element);
}

void GameDisplay::Init()
{
    Mix_PlayMusic(m_music, -1);
    SystemTimer::Instance()->Unpause();
}

void GameDisplay::Enter(int mode)
{
    Mix_ResumeMusic();
    SystemTimer::Instance()->Unpause();
    m_leave_next = false;
    if (mode == 0)
    {
        m_leave_previous = true;
    }
    else
    {
        m_leave_previous = false;
    }
}

void GameDisplay::Leave()
{
    Mix_PauseMusic();
    SystemTimer::Instance()->Pause();
}

int GameDisplay::Destroy()
{
    Mix_PauseMusic();
    Mix_FreeMusic(m_music);

    for (auto i = m_display_elements.begin(); i != m_display_elements.end(); ++i)
    {
        delete (*i);
    }
    m_display_elements.clear();
    delete m_relay;
    if (m_level_completed)
        return ++m_current_level;
    else
       return 0;
}

void GameDisplay::Update()
{
    if (m_relay->PlayersDead())
    {
        m_leave_previous = true;
        m_level_completed = false;
    }
    else if (m_relay->LevelCompleted())
    {
        m_leave_previous = true;
        m_level_completed = true;
    }
    else if (m_keyboard_input->IsKeyOn(11))
    {
        m_leave_next = true;
        m_next_display = new PauseDisplay(m_renderer, m_window_width, m_window_height);
    }
    else
    {
        for (auto i = m_display_elements.begin(); i != m_display_elements.end(); ++i)
        {
            (*i)->Update();
        }
    }
}

void GameDisplay::Draw(SDL_Renderer* renderer) const
{
    for (auto i = m_display_elements.cbegin(); i != m_display_elements.cend(); ++i)
    {
        (*i)->Draw(renderer);
    }
}
