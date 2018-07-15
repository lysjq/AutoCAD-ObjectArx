#pragma once
class CLineUtil
{
public:
	CLineUtil();
	~CLineUtil();
	//通过起点和终点构建一条直线
	static AcDbObjectId add(const AcGePoint3d &pStartPoint,const AcGePoint3d &pEndPoint);
};

