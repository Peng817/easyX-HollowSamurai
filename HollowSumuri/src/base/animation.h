#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <iostream>
#include <vector>
#include <functional>

#include "../util/atlas.h"
#include "../util/timer.h"
#include "../util/util.h"
#include "../util/Vector2.h"

class Animation
{
public:
	enum class AnchorType
	{
		Center,
		BottomMid,
	};

	Animation();
	Animation(
		float frame_interval_time,
		AnchorType type,
		std::function<void()> on_finished
	);

	~Animation() = default; //Animation对象结束时做的逻辑上的事务交给on_finished

	void set_loop(bool flag)
	{
		is_loop = flag;
	}

	void set_position(const Vector2& new_pos)
	{
		animation_anchor_point = new_pos;
	}

	void reset()
	{
		timer.restart();
		frame_idx = 0;
	}

	void on_update(float delta)
	{
		timer.on_update(delta);
	}

	void on_render();

private:

	/**
	* 图集类，Animation中的图集类Frame类是一种对Atlas图集类的兼容，
	* 在此类图集之外，Frame类还可以高效地表示一种单图式图集
	*/
	struct Frame
	{
		IMAGE* image;
		Rect rect;

		Frame(IMAGE* img, const Rect& rect)
			:image(img), rect(rect)
		{}
		Frame() = default;
		~Frame() = default;
	};

	void _init();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="image">单图图集</param>
	/// <param name="num_h">当前单图图集的图片中包含了多少单帧图像</param>
	void load_frame(IMAGE* image, int num_h);
	void load_frame(Atlas* atlas);


private:
	Timer timer;
	std::vector<Frame> frame_list;
	int frame_idx;

	bool is_loop = true;
	std::function<void()> on_finished;
	AnchorType anchor_type = AnchorType::Center;
	Vector2 animation_anchor_point;



	
};


#endif