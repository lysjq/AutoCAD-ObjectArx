#pragma once
class CLayerUtil
{
public:
	CLayerUtil();
	~CLayerUtil();

	//根据输入的名字和颜色代号创建新的图层
	static void add(TCHAR *LayerName, int colorindex);

	//根据图层名称获取图层的ID
	static AcDbObjectId GetLayerID(TCHAR *LayerName);

	//修改指定图层的颜色
	static bool SetLayerColor(TCHAR *layerName, int colorindex);

	//获取当前图形中所有的图层ID集合
	static void GetAllLayerIDList(AcDbObjectIdArray &layerids);

	//删除指定的图层
	static void DeleteLayer(TCHAR *LayerName);
};

