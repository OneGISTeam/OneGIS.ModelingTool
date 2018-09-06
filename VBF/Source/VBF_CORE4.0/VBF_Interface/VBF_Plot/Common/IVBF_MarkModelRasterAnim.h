//*******************************************************************
// FileName��IVBF_MarkModelRasterAnim.h
// Function������ʵ��ģ�ͽӿڣ�դ�񶯻�
// Author:   ��Ө
// Date:     2014-12-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RASTER_ANIM_H__
#define __IVBF_MARK_MODEL_RASTER_ANIM_H__


#include <VBF_Plot/Common/IVBF_MarkModelRaster.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelRasterAnim
// �ӿ�������դ�񶯻�
//--------------------------------------------------------------------
class IVBF_MarkModelRasterAnim : public IVBF_MarkModelRaster
{
public:
	virtual ~IVBF_MarkModelRasterAnim() {}

	// ����/��ȡ�������������л���֡���
	virtual void SetFrameInterval(int nFrameInterval)=0;
	virtual int  GetFrameInterval()=0;

	// ����/��ȡ�Ƿ�ѭ�����ţ�Ĭ��ֵΪfalse��
	virtual void SetLoop(bool bLoop)=0;
	virtual bool IsLoop()=0;
};


#endif 
