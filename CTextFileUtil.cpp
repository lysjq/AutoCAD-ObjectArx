#include "stdafx.h"
#include "CTextFileUtil.h"


CTextFileUtil::CTextFileUtil()
{
}


CTextFileUtil::~CTextFileUtil()
{
}

void CTextFileUtil::Save(const TCHAR * FileName, std::vector<CString>& text)
{
	CStdioFile File;
	if (File.Open(FileName,CFile::modeCreate|CFile::modeWrite|CFile::typeText)==TRUE)
	{
		for (int i = 0; i< text.size(); i++)
		{
			File.WriteString(text[i]);
			File.WriteString(_T("\n"));
		}
		File.Close();
	}
}

void CTextFileUtil::Load(const TCHAR * FileName, std::vector<CString>& text)
{
	text.clear();
	CStdioFile File;
	if (File.Open(FileName,CFile::modeRead|CFile::typeText)==TRUE)
	{
		CString strLine;
		while (File.ReadString(strLine))
		{
			text.push_back(strLine);
		}
		File.Close();
	}
}
