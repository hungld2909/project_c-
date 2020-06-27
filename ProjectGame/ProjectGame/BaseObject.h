

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"
class BaseObject
{ 
 public:

	 BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);
	bool LoadImg(const char* file_name); 
	void SetRect(const int& x,const int& y){rect_.x = x, rect_.y = y;}
	SDL_Rect GetRect()const { return rect_; }
	SDL_Surface* GetObject() { return p_object_; } // trả ra đối tượng surface

   protected:
	SDL_Rect rect_; // muốn lấy các tham số này cần hàm set và get. tạo setRect
	SDL_Surface* p_object_;

};

#endif