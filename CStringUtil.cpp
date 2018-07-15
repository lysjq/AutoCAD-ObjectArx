#include "stdafx.h"
#include "CStringUtil.h"


CStringUtil::CStringUtil()
{
}


CStringUtil::~CStringUtil()
{
}

void CStringUtil::Spil(const CString & text, const TCHAR * separater, std::vector<CString>& result)
{
	int pre = 0, cur = 0;
	CString strcopytext = text;
	strcopytext.Trim(_T(" "));
	if (strcopytext.Find(separater,0)<0)
	{                                                                                                                                                                                         
		if (strcopytext.GetLength() > 0)
		{
			result.push_back(strcopytext);
		}
	}
	else
	{
		int textLemgth = strcopytext.GetLength();
		while (true)
		{
			CString strspil("");
			cur = strcopytext.Find(separater, pre);
			if (cur>0)
			{
				strspil=strcopytext.Mid(pre, cur-pre);
				if (strspil.GetLength()>0)
				{
					result.push_back(strspil);
				}
				pre =static_cast<int>(cur+_tcslen(separater));
			}
			else
			{
				strspil = strcopytext.Mid(pre,textLemgth);
				if (strspil.GetLength()>0)
				{
					result.push_back(strspil);
				}
				break;
			}
		}
	}
}

void CStringUtil::join(std::vector<CString>& result, const TCHAR * separater, CString & text)
{
	text = _T("");
	if (result.size()>0)
	{
		for (size_t i = 0; i < result.size(); i++)
		{
			text += result[i] + separater;
		}
		text = text.TrimRight(separater);
	}
}

