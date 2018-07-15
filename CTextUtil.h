#pragma once
class CTextUtil
{
public:
	CTextUtil();
	~CTextUtil();

	//添加文字
	static AcDbObjectId addText(const AcGePoint3d &InsertPoint, const TCHAR *text, AcDbObjectId stytle = AcDbObjectId::kNull, double height = 2.5, double rotation = 0);

	//添加多行文字
	static AcDbObjectId addMText(const AcGePoint3d &InsertPoint, const TCHAR* text, AcDbObjectId stytle = AcDbObjectId::kNull, double height = 2.5,double width = 10);
};

