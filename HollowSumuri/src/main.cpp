#include <iostream>
#include <chrono>
#include <thread>

#include "util/timer.h"
#include "base/animation.h"
#include "base/scene.h"
#include "../test/test_resource_manager.h"

void test()
{
	TestResourceManager::test();

}


static void draw_background()
{
	static IMAGE* img_background = ResourceManager::get_instance()->get_image("background");
	int w = getwidth();
	int h = getheight();
	static Rect rect_dst =
	{

		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};

	putimage_extend(img_background, &rect_dst);
}

void game()
{
	using namespace std::chrono;
	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Hollow Sumuri"));


	try
	{
		ResourceManager::get_instance();
	}
	catch(const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("无法加载: %s"), id);
		MessageBox(hwnd, err_msg, _T("资源加载失败"),MB_OK|MB_ICONERROR);
	}

	ExMessage msg;
	bool is_quit = false;
	//定义144帧的单帧纳秒
	const nanoseconds frame_duration(1000000000 / 144);


	BeginBatchDraw();
	while (!is_quit)
	{
		while (peekmessage(&msg))
		{

		}
		//帧开始
		steady_clock::time_point frame_start = steady_clock::now();




		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		draw_background();

	
		FlushBatchDraw();

		//帧结束
		//计算处理时间
		nanoseconds process_duration = steady_clock::now() - frame_start;
		if (process_duration < frame_duration)
			std::this_thread::sleep_for(frame_duration - process_duration);

	}
	EndBatchDraw();
}

int main(int argc,char** argv)
{
	//test();
	game();
	
	return 0;
}