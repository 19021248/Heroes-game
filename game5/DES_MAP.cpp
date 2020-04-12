#include"COMMON_OBJECT.h"
#include"DES_MAP.h"
#include"CommonFunc.h"

void HeroesMap::LoadMap(char *name)
{
	FILE* openfile = NULL;
	fopen_s(&openfile, name, "rb");
	if (openfile == NULL) {
		return;
	}
	// lazy foo
	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;

	for (int i = 0; i < MAP_ENDY; i++) {
		for (int j = 0; j < MAP_ENDX; j++) {
			fscanf_s(openfile, "%d", &game_map_.tile[i][j]);
			int val = game_map_.tile[i][j];
			if (val > 0) {
				if (j > game_map_.max_x_) {
					game_map_.max_x_ = j;
				}

				if (i > game_map_.max_y_){
					game_map_.max_y_ = i;

				}
			}
		}
	}
	game_map_.max_x_ = (game_map_.max_x_ + 1)*SIZE_DEF;
	game_map_.max_y_ = (game_map_.max_y_ + 1)*SIZE_DEF;

	game_map_.start_x_ = 0;
	game_map_.start_y_ = 0;

	game_map_.file_name_ = name;
	fclose(openfile);

}
// load  doi tuong
void HeroesMap::LoadTiles(SDL_Renderer* screen) {
	char file_img[30];
	FILE* openfile = NULL;

	for (int i = 0; i < ROW_MAX; i++) {
		sprintf_s(file_img, "map/%d.png", i);
		fopen_s(&openfile, file_img, "rb");

		if (openfile == NULL) {
			continue;
		}
		fclose(openfile);

		tile_mat[i].UPimage(file_img, screen);
	}
}

// ve map

void HeroesMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;
	int map_x = 0;
	int map_y = 0;
	map_y = game_map_.start_y_ / SIZE_DEF;
	int y1 = 0;
	int y2 = 0;
	x1 = (game_map_.start_x_%SIZE_DEF)*-1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : SIZE_DEF);
	
	y1 = (game_map_.start_y_%SIZE_DEF)*-1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : SIZE_DEF);

	for (int i = y1; i < y2; i += SIZE_DEF) {
		map_x = game_map_.start_x_ / SIZE_DEF;
		for(int j = x1; j < x2; j += SIZE_DEF) {
			int val = game_map_.tile[map_y][map_x];
			if (val > 0) {
				tile_mat[val].Rect_Res(j, i);
				tile_mat[val].Render(screen);
			}
			map_x++;
		} 
		map_y++;
	}
	
}