#include "stdafx.h"
#include "CLayerUtil.h"

CLayerUtil::CLayerUtil()
{
}


CLayerUtil::~CLayerUtil()
{
}

void CLayerUtil::add(TCHAR * LayerName, int colorindex)
{
	assert(LayerName != NULL);
	assert(colorindex >= 1 && colorindex <= 255);
	AcDbLayerTable *pLayerTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTable, AcDb::kForWrite);
	if (!pLayerTable->has(LayerName))
	{
		AcDbLayerTableRecord *pLayerTableRecord = new AcDbLayerTableRecord();
		pLayerTableRecord->setName(LayerName);
		AcCmColor color;
		color.setColorIndex(colorindex);
		pLayerTableRecord->setColor(color);
		pLayerTable->add(pLayerTableRecord);
		pLayerTableRecord->close();
	}
	pLayerTable->close();


}

AcDbObjectId CLayerUtil::GetLayerID(TCHAR * LayerName)
{
	assert(LayerName);
	AcDbLayerTable *pLayerTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTable, AcDb::kForRead);
	AcDbObjectId Layerid = AcDbObjectId::kNull;
	if (pLayerTable->has(LayerName))
	{
		pLayerTable->getAt(LayerName, Layerid);
	}
	pLayerTable->close();
	return Layerid;
}

bool CLayerUtil::SetLayerColor(TCHAR * layerName, int colorindex)
{
	bool result = false;
	AcDbObjectId layerid = GetLayerID(layerName);

	AcDbLayerTableRecord *pLayerTableRecord = NULL;
	if (acdbOpenObject(pLayerTableRecord,layerid,AcDb::kForWrite)==Acad::eOk)
	{
		AcCmColor color;
		color.setColorIndex(colorindex);
		pLayerTableRecord->setColor(color);
		result = true;
		pLayerTableRecord->close();
	}
	return result;
}

void CLayerUtil::GetAllLayerIDList(AcDbObjectIdArray & layerids)
{
	AcDbLayerTable *pLayerTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTable, AcDb::kForRead);
	AcDbLayerTableIterator *it;
	pLayerTable->newIterator(it);
	for (it->start();!it->done();it->step())
	{
		AcDbLayerTableRecord *pLayerTableRecord = NULL;
		if (it->getRecord(pLayerTableRecord, AcDb::kForRead) == Acad::eOk)
		{
			layerids.append(pLayerTableRecord->objectId());
			pLayerTableRecord->close();
		}
	}
	delete it;
	pLayerTable->close();
}

void CLayerUtil::DeleteLayer(TCHAR * LayerName)
{
	AcDbObjectId Layerid = GetLayerID(LayerName);
	AcDbLayerTableRecord *pLayerRecord = NULL;
	if (acdbOpenObject(pLayerRecord,Layerid,AcDb::kForWrite)==Acad::eOk)
	{
		pLayerRecord->erase();
		pLayerRecord->close();
	}
}
