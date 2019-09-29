#ifndef RESOURCESCONSTANTS_H_INCLUDED
#define RESOURCESCONSTANTS_H_INCLUDED

#include <string>


static const std::string RESOURCES_BASE_PATH        = "resources/";
static const std::string RESOURCES_LEVELS_PATH      = "resources/levels/";

static const std::string RESOURCES_TEXTURES         = "textures.bmp";
static const std::string RESOURCES_FONT             = "Zabdilus.ttf";
static const std::string RESOURCES_MUSIC_GAME       = "game-play-normal.mp3";
static const std::string RESOURCES_MUSIC_MENU       = "title-screen.mp3";
static const std::string RESOURCES_MUSIC_LOAD       = "get-ready.mp3";
static const unsigned int RESOURCES_MUSIC_LOAD_TIME = 3100;
static const std::string RESOURCES_EXPLOSION_LOAD   = "explosion.wav";
static const std::string RESOURCES_KILL_LOAD        = "neck-snap.wav";

static const std::string RESOURCES_LEVEL_MAP        = "level";
static const std::string RESOURCES_LEVEL_MAP_EXT    = ".txt";
static const std::string RESOURCES_LEVEL_ENEMY      = "enemy";
static const std::string RESOURCES_LEVEL_ENEMY_EXT  = ".txt";
static const std::string RESOURCES_LEVEL_PLAYER     = "player";
static const std::string RESOURCES_LEVEL_PLAYER_EXT = ".txt";
static const unsigned int RESOURCES_LEVEL_COUNT     = 10;

#endif // RESOURCESCONSTANTS_H_INCLUDED
