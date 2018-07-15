#pragma once
class CViewUtil
{
public:
	CViewUtil();
	~CViewUtil();

	//获取当前的试图信息
	static void GetCurrentView(AcDbViewTableRecord &view);
	
	//创建4个等大的视口
	static void Create4ViewPort();

	//在“布局”上添加新的视口
	static void CreateViewPortInSpace();

	//创建一个新的UCS坐标系
	static void NewUCS();

	//将UCS表中已经存在的一个UCS设置为当前UCS
	static void SetCurrentUCS();
};

