#pragma once

#ifndef COMMON_OBJECT_H_
#define COMMON_OBJECT_H_

#include"CommonFunc.h"
class CommonObject {
	public:
		CommonObject(); // constructor
		 
		~CommonObject(); // destructor


		void Rect_Res(const int& x, const int& y) {
			rect_.x = x;
			rect_.y = y;
		}

		void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
		
		SDL_Texture* GetObject() const {
			return  picture_up; 
		}

		virtual bool UPimage(std::string path, SDL_Renderer*);

		SDL_Rect GetRect() const { 
			return rect_; 
		}

		void Free();


	protected:
		SDL_Texture* picture_up;
		SDL_Rect rect_;
};



#endif