#pragma once
class CHatchUtil
{
public:
	CHatchUtil();
	~CHatchUtil();

	static AcDbObjectId Add(const AcDbObjectIdArray &loopids, const TCHAR *patName, double patternScale);
};

