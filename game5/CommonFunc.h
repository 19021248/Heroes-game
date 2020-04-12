
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_
#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>



static SDL_Window* g_window = NULL; // màn hình
static SDL_Renderer* g_screen = NULL; // vẽ màn hình
static SDL_Event  g_event; // xu ly su kien

// Screen
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 1280;
const int SCREEN_BPP = 32;

const int BASIC_COL = 255;
const int COLOR_KEY_R = 200;
const int COLOR_KEY_G = 191;
const int COLOR_KEY_B = 231;


#define SIZE_DEF 64
#define MAP_ENDX 20
#define MAP_ENDY 10


// design map

typedef struct Map {
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile [MAP_ENDY][MAP_ENDX];
	char * file_name_;
};

// xu ly nhan vat
typedef struct Input {
	int left_;
	int right_;
	int down_;
	int up_;
	int jump_;
};




#endif