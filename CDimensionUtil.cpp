#include "stdafx.h"
#include "CDimensionUtil.h"
#include "CDwgDatebaseUtil.h"

CDimensionUtil::CDimensionUtil()
{
}


CDimensionUtil::~CDimensionUtil()
{
}

AcDbObjectId CDimensionUtil::AddDimAligned(const AcGePoint3d & pt1, const AcGePoint3d & pt2, const AcGePoint3d & ptLine, const TCHAR * dimtext, AcDbObjectId dimstyle)
{
	AcDbAlignedDimension *pDim = new AcDbAlignedDimension(pt1, pt2, ptLine, dimtext, dimstyle);
	return CDwgDatebaseUtil::PostToModelSpace(pDim);
}
