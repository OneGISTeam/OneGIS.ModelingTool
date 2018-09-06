//*******************************************************************
// FileName：IVBF_MarkModelShapeDome.h
// Function：军标实体模型：圆顶体，类似于圆屋顶
// Author:   杜莹
// Date:     2013-09-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_DOME_H__
#define __IVBF_MARK_MODEL_SHAPE_DOME_H__

#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_DOME_PART
// 枚举描述：圆顶体的各个部分
//--------------------------------------------------------------------
enum EVBF_DOME_PART
{
	VBF_DOME_PART_BODY			= 0,	// 主体
	VBF_DOME_PART_CONE_INNER	= 1,	// 内锥面
	VBF_DOME_PART_CONE_OUTER	= 2,	// 外锥面
	VBF_DOME_PART_SIDE_START	= 3,	// 起始侧面
	VBF_DOME_PART_SIDE_END		= 4,	// 终止侧面
	VBF_DOME_PART_PARALLEL		= 5,	// 纬线圈
	VBF_DOME_PART_MERIDIAN		= 6,	// 经线圈
	VBF_DOME_PART_COUNT					// 总数
};


//--------------------------------------------------------------------
// 定义枚举：EVBF_DOME_ORIGIN_TYPE
// 枚举描述：圆顶体的原点在球体中的位置
//--------------------------------------------------------------------
enum EVBF_DOME_ORIGIN_TYPE
{
	VBF_DOME_ORIGIN_CENTER		= 0,	// 原点位于球心（默认值）
	VBF_DOME_ORIGIN_BOTTOM		= 1,	// 原点位于球底部
	VBF_DOME_ORIGIN_TOP			= 2,	// 原点位于球顶部
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeDome
// 接口描述：圆顶体
//--------------------------------------------------------------------
class IVBF_MarkModelShapeDome : public IVBF_MarkModelShape
{
public:
	virtual ~IVBF_MarkModelShapeDome() {}

public:

	// 设置/获取圆顶体水平和垂直方向的起始角和终止角，值域分别为[0, 360],[0, 180]
	// 说明：垂直角为0度表示北极，垂直角为180度表示南极（默认情况下：原点位于球心，半径为1）
	virtual void SetTess(float fAngleH0, float fAngleH1, float fAngleV0, float fAngleV1)=0;
	virtual void GetTess(float& fAngleH0, float& fAngleH1, float& fAngleV0, float& fAngleV1)=0;

	// 设置纵横方向的分割数，默认值分为18, 36
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;

	// 设置/获取内外锥面的圆环分割数，默认值为6
	virtual void SetNumConeSplit(int nNumSplit)=0;
	virtual int  GetNumConeSplit()=0;

	// 设置/获取侧面圆环分割数，默认值为6
	virtual void SetNumSideSplit(int nNumSplit)=0;
	virtual int  GetNumSideSplit()=0;

	// 设置/获取纬线圈个数，默认值为1（必须为奇数，以赤道为对称轴）
	virtual void SetNumParallels(int num)=0;
	virtual int  GetNumParallels()=0;

	// 设置/获取经线圈个数，默认值为1
	virtual void SetNumMeridians(int num)=0;
	virtual int  GetNumMeridians()=0;
	
	// 设置/获取圆顶体底面长短轴的半径及高度（三者完全相等时表示球体，默认值均为1.0）
	virtual void SetSize(float fSizeX, float fSizeY, float fSizeZ)=0;
	virtual void GetSize(float& fSizeX, float& fSizeY, float& fSizeZ)=0;

    // 设置/获取圆顶体是否与地心一致，默认值为false
    virtual void SetAxisAccordWithEarth(bool bAccordWithEarth)=0;
    virtual bool IsAxisAccordWithEarth()=0;

    // 设置/获取模型原点在球体中的位置（默认为VBF_DOME_ORIGIN_CENTER）
    virtual void                  SetOriginType(EVBF_DOME_ORIGIN_TYPE nOrigin)=0;
    virtual EVBF_DOME_ORIGIN_TYPE GetOriginType()=0;
};


#endif 
