#ifndef _UTIL_H_
#define _UTIL_H_

#include <graphics.h>

#pragma comment(lib,"WINMM.lib") //ȷ����������Ƶ���ſ�
#pragma comment(lib,"MSIMG32.lib") //ȷ�������˻�ͼ������


struct Rect
{
	int x, y;
	int w, h;
};

/// <summary>
/// ��ϱ���ͼ���е�rect_dst�����imgͼ���е�rect_src����;
/// ���rect_srcΪ�գ���Ĭ��ʹ��imgͼ���ȫ������
/// </summary>
/// <param name="img"></param>
/// <param name="rect_dst"></param>
/// <param name="rect_src"></param>
inline void putimage_extend(IMAGE* img, const Rect* rect_dst,
	const Rect* rect_src = nullptr
)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y,
		rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0,
		rect_src ? rect_src->y : 0, rect_src ? rect_src->w : img->getwidth(),
		rect_src ? rect_src->h : img->getheight(), blend_func);
};


inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"),
		path, id);
	mciSendString(str_cmd, NULL, 0, NULL);
 }

inline void play_audio(LPCTSTR id,bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"),
		id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"),
		id);
	mciSendString(str_cmd, NULL, 0, NULL);
}




#endif // !_UTIL_H_
