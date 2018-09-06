//*******************************************************************
// FileName：VBF_Shape.h
// Function：构成点状军标符号的各类图形
// Author:   杜莹
// Date:     2014-05-14
//*******************************************************************

#ifndef __VBF_SHAPE_H__
#define __VBF_SHAPE_H__



#include <Types/Vec2i.h>
#include <Types/Vec2f>
#include <Types/VBF_Rect.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_JBPointLibDataTypes.h>
#include <VBF_Symbol/VBF_JBPointLib/VBF_JBPointLibExport.h>
#include <VBF_STL.h>

using namespace std;

// 定义特化类型
typedef CVBF_Rect<int>		CVBF_RectI;


// 定义枚举：点状规则军标军标的形状
enum VBF_JBSHAPE
{
    VBF_JBSHAPE_HANDLINE,		// 手绘线
    VBF_JBSHAPE_LINE,			// 直线
    VBF_JBSHAPE_POLYLINE,		// 折线
    VBF_JBSHAPE_CURVE,			// 曲线
    VBF_JBSHAPE_CLOSEDCURVE,     // 闭合曲线
    VBF_JBSHAPE_ARC,			// 圆弧
    VBF_JBSHAPE_CIRCLE,			// 圆
	VBF_JBSHAPE_ANGLEARC,		// 弦
    VBF_JBSHAPE_SECTOR,			// 扇形
    VBF_JBSHAPE_ELLIPSE,		// 椭圆
    VBF_JBSHAPE_RECT,			// 矩形
	VBF_JBSHAPE_POLYGON,		// 正多边形
    VBF_JBSHAPE_ARBPOLYGON,		// 任意多边形
    VBF_JBSHAPE_TEXT,			// 字符
};

//基本图形类,具体图形类从此类继承
class VBF_JBPOINTLIB_EXPORT CVBF_Shape
{
public:
	CVBF_Shape();
	virtual ~CVBF_Shape();

public:
    virtual void ZoomSelf(float scale);				//缩放
    virtual void ZoomSelf(float scale,osg::Vec2i ptRefer);	//缩放
    virtual void MoveSelf(int dx,int dy);				//移动
    virtual void RotateSelf(float angle);				//旋转
    virtual void AffineSelf(int shx,int shy);			//仿射
    virtual void DragSelf(int dx,int dy,int dragMode);	//拖动

public:
    virtual void CalcBoundaryPts()=0;					//计算边界点
    virtual vector<osg::Vec2i> GetBoundaryPts()=0;		//获取边界点

	vector<osg::Vec2i> m_vBoundaryPts;					//图形边界点，精度较粗，用于判断箭头边界

    void  CalRect();		// 计算图形轮廓
    CVBF_RectI GetRect();	// 获取图形轮廓

	//设置图元的大小
    void SetShapeScale(float scale);
    float GetShapeScale();

    //数据更新
    void dataRefresh();
		
public:

    //创建显示列表
    virtual void DrawSelf()=0;
    virtual void Read(FILE* fp)=0;

	virtual CVBF_Shape* Clone() { return NULL; }

	// 获取图形的类型
	VBF_JBSHAPE GetType() { return m_nShapeType; }

	// 获取特征点个数
    int GetPointCount();

	bool HasBrush() {return m_bHasBrush;}

	DWORD GetFillColor() {return m_fillColor;}
	void  SetFillColor(DWORD color) {m_fillColor = color;}

	osg::Vec2i GetCenterPt() {return m_centerpoint;}	//获取中心点

	void DataOffset(int x,int y);

public:	
    VBF_JBSHAPE		m_nShapeType;       // 图形类型
    int				m_pointcount;		// 实际的特征点数
    int				m_nBeginAngle;
    int				m_nLRadius;
    int				m_nSRadius;
    int				m_nSweepAngle;
    double			K;					// MM_LOMETRIC---MM_TEXT系数9

	osg::Vec2i		m_point[1000];		// 图形特征点坐标的数组
    osg::Vec2i		m_copypoint[1000];  // 备份图形点坐标的数组

    osg::Vec2i		m_centerpoint;		// 图形中心点
    CVBF_RectI		m_rect;				// 图形所在的矩形区域
    bool			m_bHasBrush;		// 是否填充
    DWORD			m_lineColor;		// BGR,读取出来数据是RGB
    DWORD			m_fillColor;		// BGR,读取出来数据是RGB
};
#endif
