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

	//���Ƶ�ǰ֡
	putimage_extend(current_frame.image, &current_rect, &current_frame.rect);

}

void Animation::_init()
{
	//��ʼ��timer
	timer.set_one_shot(false); //Ĭ�ϵĶ�����Ҫһ����ͣ�����ʱ���

	// ԭ�����ڻص�������ͨ��thisָ�������Ƶ�ǰ�����
	// ��������ڻص�������ʹ��thisָ��ʱ������ķ���Ȩ���Ѿ���Ч��
	// ��ʹ���ڸ���Ĺ��캯����
	timer.set_on_timeout(
		[&]()
		{
			//�ص�����������ÿ��ʱ��������һ�Σ���ǰ������ִ�е��߼�
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
