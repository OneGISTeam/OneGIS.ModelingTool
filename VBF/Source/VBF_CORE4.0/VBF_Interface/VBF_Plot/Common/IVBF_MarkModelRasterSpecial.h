//*******************************************************************
// FileName：IVBF_MarkModelRasterSpecial.h
// Function：几类特殊的栅格型军标实体模型接口
// Author:   杜莹
// Date:     2015-12-01
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RASTER_SPECIAL_H__
#define __IVBF_MARK_MODEL_RASTER_SPECIAL_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterSpecial
// 接口描述：几类特殊的栅格型军标实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelRasterSpecial : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelRasterSpecial() {}

	// 设置/获取模型的尺寸信息，注意：如果此处设置的长宽比不等于原始长宽比，会导致图像变形
	virtual void SetSize(bool bFixedSizeInPixels, float fWidth, float fHeight)=0;
	virtual void GetSize(bool& bFixedSizeInPixels, float& fWidth, float& fHeight)=0;
	
	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

    // 设置/获取纹理的透明度（默认值为1.0）
    virtual void  SetTexAlpha(float fAlpha)=0;
    virtual float GetTexAlpha()=0;

	// 设置/获取纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY)=0;
	virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterBoardH
// 接口描述：栅格型军标实体模型，使用水平布告牌
//--------------------------------------------------------------------
class IVBF_MarkModelRasterBoardH : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterBoardH() {}
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterBoardV
// 接口描述：栅格型军标实体模型，使用垂直布告牌
//--------------------------------------------------------------------
class IVBF_MarkModelRasterBoardV : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterBoardV() {}
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterBoardHV
// 接口描述：栅格型军标实体模型，使用完全布告牌
//--------------------------------------------------------------------
class IVBF_MarkModelRasterBoardHV : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterBoardHV() {}
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterHorizon
// 接口描述：栅格型军标实体模型，不使用布告牌，平行于地面，且仅能绕Z轴旋转
//--------------------------------------------------------------------
class IVBF_MarkModelRasterHorizon : public IVBF_MarkModelRasterSpecial
{
public:
	virtual ~IVBF_MarkModelRasterHorizon() {}
};

#endif 
