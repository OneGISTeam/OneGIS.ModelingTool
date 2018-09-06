//***************************************************************************************
// FileName��VBF_3DPlotDataTypes.h
// Function��3D��ͼʹ�õĹ�����������
// Author:   ��Ө
// Date:     2013-06-10
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_H__
#define __VBF_3DPLOT_DATATYPES_H__


#include <Types/Vec3d>
#include <Types/Vec4>
#include <string>
#include <Types/VBF_3DStyles.h>


// ��������ַ�������󳤶ȣ����ڴ��л�ʱ�Ķ�д
#define MAX_MARKID		64		// ����ID�ŵ�����ַ�����
#define MAX_CODEID		32		// ������ʽ���������ַ�����


// ʵ��ģ�͵�����
const unsigned int VBF_MARK_UNKNOWN		= 0;	// δ֪����

// ����ģ����ʵ��ģ�����͵���ʼֵ����ÿ��ģ��Ԥ��10000�����ͣ�
const unsigned int VBF_PLOT_COMMON		= 10000;	// Commonģ��
const unsigned int VBF_PLOT_SHAPE		= 20000;	// Shapeģ��
const unsigned int VBF_PLOT_ELECMAG		= 30000;	// ElecMagģ��
const unsigned int VBF_PLOT_AVIATION    = 40000;	// Aviationģ��
const unsigned int VBF_PLOT_JB_DKY		= 50000;	// ����ģ��
const unsigned int VBF_PLOT_JB_DTIS		= 60000;	// DTIS����ģ��
const unsigned int VBF_PLOT_SATELLITE	= 70000;	// ����ģ��
const unsigned int VBF_PLOT_MASSIVE     = 80000;	// ����ģ��ģ��
const unsigned int VBF_PLOT_MARINE      = 90000;	// ����ģ��

const unsigned int VBF_PLOT_STOBJECT      = 100000;	// ������ʱ�ն���ģ��

// �����ѯ��Ϣ����Ҫ��ʾ��������û������ʹ�����е�һ������
#define VBF_QUERYINFO_ITEM_ID			0x00000001	// ģ�͵�ID��
#define VBF_QUERYINFO_ITEM_CODE			0x00000002	// ģ�͵ı���
#define VBF_QUERYINFO_ITEM_COORDGEO		0x00000004	// ģ�͵ĵ�������
#define VBF_QUERYINFO_ITEM_CUSTOM		0x00000008	// �û��Զ�������


//--------------------------------------------------------------------
// ����ö�٣�EVBF_VIEW_MODE
// ö��������ģ�͵Ĺ۲췽ʽ
//--------------------------------------------------------------------
enum EVBF_VIEW_MODE
{
    VBF_VIEW_MODE_NORMAL        = 0,    // ����ģ�͵ĳ�ʼ��̬��Ĭ��ֵ��ע�⣺����ͼƬ��ģ�͵ĳ�ʼ��̬��Ϊƽ���ڵ��棩
    VBF_VIEW_MODE_BILLBOARD_H	= 1,    // ģ����ˮƽ����ʹ�ò�����
    VBF_VIEW_MODE_BILLBOARD_V	= 2,    // ģ���ڴ�ֱ����ʹ�ò�����
    VBF_VIEW_MODE_BILLBOARD_HV	= 3,    // ģ����ˮƽ�ʹ�ֱ����ͬʱʹ�ò�����
    VBF_VIEW_MODE_HORIZON       = 4     // ģ��ʼ��ƽ���ڵ��棬���ӵ��޹�
};

//--------------------------------------------------------------------
// ����ö�٣�EVBF_ROTATE_ORDER
// ö��������ģ�͵���ת˳��
//--------------------------------------------------------------------
enum EVBF_ROTATE_ORDER
{
	VBF_ROTATE_ORDER_XYZ = 0,
	VBF_ROTATE_ORDER_XZY,
	VBF_ROTATE_ORDER_YXZ,
	VBF_ROTATE_ORDER_YZX,
	VBF_ROTATE_ORDER_ZXY,	// Ĭ��ֵ
	VBF_ROTATE_ORDER_ZYX
};


