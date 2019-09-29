#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

/**
 *  \file TextRenderer.h
 *
 *  Defines class TextRenderer which uses SDL_ttf library extension to make
 *  textures out of strings.
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

/** \class TextRenderer
 *  \brief Class which makes textures out of given string.
 *  \details This class is used to to make an SDL_Texture out of a custom string
 *           in the given font and font size. Path to truetype font file must
 *           be provided.
 */
class TextRenderer
{
    public:

        /**
         *  \brief Constructor for TextRenderer
         *
         *  Makes an object of class TextRenderer with the given font file as
         *  well as size so that the call of method RenderText() for that
         *  instance will make texture in given font and size.
         *  \param font_file reference to string which keeps relative path to
         *        font file (.ttf or .otf) from the program's working directory
         *  \param font_size integer value which represents font size in pixels.
         */
        TextRenderer(const std::string &font_file, unsigned int font_size);
        /**
         *  \brief Destructor for TextRenderer
         *
         *  Closes opened TTF font.
         */
        ~TextRenderer();
        TextRenderer(const TextRenderer& other) = delete; /**< \brief Default copy constructor is disabled */
        TextRenderer& operator=(const TextRenderer&) = delete; /**< \brief Default operator = is disabled */

        /**
         *  \brief Returns pointer to SDL_Texture which is an image of given
         *         string in given color
         *
         *  \param message reference to string which is going to be turned into
         *         texture
         *  \param color RGBA of the color of texture (RGBA = Red, Green, Blue,
         *         Alpha). Value range is 0-255
         *  \param renderer pointer to SDL_Renderer which is used as context for
         *         rendering a texture; keeps settings for rendering
         *  \return SDL_Texture* pointer to SDL_Texture of the given string
         *
         */
        SDL_Texture* RenderText(const std::string &message, SDL_Color color, SDL_Renderer *renderer);

    protected:

    private:
        TTF_Font*       m_font;
};

#endif // TEXTRENDERER_H
