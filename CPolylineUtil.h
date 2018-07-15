#pragma once
class CPolylineUtil
{
public:
	CPolylineUtil();
	~CPolylineUtil();

	//根据顶点数组创建轻量多线段
	static AcDbObjectId add(const AcGePoint2dArray &Points, double width = 0);

	//根据顶点创建三维多线段
	static AcDbObjectId add(const AcGePoint3dArray &Points);

	//根据中心点、边数、外接圆半径、旋转角度（弧度）和线宽创建正多边形
	static AcDbObjectId addPolygon(AcGePoint2d &pCenterPoint, int number, double radius, double ratation, double width = 0);

	//根据两个角点创建矩形
	static AcDbObjectId addRect(const AcGePoint2d &Point1, const AcGePoint2d &Point2, double width=0);
};

