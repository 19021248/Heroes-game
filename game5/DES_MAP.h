#pragma once
#ifndef  DES_MAP_H_
#define  DES_MAP_H_


#include"COMMON_OBJECT.h"
#include"CommonFunc.h"

#define ROW_MAX 10 // number of rows
class TileMat : public CommonObject {
public:
	TileMat() { ; }
	~TileMat() { ; }
};


class HeroesMap {
public:
	HeroesMap() { ; }
	~HeroesMap() { ; }

	void LoadMap(char * name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);

	Map getMap() const {
		return game_map_;
	};


private:
	Map game_map_;
	// LOAD CAC DOI TUONG
	TileMat tile_mat[ROW_MAX];
};


#endif 
