//**********************************************************************************
// �ļ�����  VBF_3DStyles.h
// ������    ������ʽ�Ķ���
// ����:     ��Ө
// ����:     2013-06-25
//**********************************************************************************

#ifndef __VBF_3DSTYLES_H__
#define __VBF_3DSTYLES_H__


#include <Types/Vec4f>
#include <string>
#include <VBF_Common/VBF_Math/VBF_Math.h>
#include <Types/VBF_Optional.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/Image>


//-------------------------------------------------------------------
// ����ṹ�壺VBF_POINTSTYLE
// �ṹ������������ʽ
//-------------------------------------------------------------------
typedef struct _tagVBFPointStyle
{
    float			fSize;		// ��Ĵ�С
    osg::Vec4f		color;		// �����ɫ

    // ���캯��
    _tagVBFPointStyle()
    {
        fSize	= 1.0f;
        color	= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
    }

    _tagVBFPointStyle& operator=(const _tagVBFPointStyle& src)
    {
        if(this==&src) return *this;

        fSize	= src.fSize;
        color	= src.color;

        return *this;
    }

    bool operator==(const _tagVBFPointStyle& src)
    {
        if(this==&src) return true;

        if(!osg::equivalent(fSize, src.fSize)) return false;
        if(color!=src.color) return false;

        return true;
    }

} VBF_POINTSTYLE;


//-------------------------------------------------------------------
// ����ṹ�壺VBF_LINESTYLE
// �ṹ������������ʽ
//-------------------------------------------------------------------
typedef struct _tagVBFLineStyle
{
	osg::Vec4f			color;				// �ߵ���ɫ
	float				fWidth;				// �ߵĿ��
	int					nStippleFactor;		// �㻮�ߵ����ӣ���glLineStipple()�����ĵ�һ��������ֵ��Ϊ[1, 256]��
	unsigned short		nStipplePattern;	// �㻮�ߵ�ģʽ����glLineStipple()�����ĵڶ���������

	// ���캯��
	_tagVBFLineStyle()
	{
		color			= osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
		fWidth			= 2.0f;
		nStippleFactor	= 1;
		nStipplePattern	= 0xFFFF;
	}

	_tagVBFLineStyle& operator=(const _tagVBFLineStyle& src)
	{
		if(this==&src) return *this;

		color			= src.color;
		fWidth			= src.fWidth;
		nStippleFactor	= src.nStippleFactor;
		nStipplePattern	= src.nStipplePattern;
		return *this;
	}

	bool operator==(const _tagVBFLineStyle& src)
	{
		if(this==&src) return true;

		if(color!=src.color) return false;
		if(!osg::equivalent(fWidth, src.fWidth)) return false; 
		if(nStipplePattern!=src.nStipplePattern) return false;
		if(nStippleFactor!=src.nStippleFactor) return false;

		return true;
	}

} VBF_LINESTYLE;


//-------------------------------------------------------------------
// ����ṹ�壺VBF_POLYGON2DSTYLE
// �ṹ����������ά�������ʽ
//-------------------------------------------------------------------
typedef struct _tagPolygon2DStyle
{
	bool			bShadowed;			// �Ƿ���ʾ��ӰЧ��
	bool			bOutlined;			// �Ƿ���ʾ������
	osg::Vec4f		colorFill;			// �����ɫ
	osg::Vec4f		colorOutline;		// ��������ɫ������bOutlined=trueʱ��Ч��
	osg::Vec4f		colorShadow;		// ��Ӱ��ɫ������bShadowed=trueʱ��Ч��
	int				nShadowOffset;		// ��Ӱƫ����������bShadowed=trueʱ��Ч��

	// ���캯��
	_tagPolygon2DStyle()
	{
		bShadowed		= false;
		bOutlined		= true;
		colorFill		= osg::Vec4f(1.0f, 1.0f, 0.0f, 0.4f);
		colorOutline	= osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f);
		colorShadow		= osg::Vec4f(0.1f, 0.1f, 0.1f, 0.8f);
		nShadowOffset	= 8;
	}

	_tagPolygon2DStyle& operator=(const _tagPolygon2DStyle& src)
	{
		if(this==&src) return *this;

		bShadowed		= src.bShadowed;
		bOutlined		= src.bOutlined;
		colorFill		= src.colorFill;
		colorOutline	= src.colorOutline;
		colorShadow		= src.colorShadow;
		nShadowOffset	= src.nShadowOffset;

		return *this;
	}

	bool operator==(const _tagPolygon2DStyle& src)
	{
		if(this==&src) return true;

		if(bShadowed!=src.bShadowed) return false;
		if(colorFill!=src.colorFill) return false;
        if(bOutlined!=src.bOutlined) return false;

		if(bOutlined)
		{
			if(colorOutline!=src.colorOutline) return false;
		}

		if(bShadowed)
		{
			if(colorShadow!=src.colorShadow)     return false;
			if(nShadowOffset!=src.nShadowOffset) return false;
		}

		return true;
	}

}VBF_POLYGON2DSTYLE;


