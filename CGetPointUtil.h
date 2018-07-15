#pragma once
class CGetPointUtil
{
public:
	CGetPointUtil();
	~CGetPointUtil();

	//求两个3d点连线的中点
	static AcGePoint3d GetMiddlePoint(const AcGePoint3d &FirstPoint, const AcGePoint3d &SecondPoint);

	//求两个2d点连线的中点
	static AcGePoint2d GetMiddlePoint(const AcGePoint2d &FirstPoint, const AcGePoint2d &SecondPoint);
	
};

