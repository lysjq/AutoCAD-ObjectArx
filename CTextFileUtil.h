#pragma once
#include <vector>
class CTextFileUtil
{
public:
	CTextFileUtil();
	~CTextFileUtil();

	//把集合中的字符串按行写入指定文件
	static void Save(const TCHAR *FileName, std::vector<CString>& text);

	//把文件中的字符串按行为元素读入集合
	static void Load(const TCHAR *FileName, std::vector<CString>& text);

};

