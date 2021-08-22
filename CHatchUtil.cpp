#include "stdafx.h"
#include "CHatchUtil.h"
#include "CDwgDatebaseUtil.h"
#include "dbhatch.h"

CHatchUtil::CHatchUtil()
{
}


CHatchUtil::~CHatchUtil()
{
}

AcDbObjectId CHatchUtil::Add(const AcDbObjectIdArray & loopids, const TCHAR * patName, double patternScale)
{
	AcDbHatch *pHatch = new AcDbHatch();
	AcGeVector3d vec(0, 0, 1);
	pHatch->setNormal(vec);
	pHatch->setElevation(0);
	pHatch->setAssociative(true);

	pHatch->setPattern(AcDbHatch::kPreDefined, patName);
	pHatch->appendLoop(AcDbHatch::kExternal, loopids);
	auto es = pHatch->evaluateHatch();

	AcDbObjectId hatchid = CDwgDatebaseUtil::PostToModelSpace(pHatch);

	if (acdbOpenObject(pHatch,hatchid, AcDb::kForRead)==Acad::eOk)
	{
		AcDbObjectIdArray assocentids;
		pHatch->getAssocObjIds(assocentids);
		for (auto i = 0; i < assocentids.length(); i++)
		{
			AcDbEntity *pEntity = NULL;
			if (acdbOpenObject(pEntity,assocentids[i],AcDb::kForWrite)==Acad::eOk)
			{
				pEntity->addPersistentReactor(hatchid);
				pEntity->close();
			}
		}
		pHatch->close();
	}
	return AcDbObjectId();
}
