
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#undef main


// khai báo biến const để định dạng các thông số cố định. 
const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 4; // khai báo số lượng máy bay địch chạy trên màn hình.

 static SDL_Surface *g_screen = NULL;
 static SDL_Surface *g_bkground = NULL;
 static SDL_Event g_even;

namespace SDLCommonFunc // dùng namespace tránh trùng lặp dữ liệu.
{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp(); \
		// xử lý va chạm
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2); // kiểm tra va chạm
	// định nghĩa SDL_SURFACE cho vụ nổ
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
}

#endif