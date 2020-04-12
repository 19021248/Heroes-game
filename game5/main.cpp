#include<iostream>
#include"CommonFunc.h"
#include"COMMON_OBJECT.h"
#include"DES_MAP.h"
#include"PLAYER.h"
using namespace std;


// ham thiet lap
bool initData() {
	bool success = true;
	int  ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Do Dai Duong screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == NULL) {
		success = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			success = false;
		else {
			SDL_SetRenderDrawColor(g_screen, BASIC_COL, BASIC_COL, BASIC_COL, BASIC_COL);
			int  imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
				success = false;
		}
	}
	return success;
}
// lazy foo

CommonObject g_background;
bool LoadBackground(){
	bool ret = g_background.UPimage("bkg3.1.bmp", g_screen);
	if (ret == false) {
		return false;
	}
	return true;
}
// lazy foo


void close() {
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();

}
// lazy foo


#undef main
int main(int argc, char* argv[]) {
	if (initData() == false)
		return -1;

	if (LoadBackground() == false)
		return -1;
	int test_init = 1;

	HeroesMap game_map;
	game_map.LoadMap((char*) "map/H_map.dat");
	game_map.LoadTiles(g_screen);


	Player Ben10;
	Ben10.UPimage("player/rightside2.png", g_screen);
	Ben10.set_clips();


	
	while (test_init==1) {
		
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				test_init = 2;
				
			}
			Ben10.xulyhanhdong(g_event, g_screen);

		}
		SDL_SetRenderDrawColor(g_screen, BASIC_COL, BASIC_COL, BASIC_COL, BASIC_COL);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL); 
		game_map.DrawMap(g_screen); 
		Map map_data = game_map.getMap();


		Ben10.SetPlay(map_data);
		Ben10.Show(g_screen);
		SDL_RenderPresent(g_screen);

	}
	close();
	return 0;
}
