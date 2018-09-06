#ifndef _CHAR_H_
#define _CHAR_H_


#include <VBF_Symbol/VBF_JBPointLib/VBF_Shape.h>

class VBF_JBPOINTLIB_EXPORT CVBF_ShapeText : public CVBF_Shape  
{
public:
    CVBF_ShapeText();
	CVBF_ShapeText(osg::Vec2i pt1, osg::Vec2i pt2, osg::Vec2i pt3, osg::Vec2i pt4, std::string strTxt); 
    virtual ~CVBF_ShapeText();

public:
    virtual void CalcBoundaryPts();
    virtual vector<osg::Vec2i> GetBoundaryPts();
    virtual void DrawSelf();
    virtual void Read(FILE* fp);

	// ����
	CVBF_Shape* Clone();

public:

	// ��ȡ���
	double GetWidth()			{ return m_dWidth; }
	void   SetWidth(double dW)	{ m_dWidth = dW;   }

	// ��ȡ�߶�
	double GetHeight()			{ return m_dHeight; }
	void   SetHeight(double dH)	{ m_dHeight = dH;   }

	// ��ȡ�ַ�������
	int GetStrLen()				{ return m_nLen; }

	// ��ȡ�����С
	short GetStrWeight()		{return m_nWeight;}

	// ����/��ȡ�ַ�����
	std::string GetStr()				{ return m_strText; }
	void SetStr(const char* str)		{ m_strText = str; }

	// ����/��ȡ�ַ�����
	std::string GetFontName()			{ return m_strFontName; }
	void        SetFontName(string str)	{ m_strFontName = str; }

	//����/��ȡ�ַ���ת�Ƕ�
	double GetAngle()					{ return m_dFontAngle; }
	void   SetAngle(double dAngle)		{ m_dFontAngle = dAngle; }

	//����/��ȡ�ַ���ת
	bool IsRotate()						{ return m_bRotate; }
	void SetRotate(bool bRotate)		{ m_bRotate = bRotate; }

	//����/��ȡ�ַ�����
	bool IsZoom()						{ return m_bZoom; }
	void SetZoom(bool bZoom) 			{ m_bZoom = bZoom; }

	//����/��ȡ�ַ��»���
	bool IsUnderLine()					{ return m_bUnderline; } 
	void SetUnderLine(bool bUline)		{ m_bUnderline = bUline; } 

	//����/��ȡ�ַ�б��
	bool IsbItalic()					{ return m_bUnderline; } 
	void SetbItalic(bool bIatli)		{ m_bItalic = bIatli; } 

	//����/��ȡ������ɫ
	DWORD GetFontColor_Face()			{ return m_colorFace; }
	void  SetFontColor_Face(DWORD cl)	{ m_colorFace = cl; }

	//����/��ȡ���������ɫ
	DWORD GetFontColor_Side()			{ return m_colorSide; }
	void  SetFontColor_Side(DWORD cl)	{ m_colorSide = cl; }
	
private:
    std::string		m_strText;
	std::string		m_strFontName;

	bool			m_bRotate; 
	bool			m_bZoom;  

	double			m_dAngle;
	double			m_dHeight;
    double			m_dWidth;
	double			m_dFontAngle;
	double			m_dZoomScale;

    int				m_nLen;
    short			m_nWeight;
    bool			m_bItalic;		// б��
    bool			m_bUnderline;
    unsigned long	m_colorFace;
	unsigned long	m_colorSide;
};

#endif 
