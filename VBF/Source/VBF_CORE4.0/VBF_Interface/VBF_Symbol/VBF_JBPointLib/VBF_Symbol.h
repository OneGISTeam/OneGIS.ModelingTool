//*******************************************************************
// FileName：VBF_Symbol.h
// Function：点状军标符号（即规则军标）
// Author:   杜莹
// Date:     2014-05-14
//*******************************************************************

#ifndef __VBF_SYMBOL_H__
#define __VBF_SYMBOL_H__

#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

using namespace std;

class VBF_JBPOINTLIB_EXPORT CVBF_Symbol
{
public:
    CVBF_Symbol();
    virtual ~CVBF_Symbol();

public:

	// 获取符号在库中的编号/名称
	unsigned int GetID() { return m_nID; } 
	std::string  GetName() { return m_strName; }

	// 获取所属类别编号/名称
	unsigned int GetClsID()	{ return m_nClassID; }
	std::string  GetClsName();

	// 获取符号中的图元集合
	const std::vector<CVBF_Shape*>& GetShapeList()	{ return m_ShapeList;} 

    //设置符号大小，重新计算包络框
    void  SetScale(double scale);
	float GetScale()	{ return m_curScale; }

    //设置符号在库中的角度
	void  SetLibAngle(double angle) { m_dLibAngle = angle; }
	float GetLibAngle()				{ return m_dLibAngle; }

public:

    // 移动符号
    void MoveSelf(int dx, int dy);

    // 旋转符号
    void RotateSelf(float angle);

    // 放大缩小符号
    void ZoomSelf(float scale);
    void ZoomSelf(float scale, osg::Vec2i ptRefer);

    // 拖动符号
    void DragSelf(int dx, int dy);

    // 符号的仿射变换
    void AffineSelf(int dx, int dy, osg::Vec2i Pt);

    // 获取各个位置的坐标 
    osg::Vec2i GetLTPt();		// 左上角
    osg::Vec2i GetLBPt();		// 左下角
    osg::Vec2i GetRTPt();		// 右上角
    osg::Vec2i GetRBPt();		// 右下角
    osg::Vec2i GetCenterPt();	// 中心点
    osg::Vec2i GetRCenterPt();	// 右边中心点
    osg::Vec2i GetLCenterPt();	// 右边中心点
    osg::Vec2i GetTCenterPt();	// 右边中心点

public:
	
	// 由文件读入符号信息
	void Read(FILE* fp);

	// 计算符号的外边形框
    void CalcSblRECT();
    CVBF_RectI GetSblRECT();

    // 画符号的外边形框
    void DrawSblGLBox();

    // 数据更新
    void dataRefresh();

public:

	// 复制
	CVBF_Symbol* Clone();

	void DataOffset(int x,int y);
	

private:

    // 符号属性
	unsigned int    m_nClassID;		// 在库中隶属符号类编号
	unsigned int    m_nID;			// 符号在库中编号
	std::string		m_strName;		// 符号在库中名称，设长度不超过10个字符
    osg::Vec2i		m_ptLocate;     // 符号在库中定位点
    double          m_dLibAngle;    // 库中在库中0度角的方向

	// 符号样式
    CVBF_RectI		m_sblrect;		// 符号的外轮廓矩形
    double			m_curScale;		// 符号放大缩小比例
    double			m_dAngle;
   
	// 图元集合
	std::vector<CVBF_Shape*> m_ShapeList; 
};

#endif 
