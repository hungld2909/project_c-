
#include "stdafx.h"
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"


bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}
	return true;

}

int main(int arc,char* argv[])
{
	bool is_run_screen = true;
	int bkgn_x = 0;
	bool is_quit = false;
	if (Init() == false)
		return 0;
	g_bkground = SDLCommonFunc::LoadImage("bg4800.png");
	// kiểm tra nó có Null hay không nếu = 0 return Null
	if (g_bkground == NULL)
	{
		return 0;
	}
	//make player power
	PlayerPower player_power;
	//bản chất là load 1 tấm ảnh trên màn hình screen. nhưng ở đây chúng ta load 3 tấm ảnh ở 3 vị liên tiếp nhau.
	player_power.Init();
	
	// make MainObject

	MainObject human_object;
	// muốn sét vị trí nó xuất hiện dùng hàm setRect() của lớp cha BaseObject
	human_object.SetRect(200, 100);
	bool ret = human_object.LoadImg("plane_fly.png");
	// xét vị trí xuất hiện trên màn hình
	if(!ret)
	{
		return 0;
	}
	// khai báo vụ nổ ở đây
	ExplosionObject exp_threats;
	ExplosionObject exp_main;
	ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clips();
	if (ret == false) return 0;


	// khai báo số lượng máy bay dịch trên mà hình
	ThreatsObject* p_threats = new ThreatsObject[NUM_THREATS];
	for (int t = 0; t < NUM_THREATS; t++)
	{
		ThreatsObject* p_threat = (p_threats + t); // khởi tạo 1 đối tượng ở đây
		if (p_threat)
		{
			// Make ThreatsObject
			
			ret = p_threat->LoadImg("af1.png");
			// kiểm tra nếu nó không tìm thấy ảnh thì return = 0. k cho chạy chương trình
			if (ret == false)
			{
				return 0;
			}
			// giúp đối tượng xuất hiện ở 1 vị trí ngẫu nhiên trên màn hình

			int rand_y = rand() % 400;
			if (rand_y > SCREEN_HEIGHT - 200)
			{
 				rand_y = SCREEN_HEIGHT * 0.3;
			}
			p_threat->SetRect(SCREEN_WIDTH + t * 400, rand_y);
			p_threat->set_x_val(4); // tốc độ máy bay địch chạy

			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
			// nap dan cho doi tuong cua minh
			//-------------------------
		}
	}
	// chơi  3 mạng mới game over.
	unsigned int die_number = 0;

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			human_object.HandleInputAction(g_even); // di chuyển. MainObject
		}

		//*Apply background
		// WAY 1: nối 2 ảnh vào 1 màn hình*/
		//bkgn_x -= 2;   // cứ mỗi lần lặp lại trừ đi 1 lượng của màn hình.
		//SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0); // với mỗi lần thay đổi vị trí thì phải upload lại ảnh background
		//SDLCommonFunc::ApplySurface(g_bkground,g_screen,bkgn_x + SCREEN_WIDTH,0); // sau đó apply thêm 1 hình nền backgroad nữa.
		//if (bkgn_x <= -SCREEN_WIDTH)/* nếu nó đi hết 1 lượng -SCREEN_WIDTH thì lại đưa nó về màn hình lúc ban đầu*/
		//{
		//	bkgn_x = 0;
		//}


		/*Way 2:*/
		if (is_run_screen == true) // nếu bằng true thì chạy tiếp.
		{
			bkgn_x -= 2;
			if (bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH)) // nếu nó bằng false thì chạy tới đoạn ảnh cuối cùng và dừng ở đấy. làm ảnh background
			{			// chạy 3 phiên và dừng lại phiên cuối.
				is_run_screen = false;
			}
			else
			{
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
			}
			
			
		}
		else
		{
			SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		}
		//----------------Show player power
		player_power.Render(g_screen);
		//---------------------------------------------------------------------------
		human_object.Show(g_screen);
		human_object.HandleMove();
		human_object.MakeAmo(g_screen);
		
		//implement Run threatsObject
		for (int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatsObject* p_threat = (p_threats + tt);
			// control allway check k nó chết chương trình
			if(p_threat)
			{
				// Run Threats
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				if (SDL_Flip(g_screen) == -1)
					return 0; // dùng để update lại màn hình.
				// check collision main and threats
				bool is_col = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_threat->GetRect());
				if (is_col)
				{// trước khi xảy ra game over thì phải xảy ra vụ nổ
					for (int ex = 0; ex < 4; ex++)
					{
						// lấy ví trị cần đặt vụ nổ.
						int x_pos = human_object.GetRect().x + human_object.GetRect().w*0.5 - EXPLOSION_WIDTH*0.5;
						int y_pos = human_object.GetRect().y + human_object.GetRect().w*0.5 - EXPLOSION_HEIGHT * 0.5;
						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.ShowEx(g_screen);
						SDL_Delay(100);
						if (SDL_Flip(g_screen) == -1)
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
							
					}
					die_number++;
					if (die_number <= 2)
					{
						// tọa 1 cai trễ, sau khi bắn 1 phát sẽ mất 1 thời gian hồi sinh
						SDL_Delay(1000);
						// tạo vị trí về vị trí ban đầu
						human_object.SetRect(100, 200);
						player_power.Decrease(); // bớt đi 1 mạng
						player_power.Render(g_screen); // reset mạng
								 //Update screen
						if (SDL_Flip(g_screen) == -1)
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
						
					}
					else
					{
						if (MessageBox(NULL, L"GAME OVER (GoodBye)!!!", L"Info", MB_OK) == IDOK)
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;
						}
					}
				}
				std::vector<AmoObject*> amo_list = human_object.GetAmolist();
				for (int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo != NULL)
					{
 						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if (ret_col == true)
						{
							p_threat->Reset(SCREEN_WIDTH + tt*400);
							human_object.RemoveAmo(im); // remove đạn của threats // nếu k để viên đạn đi xuyên cũng dc
						}
					}
				}
			}
	}
		 //Update screen
		if (SDL_Flip(g_screen) == -1)
		{
			delete[] p_threats;
			SDLCommonFunc::CleanUp();
			SDL_Quit();
			return 0;
		}

			
	}
	// delete control  Threats
	delete[] p_threats;
	
	SDLCommonFunc:: CleanUp();
	SDL_Quit();
	return 1;
	
}

