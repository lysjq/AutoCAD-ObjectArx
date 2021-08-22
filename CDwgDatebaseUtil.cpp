#include "stdafx.h"
#include "CDwgDatebaseUtil.h"

CDwgDatebaseUtil::CDwgDatebaseUtil()
{
}


CDwgDatebaseUtil::~CDwgDatebaseUtil()
{
}

AcDbObjectId CDwgDatebaseUtil::PostToModelSpace(AcDbEntity * pEntity)
{
	Acad::ErrorStatus es;
	//检查输入参数有效性
	assert(pEntity != NULL);

	//获取当前图形数据库的块表
	AcDbBlockTable *pBlockTable;
	es=acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

	//获取模型空间对应的块表记录
	AcDbBlockTableRecord *pBlockTableRecord;
	es=pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);


	//将实体添加到空间对应的块表记录中
	AcDbObjectId ObjectID;
	es=pBlockTableRecord->appendAcDbEntity(ObjectID, pEntity);
	if (es!=Acad::eOk)
	{
		pBlockTable->close();
		pBlockTableRecord->close();
		//添加失败时，要delete，成功并且appendAcdbEntity之后，由数据库来操作该对象
		delete pEntity;
		pEntity = NULL;
		return AcDbObjectId::kNull;
	}

	//关闭模型空间和实体
	pBlockTable->close();
	pBlockTableRecord->close();
	pEntity->close();

	return ObjectID;
}

AcDbObjectIdArray CDwgDatebaseUtil::GetAllEntityIDs(const TCHAR * layerName)
{
	AcDbObjectIdArray EntityIDs;
	bool bifFilterlayer = false;
	AcDbObjectId layerid;
	if (layerName != NULL)
	{
		AcDbLayerTable *layertable=NULL;
		acdbHostApplicationServices()->workingDatabase()->getSymbolTable(layertable, AcDb::kForRead);
		if (!layertable->has(layerName))
		{
			layertable->close();
			acutPrintf(_T("在当前模型空间未找到名称为: %s 的图层"), layerName);
			return EntityIDs;
		}
		layertable->getAt(layerName, layerid);
		layertable->close();
		bifFilterlayer = true;
	}

	AcDbBlockTable *pBlockTable;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord *PBlockTableRecoard;
	pBlockTable->getAt(ACDB_MODEL_SPACE, PBlockTableRecoard, AcDb::kForRead);
	pBlockTable->close();

	AcDbBlockTableRecordIterator *it=NULL;
	PBlockTableRecoard->newIterator(it);
	for (it->start();!it->done();it->step())
	{
		AcDbEntity *pEntity = NULL;
		Acad::ErrorStatus es = it->getEntity(pEntity, AcDb::kForRead);
		if (Acad::eOk==es)
		{
			if (bifFilterlayer)					//如果图层名不为空，过滤出符合图层名称的实体
			{
				if (pEntity->layerId() == layerid)
				{
					EntityIDs.append(pEntity->objectId());
				}
			}
			else								//否则把所有的都加入id集
			{
				EntityIDs.append(pEntity->objectId());
			}
			pEntity->close();
		}
		else
		{
			acutPrintf(TEXT("\nCDwgDatebaseUtil::GetAllEntityIDs中打开实体失败，（错误代码:%d）"), (int)es);
		}
	}
	delete it;
	PBlockTableRecoard->close();
	return EntityIDs;
}
