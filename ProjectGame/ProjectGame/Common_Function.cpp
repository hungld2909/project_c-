
#include "stdafx.h"   
#include "Common_Function.h"

//--------------------------------------------------------------------------------------
SDL_Surface* SDLCommonFunc :: LoadImage(std::string file_path)
{
	//Hàm này trả về là kiểu SDL Surface là một kiểu dữ liệu mà nó có thể tạo ra một surface image bao phủ lên màn hình windows.
	//Đối số đầu vào là tên của ảnh background.
	SDL_Surface *load_image = NULL;
	SDL_Surface *optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str()); //+ IMG_load sẽ thực hiện đọc file ảnh và trả về kết quả là kiểu dữ liệu SDL_Surface. 
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		// + Sau đó kết quả trả về được đưa vào hàm định dạng hiển thị SDL_DisplayFormat để tối ưu hóa surface cho phù hợp.
		SDL_FreeSurface(load_image);

	}
	if (optimize_image != NULL)
	{
		UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
		SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		// đoạn code này truyền màu giống với màu nên của nhân vật 
		// do ở trên tấm ảnh có mã màu background dạng hexa: 0,0xFF,0xFF do đó phải truyền SDL_MapRGB
		// do mã màu của background là 0 , 255, 255 chuyển sang hexa sẽ có dạng  0 , 0xFF, 0xFF.
	}
	return optimize_image;
}
//---------------------------------------------------------------------
void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	// hàm này dùng để set vụ nổ
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);

}

void SDLCommonFunc:: ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);

}
// xử lý va chạm
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

void SDLCommonFunc::CleanUp()
{ // giai phong bo nho
	// giải phóng các đối tượng
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

