#pragma once
class CIOUtil
{
public:
	CIOUtil();
	~CIOUtil();

	//将当前图形中存在的所有图层及其特性(图层名称、颜色、图层线型、图层线宽)导出到指定的文本文件中
	static void ExportLayer(const TCHAR* FileName);

	//按照指定文本文件中的图层列表属性(图层名称、颜色、图层线型、图层线宽)在当前图形中创建图层
	static void ImportLayer(const TCHAR* FileName);
};

