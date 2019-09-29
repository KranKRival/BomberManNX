#include "System/TextRenderer.h"

#ifdef DEBUG_OUTPUT_TEXT_RENDERER
#include <iostream>
#endif // DEBUG_OUTPUT_TEXT_RENDERER

TextRenderer::TextRenderer(const std::string &font_file, unsigned int font_size)
    : m_font(nullptr)
{
    m_font = TTF_OpenFont(font_file.c_str(), font_size);
	if (m_font == nullptr){
        #ifdef DEBUG_OUTPUT_TEXT_RENDERER
		std::cout << "TTF_OpenFont" << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_TEXT_RENDERER
	}
}

TextRenderer::~TextRenderer()
{
    #ifdef DEBUG_OUTPUT_TEXT_RENDERER
    std::cout << "Text Renderer: Closed Font" << std::endl;
    #endif // DEBUG_OUTPUT_TEXT_RENDERER
    TTF_CloseFont(m_font);
}

SDL_Texture* TextRenderer::RenderText(const std::string &message, SDL_Color color, SDL_Renderer *renderer)
{
    if (m_font == nullptr)
	{
		return nullptr;
	}
        

	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(m_font, message.c_str(), color);
	if (surf == nullptr){
        #ifdef DEBUG_OUTPUT_TEXT_RENDERER
		std::cout << "TTF_RenderText_Blended" << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_TEXT_RENDERER
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
        #ifdef DEBUG_OUTPUT_TEXT_RENDERER
		std::cout << "CreateTexture" << SDL_GetError() << std::endl;
        #endif // DEBUG_OUTPUT_TEXT_RENDERER
        return nullptr;
	}

	SDL_FreeSurface(surf);
	return texture;
}
