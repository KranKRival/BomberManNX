#include "Display/PlayersNumberDisplay.h"
#include "System/TextRenderer.h"
#include "Constants/ResourcesConstants.h"

PlayersNumberDisplay::PlayersNumberDisplay(SDL_Renderer* renderer,
                                           unsigned int window_width,
                                           unsigned int window_height)
    : Display(),
      m_renderer(renderer),
      m_arrow(0),
      m_button_pressed_down(false),
      m_button_pressed_up(false),
      m_button_pressed_enter(false),
      m_window_width(window_width),
      m_window_height(window_height)
{
    std::string path_font = RESOURCES_BASE_PATH + RESOURCES_FONT;
    TextRenderer text_renderer(path_font,64);

    SDL_Color color = {255, 0, 0, 255};
    SDL_Rect SrcR = { 0, 0, 0, 0 };
    SDL_Rect DestR = { 0, 0, 0, 0 };
    SDL_Texture* image;

    image = text_renderer.RenderText("CHOOSE NUMBER OF PLAYERS", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = window_width / 2 -  SrcR.w / 2;
    DestR.y = window_height / 2 - SrcR.h / 2 - SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("One Player", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = window_width / 2 -  SrcR.w / 2;
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("Two Players (Not working yet)", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    m_textures.push_back(image);
    m_textures_draw_src.push_back(SrcR);
    m_textures_draw_dest.push_back(DestR);

    m_arrow_texture = text_renderer.RenderText(">", color, renderer);
    SDL_QueryTexture(m_arrow_texture, NULL, NULL, &m_arrow_width, &m_arrow_height);

}

PlayersNumberDisplay::~PlayersNumberDisplay()
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

void PlayersNumberDisplay::Init()
{
    Enter();
}

void PlayersNumberDisplay::Enter(int mode)
{
    m_leave_next = false;
    m_leave_previous = false;
    m_arrow = 1;
    m_button_pressed_down = false;
    m_button_pressed_up = false;
    m_button_pressed_enter = false;
}

void PlayersNumberDisplay::Leave()
{

}

int PlayersNumberDisplay::Destroy()
{
    for (auto i = m_textures.begin(); i != m_textures.end(); ++i)
    {
        SDL_DestroyTexture(*i);
    }
    SDL_DestroyTexture(m_arrow_texture);
    m_textures.clear();
    m_textures_draw_dest.clear();
    m_textures_draw_src.clear();
    return m_players_selected;
}

void PlayersNumberDisplay::Update()
{
   if (m_button_pressed_down && m_keyboard_input->IsKeyOn(15))
    {
        m_button_pressed_down = false;
        ++m_arrow;
        if (m_arrow >= (int)m_textures.size())
            m_arrow = 1;
    }
    if (m_button_pressed_up && m_keyboard_input->IsKeyOn(13))
    {
        m_button_pressed_up = false;
        --m_arrow;
        if (m_arrow < 1)
            m_arrow = m_textures.size() - 1;
    }
    if (m_button_pressed_enter && m_keyboard_input->IsKeyOn(10))
    {
        switch(m_arrow)
        {
        case 0:
        case 1:
            m_players_selected = 1;
            m_leave_previous = true;
            break;
        case 2:
            m_players_selected = 2;
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

void PlayersNumberDisplay::Draw(SDL_Renderer* renderer) const
{
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
