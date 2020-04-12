#include"CommonFunc.h"
#include"COMMON_OBJECT.h"
CommonObject::CommonObject() {
	picture_up = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

CommonObject::~CommonObject() {
	Free();
}

bool CommonObject::UPimage(std::string path, SDL_Renderer* screen) {

	SDL_Texture* new_pic = NULL;

	SDL_Surface* xuly_nen = IMG_Load(path.c_str());

	if (xuly_nen != NULL) {
		SDL_SetColorKey(xuly_nen, SDL_TRUE, SDL_MapRGB(xuly_nen->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_pic = SDL_CreateTextureFromSurface(screen, xuly_nen);
		if (new_pic != NULL) {
			rect_.w = xuly_nen->w;
			rect_.h = xuly_nen->h;
		}
		SDL_FreeSurface(xuly_nen);

	}

	picture_up = new_pic;
	return picture_up != NULL;
}
// lazyfoo

void CommonObject::Render(SDL_Renderer* des, const SDL_Rect*clip)
{
	SDL_Rect RDQ = {
		rect_.x, rect_.y, rect_.w, rect_.h 
	};

	SDL_RenderCopy(des, picture_up, clip, &RDQ);


}

void CommonObject::Free() {
	if (picture_up != NULL) {
		SDL_DestroyTexture(picture_up);

		picture_up = NULL;

		rect_.w = 0;

		rect_.h = 0;
	}
}


