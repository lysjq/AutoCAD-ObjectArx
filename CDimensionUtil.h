#pragma once
class CDimensionUtil
{
public:
	CDimensionUtil();
	~CDimensionUtil();

	static AcDbObjectId AddDimAligned(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, const TCHAR* dimtext = NULL, AcDbObjectId dimstyle = AcDbObjectId::kNull);


};