//-------------------------------------------------------------------
// ����ṹ�壺VBF_POLYGON3DSTYLE
// �ṹ����������ά�������ʽ
//-------------------------------------------------------------------
typedef struct _tagPolygon3DStyle
{
	osg::Vec4f		colorFill;		// �����ɫ

	// ���캯��
	_tagPolygon3DStyle()
	{
		colorFill	= osg::Vec4f(1.0f, 1.0f, 0.0f, 0.4f);
	}

	_tagPolygon3DStyle& operator=(const _tagPolygon3DStyle& src)
	{
		if(this==&src) return *this;
		
		colorFill	= src.colorFill;
		return *this;
	}

	bool operator==(const _tagPolygon3DStyle& src)
	{
		if(this==&src) return true;
		
		if(colorFill!=src.colorFill) return false;
		return true;
	}

}VBF_POLYGON3DSTYLE;


//-------------------------------------------------------------------
// ����ṹ�壺VBF_TEXTSTYLE
// �ṹ���������ı���ʽ
//-------------------------------------------------------------------
typedef struct _tagVBFTextStyle
{
	// ������ʽ
	std::string		strFontName;	// ���������磺simhei��ϵͳ�����β���C:/Windows/Fonts/simhei.ttf��simhei.ttc�ļ���
	float			fFontSize;		// �����С
	unsigned int	nFontResX;		// �������ֱ��ʣ�ע�⣺�ֱ��ʹ����������Ⱦ������
	unsigned int	nFontResY;		// ��������ֱ���

	// �ı���ʽ
	osg::Vec4f		colorText;		// �ı���ɫ
	float			fLineSpacing;	// �м�ࣨ���������߶ȵı��ʣ�

	// ������ʽ
	bool			bSerif;			// �Ƿ����
	osg::Vec4f		colorSerif;		// ������ɫ
	float			fSerifOffset;	// ����ƫ����������ֵ��ΧΪ��[0.03, 0.1]��
	float			fRationHW;// ���ָ߶����ȱ�

	// ���캯��
	_tagVBFTextStyle()
	{
		strFontName		= "simhei";
		fFontSize		= 24.0f;
        nFontResX		= 32;
        nFontResY		= 32;
		fLineSpacing	= 0.4f;
        colorText		= osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
		bSerif			= true;
        colorSerif		= osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		fSerifOffset	= 0.04f;
		fRationHW       = 2.0;
	}

	_tagVBFTextStyle& operator=(const _tagVBFTextStyle& src)
	{
		if(this==&src) return *this;

		strFontName		= src.strFontName;
		fFontSize		= src.fFontSize;
		nFontResX		= src.nFontResX;
		nFontResY		= src.nFontResY;
		fLineSpacing	= src.fLineSpacing;
		colorText		= src.colorText;
		bSerif			= src.bSerif;
		colorSerif		= src.colorSerif;
		fSerifOffset	= src.fSerifOffset;
		fRationHW       = src.fRationHW;
	
		return *this;
	}

	bool operator==(const _tagVBFTextStyle& src)
	{
		if(this==&src) return true;

		if(strFontName!=src.strFontName) return false;
		if(!osg::equivalent(fFontSize, src.fFontSize)) return false;
		if(nFontResX!=src.nFontResX) return false;
		if(nFontResY!=src.nFontResY) return false;
		if(!osg::equivalent(fLineSpacing, src.fLineSpacing)) return false;
		if(colorText!=src.colorText) return false;
        if(bSerif!=src.bSerif) return false;
		if(colorSerif!=src.colorSerif) return false;
		if(!osg::equivalent(fSerifOffset, src.fSerifOffset)) return false;
		if(!osg::equivalent(fRationHW, src.fRationHW)) return false;

		return true;
	}

} VBF_TEXTSTYLE;


