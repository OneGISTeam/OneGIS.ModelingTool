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

	// 复制
	CVBF_Shape* Clone();

public:

	// 获取宽度
	double GetWidth()			{ return m_dWidth; }
	void   SetWidth(double dW)	{ m_dWidth = dW;   }

	// 获取高度
	double GetHeight()			{ return m_dHeight; }
	void   SetHeight(double dH)	{ m_dHeight = dH;   }

	// 获取字符串长度
	int GetStrLen()				{ return m_nLen; }

	// 获取字体大小
	short GetStrWeight()		{return m_nWeight;}

	// 设置/获取字符内容
	std::string GetStr()				{ return m_strText; }
	void SetStr(const char* str)		{ m_strText = str; }

	// 设置/获取字符类型
	std::string GetFontName()			{ return m_strFontName; }
	void        SetFontName(string str)	{ m_strFontName = str; }

	//设置/获取字符旋转角度
	double GetAngle()					{ return m_dFontAngle; }
	void   SetAngle(double dAngle)		{ m_dFontAngle = dAngle; }

	//设置/获取字符旋转
	bool IsRotate()						{ return m_bRotate; }
	void SetRotate(bool bRotate)		{ m_bRotate = bRotate; }

	//设置/获取字符缩放
	bool IsZoom()						{ return m_bZoom; }
	void SetZoom(bool bZoom) 			{ m_bZoom = bZoom; }

	//设置/获取字符下划线
	bool IsUnderLine()					{ return m_bUnderline; } 
	void SetUnderLine(bool bUline)		{ m_bUnderline = bUline; } 

	//设置/获取字符斜体
	bool IsbItalic()					{ return m_bUnderline; } 
	void SetbItalic(bool bIatli)		{ m_bItalic = bIatli; } 

	//设置/获取字体颜色
	DWORD GetFontColor_Face()			{ return m_colorFace; }
	void  SetFontColor_Face(DWORD cl)	{ m_colorFace = cl; }

	//设置/获取字体侧面颜色
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
    bool			m_bItalic;		// 斜体
    bool			m_bUnderline;
    unsigned long	m_colorFace;
	unsigned long	m_colorSide;
};

#endif 
