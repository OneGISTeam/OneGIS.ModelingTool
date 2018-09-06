
#ifndef __IMCE_SymbolMeta_H__
#define __IMCE_SymbolMeta_H__


#include <stdio.h>
#include <VBF_Macros.h>
#include <VBF_STL.h>
#include <VBF_Symbol/MCE_SymbolTemplLib/VBF_WinGDI.h>
#include <VBF_Symbol/MCE_SymbolTemplLib/VBF_ReadWrite.h>
#include <VBF_Symbol/MCE_SymbolTemplLib/MCE_GDIStruct.h>
#include <Types/VBF_Rect.h>
#include <Types/Vec2i.h>


// 定义特化类型
typedef CVBF_Rect<long>		CVBF_RectL;

enum
{
	MAPSB_META_POLY			= 0,		// 折线与闭合
	MAPSB_META_POLYCURVE	= 1,		// 曲线与闭合
	MAPSB_META_ARC			= 2,		// 园弧
	MAPSB_META_COMBINE		= 3,		// 组合图元
	MAPSB_META_TEXT			= 4,		// 文字图元
	MAPSB_META_BOUNDTEXT	= 5,		// 文本框
	MAPSB_META_MULTIIMAGE	= 6			// 多图像图元
};


//------------------------------------
// 定义图元的在线上的绘制方式(线符号)

#define LINEMETA_POS_HEAD 0  // nPosType=0 : 图元仅在线的首部绘制
#define LINEMETA_POS_MID  1  // nPosType=1 : 图元仅在线的中部绘制
#define LINEMETA_POS_TAIL 2  // nPosType=2 : 图元仅在线的尾部绘制 
#define LINEMETA_POS_ALL  3  // nPosType=3 : 图元在线上全线绘制


//------------------------------------
// 定义图元与中心线匹配的类型(线符号)

#define LINEMETA_MATCH_NO    0  // nMatchType=0 : 与中心线不匹配
#define LINEMETA_MATCH_HALF  1  // nMatchType=1 : 与中心线半匹配
#define LINEMETA_MATCH_ALL   2  // nMatchType=2 : 与中心线全匹配

typedef struct  _tagVRPUnit
{
	std::string		m_sSbName;
	std::string		m_sMainName;
	int				m_nFrame;
	COLORREF		m_crMask;
	bool			m_bDirection;

	_tagVRPUnit()
	{
		Default();
	}

	_tagVRPUnit( _tagVRPUnit& vr )
	{
		Set( vr );
	}
	~_tagVRPUnit() {}

	void Default()
	{
		m_sSbName    = "";
		m_sMainName  = "";
		m_nFrame     = 1;
		m_crMask     = RGB(255, 255, 255);
		m_bDirection = true;
	}

	void Read(FILE* fp)
	{
		if(NULL==fp) return;

		ReadString(fp, m_sSbName);
		ReadString(fp, m_sMainName);
		ReadInt(fp, m_nFrame);
		ReadColor(fp, m_crMask);
		ReadBool(fp, m_bDirection);
	}

	_tagVRPUnit& operator=( _tagVRPUnit& vr )
	{
		Set( vr );
		return *this;
	}

	void Set( _tagVRPUnit& vr )
	{
		m_sSbName    = vr.m_sSbName;
		m_sMainName  = vr.m_sMainName;
		m_nFrame     = vr.m_nFrame;
		m_crMask     = vr.m_crMask;
		m_bDirection = vr.m_bDirection;
	}

} VRPUNIT;



class IMCE_SymbolMeta
{
public:
	virtual ~IMCE_SymbolMeta() {}

	virtual IMCE_SymbolMeta* Clone()=0;

	virtual int Type()=0;

	virtual void Read(FILE* fp)=0;
	virtual bool IsClose() = 0;

	virtual void SetPenColor( COLORREF cr ) = 0;
	virtual void SetSmooth( bool bSmooth )  = 0;
	virtual void SetPenData( const CMCE_PenBasic& dataPen )  = 0;
	virtual void GetPenData( CMCE_PenBasic& dataPen ) = 0;
	virtual void SetBrushData( const CMCE_BrushBasic& dataBrush ) = 0;
	virtual void GetBrushData( CMCE_BrushBasic& dataBrush ) = 0;
	
	virtual void BackupData() =0;
	virtual void RestoreData()=0;
//DY	virtual void Draw(CDC* pDC, int nState=0)=0;
	virtual void SetRgn()=0;
	virtual CVBF_RectL GetBoundingRect()=0;

	virtual void SetOffset(osg::Vec2i ptOff)=0;
	virtual void OffsetRgn(osg::Vec2i ptOff)=0;
	virtual void Zoom(osg::Vec2i ptRef,float fScalex,float fScaley)=0;
	virtual void Rotate(osg::Vec2i ptRef,float fAngle)=0;
	virtual void Symmetry(osg::Vec2i ptB,osg::Vec2i ptE)=0;
	virtual void Shear(osg::Vec2i ptRef,float fShx, float fShy,int nShearType=0)=0;
	virtual void Offset(osg::Vec2i ptOff)=0;
};

class IMCE_SymbolMetaPoly : public IMCE_SymbolMeta
{ 
public:
	virtual ~IMCE_SymbolMetaPoly() {}
};
class IMCE_SymbolMetaPolyCurve : public IMCE_SymbolMeta
{ 
public:
	virtual ~IMCE_SymbolMetaPolyCurve() {}
};
class IMCE_SymbolMetaArc : public IMCE_SymbolMeta
{ 
public:
	virtual ~IMCE_SymbolMetaArc() {}
};
class IMCE_SymbolMetaText : public IMCE_SymbolMeta
{ 
public:
	virtual ~IMCE_SymbolMetaText() {}
};
class IMCE_SymbolMetaBoundText : public IMCE_SymbolMeta
{ 
public:
	virtual ~IMCE_SymbolMetaBoundText() {}
};

class IMCE_SymbolMetaMultiImage : public IMCE_SymbolMeta
{ 
public:
	virtual ~IMCE_SymbolMetaMultiImage() {}
};
class IMCE_SymbolMetaCombination : public IMCE_SymbolMeta
{ 
public:
	virtual ~IMCE_SymbolMetaCombination() {}
};
#endif 
