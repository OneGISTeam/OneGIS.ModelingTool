//***************************************************************************************
// FileName：VBF_3DPlotDataTypes.h
// Function：3D标图使用的公用数据类型
// Author:   杜莹
// Date:     2013-06-10
//***************************************************************************************

#ifndef __VBF_3DPLOT_DATATYPES_H__
#define __VBF_3DPLOT_DATATYPES_H__


#include <Types/Vec3d>
#include <Types/Vec4>
#include <string>
#include <Types/VBF_3DStyles.h>


// 定义各种字符串的最大长度，便于串行化时的读写
#define MAX_MARKID		64		// 军标ID号的最大字符长度
#define MAX_CODEID		32		// 军标样式编码的最大字符长度


// 实体模型的类型
const unsigned int VBF_MARK_UNKNOWN		= 0;	// 未知类型

// 各个模块中实体模型类型的起始值（给每个模块预留10000个类型）
const unsigned int VBF_PLOT_COMMON		= 10000;	// Common模块
const unsigned int VBF_PLOT_SHAPE		= 20000;	// Shape模块
const unsigned int VBF_PLOT_ELECMAG		= 30000;	// ElecMag模块
const unsigned int VBF_PLOT_AVIATION    = 40000;	// Aviation模块
const unsigned int VBF_PLOT_JB_DKY		= 50000;	// 军标模块
const unsigned int VBF_PLOT_JB_DTIS		= 60000;	// DTIS军标模块
const unsigned int VBF_PLOT_SATELLITE	= 70000;	// 卫星模块
const unsigned int VBF_PLOT_MASSIVE     = 80000;	// 海量模型模块
const unsigned int VBF_PLOT_MARINE      = 90000;	// 航海模块

const unsigned int VBF_PLOT_STOBJECT      = 100000;	// 多粒度时空对象模型

// 定义查询信息中需要显示的内容项，用户可组合使用其中的一项或多项
#define VBF_QUERYINFO_ITEM_ID			0x00000001	// 模型的ID号
#define VBF_QUERYINFO_ITEM_CODE			0x00000002	// 模型的编码
#define VBF_QUERYINFO_ITEM_COORDGEO		0x00000004	// 模型的地理坐标
#define VBF_QUERYINFO_ITEM_CUSTOM		0x00000008	// 用户自定义内容


//--------------------------------------------------------------------
// 定义枚举：EVBF_VIEW_MODE
// 枚举描述：模型的观察方式
//--------------------------------------------------------------------
enum EVBF_VIEW_MODE
{
    VBF_VIEW_MODE_NORMAL        = 0,    // 保持模型的初始姿态（默认值，注意：所有图片类模型的初始姿态均为平行于地面）
    VBF_VIEW_MODE_BILLBOARD_H	= 1,    // 模型在水平方向使用布告牌
    VBF_VIEW_MODE_BILLBOARD_V	= 2,    // 模型在垂直方向使用布告牌
    VBF_VIEW_MODE_BILLBOARD_HV	= 3,    // 模型在水平和垂直方向同时使用布告牌
    VBF_VIEW_MODE_HORIZON       = 4     // 模型始终平行于地面，与视点无关
};

//--------------------------------------------------------------------
// 定义枚举：EVBF_ROTATE_ORDER
// 枚举描述：模型的旋转顺序
//--------------------------------------------------------------------
enum EVBF_ROTATE_ORDER
{
	VBF_ROTATE_ORDER_XYZ = 0,
	VBF_ROTATE_ORDER_XZY,
	VBF_ROTATE_ORDER_YXZ,
	VBF_ROTATE_ORDER_YZX,
	VBF_ROTATE_ORDER_ZXY,	// 默认值
	VBF_ROTATE_ORDER_ZYX
};


//------------------------------------------------------------------
// 定义枚举：EVBF_SIMTIMEMODE
// 枚举描述：仿真时间方式(定长/变长)
//------------------------------------------------------------------
enum EVBF_SIMTIME_MODE
{
	VBF_SIMTIME_MODE_FIXED		= 0,	// 定长：根据仿真时间步长(秒)，插入固定个数的点
	VBF_SIMTIME_MODE_VARIABLE	= 1,	// 变长：根据两次数据点之间的时间差(秒)，计算需要插值的点数（默认值）
	VBF_SIMTIME_MODE_REALTIME	= 2		// 实时：不需要系统内部插值，直接使用StepGeoPos()中传递的坐标值
};


