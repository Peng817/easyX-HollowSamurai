#include "resource_manager.h"
#include <iostream>


ResourceManager* ResourceManager::get_instance()
{
	static ResourceManager instance;
	return &instance;
}

ResourceManager::ResourceManager()
{
	load();
}

void ResourceManager::flip_image(std::string src_id, std::string dst_id, int frame_num)
{
	IMAGE* src_img = get_image(src_id);
	IMAGE* dst_img = new IMAGE(*src_img);
	flip_image(src_img, frame_num, dst_img);
	this->img_pool[dst_id] = dst_img;
}

void ResourceManager::flip_image(IMAGE* src_img, int frame_num, IMAGE* dst_img)
{
	int w_frame = src_img->getwidth() / frame_num;

	int w = src_img->getwidth();
	int h = src_img->getheight();
	
	//格式化目标图片
	Resize(dst_img, w, h);
	DWORD* src_buffer = GetImageBuffer(src_img);
	DWORD* dst_buffer = GetImageBuffer(dst_img);
	for (int i = 0; i < frame_num; ++i)
	{
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; ++y)
		{
			for (int x = x_left; x < x_right; ++x)
			{
				int src_pixel_id = y * w + x;
				int dst_pixel_id = y * w + x_right - (x - x_left);
				dst_buffer[dst_pixel_id] = src_buffer[src_pixel_id];
			}
		}
	}
}

void ResourceManager::flip_atlas(std::string src_id, std::string dst_id)
{
	Atlas* src_atlas = get_atlas(src_id);
	Atlas* dst_atlas = new Atlas();
	int frame_num = src_atlas->get_size();
	for (int i = 0; i < frame_num; ++i)
	{
		IMAGE dst_img;
		flip_image(src_atlas->get_image(i),1,&dst_img);
		dst_atlas->add_image(dst_img);
		//dst_img：:~IMAGE();
	}
	this->atlas_pool[dst_id] = dst_atlas;
}

void ResourceManager::load()
{
	for (const auto& info : atlas_res_info_list) 
	{
		Atlas* atlas = new Atlas();
		atlas->load(info.resource_path,info.frame_num);
		for(int i = 0;i < info.frame_num;++i){
			if(!check_image_valid(atlas->get_image(i)))
				throw info.resource_path;
		}
		this->atlas_pool[info.id] = atlas;
	}

	for (const auto& info : img_res_info_list)
	{
		IMAGE* image = new IMAGE();
		loadimage(image, info.resource_path);
		if (!check_image_valid(image))
			throw info.resource_path;
		this->img_pool[info.id] = image;
	}

	flip_image("player_run_right", "player_run_left", 10);
	flip_image("player_attack_right", "player_attack_left", 5);
	flip_image("player_dead_right", "player_dead_left", 6);
	flip_image("player_fall_right", "player_fall_left", 5);
	flip_image("player_idle_right", "player_idle_left", 5);
	flip_image("player_jump_right", "player_jump_left", 5);
	flip_image("player_roll_right", "player_roll_left", 7);


	flip_atlas("enemy_aim_left", "enemy_aim_right");
	flip_atlas("enemy_barb_break_left", "enemy_barb_break_right");
	flip_atlas("enemy_barb_loose_left", "enemy_barb_loose_right");
	flip_atlas("enemy_dash_in_air_left", "enemy_dash_in_air_right");
	flip_atlas("enemy_dash_on_floor_left", "enemy_dash_on_floor_right");
	flip_atlas("enemy_fall_left", "enemy_fall_right");
	flip_atlas("enemy_idle_left", "enemy_idle_right");
	flip_atlas("enemy_jump_left", "enemy_jump_right");
	flip_atlas("enemy_run_left", "enemy_run_right");
	flip_atlas("enemy_squat_left", "enemy_squat_right");
	flip_atlas("enemy_sword_left", "enemy_sword_right");
	flip_atlas("enemy_throw_barb_left", "enemy_throw_barb_right");
	flip_atlas("enemy_throw_silk_left", "enemy_throw_silk_right");
	flip_atlas("enemy_throw_sword_left", "enemy_throw_sword_right");
	flip_atlas("enemy_vfx_dash_in_air_left", "enemy_vfx_dash_in_air_right");
	flip_atlas("enemy_vfx_dash_on_floor_left", "enemy_vfx_dash_on_floor_right");
	flip_atlas("enemy_silk_left", "enemy_silk_right");

	load_audio(_T(R"(res\audio\bgm.mp3)"),			_T("bgm"));
	load_audio(_T(R"(res\audio\barb_break.mp3)"),	_T("barb_break"));
	load_audio(_T(R"(res\audio\bullet_time.mp3)"),	_T("bullet_time"));


	load_audio(_T(R"(res\audio\enemy_dash.mp3)"),	_T("enemy_dash"));
	load_audio(_T(R"(res\audio\enemy_run.mp3)"),	_T("enemy_run"));
	load_audio(_T(R"(res\audio\enemy_hurt_1.mp3)"),	_T("enemy_hurt_1"));
	load_audio(_T(R"(res\audio\enemy_hurt_2.mp3)"),	_T("enemy_hurt_2"));
	load_audio(_T(R"(res\audio\enemy_hurt_3.mp3)"),	_T("enemy_hurt_3"));
	load_audio(_T(R"(res\audio\enemy_throw_barbs.mp3)"),	_T("enemy_throw_barbs"));
	load_audio(_T(R"(res\audio\enemy_throw_silk.mp3)"),		_T("enemy_throw_silk"));
	load_audio(_T(R"(res\audio\enemy_throw_sword.mp3)"),	_T("enemy_throw_sword"));

	load_audio(_T(R"(res\audio\player_attack_1.mp3)"),	_T("player_attack_1"));
	load_audio(_T(R"(res\audio\player_attack_2.mp3)"),	_T("player_attack_2"));
	load_audio(_T(R"(res\audio\player_attack_3.mp3)"),	_T("player_attack_3"));
	load_audio(_T(R"(res\audio\player_dead.mp3)"),		_T("player_dead"));
	load_audio(_T(R"(res\audio\player_hurt.mp3)"),		_T("player_hurt"));
	load_audio(_T(R"(res\audio\player_jump.mp3)"),		_T("player_jump"));
	load_audio(_T(R"(res\audio\player_land.mp3)"),		_T("player_land"));
	load_audio(_T(R"(res\audio\player_roll.mp3)"),		_T("player_roll"));
	load_audio(_T(R"(res\audio\player_run.mp3)"),		_T("player_run"));
}

