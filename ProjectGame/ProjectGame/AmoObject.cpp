#include "stdafx.h"   
#include "AmoObject.h"

AmoObject ::AmoObject() // định nghĩa contructor
{ 
	// gán 
	rect_.x = 0; 
	rect_.y = 0;
	x_val_ = 0;
	y_val = 0;
	is_move_ = false;
	amo_type_ = NONE;

}
AmoObject :: ~AmoObject()
{

}
void AmoObject::HandleInputAction(SDL_Event events)
{

}
void AmoObject::HandleMove(const int& x_border,const int& y_border) // border là độ rộng của màn hình
{
	rect_.x += x_val_; 
	if (rect_.x > x_border)
	{
		// kiểm tra nếu viện đạn đi ra hết khỏi màn hình tự động kết thúc. tránh bị tốn bộ nhớ
		is_move_ = false;
	}
	// đạn xe bắn theo chiều X. nếu muốn đạn bắn chiều khác hoặc bắn chéo thì thêm Y

}
void AmoObject::HandleMoveRightToLeft()
{
	rect_.x -= 8;
	if (rect_.x <0)
	{
		is_move_ = false;
	}
}
 