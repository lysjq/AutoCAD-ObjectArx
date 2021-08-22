#include "stdafx.h"
#include "CIOUtil.h"
#include "CLayerUtil.h"
#include <vector>
#include "CTextFileUtil.h"
#include "CStringUtil.h"
CIOUtil::CIOUtil()
{
}


CIOUtil::~CIOUtil()
{
}

void CIOUtil::ExportLayer(const TCHAR * FileName)
{
	AcDbObjectIdArray Layerids;
	CLayerUtil::GetAllLayerIDList(Layerids);
	std::vector<CString> LayerInfos;
	for (int i = 0; i < Layerids.length(); i++)
	{
		AcDbLayerTableRecord *pLayerTableRecord=NULL;
		if (acdbOpenObject(pLayerTableRecord, Layerids[i], AcDb::kForRead) == Acad::eOk)
		{
			std::vector<CString> line;
			TCHAR* LayerName;
			pLayerTableRecord->getName(LayerName);
			line.push_back(LayerName);
			acutDelString(LayerName);

			AcCmColor color = pLayerTableRecord->color();
			int colorindex=color.colorIndex();
			CString strcolor;
			strcolor.Format(_T("%d"), colorindex);
			line.push_back(strcolor);

			AcDbLinetypeTableRecord *pLineTypeTableRecord = NULL;
			if (acdbOpenObject(pLineTypeTableRecord, pLayerTableRecord->linetypeObjectId(), AcDb::kForRead) == Acad::eOk)
			{
				TCHAR *LineTypeName;
				pLineTypeTableRecord->getName(LineTypeName);
				line.push_back(LineTypeName);
				acutDelString(LineTypeName);
				pLineTypeTableRecord->close();
			}

			AcDb::LineWeight LineWeight=pLayerTableRecord->lineWeight();
			int iLineWeight =(int)LineWeight;
			CString strLineWeight;
			strLineWeight.Format(_T("%d"), iLineWeight);
			line.push_back(strLineWeight);
			CString LayerLineInfo;
			CStringUtil::join(line, _T(","), LayerLineInfo);
			LayerInfos.push_back(LayerLineInfo);
			pLayerTableRecord->close();
		}
	}
	CTextFileUtil::Save(FileName, LayerInfos);
} 

void CIOUtil::ImportLayer(const TCHAR * FileName)
{
	std::vector<CString> strLayerInfos;
	CTextFileUtil::Load(FileName, strLayerInfos);
	for (int i = 0; i < strLayerInfos.size(); i++)
	{
		std::vector<CString> vecstrLayerLine;//Í¼²ãÃû³Æ¡¢ÑÕÉ«¡¢Í¼²ãÏßÐÍ¡¢Í¼²ãÏß¿í
		CString strLayerLine = strLayerInfos[i];
		CStringUtil::Spil(strLayerLine, _T(","), vecstrLayerLine);
		AcDbLayerTable *pLayerTable = NULL;
		acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTable, AcDb::kForWrite);

		AcDbLayerTableRecord *pLayerTableRcord = NULL;
		TCHAR *LayerName = vecstrLayerLine[0].GetBuffer();
		if (pLayerTable ->has(LayerName))
		{
			pLayerTable->getAt(LayerName,pLayerTableRcord, AcDb::kForWrite);
		}
		else
		{
			pLayerTableRcord = new AcDbLayerTableRecord();
			pLayerTableRcord->setName(LayerName);
			pLayerTable->add(pLayerTableRcord);
		}

		AcCmColor LayerColor;
		LayerColor.setColorIndex(_ttoi(vecstrLayerLine[1]));
		pLayerTableRcord->setColor(LayerColor);

		AcDbLinetypeTable *pLineTyepe = NULL;
		acdbHostApplicationServices()->workingDatabase()->getLinetypeTable(pLineTyepe, AcDb::kForWrite);
		if (pLineTyepe->has(vecstrLayerLine[2]))
		{
			AcDbObjectId LineTypeid;
			pLineTyepe->getAt(vecstrLayerLine[2], LineTypeid);
			pLayerTableRcord->setLinetypeObjectId(LineTypeid);
		}
		pLineTyepe->close();

		AcDb::LineWeight LineWeight = (AcDb::LineWeight)_ttoi(vecstrLayerLine[2]);
		pLayerTableRcord->setLineWeight(LineWeight);
		
		pLayerTable->close();
		pLayerTableRcord->close();
	}

}
