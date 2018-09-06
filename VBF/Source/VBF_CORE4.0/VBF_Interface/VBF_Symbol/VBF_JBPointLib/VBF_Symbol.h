//*******************************************************************
// FileName��VBF_Symbol.h
// Function����״������ţ���������꣩
// Author:   ��Ө
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

	// ��ȡ�����ڿ��еı��/����
	unsigned int GetID() { return m_nID; } 
	std::string  GetName() { return m_strName; }

	// ��ȡ���������/����
	unsigned int GetClsID()	{ return m_nClassID; }
	std::string  GetClsName();

	// ��ȡ�����е�ͼԪ����
	const std::vector<CVBF_Shape*>& GetShapeList()	{ return m_ShapeList;} 

    //���÷��Ŵ�С�����¼�������
    void  SetScale(double scale);
	float GetScale()	{ return m_curScale; }

    //���÷����ڿ��еĽǶ�
	void  SetLibAngle(double angle) { m_dLibAngle = angle; }
	float GetLibAngle()				{ return m_dLibAngle; }

public:

    // �ƶ�����
    void MoveSelf(int dx, int dy);

    // ��ת����
    void RotateSelf(float angle);

    // �Ŵ���С����
    void ZoomSelf(float scale);
    void ZoomSelf(float scale, osg::Vec2i ptRefer);

    // �϶�����
    void DragSelf(int dx, int dy);

    // ���ŵķ���任
    void AffineSelf(int dx, int dy, osg::Vec2i Pt);

    // ��ȡ����λ�õ����� 
    osg::Vec2i GetLTPt();		// ���Ͻ�
    osg::Vec2i GetLBPt();		// ���½�
    osg::Vec2i GetRTPt();		// ���Ͻ�
    osg::Vec2i GetRBPt();		// ���½�
    osg::Vec2i GetCenterPt();	// ���ĵ�
    osg::Vec2i GetRCenterPt();	// �ұ����ĵ�
    osg::Vec2i GetLCenterPt();	// �ұ����ĵ�
    osg::Vec2i GetTCenterPt();	// �ұ����ĵ�

public:
	
	// ���ļ����������Ϣ
	void Read(FILE* fp);

	// ������ŵ�����ο�
    void CalcSblRECT();
    CVBF_RectI GetSblRECT();

    // �����ŵ�����ο�
    void DrawSblGLBox();

    // ���ݸ���
    void dataRefresh();

public:

	// ����
	CVBF_Symbol* Clone();

	void DataOffset(int x,int y);
	

private:

    // ��������
	unsigned int    m_nClassID;		// �ڿ���������������
	unsigned int    m_nID;			// �����ڿ��б��
	std::string		m_strName;		// �����ڿ������ƣ��賤�Ȳ�����10���ַ�
    osg::Vec2i		m_ptLocate;     // �����ڿ��ж�λ��
    double          m_dLibAngle;    // �����ڿ���0�Ƚǵķ���

	// ������ʽ
    CVBF_RectI		m_sblrect;		// ���ŵ�����������
    double			m_curScale;		// ���ŷŴ���С����
    double			m_dAngle;
   
	// ͼԪ����
	std::vector<CVBF_Shape*> m_ShapeList; 
};

#endif 
