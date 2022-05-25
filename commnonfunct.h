#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_


#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <wchar.h>
#define TILE_SIZE 64
#define MAX_MAP_X 400 //400
#define MAX_MAP_Y 10 //10
#define BLANK_TILE 0
#define GRASS 6

#define STATE_MONEY 4

#define BULLET_COUNT_X2 10
#define BULLET_COUNT_X3 11

using namespace std;

static SDL_Window* win = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Renderer* g_menu = NULL;
static SDL_Event g_e;
static Mix_Chunk* g_sound_bullet[5];
static Mix_Chunk* g_sound_exp[2];
static Mix_Music* g_sound_gameplay[1];
static bool start = false;

const int FRAME_PER_SEC = 20; //25
const int width = 1280;//1280
const int height = 640;//640
const int BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int Render_draw_color =0xff;


struct input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
    int fall;
};

struct Map
{
    int start_x;
    int start_y;


    int max_x;
    int max_y;


    int tile[MAX_MAP_Y][MAX_MAP_X];
    string file_name;
};

namespace SDLCommonfunc
{
    bool checkcollision(const SDL_Rect& object1, const SDL_Rect& object2);

};


#endif