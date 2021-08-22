#include "stdafx.h"
#include "CViewUtil.h"
#include "dbapserv.h"
#include "AcDbLMgr.h"


CViewUtil::CViewUtil()
{
}


CViewUtil::~CViewUtil()
{
}

void CViewUtil::GetCurrentView(AcDbViewTableRecord & view)
{
	resbuf rb;
	resbuf wcs, ucs, dcs;
	wcs.restype = RTSHORT;
	wcs.resval.rint = 0;
	ucs.restype = RTSHORT;
	ucs.resval.rint = 1;
	dcs.restype = RTSHORT;
	dcs.resval.rint = 2;

	//获得当前适口的“查看”模式
	acedGetVar(_T("VIEWMODE"), &rb);
	view.setPerspectiveEnabled((rb.resval.rint & 1) != 0);
	view.setFrontClipEnabled((rb.resval.rint & 2) != 0);
	view.setBackClipEnabled((rb.resval.rint & 4) != 0);
	view.setFrontClipAtEye((rb.resval.rint & 16) == 0);

	//当前视口中视图的中心点
	acedGetVar(_T("VIEWCTR"), &rb);
	acedTrans(rb.resval.rpoint, &ucs, &dcs, 0, rb.resval.rpoint);
	view.setCenterPoint(AcGePoint2d(rb.resval.rpoint[X], rb.resval.rpoint[Y]));

	//........
	//.......
}

void CViewUtil::Create4ViewPort()
{
	AcDbViewportTable *pViewPortTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getViewportTable(pViewPortTable, AcDb::kForWrite);

	AcGePoint2d p1(0, 0);
	AcGePoint2d p2(0.5, 0.5);
	AcDbViewportTableRecord *pViewPortRecord1 =new AcDbViewportTableRecord();
	pViewPortRecord1->setLowerLeftCorner(p1);
	pViewPortRecord1->setUpperRightCorner(p2);

	p1.set(0.5, 0);
	p1.set(1, 0.5);
	AcDbViewportTableRecord *pViewPortRecord2 = new AcDbViewportTableRecord();
	pViewPortRecord2->setLowerLeftCorner(p1);
	pViewPortRecord2->setUpperRightCorner(p2);

	p1.set(0, 0.5);
	p1.set(0.5,1);
	AcDbViewportTableRecord *pViewPortRecord3 = new AcDbViewportTableRecord();
	pViewPortRecord3->setLowerLeftCorner(p1);
	pViewPortRecord3->setUpperRightCorner(p2);

	p1.set(0.5, 0.5);
	p1.set(1, 1);
	AcDbViewportTableRecord *pViewPortRecord4 = new AcDbViewportTableRecord();
	pViewPortRecord4->setLowerLeftCorner(p1);
	pViewPortRecord4->setUpperRightCorner(p2);

	pViewPortTable->add(pViewPortRecord1);
	pViewPortTable->add(pViewPortRecord2);
	pViewPortTable->add(pViewPortRecord3);
	pViewPortTable->add(pViewPortRecord4);

	pViewPortTable->close();
	pViewPortRecord1->close();
	pViewPortRecord2->close();
	pViewPortRecord3->close();
	pViewPortRecord4->close();

	//判断当前空间
	resbuf rb;
	acedGetVar(_T("TILEMODE"), &rb);
	//当前工作空间是模型空间
	if (rb.resval.rint==1)
	{
	}
	else
	{

	}

}

void CViewUtil::CreateViewPortInSpace()
{
	Acad::ErrorStatus es;
	es = acdbHostApplicationServices()->layoutManager()->setCurrentLayout(_T("布局1"));
	if (es!=Acad::eOk)
	{
		return;
	}
	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

	AcDbBlockTableRecord *pBlockTableRecord = NULL;
	pBlockTable->getAt(ACDB_PAPER_SPACE, pBlockTableRecord,AcDb::kForWrite);

	AcDbViewport *pViewPort = new AcDbViewport();
	pViewPort->setCenterPoint(AcGePoint3d(100, 50, 0));
	pViewPort->setHeight(80);
	pViewPort->setWidth(120);
	AcDbObjectId objectid;
	pBlockTableRecord->appendAcDbEntity(objectid, pViewPort);

	pBlockTable->close();
	pBlockTableRecord->close();
	pViewPort->close();

	//将新建的视图作为当前视图
	AcDbViewport *pVP = NULL;
	if (acdbOpenObject(pVP,objectid,AcDb::kForWrite)==Acad::eOk)
	{
		pVP->setOn();
		acedSetCurrentVPort(pVP);
		pVP->close();
	}

}

void CViewUtil::NewUCS()
{
	TCHAR UCSName[40];
	if (acedGetString(NULL,_T("输入要创建的UCS名称： "),UCSName)!=RTNORM)
	{
		return;
	}
	AcDbUCSTable *pUCSTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getUCSTable(pUCSTable,AcDb::kForWrite);

	AcDbUCSTableRecord *pUCSTableRecord = new AcDbUCSTableRecord();
	AcGePoint3d OriginPoint(0, 0, 0);
	AcGeVector3d Xaxis(1, 1, 0);
	AcGeVector3d Yaxis(-1, 1, 0);
	pUCSTableRecord->setName(UCSName);
	pUCSTableRecord->setOrigin(OriginPoint);
	pUCSTableRecord->setXAxis(Xaxis);
	pUCSTableRecord->setYAxis(Yaxis);
	pUCSTable->add(pUCSTableRecord);

	pUCSTable->close();
	pUCSTableRecord->close();
}

void CViewUtil::SetCurrentUCS()
{
	TCHAR UCSName[40];
	if (acedGetString(NULL,_T("输入要设置为当前UCS坐标系的名称： "),UCSName)!=RTNORM)
	{
		return;
	}
	AcDbUCSTable *pUCSTable = NULL;
	acdbHostApplicationServices()->workingDatabase()->getUCSTable(pUCSTable, AcDb::kForRead);

	if (pUCSTable->has(UCSName))
	{
		AcDbUCSTableRecord *pUCSTableRecord = NULL;
		pUCSTable->getAt(UCSName, pUCSTableRecord, AcDb::kForWrite);

		AcGePoint3d OriginPoint = pUCSTableRecord->origin();
		AcGeVector3d XAxis = pUCSTableRecord->xAxis();
		AcGeVector3d YAxis = pUCSTableRecord->yAxis();
		AcGeVector3d ZAxis = XAxis.crossProduct(YAxis);

		pUCSTableRecord->close();
		AcGeMatrix3d mat;
		mat.setCoordSystem(OriginPoint, XAxis, YAxis, ZAxis);
		acedGetCurrentUCS(mat);

	}
	pUCSTable->close();
}


