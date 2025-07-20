#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <graphics.h>

#include "atlas.h"
#include "util.h"

class ResourceManager
{
public:
	static ResourceManager* get_instance();
	

	void load();
	
	IMAGE* get_image(std::string id);
	Atlas* get_atlas(std::string id);

	//HACK: only for test
	void show_resource_info_size();
public:
	/// <summary>
	/// 多图式图集，资源路径记录为根目录
	/// </summary>
	struct AtlasResInfo
	{
		std::string id;
		LPCTSTR resource_path;
		int frame_num;
	};

	/// <summary>
	/// 单图式图集，资源路径记录为单图路径名
	/// </summary>
	struct ImageResInfo 
	{
		std::string id;
		LPCTSTR resource_path;
	};




private:
	ResourceManager();
	static inline bool check_image_valid(IMAGE* image)
	{
		return GetImageBuffer(image);
	}

	void flip_image(std::string src_id, std::string dst_id,int frame_num);
	void flip_image(IMAGE* src_img, int frame_num, IMAGE* dst_img);
	void flip_atlas(std::string src_id, std::string dst_id);


private:
	std::unordered_map<std::string, IMAGE*> img_pool;
	std::unordered_map < std::string, Atlas*> atlas_pool;


private:
	static const std::vector<ImageResInfo> img_res_info_list;
	static const std::vector<AtlasResInfo> atlas_res_info_list;
};


#endif // !_RESOURCE_MANAGER_H_