IMAGE* ResourceManager::get_image(std::string id)
{
	const auto& it = img_pool.find(id);
	if (it == img_pool.end())
		return nullptr;
	else return it->second;
}

Atlas* ResourceManager::get_atlas(std::string id)
{
	const auto& it = atlas_pool.find(id);
	if (it == atlas_pool.end())
		return nullptr;
	else return it->second;
}

void ResourceManager::show_resource_info_size()
{
	std::cout<< "atlas_pool size: "<<atlas_pool.size()<<std::endl;
	std::cout<< "img_pool size: "<<img_pool.size()<<std::endl;

}

const std::vector<ResourceManager::AtlasResInfo> ResourceManager::atlas_res_info_list =
{
	{"enemy_barb_break_left",	_T(R"(res/enemy/barb_break/%d.png)"),	3},
	{"enemy_barb_loose_left",	_T(R"(res/enemy/barb_loose/%d.png)"),	5},	
	{"enemy_silk_left",		_T(R"(res/enemy/silk/%d.png)"),			9},	
	{"enemy_sword_left",	_T(R"(res/enemy/sword/%d.png)"),		3},

	{"enemy_aim_left",				_T(R"(res/enemy/aim/%d.png)"),				9},
	{"enemy_dash_in_air_left",		_T(R"(res/enemy/dash_in_air/%d.png)"),		2},
	{"enemy_dash_on_floor_left",	_T(R"(res/enemy/dash_on_floor/%d.png)"),	2},
	{"enemy_fall_left",				_T(R"(res/enemy/fall/%d.png)"),				4},
	{"enemy_idle_left",				_T(R"(res/enemy/idle/%d.png)"),				6},
	{"enemy_jump_left",				_T(R"(res/enemy/jump/%d.png)"),				8},
	{"enemy_run_left",				_T(R"(res/enemy/run/%d.png)"),				8},
	{"enemy_squat_left",			_T(R"(res/enemy/squat/%d.png)"),			10},
	{"enemy_throw_barb_left",		_T(R"(res/enemy/throw_barb/%d.png)"),		8},
	{"enemy_throw_silk_left",		_T(R"(res/enemy/throw_silk/%d.png)"),		17},
	{"enemy_throw_sword_left",		_T(R"(res/enemy/throw_sword/%d.png)"),		16},

	{"enemy_vfx_dash_in_air_left",	_T(R"(res/enemy/vfx_dash_in_air/%d.png)"),	5},
	{"enemy_vfx_dash_on_floor_left",_T(R"(res/enemy/vfx_dash_on_floor/%d.png)"),6},
};

const std::vector<ResourceManager::ImageResInfo> ResourceManager::img_res_info_list =
{
	{"background",_T(R"(res/background.png)")},
	{"ui_heart",_T(R"(res/ui_heart.png)")},

	{"player_attack_right",		_T(R"(res/player/attack.png)")},
	{"player_dead_right",		_T(R"(res/player/dead.png)")},
	{"player_fall_right",		_T(R"(res/player/fall.png)")},
	{"player_idle_right",		_T(R"(res/player/idle.png)")},
	{"player_jump_right",		_T(R"(res/player/jump.png)")},
	{"player_run_right",		_T(R"(res/player/run.png)")},
	{"player_roll_right",		_T(R"(res/player/roll.png)")},

	{"player_vfx_attack_down",	_T(R"(res/player/vfx_attack_down.png)")},
	{"player_vfx_attack_left",	_T(R"(res/player/vfx_attack_left.png)")},
	{"player_vfx_attack_right",	_T(R"(res/player/vfx_attack_right.png)")},
	{"player_vfx_attack_up",	_T(R"(res/player/vfx_attack_up.png)")},
	{"player_vfx_jump",			_T(R"(res/player/vfx_jump.png)")},
	{"player_vfx_land",			_T(R"(res/player/vfx_land.png)")},

};