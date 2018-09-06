//*******************************************************************
// FileName：IVBF_MarkModelRasterAnim.h
// Function：军标实体模型接口：栅格动画
// Author:   杜莹
// Date:     2014-12-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RASTER_ANIM_H__
#define __IVBF_MARK_MODEL_RASTER_ANIM_H__


#include <VBF_Plot/Common/IVBF_MarkModelRaster.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRasterAnim
// 接口描述：栅格动画
//--------------------------------------------------------------------
class IVBF_MarkModelRasterAnim : public IVBF_MarkModelRaster
{
public:
	virtual ~IVBF_MarkModelRasterAnim() {}

	// 设置/获取相邻两幅纹理切换的帧间隔
	virtual void SetFrameInterval(int nFrameInterval)=0;
	virtual int  GetFrameInterval()=0;

	// 设置/获取是否循环播放（默认值为false）
	virtual void SetLoop(bool bLoop)=0;
	virtual bool IsLoop()=0;
};


#endif 
