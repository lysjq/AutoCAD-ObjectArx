#include "stdafx.h"
#include "CEntityUtil.h"


CEntityUtil::CEntityUtil()
{
}


CEntityUtil::~CEntityUtil()
{
}

void CEntityUtil::setColor(AcDbObjectId objectID, int ColorIndex)
{
	//检测参数有效性
	assert(ColorIndex >= 0 && ColorIndex <= 255);
	AcDbEntity *pEntity;
	if (acdbOpenAcDbEntity(pEntity,objectID,AcDb::kForWrite)==Acad::eOk)
	{
		pEntity->setColorIndex(ColorIndex);
		pEntity->close();
	}
}

void CEntityUtil::setLayer(AcDbObjectId objectID, const TCHAR * LayerName)
{
	AcDbEntity *pEntity;
	if (acdbOpenAcDbEntity(pEntity, objectID, AcDb::kForWrite)==Acad::eOk)
	{
		pEntity->setLayer(LayerName);
		pEntity->close();
	}
}

void CEntityUtil::setLineType(AcDbObjectId objectID, const TCHAR * LineType)
{
	AcDbEntity *pEntity;
	if (acdbOpenAcDbEntity(pEntity,objectID,AcDb::kForWrite)==Acad::eOk)
	{
		pEntity->setLinetype(LineType);
		pEntity->close();
	}
}

Acad::ErrorStatus CEntityUtil::Rotate(AcDbObjectId objectid, const AcGePoint2d & pBasePoint, double rotationAngle)
{
	AcGeMatrix3d xform;
	AcGeVector3d vec(0, 0, 1);
	AcGePoint3d RotatePoint(pBasePoint.x, pBasePoint.y, 0);
	xform.setToRotation(rotationAngle, vec, RotatePoint);

	Acad::ErrorStatus es;
	AcDbEntity *pEntity;
	es = acdbOpenObject(pEntity, objectid, AcDb::kForWrite);
	if (Acad::eOk==es)
	{
		es=pEntity->transformBy(xform);
		pEntity->close();
	}
	return es;
}

Acad::ErrorStatus CEntityUtil::Move(AcDbObjectId objectID, AcGePoint3d & pBasePoint, AcGePoint3d & pDest)
{
	AcGeMatrix3d xform;
	AcGeVector3d vec(pDest.x - pBasePoint.x, pDest.y - pBasePoint.y, pDest.z - pBasePoint.z);
	xform.setToTranslation(vec);
	Acad::ErrorStatus es;
	AcDbEntity *pEntity;
	es = acdbOpenObject(pEntity, objectID, AcDb::kForWrite);
	if (Acad::eOk == es)
	{
		es=pEntity->transformBy(xform);
		pEntity->close();
	}
	return es;
}

Acad::ErrorStatus CEntityUtil::Scale(AcDbObjectId objectID, const AcGePoint3d & pBasePoint, double scaleSize)
{
	AcGeMatrix3d xform;
	xform.setToScaling(scaleSize, pBasePoint);
	Acad::ErrorStatus es;
	AcDbEntity *pEntity;
	es = acdbOpenObject(pEntity, objectID, AcDb::kForWrite);
	if (Acad::eOk==es)
	{
		es = pEntity->transformBy(xform);
		pEntity->close();
	}
	return es;
}
