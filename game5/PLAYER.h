#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include"COMMON_OBJECT.h"
#include"CommonFunc.h"
#include"DES_MAP.h"

class Player : public CommonObject {
public:
	Player();
	~Player();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,

	};
	//load anh
	bool UPimage(std::string path, SDL_Renderer* screen);
	// show frame
	void Show(SDL_Renderer*des);
	void xulyhanhdong(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void SetPlay(Map& map_data); // SetPlay = Doplayer // map_data= map end
	void MapClash(Map& map_data); // MapClash= CheckToMap
private:

	float x_val_; // di chn phai bao nhieu
	float y_val_; // di chn xuong bao nhieu
	//vi tri hien tai
	float x_pos_; 
	float y_pos_;
	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	bool check_ground;

	Input input_type_;
	int frame_; // 1 2 3 4 5 6 7 8;
	int status_; // luu trang thai when click button

};
 


#endif