//*******************************************************************
// FileName��IVBF_MarkModelRadarEnergyXYZ.h
// Function������ʵ��ģ�ͣ���ŷ���ͼ��ֱ������ϵ��
// Author:   ��Ө
// Date:     2015-01-08
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RADARENERGY_XYZ_H__
#define __IVBF_MARK_MODEL_RADARENERGY_XYZ_H__


#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>


class IVBF_MarkModelRadarEnergyXYZ : public IVBF_MarkModelGraphics
{
public:
    virtual ~IVBF_MarkModelRadarEnergyXYZ() {}

    // ���õ�ŷ���ͼ�����ļ����ƣ�����·����ֱ������ϵ������ȡ���а���㼯����ɫ����
    virtual void			   SetEnergyFileName(const string& strFileName)=0;
	virtual const std::string& GetEnergyFileName()=0;

    virtual void  SetSize(float fSize)=0;
	virtual float GetSize()=0;
};


#endif 
