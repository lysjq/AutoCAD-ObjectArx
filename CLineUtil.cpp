#include "stdafx.h"
#include "CLineUtil.h"
#include "CDwgDatebaseUtil.h"

CLineUtil::CLineUtil()
{
}


CLineUtil::~CLineUtil()
{
}

AcDbObjectId CLineUtil::add(const AcGePoint3d & pStartPoint, const AcGePoint3d & pEndPoint)
{
	//创建直线实体
	AcDbLine *pLine = new AcDbLine(pStartPoint, pEndPoint);
	//把直线实体添加到模型空间
	return CDwgDatebaseUtil::PostToModelSpace(pLine);
}

