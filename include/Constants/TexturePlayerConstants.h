#ifndef TEXTUREPLAYERCONSTANTS_H_INCLUDED
#define TEXTUREPLAYERCONSTANTS_H_INCLUDED

/* Player Textures */
static const unsigned int TEXTURE_PLAYER_SIZE_W = 17;
static const unsigned int TEXTURE_PLAYER_SIZE_H = 23;
static const unsigned int TEXTURE_PLAYER_SOURCE_W = 18;
static const unsigned int TEXTURE_PLAYER_SOURCE_H = 32;
static const unsigned int TEXTURE_PLAYER_X = 1;
static const unsigned int TEXTURE_PLAYER_Y = 4;
static const unsigned int TEXTURE_PLAYER_SOURCE_CONST = 6; //SOURCE_CONST=4 + SOURCE_W + 2;
static const unsigned int TEXTURE_PLAYER_MAIN_SOURCE_OFFSET = 568;
static const unsigned int TEXTURE_PLAYER_MINI_SOURCE_OFFSET = 3;
static const unsigned int TEXTURE_PLAYER_TEXTURE_OFFSET = TEXTURE_PLAYER_SOURCE_CONST
                                                            + TEXTURE_PLAYER_SOURCE_W;

#endif // TEXTUREPLAYERCONSTANTS_H_INCLUDED