//------------------------------------------------------------------
// ����ö�٣�EVBF_SIMTIMEMODE
// ö������������ʱ�䷽ʽ(����/�䳤)
//------------------------------------------------------------------
enum EVBF_SIMTIME_MODE
{
	VBF_SIMTIME_MODE_FIXED		= 0,	// ���������ݷ���ʱ�䲽��(��)������̶������ĵ�
	VBF_SIMTIME_MODE_VARIABLE	= 1,	// �䳤�������������ݵ�֮���ʱ���(��)��������Ҫ��ֵ�ĵ�����Ĭ��ֵ��
	VBF_SIMTIME_MODE_REALTIME	= 2		// ʵʱ������Ҫϵͳ�ڲ���ֵ��ֱ��ʹ��StepGeoPos()�д��ݵ�����ֵ
};


//------------------------------------------------------------------
// ����ṹ�壺VBF_FLICKERPARAM
// �ṹ����������˸�Ĳ���
//------------------------------------------------------------------
typedef struct _tagVBFFlickerParam
{
    int     nFlickerTimes;      // ��˸���ܴ���
    int     nFlickerInterval;   // ��˸���ٶȣ���������˸֮��ļ�� (��λ��֡)
    bool    bFlickerAlways;     // �Ƿ�һֱ��˸�����Ϊtrue������nFlickerTimes��������

    _tagVBFFlickerParam()
    {
        nFlickerTimes    = 3;
        nFlickerInterval = 20;
        bFlickerAlways   = false;
    }

    _tagVBFFlickerParam& operator=(const _tagVBFFlickerParam& src)
    {
        if(this==&src) return *this;

        nFlickerTimes    = src.nFlickerTimes;
        nFlickerInterval = src.nFlickerInterval;
        bFlickerAlways   = src.bFlickerAlways;

        return *this;
    }

} VBF_FLICKERPARAM;


//------------------------------------------------------------------
// ����ṹ�壺VBF_MARKDOCLAYERINFO
// �ṹ��������ģ�͵��ĵ�ͼ����Ϣ����ģ�����ڵ��ĵ���ͼ���ģ��ID��
//------------------------------------------------------------------
typedef struct _tagVBFMarkDocLayerInfo
{
    std::string		strDocName;     // ģ�����ڵ��ĵ�
    std::string     strLayerName;   // ģ�����ڵ�ͼ��
    std::string     strMarkID;      // ģ�͵�ID��

    _tagVBFMarkDocLayerInfo()
    {
        strDocName   = "";
        strLayerName = "";
        strMarkID    = "";
    }

    _tagVBFMarkDocLayerInfo& operator=(const _tagVBFMarkDocLayerInfo& src)
    {
        if(this==&src) return *this;

        strDocName   = src.strDocName;
        strLayerName = src.strLayerName;
        strMarkID    = src.strMarkID;

        return *this;
    }

} VBF_MARKDOCLAYERINFO;



//------------------------------------------------------------------
// ����ṹ�壺VBF_MARKQUERYSTYLE
// �ṹ������������ģ�ͱ���ѯ�������ʾ��ʽ������ģ�͵Ŀ���ѡ��ȣ�
//------------------------------------------------------------------
typedef struct _tagVBFMarkQueryStyle
{
    // ��ѯ���ģ��
    osg::Vec4f              colorBlend;             // ��ѯ���ģ�ͻ�ɫ
    bool                    bModulate;              // ��ѯ���ģ�ͻ�ɫ�Ƿ�ʹ�ó�ɫ

    // ��ѯ�����Ϣ
    DWORD                   dwInfoItem;             // ��ѯ��Ϣ������
    std::string             strCustomInfo;          // ��ѯ��Ϣ���û��Զ��������
    VBF_TEXTSTYLE           TextStyle;              // ��ѯ��Ϣ���ı���ʽ
    bool                    bFrameVisible;          // ��ѯ��Ϣ�ı������Ƿ�ɼ�
    VBF_POLYGON2DSTYLE      FrameStyle;             // ��ѯ��Ϣ�ı�������ʽ

    _tagVBFMarkQueryStyle()
    {
        // ģ�ͻ�ɫ
        colorBlend  = osg::Vec4f(0, 1, 1, 0.6);
        bModulate   = false;

        // ��ѯ��Ϣ������
        dwInfoItem    = (VBF_QUERYINFO_ITEM_ID | VBF_QUERYINFO_ITEM_CODE);
        strCustomInfo = "";

        // ��ѯ��Ϣ���ı���ʽ
        TextStyle.strFontName       = "msyh";
        TextStyle.bSerif            = true;
        TextStyle.fFontSize         = 22;
        TextStyle.colorText         = osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);	// ��ɫ
        TextStyle.colorSerif        = osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);	// ��ɫ

        // ��ѯ��Ϣ�ı�������ʽ
        bFrameVisible = true;

        FrameStyle.bShadowed        = true;
        FrameStyle.nShadowOffset    = 4;
        FrameStyle.colorFill        = osg::Vec4f(1.0f, 1.0f, 0.0f, 0.7f);
        FrameStyle.colorOutline     = osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f);
        FrameStyle.colorShadow      = osg::Vec4f(0.1, 0.1, 0.1, 1.0);
    }

    _tagVBFMarkQueryStyle& operator=(const _tagVBFMarkQueryStyle& src)
    {
        if(this==&src) return *this;

        colorBlend      = src.colorBlend;
        bModulate       = src.bModulate;
        dwInfoItem      = src.dwInfoItem;
        strCustomInfo   = src.strCustomInfo;
        TextStyle       = src.TextStyle;
        bFrameVisible   = src.bFrameVisible;
        FrameStyle      = src.FrameStyle;

        return *this;
    }

} VBF_MARKQUERYSTYLE;


