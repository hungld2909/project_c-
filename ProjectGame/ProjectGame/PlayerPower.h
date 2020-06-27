#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_
#include "BaseObject.h"
#include <vector>


class PlayerPower : public BaseObject
{
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num) {number_ = num; }
	void AddPost(const int& xpos);
	void Render(SDL_Surface* des); // hàm show tấm ảnh
	void Init(); // hàm khởi tạo những thông số ban đầu
	//hàm khi va trạm giảm số mạng
	void Decrease();

private:
	int number_;
	std::vector<int> post_list_;
};


#endif
