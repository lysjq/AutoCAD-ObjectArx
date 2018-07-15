#pragma once
#include <vector>
class CStringUtil
{
public:
	CStringUtil();
	~CStringUtil();
	//根据给定字符分割字符串，并把分割的字符串写入集合
	static void Spil(const CString &text, const TCHAR *separater, std::vector<CString>&result);

	//把一个集合中的字符串根据给定的字符链接成一个字符串
	static void join(std::vector<CString>& result,const TCHAR *separater, CString &text);
};

