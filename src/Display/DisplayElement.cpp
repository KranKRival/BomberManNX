#include "Display/DisplayElement.h"

DisplayElement::DisplayElement(SDL_Texture* texture)
    : m_texture(texture)
{
}

DisplayElement::~DisplayElement()
{
}
