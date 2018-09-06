//*******************************************************************
// FileName��VBF_Shape.h
// Function�����ɵ�״������ŵĸ���ͼ��
// Author:   ��Ө
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

// �����ػ�����
typedef CVBF_Rect<int>		CVBF_RectI;


// ����ö�٣���״�������������״
enum VBF_JBSHAPE
{
    VBF_JBSHAPE_HANDLINE,		// �ֻ���
    VBF_JBSHAPE_LINE,			// ֱ��
    VBF_JBSHAPE_POLYLINE,		// ����
    VBF_JBSHAPE_CURVE,			// ����
    VBF_JBSHAPE_CLOSEDCURVE,     // �պ�����
    VBF_JBSHAPE_ARC,			// Բ��
    VBF_JBSHAPE_CIRCLE,			// Բ
	VBF_JBSHAPE_ANGLEARC,		// ��
    VBF_JBSHAPE_SECTOR,			// ����
    VBF_JBSHAPE_ELLIPSE,		// ��Բ
    VBF_JBSHAPE_RECT,			// ����
	VBF_JBSHAPE_POLYGON,		// �������
    VBF_JBSHAPE_ARBPOLYGON,		// ��������
    VBF_JBSHAPE_TEXT,			// �ַ�
};

//����ͼ����,����ͼ����Ӵ���̳�
class VBF_JBPOINTLIB_EXPORT CVBF_Shape
{
public:
	CVBF_Shape();
	virtual ~CVBF_Shape();

public:
    virtual void ZoomSelf(float scale);				//����
    virtual void ZoomSelf(float scale,osg::Vec2i ptRefer);	//����
    virtual void MoveSelf(int dx,int dy);				//�ƶ�
    virtual void RotateSelf(float angle);				//��ת
    virtual void AffineSelf(int shx,int shy);			//����
    virtual void DragSelf(int dx,int dy,int dragMode);	//�϶�

public:
    virtual void CalcBoundaryPts()=0;					//����߽��
    virtual vector<osg::Vec2i> GetBoundaryPts()=0;		//��ȡ�߽��

	vector<osg::Vec2i> m_vBoundaryPts;					//ͼ�α߽�㣬���Ƚϴ֣������жϼ�ͷ�߽�

    void  CalRect();		// ����ͼ������
    CVBF_RectI GetRect();	// ��ȡͼ������

	//����ͼԪ�Ĵ�С
    void SetShapeScale(float scale);
    float GetShapeScale();

    //���ݸ���
    void dataRefresh();
		
public:

    //������ʾ�б�
    virtual void DrawSelf()=0;
    virtual void Read(FILE* fp)=0;

	virtual CVBF_Shape* Clone() { return NULL; }

	// ��ȡͼ�ε�����
	VBF_JBSHAPE GetType() { return m_nShapeType; }

	// ��ȡ���������
    int GetPointCount();

	bool HasBrush() {return m_bHasBrush;}

	DWORD GetFillColor() {return m_fillColor;}
	void  SetFillColor(DWORD color) {m_fillColor = color;}

	osg::Vec2i GetCenterPt() {return m_centerpoint;}	//��ȡ���ĵ�

	void DataOffset(int x,int y);

public:	
    VBF_JBSHAPE		m_nShapeType;       // ͼ������
    int				m_pointcount;		// ʵ�ʵ���������
    int				m_nBeginAngle;
    int				m_nLRadius;
    int				m_nSRadius;
    int				m_nSweepAngle;
    double			K;					// MM_LOMETRIC---MM_TEXTϵ��9

	osg::Vec2i		m_point[1000];		// ͼ�����������������
    osg::Vec2i		m_copypoint[1000];  // ����ͼ�ε����������

    osg::Vec2i		m_centerpoint;		// ͼ�����ĵ�
    CVBF_RectI		m_rect;				// ͼ�����ڵľ�������
    bool			m_bHasBrush;		// �Ƿ����
    DWORD			m_lineColor;		// BGR,��ȡ����������RGB
    DWORD			m_fillColor;		// BGR,��ȡ����������RGB
};
#endif
