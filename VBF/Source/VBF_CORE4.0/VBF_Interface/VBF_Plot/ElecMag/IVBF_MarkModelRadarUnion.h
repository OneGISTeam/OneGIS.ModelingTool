//*******************************************************************
// FileName��IVBF_MarkModelRadarUnion.h
// Function������ʵ��ģ�ͣ��״������ţ�����ʾ��
// Author:   ��Ө
// Date:     2015-01-08
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RADARUNION_H__
#define __IVBF_MARK_MODEL_RADARUNION_H__


#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>


class IVBF_MarkModelRadarUnion : public IVBF_MarkModelGraphics
{
public:
    virtual ~IVBF_MarkModelRadarUnion() {}

    // ���õ�ŷ���ͼ�����ļ����ƣ�����·��������ȡ���а���㼯����ɫ����
    virtual void		       SetEnergyFileName(const std::string& strEnergyFile)=0;
	virtual const std::string& GetEnergyFileName()=0;

    virtual void  SetSize(float fSize)=0;
	virtual float GetSize()=0;
};


#endif 