//---------------------------------------------------------
// ����ö�٣�VBF_CUBEFACE
// ö���������������������
//---------------------------------------------------------
enum EVBF_CUBEFACE
{
    VBF_CUBEFACE_POSITIVEX  = 0,    // +x, right
    VBF_CUBEFACE_NEGATIVEX  = 1,    // -x, left
    VBF_CUBEFACE_POSITIVEY  = 2,    // +y, back
    VBF_CUBEFACE_NEGATIVEY  = 3,    // -y, front
    VBF_CUBEFACE_POSITIVEZ  = 4,    // +z, top
    VBF_CUBEFACE_NEGATIVEZ  = 5     // -z, bottom
};


//---------------------------------------------------------
// ����ṹ�壺VBF_BOUNDINGBOXSTYLE
// �ṹ����������Χ����ʽ
//---------------------------------------------------------
typedef struct _tagVBFBoundingBoxStyle
{
	// ���
	osg::Vec4f	color;				// ��Χ����ɫ
	float		fLineWidth;			// ��Χ�ߴֶ�
    float		fExpand;			// ��Χ����������������ڰ�Χ�гߴ磬ֵ��Ϊ[0.0, 1.0]��

	// ��˸
	int			nFlickerTimes;		// ��˸���ܴ���
	int			nFlickerInterval;	// ������˸֮��ļ�� (��λ��֡)
	bool		bFlickerAlways;		// �Ƿ�һֱ��˸

    // ��Χ�е�������Ŀɼ��ԣ�Ĭ��Ϊ�ɼ���ÿ�����ö��ֵ�μ�EVBF_CUBEFACE��
    bool        bFaceVisible[6];

	_tagVBFBoundingBoxStyle()
	{
		color				= osg::Vec4f(0.0f, 1.0f, 1.0f, 0.2f);
		fLineWidth			= 2.0f;	
		fExpand				= 0.05f;

		nFlickerTimes		= 3;
		nFlickerInterval	= 20;
        bFlickerAlways		= false;

        // ��Χ�е�������Ŀɼ���
        for(int i=0; i<6; i++)
        {
            bFaceVisible[i] = true;
        }
	}

	_tagVBFBoundingBoxStyle& operator=(const _tagVBFBoundingBoxStyle& src)
	{
		if(this==&src) return *this;

		color				= src.color;
		fLineWidth			= src.fLineWidth;	
		fExpand				= src.fExpand;

		nFlickerTimes		= src.nFlickerTimes;
		nFlickerInterval	= src.nFlickerInterval;
		bFlickerAlways		= src.bFlickerAlways;

        // ��Χ�е�������Ŀɼ���
        for(int i=0; i<6; i++)
        {
            bFaceVisible[i] = src.bFaceVisible[i];
        }

		return *this;
	}

	bool operator==(const _tagVBFBoundingBoxStyle& src)
	{
		if(this==&src) return true;

		if(color!=src.color) return false; 
		if(!osg::equivalent(fLineWidth, src.fLineWidth)) return false;	
		if(!osg::equivalent(fExpand, src.fExpand)) return false;

		if(nFlickerTimes!=src.nFlickerTimes) return false;
		if(nFlickerInterval!=src.nFlickerInterval) return false;
		if(bFlickerAlways!=src.bFlickerAlways) return false;

        // ��Χ�е�������Ŀɼ���
        for(int i=0; i<6; i++)
        {
            if(bFaceVisible[i]!=src.bFaceVisible[i]) return false;
        }

		return true;
	}

} VBF_BOUNDINGBOXSTYLE;


