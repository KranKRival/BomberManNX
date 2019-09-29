#include "Display/WelcomeDisplay.h"
#include "Display/MainMenuDisplay.h"
#include <SDL2/SDL.h>
#include "System/TextRenderer.h"
#include "Constants/ResourcesConstants.h"

#include <iostream>

WelcomeDisplay::WelcomeDisplay(SDL_Texture* texture,
                               SDL_Renderer* renderer,
                               unsigned int window_width,
                               unsigned int window_height)
    : Display(),
      m_texture(texture),
      m_renderer(renderer),
      m_pressed_next(false),
      m_pressed_previous(false),
      m_window_width(window_width),
      m_window_height(window_height)
{
    std::string path_font = RESOURCES_BASE_PATH + RESOURCES_FONT;
    TextRenderer text_renderer(path_font,96);
    SDL_Color color = {0, 255, 0, 255};
    SDL_Rect SrcR = { 0, 0, 0, 0 };
    SDL_Rect DestR = { 0, 0, 0, 0 };
    SDL_Texture* image;

    image = text_renderer.RenderText("WELCOME TO BOMBERMAN NX", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = window_width / 2 -  SrcR.w / 2;
    DestR.y = window_height / 2 - SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("Press ( + ) to start", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = DestR.x + (DestR.w-SrcR.w) / 2;
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);
}

WelcomeDisplay::~WelcomeDisplay()
{
    Destroy();
}

void WelcomeDisplay::Enter(int mode)
{
    m_leave_previous = true;
    m_leave_next = false;
}

void WelcomeDisplay::Leave()
{
    Destroy();
}

int WelcomeDisplay::Destroy()
{
    for (auto i = m_textures.begin(); i != m_textures.end(); ++i)
    {
        SDL_DestroyTexture(*i);
    }
    m_textures.clear();
    m_textures_draw_src.clear();
    m_textures_draw_dest.clear();
    return 0;
}

void WelcomeDisplay::Update()
{
    if (m_pressed_next && m_keyboard_input->IsKeyOn(10))
    {
        m_pressed_next = false;
        m_next_display = new MainMenuDisplay(m_texture,m_renderer,m_window_width,m_window_height);
        m_leave_next = true;
    }
    if (m_pressed_previous && m_keyboard_input->IsKeyOn(11))
    {
        m_pressed_previous = false;
        m_leave_previous = true;
    }

    if ( !(m_keyboard_input->IsKeyOn(10)) )
        m_pressed_next = true;
    if ( !(m_keyboard_input->IsKeyOn(11)) )
        m_pressed_previous = true;
}

void WelcomeDisplay::Draw(SDL_Renderer* renderer) const
{
    for (unsigned int i=0; i<m_textures.size(); ++i)
    {
        SDL_RenderCopy(renderer,m_textures[i],&m_textures_draw_src[i],&m_textures_draw_dest[i]);
    }
}
