#include "stdafx.h"
#include "CTextUtil.h"
#include "CDwgDatebaseUtil.h"

CTextUtil::CTextUtil()
{
}


CTextUtil::~CTextUtil()
{
}

AcDbObjectId CTextUtil::addText(const AcGePoint3d & InsertPoint, const TCHAR * text, AcDbObjectId stytle, double height, double rotation)
{
	AcDbText *pText = new AcDbText(InsertPoint, text, stytle, height, rotation);

	return CDwgDatebaseUtil::PostToModelSpace(pText);
}

AcDbObjectId CTextUtil::addMText(const AcGePoint3d & InsertPoint, const TCHAR * text, AcDbObjectId stytle, double height, double width)
{
	AcDbMText *pMText = new AcDbMText();
	pMText->setLocation(InsertPoint);
	pMText->setTextStyle(stytle);
	pMText->setContents(text);
	pMText->setHeight(height);
	pMText->setWidth(width);

	return CDwgDatebaseUtil::PostToModelSpace(pMText);
}
