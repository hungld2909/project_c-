
#include "stdafx.h"   
#include "BaseObject.h"


// gọi hàm contruct
BaseObject::BaseObject()  
{
	
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}

BaseObject::~BaseObject()
{
	if (p_object_ != NULL)
	{
		SDL_FreeSurface(p_object_); // delete đối tượng này
	}

}
// p_object là đích
void BaseObject::Show(SDL_Surface * des)
{
	if (p_object_ != NULL)
	{
		SDLCommonFunc::ApplySurface(p_object_, des, rect_.x,rect_.y);
	}

}
bool BaseObject::LoadImg(const char* file_name)
{
	p_object_ = SDLCommonFunc::LoadImage(file_name);
	if (p_object_ == NULL)
		return false;
	return true;

}

//header la khoi tao, khai bao
//con copp la dinh nghia
//
//neu ko co cpp, thi ben header se bao xanh, y la chua dinh nghia ham nay
//
//con bên cpp ma viet sai, no sai bao, class ko co ham do
//nen neu viet sai ten ben cpp thi cpp vua bao class ko co ham, ma header cung bao ham chua dc dinh nghia