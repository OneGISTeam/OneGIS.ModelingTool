
#ifndef __SYSBOLTEMPLAT_H__
#define __SYSBOLTEMPLAT_H__

#include <VBF_Base/VBF_Referenced.h>

// 符号的基本特征数据
typedef struct  _tagMAPSBFeature
{
	_tagMAPSBFeature()
	{
		strName    = _T("ABC") ;
		strNote    = _T("") ; 
		uClassCode = 0  ;
		uCode      = 0  ;
		sizSb      = CSize(400,400);
		fScale     = 0.25f ;
	}
	_tagMAPSBFeature(_tagMAPSBFeature& sb)
	{
		Set( sb ) ;
	}
	_tagMAPSBFeature& operator=(_tagMAPSBFeature& sb)
	{
		Set( sb ) ;
		return *this;
	}
	void Set( _tagMAPSBFeature& sb ) 
	{
		strName    = sb.strName;
		strNote    = sb.strNote; 
		uClassCode = sb.uClassCode;
		uCode      = sb.uCode;
		sizSb      = sb.sizSb  ;
		fScale     = sb.fScale ;
	}
	void Serialize(CArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar << strName   ;
			ar << strNote   ; 
			ar << uClassCode;
			ar << uCode     ;
			ar << sizSb     ;
			ar << fScale    ;
		}
		else
		{
			ar >> strName   ;
			ar >> strNote   ; 
			ar >> uClassCode;
			ar >> uCode     ;
			ar >> sizSb     ;
			ar >> fScale    ; 
		}
	}

	CString strName    ;  //符号名称
	CString strNote    ;  //符号说明
	unsigned int    uClassCode ;  //符号类的编码
	unsigned int    uCode      ;  //符号编码
	CSize   sizSb   ;     // 制作时的符号大小
	float   fScale  ;     // 实际大小与制作时的符号大小的比例

}  MAPSB_SBFEATURE ;


class IMCE_SymbolTemplate : public ::CVBF_Referenced 
{
public:
	virtual ~IMCE_SymbolTemplate(){}
public:

	virtual int Type() =0;

	virtual MAPSB_SBFEATURE& GetSBFeature()=0;
	//获取符号制作大小和实际大小
	virtual CSize GetSymbolActualSize() =0;
	virtual CSize GetSymbolVirtualSize()=0;
	virtual void SetPenColor( COLORREF cr )=0 ;
	virtual void SetSmooth( bool bSmooth ) =0;

};

class IMCE_PointSymbolTemplate:public IMCE_SymbolTemplate
{
public:
	virtual ~IMCE_PointSymbolTemplate(){}
public:
	virtual void Draw(CDC *pDC,osg::Vec2i ptDraw,int nState=0 )=0 ;
	virtual void Draw(CDC *pDC,osg::Vec2i ptDraw,float fScaleX,float fScaleY,float fAngle,int nState=0)=0;

	virtual osg::Vec2i& GetPositionPoint()=0;
	virtual void SetPositionPoint(osg::Vec2i& pt)=0;

	virtual osg::Vec2i& GetDirectionPoint()=0;
	virtual void SetDirectionPoint(osg::Vec2i& pt)=0;
	
	virtual void SetData( float fScalex,float fScaley,float fAngle )=0 ;
	virtual void RestoreData()=0 ;
	virtual void GetRgn(osg::Vec2i ptDraw,float fScaleX,float fScaleY,float fAngle,HRGN& hrgn)=0;
	virtual CVBF_RectL GetBoundingRect(osg::Vec2i ptDraw,float fScaleX,float fScaleY,float fAngle)=0;
	virtual float GetDirectionAngle() =0;

	virtual int  GetDirectionType()=0;
	virtual void SetDirectionType(int nType)=0;

	virtual void Zoom(osg::Vec2i ptRef,float fScalex,float fScaley)=0;
	virtual void Offset(osg::Vec2i ptOff)=0;

};
class IMCE_LineSymbolTemplate:public IMCE_SymbolTemplate
{
public:
	virtual ~IMCE_LineSymbolTemplate(){}
public:
	virtual void SetPenColor( COLORREF cr )=0 ;
	virtual void SetSmooth( bool bSmooth )=0 ;
	virtual void SetScale(float fScalex,float fScaley)=0;
	virtual void Draw(CDC *pDC,osg::Vec2i* pPoint,int nCount,int nState=0)=0;

	virtual int GetBaseLine() =0;
	virtual int GetSectionB() =0;
	virtual int GetSectionE() =0;
	virtual void SetBaseLine(int nBaseline) =0;
	virtual void SetSectionB(int nSectionB) =0;
	virtual void SetSectionE(int nSectionE) =0;

	virtual void AdjustMetasData()=0;
};

class IMCE_SupperSymbolTemplate//:public IMCE_SymbolTemplate
{
public:
	virtual ~IMCE_SupperSymbolTemplate(){}
public:
	virtual void SetOffSerif(osg::Vec2i ptOff)=0;
	virtual void SetColorSerif(COLORREF color)=0;
	virtual bool IsSerif()=0; 
	virtual void SetSerif(bool bSerif)=0; 

	virtual void Draw( CDC* pDC,osg::Vec2i ptDraw,float fScale,float fAngle )=0;
	virtual void Draw( CDC* pDC,CVBF_RectL rDraw,int nFrame=0 )=0;

};
#endif 
