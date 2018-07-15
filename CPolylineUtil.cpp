#include "stdafx.h"
#include "CPolylineUtil.h"
#include "CDwgDatebaseUtil.h"
#include <cmath>
#include "CEntityUtil.h"
#define PI 3.1415926

CPolylineUtil::CPolylineUtil()
{
}


CPolylineUtil::~CPolylineUtil()
{
}

AcDbObjectId CPolylineUtil::add(const AcGePoint2dArray & Points, double width)
{
	int numVertices = Points.length();
	AcDbPolyline *pPolyline = new AcDbPolyline(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		pPolyline->addVertexAt(i, Points.at(i), 0, width, width);
	}

	return CDwgDatebaseUtil::PostToModelSpace(pPolyline);
}

AcDbObjectId CPolylineUtil::add(const AcGePoint3dArray & Points)
{
	AcGePoint3dArray verts = Points;
	AcDb3dPolyline *pPolyline = new AcDb3dPolyline(AcDb::k3dSimplePoly, verts);
	return CDwgDatebaseUtil::PostToModelSpace(pPolyline);
}

AcDbObjectId CPolylineUtil::addPolygon(AcGePoint2d & pCenterPoint, int number, double radius, double ratation, double width)
{
	double angle = 2 * PI / number;
	AcGePoint2dArray Points;
	for (int i = 0; i < number; i++)
	{
		AcGePoint2d pt;
		pt.x = pCenterPoint.x + radius * cos(i*angle);
		pt.y = pCenterPoint.y + radius * sin(i*angle);
		Points.append(pt);
	}
	AcDbObjectId Polyid = add(Points, width);

	AcDbEntity *pEntity;
	Acad::ErrorStatus es;
	es = acdbOpenObject(pEntity, Polyid, AcDb::kForWrite);
	if (Acad::eOk==es)
	{
		if (pEntity->isKindOf(AcDbPolyline::desc()) == Adesk::kTrue)
		{
			AcDbPolyline *pPolyline = AcDbPolyline::cast(pEntity);
			pPolyline->setClosed(Adesk::kTrue);
		}
		pEntity->close();
	}
	CEntityUtil::Rotate(Polyid, pCenterPoint, ratation);
	return Polyid;
}

AcDbObjectId CPolylineUtil::addRect(const AcGePoint2d & Point1, const AcGePoint2d & Point2, double width)
{
	double x1 = min(Point1.x, Point2.x);
	double x2 = max(Point1.x, Point2.x);
	double y1 = min(Point1.y, Point2.y);
	double y2 = max(Point1.y, Point2.y);
	AcGePoint2d LeftButtom(x1, y1);
	AcGePoint2d LeftTop(x1, y2);
	AcGePoint2d RightTop(x2, y2);
	AcGePoint2d RightButtom(x2, y1);

	AcDbPolyline *pPolyline = new AcDbPolyline(4);
	pPolyline->addVertexAt(0, LeftButtom, 0, width, width);
	pPolyline->addVertexAt(1, LeftTop, 0, width, width);
	pPolyline->addVertexAt(2, RightTop, 0, width, width);
	pPolyline->addVertexAt(3, RightButtom, 0, width, width);

	pPolyline->setClosed(Adesk::kTrue);

	return CDwgDatebaseUtil::PostToModelSpace(pPolyline);
}
