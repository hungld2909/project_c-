﻿#include "stdafx.h"  
#include "ThreatsObject.h"


// định nghĩa hàm contructer ở đây
ThreatsObject::ThreatsObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	//  khởi tạo ban đầu = 0
	x_val_ = 0;
	y_val_ = 0;
}
ThreatsObject:: ~ThreatsObject()
{
	if (p_amo_list_.size() > 0)
	{
		for (int i = 0; i < p_amo_list_.size(); i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear(); // giúp chương trình giải phóng toàn bộ bộ nhớ
		// khi dùng control có lưu là phải có delete phải lưu ý

	}

}
void ThreatsObject::InitAmo(AmoObject* p_amo)
{
	if (p_amo)
	{
		bool ret = p_amo->LoadImg("sphere.png");
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			p_amo->set_x_val(8);
			p_amo_list_.push_back(p_amo);
		}
	}
}
void ThreatsObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_litmit)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x,rect_.y + rect_.h*0.5); 
			}
		}
	}
}
void ThreatsObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;
		// tạo ra 1 biến random
		int rand_y = rand()%400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LITMIT_THREAT) // UNDER_LITMIT_THREAT bên file.h để k thể xuống kịch màn hình. xuống giới hạn 200
		{
			rand_y = SCREEN_HEIGHT * 0.3;
		}
		// sẽ gán 1 lượng
		rect_.y = rand_y;
	}

}
void ThreatsObject::HandleInputAction(SDL_Event events)
{

}
void ThreatsObject::Reset(const int& xborder)
{
	rect_.x = xborder;
	// tạo ra 1 biến random
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - UNDER_LITMIT_THREAT) // UNDER_LITMIT_THREAT bên file.h để k thể xuống kịch màn hình. xuống giới hạn 200
	{
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	// sẽ gán 1 lượng
	rect_.y = rand_y;
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			RetAmo(p_amo);
		}
	}
}
void ThreatsObject::RetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);

}