#pragma once
class CBlockUtil
{
public:
	CBlockUtil();
	~CBlockUtil();

	//创建一个带属性的块定义，返回块名称
	static void addMyBlockDefine();

	//根据用户输入的块名和位置点插入块参照
	static void InsertBlock();

	//从图块中提取特定属性的值
	static bool GetAttributeValue(AcDbBlockReference *pBlockRef, TCHAR *Tag, AcString &Value);
};

 