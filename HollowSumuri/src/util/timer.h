#ifndef _TIMER_H
#define _TIMER_H

#include <functional>

class Timer
{
private:
	float wait_time = 0; //生存时间属性
	float pass_time = 0; //已消耗时间

	std::function<void()> on_timeout; //回调
	bool is_oneshot = false;
	bool shotted = false;

public:
	Timer() = default;
	~Timer() = default;
	
	void restart()
	{
		pass_time = 0;
	}

	void set_wait_time(float val)
	{
		wait_time = val;
	}

	void set_on_timeout(std::function<void()> func)
	{
		on_timeout = func;
	}

	void set_one_shot(bool flag)
	{
		is_oneshot = flag;
	}

	void on_update(float delta)
	{
		pass_time += delta;
		if (pass_time >= wait_time)
		{
			bool can_shot = true;
			if (is_oneshot)
			{
				if (!shotted)
				{
					shotted = true;
				}
				else
				{
					can_shot = false;
				}
			}
			
			if (can_shot && on_timeout)
			{
				on_timeout();
			}

			pass_time -= wait_time;
		}
	}
};


#endif // !_TIMER_H