//------------------------------------------------------------------
// ����ṹ�壺VBF_MARKSTATEINFO
// �ṹ������������ģ�͵�״̬��Ϣ
//------------------------------------------------------------------
typedef struct _tagVBFMarkStateInfo
{
	char	szName[64];		// ״̬���ƣ��硰��ը���������ˡ���
	char	szDesc[256];	// ״̬������Ϣ

	_tagVBFMarkStateInfo()
	{
		szName[0]	= '\0';
		szDesc[0]	= '\0';
	}

} VBF_MARKSTATEINFO;


//--------------------------------------------------------------------------
// ����ṹ�壺VBF_TRAILPOINT
// �ṹ��������ģ�����˶������еĹ켣����Ϣ
//--------------------------------------------------------------------------
typedef struct _tagVBFTrailPoint
{
    bool			bKeyPoint;		// �Ƿ�Ϊ�ؼ��㣨���Ƿ�Ϊ�û����������㣬��ֵ��ϵͳ�ڲ����ã�
    osg::Vec3d		vPosGeo;		// ģ�͵ĵ�������
    float			fRotateX;		// ��ת�� (��λ���Ƕ�)
    float			fRotateY;
    float			fRotateZ;
    std::string     strInfo;        // �õ㴦����Ϣ������Ϊ���ַ�����ֻ�йؼ��������Ϣ����ֵ��û�У�

    // ���캯��
    _tagVBFTrailPoint()
    {
        bKeyPoint	= false;
        vPosGeo		= osg::Vec3d(0.0, 0.0, 0.0);
        fRotateX	= 0.0f;
        fRotateY	= 0.0f;
        fRotateZ	= 0.0f;
        strInfo     = "";
    }

    // ���캯��
    _tagVBFTrailPoint(bool bKey, const osg::Vec3d& vGeo, float fRotateX0, float fRotateY0, float fRotateZ0, const std::string& strInfo0="")
    {
        bKeyPoint	= bKey;
        vPosGeo		= vGeo;
        fRotateX	= fRotateX0;
        fRotateY	= fRotateY0;
        fRotateZ	= fRotateZ0;
        strInfo     = strInfo0;
    }

    // �������캯��
    _tagVBFTrailPoint(const _tagVBFTrailPoint& src)
    {
        *this = src;
    }

    // ��ֵ�����
    _tagVBFTrailPoint& operator=(const _tagVBFTrailPoint& src)
    {
        // ��ֹsrc=src�����Ĳ���
        if( this==&src )  return *this;

        bKeyPoint	= src.bKeyPoint;
        vPosGeo		= src.vPosGeo;
        fRotateX	= src.fRotateX;
        fRotateY	= src.fRotateY;
        fRotateZ	= src.fRotateZ;
        strInfo     = src.strInfo;

        return *this;
    }

    // ����==�����
    bool operator==(const _tagVBFTrailPoint& src)
    {
        if( this==&src )  return true;

        if(bKeyPoint!=src.bKeyPoint)    return false;
        if(vPosGeo!=src.vPosGeo)        return false;
        if(fRotateX!=src.fRotateX)      return false;
        if(fRotateY!=src.fRotateY)      return false;
        if(fRotateZ!=src.fRotateZ)      return false;
        if(strInfo!=src.strInfo)        return false;

        return true;
    }

} VBF_TRAILPOINT;



#endif
