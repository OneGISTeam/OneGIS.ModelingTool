//*******************************************************************
// FileName��IVBF_MarkModelVolumeRayTracing.h
// Function�������ݵ�״��ͼʵ��ģ�ͽӿڣ�����׷�ٷ���
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_VOLUME_RAY_TRACING_H__
#define __IVBF_MARK_MODEL_VOLUME_RAY_TRACING_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelVolumeRayTracing
// �ӿ�������Meshʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelVolumeRayTracing : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelVolumeRayTracing() {}
    virtual bool SetFileName(const std::string& strFnVolumeData,const std::string& strFnColorTable)=0;

};


#endif 
