#pragma once
class CEntityUtil
{
public:
	CEntityUtil();
	~CEntityUtil();
	//修改实体颜色
	static void setColor(AcDbObjectId objectID, int ColorIndex);

	//修改实体的图层
	static void setLayer(AcDbObjectId objectID, const TCHAR* LayerName);

	//修改实体的线性
	static void setLineType(AcDbObjectId objectID, const TCHAR* LineType);

	//按照指定角度沿一点旋转指定的实体
	static Acad::ErrorStatus Rotate(AcDbObjectId objectID, const AcGePoint2d &pBasePoint, double rotationAngle);

	//把实体从一点移动到另外一点
	static Acad::ErrorStatus Move(AcDbObjectId objectID, AcGePoint3d &pBasePoint, AcGePoint3d &pDest);

	//沿一点按比列缩放指定的实体
	static Acad::ErrorStatus Scale(AcDbObjectId objectID, const AcGePoint3d &pBasePoint, double scaleSize);
};

