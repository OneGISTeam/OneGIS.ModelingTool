//*******************************************************************
// FileName��IVBF_MarkModelCal3D.h
// Function����ʾCal3Dģ�͵ĵ�״ʵ��ģ�ͽӿ�
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CAL3D_H__
#define __IVBF_MARK_MODEL_CAL3D_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelCal3D
// �ӿ�������Cal3Dʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelCal3D : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelCal3D() {}

    // ����/��ȡģ�͵������ļ�������·����������ļ������ڣ�����false
    // ������strFileName -- ��׺Ϊxml��cfg
    virtual bool SetFileName(const std::string& strFileName)=0;
    virtual void GetFileName(std::string& strFileName)=0;

    virtual void DoAction(const std::string& strActionName, bool bEnabled)=0;

    // ��ȡģ�͵Ķ�������
    virtual int GetNumActions()=0;

    virtual void BlendCycle( int id, float weight, float delay, float timeFactor = 1.0f )=0;
    virtual void ClearCycle( int id, float delay )=0;
    virtual void ExecuteAction( int id, float delayIn = 0.0f, float delayOut = 0.0f,
                          float weightTarget=1.0f, bool autoLock=false, float timeFactor=1.0f)=0;

};


#endif 
