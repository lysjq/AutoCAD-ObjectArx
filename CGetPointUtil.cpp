#include "stdafx.h"
#include "CGetPointUtil.h"


CGetPointUtil::CGetPointUtil()
{
}


CGetPointUtil::~CGetPointUtil()
{
}

AcGePoint3d CGetPointUtil::GetMiddlePoint(const AcGePoint3d & FirstPoint, const AcGePoint3d & SecondPoint)
{
	double x = (FirstPoint.x + SecondPoint.x)*0.5;
	double y = (FirstPoint.y + SecondPoint.y)*0.5;
	double z = (FirstPoint.z + SecondPoint.z)*0.5;
	return AcGePoint3d(x,y,z);
}

AcGePoint2d CGetPointUtil::GetMiddlePoint(const AcGePoint2d & FirstPoint, const AcGePoint2d & SecondPoint)
{
	double x = (FirstPoint.x + SecondPoint.x)*0.5;
	double y= (FirstPoint.y + SecondPoint.y)*0.5;
	return AcGePoint2d(x,y);
}
