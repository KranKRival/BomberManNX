#include "Display/LoadingDisplay.h"
#include "System/TextRenderer.h"
#include "Display/GameDisplay.h"
#include "Constants/ResourcesConstants.h"
#include <string>
#include <sstream>

//#define DEBUG_OUTPUT_GAME_DISPLAY

#ifdef DEBUG_OUTPUT_GAME_DISPLAY
#include <iostream>
#endif

LoadingDisplay::LoadingDisplay(SDL_Texture* texture,
                               SDL_Renderer* renderer,
                               unsigned int window_width,
                               unsigned int window_height,
                               unsigned int players_number,
                               unsigned int max_level)
    : Display(),
      m_texture(texture),
      m_renderer(renderer),
      m_window_width(window_width),
      m_window_height(window_height),
      m_players_number(players_number),
      m_current_level(1),
      m_max_level(max_level),
      m_timer(),
      m_game_over(false),
      m_music(nullptr),
      m_music_wait(RESOURCES_MUSIC_LOAD_TIME)
{
    std::stringstream sstm;
    sstm << "STAGE " << m_current_level;
    MakeTexture(sstm.str());
    std::string path_music = RESOURCES_BASE_PATH + RESOURCES_MUSIC_LOAD;
    m_music = Mix_LoadMUS(path_music.c_str());
}

LoadingDisplay::~LoadingDisplay()
{
    for (auto i = m_textures.begin(); i != m_textures.end(); ++i)
    {
        SDL_DestroyTexture(*i);
    }
    m_textures.clear();
    m_textures_draw_src.clear();
    m_textures_draw_dest.clear();
}

void LoadingDisplay::Init()
{
    Mix_PlayMusic(m_music, -1);
}

void LoadingDisplay::Enter(int mode)
{
    Mix_PlayMusic(m_music, -1);
    m_next_display = nullptr;
    m_leave_previous = false;
    m_leave_next = false;
    m_timer.Unpause();
    m_timer.ResetTimer();
    if (mode == 0)
    {
        m_game_over = true;
        MakeTexture("GAME OVER");
    }
    else
    {
        m_current_level = mode;
        if (m_current_level <= RESOURCES_LEVEL_COUNT)
        {
            std::stringstream sstm;
            sstm << "STAGE " << m_current_level;
            MakeTexture(sstm.str());
        }
        else
        {
            MakeTexture("GAME COMPLETED");
            m_game_over = true;
        }
    }
}

void LoadingDisplay::Leave()
{
    Mix_HaltMusic();
    DestroyTextures();
}

int LoadingDisplay::Destroy()
{
    Mix_HaltMusic();
    Mix_FreeMusic(m_music);

    DestroyTextures();
    return 0;
}

void LoadingDisplay::DestroyTextures()
{
    for (auto i = m_textures.begin(); i != m_textures.end(); ++i)
    {
        SDL_DestroyTexture(*i);
    }
    m_textures.clear();
    m_textures_draw_src.clear();
    m_textures_draw_dest.clear();
}

void LoadingDisplay::Update()
{
    if (m_next_display == nullptr && !m_game_over)
    {
        #ifdef DEBUG_OUTPUT_GAME_DISPLAY
        std::cout << "LoadingDisplay: making GameDisplay; time: " << m_timer.GetTimeElapsed() << std::endl;
        #endif
        //SDL_Delay(1000); // test for fake concurrency
        m_next_display = new GameDisplay(m_texture,m_renderer,m_window_width,m_window_height,m_players_number,m_current_level);
        //SDL_Delay(1000); // test for fake concurrency
        #ifdef DEBUG_OUTPUT_GAME_DISPLAY
        std::cout << "LoadingDisplay: finished making GameDisplay; time: " << m_timer.GetTimeElapsed() << std::endl;
        #endif
    }
    else if (m_timer.GetTimeElapsed() > m_music_wait) // take action only after the music has finished
    {
        if (m_game_over)
        {
            m_leave_previous = true;
        }
        else
        {
            m_leave_next = true;
        }
    }
}

void LoadingDisplay::Draw(SDL_Renderer* renderer) const
{
    for (unsigned int i=0; i<m_textures.size(); ++i)
    {
        SDL_RenderCopy(renderer,m_textures[i],&m_textures_draw_src[i],&m_textures_draw_dest[i]);
    }
}

void LoadingDisplay::MakeTexture(std::string text)
{
    std::string path_font = RESOURCES_BASE_PATH + RESOURCES_FONT;
    TextRenderer text_renderer(path_font,96);

    SDL_Color color = {0, 0, 200, 255};
    SDL_Rect SrcR = { 0, 0, 0, 0 };
    SDL_Rect DestR = { 0, 0, 0, 0 };
    SDL_Texture* image;

    image = text_renderer.RenderText(text, color, m_renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = m_window_width / 2 -  SrcR.w / 2;
    DestR.y = m_window_height / 2 - SrcR.h / 2;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);
}
