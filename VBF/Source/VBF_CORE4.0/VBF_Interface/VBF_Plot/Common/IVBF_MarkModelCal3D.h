//*******************************************************************
// FileName：IVBF_MarkModelCal3D.h
// Function：显示Cal3D模型的点状实体模型接口
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CAL3D_H__
#define __IVBF_MARK_MODEL_CAL3D_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelCal3D
// 接口描述：Cal3D实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelCal3D : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelCal3D() {}

    // 设置/获取模型的完整文件名（含路径），如果文件不存在，返回false
    // 参数：strFileName -- 后缀为xml或cfg
    virtual bool SetFileName(const std::string& strFileName)=0;
    virtual void GetFileName(std::string& strFileName)=0;

    virtual void DoAction(const std::string& strActionName, bool bEnabled)=0;

    // 获取模型的动作总数
    virtual int GetNumActions()=0;

    virtual void BlendCycle( int id, float weight, float delay, float timeFactor = 1.0f )=0;
    virtual void ClearCycle( int id, float delay )=0;
    virtual void ExecuteAction( int id, float delayIn = 0.0f, float delayOut = 0.0f,
                          float weightTarget=1.0f, bool autoLock=false, float timeFactor=1.0f)=0;

};


#endif 
