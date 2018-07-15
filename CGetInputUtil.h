#pragma once
class CGetInputUtil
{
public:
	CGetInputUtil();
	~CGetInputUtil();

	//WCS转化为UCS
	static AcGePoint3d WcsToUcsPoint(const AcGePoint3d &point);

	//UCS转换为WCS
	static AcGePoint3d UcsToWcsPoint(const AcGePoint3d &point);

	//指定基点的情况下提示用户选取一个点
	static bool GetPoint(const AcGePoint3d &basePoint, const TCHAR* prompt, AcGePoint3d &point);

	//不指定基点的情况下提示用户选取一个点
	static bool GetPoint(const TCHAR* prompt, AcGePoint3d &point);
};

