#ifndef _ATLAS_H_
#define _ATLAS_H_

#include<vector>
#include<graphics.h>


/**
* ͼ���࣬���ڷ����������ͼ
* 
*/
class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	void load(LPCTSTR path_template, int num)
	{
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];//��ʱ�ַ�����
		for (int i = 0; i < num; i++)
		{
			//_sprintf_s��c++�еĺ������ط�����ʹ�ñ��������˻�������С����
			_stprintf_s(path_file, path_template, i+1);
			loadimage(&img_list[i], path_file);
		}
	}

	void clear()
	{
		img_list.clear();
	}

	IMAGE* get_image(int idx)
	{
		return &img_list[idx];
	}

	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}

	int get_size()const
	{
		return img_list.size();
	}

private:
	std::vector<IMAGE> img_list;
};


#endif // !_ATLAS_H_
