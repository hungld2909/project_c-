#include "stdafx.h"  
#include "ExplosionObject.h"




 ExplosionObject::ExplosionObject()
{
	 frame_ = 0;


}
 ExplosionObject ::~ExplosionObject()
 {

 }
 void ExplosionObject::set_clips()
 {// clip the sprites
	 clip_[0].x = 0;
	 clip_[0].y = 0;
	 clip_[0].w = EXPLOSION_WIDTH;
	 clip_[0].h = EXPLOSION_HEIGHT;

	 clip_[1].x = EXPLOSION_WIDTH;
	 clip_[1].y = 0;
	 clip_[1].w = EXPLOSION_WIDTH;
	 clip_[1].h = EXPLOSION_HEIGHT;

	 clip_[2].x = EXPLOSION_WIDTH * 2;
	 clip_[2].y = 0;
	 clip_[2].w = EXPLOSION_WIDTH;
	 clip_[2].h = EXPLOSION_HEIGHT;

	 clip_[3].x = EXPLOSION_WIDTH * 3;
	 clip_[3].y = 0;
	 clip_[3].w = EXPLOSION_WIDTH;
	 clip_[3].h = EXPLOSION_HEIGHT;

}

void ExplosionObject:: move()
{

}
	

void ExplosionObject::ShowEx(SDL_Surface* des)
{
	if (frame_ >= 4)
	{
		frame_ = 0;
		
	}
	SDLCommonFunc::ApplySurfaceClip(this->p_object_,des,&clip_[frame_],rect_.x, rect_.y);
}