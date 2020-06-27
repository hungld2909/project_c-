#include "stdafx.h" 
#include "PlayerPower.h"
PlayerPower::PlayerPower() // tao contructor
{

}	
PlayerPower::~PlayerPower()
{

}
//void PlayerPower::SetNumber(const int& num) {number_ = num; }
void PlayerPower::AddPost(const int& xpos)
{ // mỗi lần gọi hàm này là lưu lại cái list_push nó lại
	post_list_.push_back(xpos);
	// nếu có 3 mạng là 3 cái xpos
}

void PlayerPower::Render(SDL_Surface* des)
{
	// kiểm tra 3 mạng bằng 3 vị trí
	if (number_ == post_list_.size())
	{
		for (int i = 0; i < post_list_.size(); i++)
		{	
			rect_.x = post_list_.at(i);
			// gọi ham show
			Show(des);
;		}

	}
}
void PlayerPower::Init()
{ 
	LoadImg("player_power1.png");
	// gán giá trị 3 mạng 
	number_ = 3;
	// check 
	if (post_list_.size() > 0)
	{
		post_list_.clear();
	}
	AddPost(20);
	AddPost(60);
	AddPost(100);
}

// thời điểm ban đầu size sẽ bằng 0;
// nhưng khi chơi game nhiều Game0ver,lập đi lập lại thì pos_list nó vẫn tồn tại trước đó. phải xóa nó đi chạy lại từ đầu
// nếu tắt chương trình thì nó sẽ giải phóng.

void PlayerPower::Decrease()
{
	number_--;
	post_list_.pop_back();
	// pop_back là vị trí sẽ mất đi. sẽ xuất hiện lại về vị trí ban đầu
}