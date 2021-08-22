#include "stdafx.h"
#include "CGetInputUtil.h"
#include "geassign.h"


CGetInputUtil::CGetInputUtil()
{
}


CGetInputUtil::~CGetInputUtil()
{
}

AcGePoint3d CGetInputUtil::WcsToUcsPoint(const AcGePoint3d & point)
{
	AcGePoint3d pt;
	resbuf rbfrom, rbto;
	rbfrom.restype = RTSHORT;
	rbfrom.resval.rint = 0;//WCS
	rbto.restype = RTSHORT;
	rbto.resval.rint = 1;//UCS

	acedTrans(asDblArray(point), &rbfrom, &rbto, Adesk::kFalse, asDblArray(pt));

	return pt;
}

AcGePoint3d CGetInputUtil::UcsToWcsPoint(const AcGePoint3d & point)
{
	AcGePoint3d pt;
	resbuf rbfrom,rbto;
	rbfrom.restype = RTSHORT;
	rbfrom.resval.rint = 1;//UCS
	rbto.restype = RTSHORT;
	rbto.resval.rint = 0;//WCS

	acedTrans(asDblArray(point), &rbfrom, &rbto, Adesk::kFalse, asDblArray(pt));
	return pt;
}

bool CGetInputUtil::GetPoint(const AcGePoint3d & basePoint, const TCHAR * prompt, AcGePoint3d & point)
{
	//acedGetPoint函数的几点参数和返回的失去点坐标都是UCS坐标，执行前需转换，之后在转回来
	AcGePoint3d ucspoint = WcsToUcsPoint(basePoint);
	int nReturn = acedGetPoint(asDblArray(ucspoint), prompt, asDblArray(point));
	if (nReturn==RTNORM)
	{
		point = UcsToWcsPoint(point);
		return true;

	}
	else
	{
		return false;
	}
}

bool CGetInputUtil::GetPoint(const TCHAR * prompt, AcGePoint3d & point)
{
	int nReturn = acedGetPoint(NULL, prompt, asDblArray(point));
	if (nReturn==RTNORM)
	{
		point = UcsToWcsPoint(point);
		return true;
	}
	else
	{
		return false;
	}
}
