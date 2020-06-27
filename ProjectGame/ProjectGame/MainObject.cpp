#include "stdafx.h"   
#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val = 0;


}
MainObject::~MainObject()
{

}
void MainObject::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN) // bắt xự kiện bàn phím được ấn xuống hoặc thả ra	
	{
		switch (events.key.keysym.sym)

		{
		case SDLK_UP:
			y_val-= HEIGHT_MAIN_OBJECT / 6; // kích thước của đối tượng chia cho 6. để duy chuyển trên màn hình.
			// đây là lượng trên màn hình. để máy bay di chuyển nhanh hay chậm tùy thuộc vào cái này. 
				break;
		case SDLK_DOWN:
			// nếu ấn xuống thì phải tăng lên. 
			y_val += HEIGHT_MAIN_OBJECT / 6; // nếu bấm xuống thì được + lên.
				break;
		case SDLK_LEFT:
			x_val_-= WIDTH_MAIN_OBJECT / 6;
				break;
		case SDLK_RIGHT:
			x_val_+= WIDTH_MAIN_OBJECT / 6;
				break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		// hàm này để giúp ấn đi từng bước 1.
		// nếu không có hàm này máy bay tự động chạy từ đầu màn hình về tới cuối màn hình.
		switch (events.key.keysym.sym)
		{
			// ở trên là dấu + ở dưới phải là dấu -
		case SDLK_UP: y_val += HEIGHT_MAIN_OBJECT / 6; break;
		case SDLK_DOWN: y_val -= HEIGHT_MAIN_OBJECT / 6; break;
		case SDLK_LEFT: x_val_ += WIDTH_MAIN_OBJECT / 6; break;
		case SDLK_RIGHT: x_val_ -= WIDTH_MAIN_OBJECT / 6; break;

		default:
			break;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		// xử lý chuột. khi chuột bấm xuống thì 1 viên đạn được sinh ra.
		AmoObject* p_amo = new AmoObject();
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->setWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg("laser.png");
			p_amo->set_type(AmoObject::LASER);
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_amo->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg("sphere.png");
			p_amo->set_type(AmoObject::SPHERE);
		}
		// đạn bắn ra từ đầu máy bay. tính lượng để sao cho bạn bắn ra ở giữa đầu máy bay.
		p_amo->SetRect(this->rect_.x + this->rect_.w - 10, this->rect_.y + this->rect_.h*0.5);
		p_amo->set_is_move(true);
		p_amo->set_x_val(20);
		p_amo_list_.push_back(p_amo);
	}
	else
	{
		// todo 
	}

}
void MainObject::MakeAmo(SDL_Surface* des)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo != NULL)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if (p_amo != NULL)
				{
					p_amo_list_.erase(p_amo_list_.begin() + i);
					
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}

void MainObject:: HandleMove()
{
	rect_.x += x_val_;
	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
	{
		rect_.x -= x_val_; // nếu mà lùi sát vào màn hình nó kiểm tra  < 0 thì nó lai ++ lại vị trí cũ.

	}
	rect_.y += y_val;
	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT -100) 
	// trừ 200 ở đây là k cho máy bay bay ở sát mặt đất. trừ khoảng cách height 100
	{
		rect_.y -= y_val;
	}
}
// remove 1 viên đạn 
void MainObject::RemoveAmo(const int& idx)
{
	
	
		for (int i = 0; i < p_amo_list_.size(); i++)
		{
			if (idx < p_amo_list_.size())
			{
				AmoObject* p_amo = p_amo_list_.at(idx);
				// xog sau đó xóa đối tượng ra khỏi danh sách.
				p_amo_list_.erase(p_amo_list_.begin() + idx);
				if (p_amo != NULL)
				{
					delete p_amo;
					p_amo = NULL;
				}
			}
	}
	
	
}