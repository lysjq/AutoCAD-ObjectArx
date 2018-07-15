#pragma once
class CJig:public AcEdJig
{
public:
	CJig();
	virtual ~CJig();
	//外部调用的函数，一般用于初始化
	bool doit(const AcGePoint3d &centerPoint, AcDbObjectId &polyid);

	//此函数被drag函数调用以获得用户输入
	virtual AcEdJig::DragStatus sampler();

	//对需要在拖到过程中发生变化的实体进行修改
	virtual Adesk::Boolean update();

	//指定Jig操作的对象
	virtual AcDbEntity *entity() const;

private:
	AcDbPolyline * m_pPoly;
	AcGePoint3d m_centerPoint;
	AcGePoint3d m_curPoint;

};

