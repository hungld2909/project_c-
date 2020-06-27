﻿
#ifndef THREATS_OBJECT_H
#define THREATS_OBJECT_H
#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33
const int UNDER_LITMIT_THREAT = 200;
class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();
	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);
	// tạo 2 hàm set get để sử dụng
	void set_x_val(const int& val) { x_val_ = val; }
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }
	void SetAmolist(std::vector<AmoObject*>amo_list) { p_amo_list_ = amo_list; }
	std::vector<AmoObject*> GetAmolist() const { return p_amo_list_; }
	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des,const int& x_limit,const int& y_litmit); // ban dan ra.
	void Reset(const int& xborder);
	void RetAmo(AmoObject* p_amo); // reset viên đạn thì phải chuyền vào biến viên đạn là AmoObject
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;
};

#endif 