//------------------------------------------------------------------
// 定义结构体：VBF_FLICKERPARAM
// 结构体描述：闪烁的参数
//------------------------------------------------------------------
typedef struct _tagVBFFlickerParam
{
    int     nFlickerTimes;      // 闪烁的总次数
    int     nFlickerInterval;   // 闪烁的速度，即两次闪烁之间的间隔 (单位：帧)
    bool    bFlickerAlways;     // 是否一直闪烁，如果为true，参数nFlickerTimes将被忽略

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
// 定义结构体：VBF_MARKDOCLAYERINFO
// 结构体描述：模型的文档图层信息，即模型所在的文档、图层和模型ID号
//------------------------------------------------------------------
typedef struct _tagVBFMarkDocLayerInfo
{
    std::string		strDocName;     // 模型所在的文档
    std::string     strLayerName;   // 模型所在的图层
    std::string     strMarkID;      // 模型的ID号

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
// 定义结构体：VBF_MARKQUERYSTYLE
// 结构体描述：军标模型被查询到后的显示样式（用于模型的快速选择等）
//------------------------------------------------------------------
typedef struct _tagVBFMarkQueryStyle
{
    // 查询后的模型
    osg::Vec4f              colorBlend;             // 查询后的模型混色
    bool                    bModulate;              // 查询后的模型混色是否使用乘色

    // 查询后的信息
    DWORD                   dwInfoItem;             // 查询信息的内容
    std::string             strCustomInfo;          // 查询信息中用户自定义的内容
    VBF_TEXTSTYLE           TextStyle;              // 查询信息的文本样式
    bool                    bFrameVisible;          // 查询信息的背景框是否可见
    VBF_POLYGON2DSTYLE      FrameStyle;             // 查询信息的背景框样式

    _tagVBFMarkQueryStyle()
    {
        // 模型混色
        colorBlend  = osg::Vec4f(0, 1, 1, 0.6);
        bModulate   = false;

        // 查询信息的内容
        dwInfoItem    = (VBF_QUERYINFO_ITEM_ID | VBF_QUERYINFO_ITEM_CODE);
        strCustomInfo = "";

        // 查询信息的文本样式
        TextStyle.strFontName       = "msyh";
        TextStyle.bSerif            = true;
        TextStyle.fFontSize         = 22;
        TextStyle.colorText         = osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);	// 字色
        TextStyle.colorSerif        = osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);	// 衬色

        // 查询信息的背景框样式
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
// 定义结构体：VBF_MARKSTATEINFO
// 结构体描述：军标模型的状态信息
//------------------------------------------------------------------
typedef struct _tagVBFMarkStateInfo
{
	char	szName[64];		// 状态名称，如“爆炸”，“毁伤”等
	char	szDesc[256];	// 状态描述信息

	_tagVBFMarkStateInfo()
	{
		szName[0]	= '\0';
		szDesc[0]	= '\0';
	}

} VBF_MARKSTATEINFO;


//--------------------------------------------------------------------------
// 定义结构体：VBF_TRAILPOINT
// 结构体描述：模型在运动过程中的轨迹点信息
//--------------------------------------------------------------------------
typedef struct _tagVBFTrailPoint
{
    bool			bKeyPoint;		// 是否为关键点（即是否为用户输入的坐标点，该值由系统内部设置）
    osg::Vec3d		vPosGeo;		// 模型的地理坐标
    float			fRotateX;		// 旋转角 (单位：角度)
    float			fRotateY;
    float			fRotateZ;
    std::string     strInfo;        // 该点处的信息（可以为空字符串，只有关键点才有信息，插值点没有）

    // 构造函数
    _tagVBFTrailPoint()
    {
        bKeyPoint	= false;
        vPosGeo		= osg::Vec3d(0.0, 0.0, 0.0);
        fRotateX	= 0.0f;
        fRotateY	= 0.0f;
        fRotateZ	= 0.0f;
        strInfo     = "";
    }

    // 构造函数
    _tagVBFTrailPoint(bool bKey, const osg::Vec3d& vGeo, float fRotateX0, float fRotateY0, float fRotateZ0, const std::string& strInfo0="")
    {
        bKeyPoint	= bKey;
        vPosGeo		= vGeo;
        fRotateX	= fRotateX0;
        fRotateY	= fRotateY0;
        fRotateZ	= fRotateZ0;
        strInfo     = strInfo0;
    }

    // 拷贝构造函数
    _tagVBFTrailPoint(const _tagVBFTrailPoint& src)
    {
        *this = src;
    }

    // 赋值运算符
    _tagVBFTrailPoint& operator=(const _tagVBFTrailPoint& src)
    {
        // 防止src=src这样的操作
        if( this==&src )  return *this;

        bKeyPoint	= src.bKeyPoint;
        vPosGeo		= src.vPosGeo;
        fRotateX	= src.fRotateX;
        fRotateY	= src.fRotateY;
        fRotateZ	= src.fRotateZ;
        strInfo     = src.strInfo;

        return *this;
    }

    // 重载==运算符
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
