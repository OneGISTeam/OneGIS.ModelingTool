//*******************************************************************
// FileName：IVBF_MarkModelVolumeRayTracing.h
// Function：体数据点状标图实体模型接口（光线追踪法）
// Author:
// Date:
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_VOLUME_RAY_TRACING_H__
#define __IVBF_MARK_MODEL_VOLUME_RAY_TRACING_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelVolumeRayTracing
// 接口描述：Mesh实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelVolumeRayTracing : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelVolumeRayTracing() {}
    virtual bool SetFileName(const std::string& strFnVolumeData,const std::string& strFnColorTable)=0;

};


#endif 
