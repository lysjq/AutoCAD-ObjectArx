#pragma once
class CDwgDatebaseUtil
{
public:
	CDwgDatebaseUtil();
	~CDwgDatebaseUtil();
	//将模型对象添加到图形数据库
	static AcDbObjectId PostToModelSpace(AcDbEntity *pEntity);

	//遍历当前图形的模型空间，获取位于某个图层上的所有实体，若图层名为空，则遍历当前模型空间的所有实体，返回ID集
	static AcDbObjectIdArray GetAllEntityIDs(const TCHAR *layerName=NULL);
};

