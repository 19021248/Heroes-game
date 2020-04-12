#include"COMMON_OBJECT.h"
#include"CommonFunc.h"
#include"DES_MAP.h"
#include"PLAYER.h"

#define BLANK_TILE 0 // o trong khoang khong
#define Jumpp 1.0
#define MAX_FALL_SPEED 5
#define PLAYER_SPEED 5
Player::Player() {
	frame_ = 0;
	x_pos_ = 0;
	y_pos_= 0;
	x_val_ = 0;
	y_val_= 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	check_ground = false;

}

Player::~Player() {

}

bool Player::UPimage(std::string path, SDL_Renderer* screen) {
	bool ret = CommonObject::UPimage(path, screen);
	if (ret == true) {
		width_frame_ = rect_.w / 8; // 8 frame;
		height_frame_ = rect_.h;

	}
	return ret;
}

void Player::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2*width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3*width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4*width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5*width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6*width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7*width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;

	}
}
// animation wiki
void Player::Show(SDL_Renderer* des) {
	if (status_ == WALK_LEFT) {
		UPimage("player/leftside2.png", des); // load anh trong file;
	}
	else {
		UPimage("player/rightside2.png", des);
	}

	if (input_type_.left_ == 1 || input_type_.right_ == 1) {
		frame_++;
	}
	else {
		frame_ = 0;
	}
	if (frame_ >= 8) {
		frame_ = 0;
	}
	rect_.x = x_pos_; // vi tri hien thi nhan vat
	rect_.y = y_pos_; // vi tri hien thi nhan vat

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect RDQ = { rect_.x, rect_.y, width_frame_, height_frame_ };
	// cho len man hinh
	SDL_RenderCopy(des, picture_up, current_clip, &RDQ);
}

void Player::xulyhanhdong(SDL_Event events, SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT: {
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
		}
						 break;
		case SDLK_LEFT: {
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
		}
						break;

		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT: {
			input_type_.right_ = 0;
		}
						 break;
		case SDLK_LEFT: {
			input_type_.left_ = 0;
		}
			break;
		}

	}
}

void Player::SetPlay(Map& map_data) {
	x_val_ = 0;
	y_val_ += 0.8;

	if (y_val_ >= MAX_FALL_SPEED) {
		y_val_ = MAX_FALL_SPEED;
	}

	if (input_type_.left_ == 1) {
		x_val_ -= PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1) {
		x_val_ += PLAYER_SPEED;
	}
	MapClash(map_data);

}

void Player::MapClash(Map& map_data) {
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	// x_pos_ y_pos_ toa do nhan vat


	// check chieu ngang
	int height_min = height_frame_ < SIZE_DEF ? height_frame_ : SIZE_DEF;
	x1 = (x_pos_ + x_val_) / SIZE_DEF; // start pos
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / SIZE_DEF; // di chn den o thu bao nhieu theo chieu ngang
	
	y1 = (y_pos_) / SIZE_DEF;
	y2 = (y_pos_ + height_min - 1) / SIZE_DEF; // o thu bao nhieu theo chieu doc

	if (x1 >= 0 && x2 < MAP_ENDX && y1 >= 0 && y2 < MAP_ENDY) {
		if (x_val_ > 0) {// move right;
				if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
					x_pos_ = x2 * SIZE_DEF; // dung khi gap va cham
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;
				}

		}
		else if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
				x_pos_ = (x1 + 1)*SIZE_DEF;
				x_val_ = 0;
			}

		}
	}

// check chieu doc
	
	int width_min = width_frame_ < SIZE_DEF ? width_frame_ : SIZE_DEF;
	x1 = (x_pos_) / SIZE_DEF;
	x2 = (x_pos_ + width_frame_) / SIZE_DEF;

	y1 = (y_pos_ + y_val_) / SIZE_DEF;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / SIZE_DEF;

	if (x1 >= 0 && x2 < MAP_ENDX && y1 >= 0 && y2 < MAP_ENDY) {
		if (y_val_ > 0) {
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2]!=BLANK_TILE){
				y_pos_ = y2 * SIZE_DEF;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				check_ground = true;

			}

		}
		else if (y_val_ < 0) {
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
				y_pos_ = (y1 + 1)*SIZE_DEF;
				y_val_ = 0;
			}
		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}





}
