#include "Display/MainMenuDisplay.h"
#include "System/TextRenderer.h"
#include "Display/GameDisplay.h"
#include "Display/LoadingDisplay.h"
#include "Display/PlayersNumberDisplay.h"
#include "Constants/ResourcesConstants.h"

//#define DEBUG_OUTPUT_MAIN_MENU_DISPAY

#ifdef DEBUG_OUTPUT_MAIN_MENU_DISPAY
#include <iostream>
#endif // DEBUG_OUTPUT_MAIN_MENU_DISPAY

MainMenuDisplay::MainMenuDisplay(SDL_Texture* texture,
                                 SDL_Renderer* renderer,
                                 unsigned int window_width,
                                 unsigned int window_height)
    : Display(),
      m_texture(texture),
      m_renderer(renderer),
      m_arrow(0),
      m_button_pressed_down(false),
      m_button_pressed_up(false),
      m_button_pressed_enter(false),
      m_window_width(window_width),
      m_window_height(window_height),
      m_players_number(1),
      m_music(nullptr),
      m_in_options(false)
{
    std::string path_font = RESOURCES_BASE_PATH + RESOURCES_FONT;
    TextRenderer text_renderer(path_font,64);

    SDL_Color color = {255, 0, 0, 255};
    SDL_Rect SrcR = { 0, 0, 0, 0 };
    SDL_Rect DestR = { 0, 0, 0, 0 };
    SDL_Texture* image;

    image = text_renderer.RenderText("NEW GAME", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = window_width / 2 -  SrcR.w / 2;
    DestR.y = window_height / 2 - SrcR.h / 2 - SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("OPTIONS", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("EXIT", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);

    m_arrow_texture = text_renderer.RenderText(">", color, renderer);
    SDL_QueryTexture(m_arrow_texture, NULL, NULL, &m_arrow_width, &m_arrow_height);

    std::string path_music = RESOURCES_BASE_PATH + RESOURCES_MUSIC_MENU;
    m_music = Mix_LoadMUS(path_music.c_str());
}

MainMenuDisplay::~MainMenuDisplay()
{
    for (auto i = m_textures.begin(); i != m_textures.end(); ++i)
    {
        SDL_DestroyTexture(*i);
    }
    SDL_DestroyTexture(m_arrow_texture);
    m_textures.clear();
    m_textures_draw_dest.clear();
    m_textures_draw_src.clear();
}

void MainMenuDisplay::Init()
{
    Mix_PlayMusic(m_music, -1);

    Enter();
}

void MainMenuDisplay::Enter(int mode)
{
    if (!m_in_options)
        Mix_PlayMusic(m_music, -1);
    else
    {
        m_in_options = false;
        m_players_number = mode;
    }

    m_leave_next = false;
    m_leave_previous = false;
    m_arrow = 0;
    m_button_pressed_down = false;
    m_button_pressed_up = false;
    m_button_pressed_enter = false;
}

void MainMenuDisplay::Leave()
{
    if (!m_in_options)
        Mix_HaltMusic();
}

int MainMenuDisplay::Destroy()
{
    Mix_HaltMusic();
    Mix_FreeMusic(m_music);

    for (auto i = m_textures.begin(); i != m_textures.end(); ++i)
    {
        SDL_DestroyTexture(*i);
    }
    SDL_DestroyTexture(m_arrow_texture);
    m_textures.clear();
    m_textures_draw_dest.clear();
    m_textures_draw_src.clear();
    return 0;
}

void MainMenuDisplay::Update()
{
    if (m_button_pressed_down && m_keyboard_input->IsKeyOn(15))
    {
        m_button_pressed_down = false;
        ++m_arrow;
        if (m_arrow >= (int)m_textures.size())
            m_arrow = 0;
    }
    if (m_button_pressed_up && m_keyboard_input->IsKeyOn(13))
    {
        m_button_pressed_up = false;
        --m_arrow;
        if (m_arrow < 0)
            m_arrow = m_textures.size() - 1;
    }
    if (m_button_pressed_enter && m_keyboard_input->IsKeyOn(10))
    {
        switch(m_arrow)
        {
        case 0:
            m_next_display = new LoadingDisplay(m_texture,m_renderer,m_window_width,m_window_height,m_players_number,RESOURCES_LEVEL_COUNT);
            m_in_options = false;
            m_leave_next = true;
            break;
        case 1:
            m_next_display = new PlayersNumberDisplay(m_renderer,m_window_width,m_window_height);
            m_in_options = true;
            m_leave_next = true;
            break;
        case 2:
            m_leave_previous = true;
            break;
        default:
            break;
        }
    }

    if ( !(m_keyboard_input->IsKeyOn(15)) )
        m_button_pressed_down = true;
    if ( !(m_keyboard_input->IsKeyOn(13)) )
        m_button_pressed_up = true;
    if ( !(m_keyboard_input->IsKeyOn(10)) )
        m_button_pressed_enter = true;
}

void MainMenuDisplay::Draw(SDL_Renderer* renderer) const
{
    #ifdef DEBUG_OUTPUT_MAIN_MENU_DISPAY
    std::cout << "MainMenuDisplay arrow: " << m_arrow << std::endl;
    #endif // DEBUG_OUTPUT_MAIN_MENU_DISPAY
    for (unsigned int i=0; i<m_textures.size(); ++i)
    {
        SDL_RenderCopy(renderer,m_textures[i],&m_textures_draw_src[i],&m_textures_draw_dest[i]);
    }
    SDL_Rect SrcR;
    SrcR.h = m_arrow_height;
    SrcR.w = m_arrow_width;
    SrcR.x = 0;
    SrcR.y = 0;
    SDL_Rect DestR;
    DestR.h = m_arrow_height;
    DestR.w = m_arrow_width;
    DestR.x = m_textures_draw_dest[m_arrow].x-m_arrow_width-50;
    DestR.y = m_textures_draw_dest[m_arrow].y;
    SDL_RenderCopy(renderer,m_arrow_texture,&SrcR,&DestR);
}

