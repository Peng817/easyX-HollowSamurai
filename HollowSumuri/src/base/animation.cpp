#include "animation.h"


Animation::Animation()
{
	_init();
}

void Animation::on_render()
{
	const Frame& current_frame = frame_list[frame_idx];
	
	Rect current_rect;
	current_rect.h = current_frame.rect.h;
	current_rect.w = current_frame.rect.w;
	switch (anchor_type)
	{
	case AnchorType::Center:
		current_rect.x = animation_anchor_point.x - current_frame.rect.w / 2;
		current_rect.y = animation_anchor_point.y - current_frame.rect.h / 2;
		break;
	case AnchorType::BottomMid:
		current_rect.x = animation_anchor_point.x;
		current_rect.y = animation_anchor_point.y + current_frame.rect.h / 2;
		break;
	}

	//绘制当前帧
	putimage_extend(current_frame.image, &current_rect, &current_frame.rect);

}

void Animation::_init()
{
	//初始化timer
	timer.set_one_shot(false); //默认的动画需要一个不停脉冲的时间泵

	// 原本对于回调函数想通过this指针来控制当前类对象，
	// 结果发现在回调函数中使用this指针时，对象的访问权限已经生效，
	// 即使是在该类的构造函数中
	timer.set_on_timeout(
		[&]()
		{
			//回调函数决定了每次时间类脉冲一次，当前动画类执行的逻辑
			frame_idx++;
			if (frame_idx >= frame_list.size())
			{
				if (!is_loop && on_finished)
				{
					on_finished();
				}
				frame_idx = is_loop ? 0 : frame_list.size() - 1;
			}
		}
	);
}

void Animation::load_frame(IMAGE* image, int num_h)
{
	int w = image->getwidth();
	int h = image->getheight();
	int w_per_frame = w / num_h;

	for (int i = 0; i < num_h; ++i)
	{
		Rect rect;
		rect.x = i * w_per_frame; rect.y = 0;
		rect.w = w_per_frame;
		rect.h = h;
		frame_list.emplace_back(image, rect);
	}
}

void Animation::load_frame(Atlas* atlas)
{
	Rect rect;
	IMAGE* sample_image = atlas->get_image(0);
	rect.x = 0; rect.y = 0;
	rect.h = sample_image->getheight();
	rect.w = sample_image->getwidth();

	for (int i = 0; i < atlas->get_size(); ++i)
	{
		frame_list.emplace_back(atlas->get_image(i), rect);
	}
}


Animation::Animation(float frame_interval_time, AnchorType type, std::function<void()> on_finished)
{
	_init();
	this->anchor_type = type;
	this->on_finished = on_finished;
	this->timer.set_wait_time(frame_interval_time);
}