//-------------------------------------------------------------------
// ����ö�٣�VBF_TEXENV_MODE
// ö��������ͬʱʹ�ö�����ɫ������ʱ�����ߵĻ�Ϸ�ʽ������ʵ�岿�ֵ���ɫ����
//-------------------------------------------------------------------
enum EVBF_TEXENV_MODE
{
	VBF_TEXENV_MODULATE		= 0,	// ��ɫ��     rgba=colorVert*colorTex��Ĭ�ϣ�
	VBF_TEXENV_REPLACE		= 1,	// �滻��     rgb=colorVert.rgb, a=colorVert.a*colorTex.a
	VBF_TEXENV_DECAL		= 2,	// ������     rgb=mix(colorTex.rgb, colorVert.rgb, colorTex.a), a=colorVert.a
	VBF_TEXENV_ALPHAREPLACE	= 3		// Alpha�滻��rgb=colorVert.rgb, a=colorTex.a
};


//-------------------------------------------------------------------
// ����ṹ�壺VBF_LINETEXSTYLE
// �ṹ����������ĳ�������ظ������������ʽ
//-------------------------------------------------------------------
typedef struct _tagVBFLineTexStyle
{
	ref_ptr<osg::Image>		piImage;			// ����ͼ��
	bool					bTexToCache;		// �����Ƿ���뻺��
	float					fDynSpeed;			// ����̬�仯���ٶȣ�ÿ֡�仯һ���������ڵı���
	osg::Vec4f				color;				// ���������ϵ���ɫ�������п����Ǻڰ�ɫ��

	// ������ɫ������Ļ�Ϸ�ʽ
	EVBF_TEXENV_MODE		nTexEnvMode;

	// ��ѡ�����û�δ���ã�ϵͳ�ڲ��Զ����㣩
	CVBF_Optional<int>		nCycleLength;		// ����ͼ��һ���ظ���������Ļ����ռ����������Ĭ��ֵΪ����ͼ��Ŀ�ȣ���λ�����أ�
	CVBF_Optional<int>		nWidth;				// �߶ο�ȣ�Ĭ��ֵΪ����ͼ��ĸ߶ȣ���λ�����أ�
	CVBF_Optional<int>		nRepeatTimes;		// �����ظ��Ĵ���������û�δ���ã�ϵͳ�ڲ��Զ����㣩

	// ���캯��
	_tagVBFLineTexStyle()
	{
		bTexToCache	= false;
		fDynSpeed	= 0.01f;
		color		= osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		nTexEnvMode	= VBF_TEXENV_MODULATE;
	}

	_tagVBFLineTexStyle& operator=(const _tagVBFLineTexStyle& src)
	{
		if(this==&src) return *this;

		bTexToCache		= src.bTexToCache;
		piImage			= src.piImage;
		fDynSpeed		= src.fDynSpeed;
		color			= src.color;

		nCycleLength	= src.nCycleLength;
		nWidth			= src.nWidth;
		nRepeatTimes	= src.nRepeatTimes;
		nTexEnvMode		= src.nTexEnvMode;

		return *this;
	}

	bool operator==(const _tagVBFLineTexStyle& src)
	{
		if(bTexToCache!=src.bTexToCache) return false;
		if(piImage.get()!=src.piImage.get()) return false;
		if(!osg::equivalent(fDynSpeed, src.fDynSpeed)) return false;
		if(color!=src.color) return false;
		if(nCycleLength!=src.nCycleLength) return false;
		if(nWidth!=src.nWidth) return false;
		if(nRepeatTimes!=src.nRepeatTimes) return false;
		if(nTexEnvMode!=src.nTexEnvMode) return false;

		return true;
	}

} VBF_LINETEXSTYLE;


#endif
