//*******************************************************************
// FileName��IVBF_MarkModelSkyGroundConnect.h
// Function��ʵ��ģ�ͣ����������֮���ͨ��
// Author:   ��Ө
// Date:     2016-06-27
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SKY_GROUND_CONNECT_H__
#define __IVBF_MARK_MODEL_SKY_GROUND_CONNECT_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Satellite/VBF_3DPlotDataTypes_Satellite.h>
#include <Types/VBF_3DStyles.h>
#include <string>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelSkyGroundConnect
// �ӿ����������������֮���ͨ��
//--------------------------------------------------------------------
class IVBF_MarkModelSkyGroundConnect : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelSkyGroundConnect() {}

    // ����/��ȡ��ʼ����ֹ�����������
    virtual void SetWorldPos(const osg::Vec3d& vPosFrom, const osg::Vec3d& vPosTo)=0;
    virtual void GetWorldPos(osg::Vec3d& vPosFrom, osg::Vec3d& vPosTo)=0;

    // ����/��ȡ��ʼ����ֹ�뾶��Ҫ��fRadiusFrom<fRadiusTo��
    virtual void SetRadius(float fRadiusFrom, float fRadiusTo)=0;
    virtual void GetRadius(float& fRadiusFrom, float& fRadiusTo)=0;

    // ����/��ȡ��ʼ����ֹ͸���ȣ�Ҫ��fAlphaFrom<fAlphaTo��
    virtual void SetAlpha(float fAlphaFrom, float fAlphaTo)=0;
    virtual void GetAlpha(float& fAlphaFrom, float& fAlphaTo)=0;

    // ����/��ȡ��ɫ
    virtual void             SetColor(const osg::Vec4& color)=0;
    virtual const osg::Vec4& GetColor()=0;

    // ����/��ȡÿ�����֡��ɫ�仯һ�Σ�Ĭ��ֵΪ2֡��
    virtual void SetColorChangeFrames(int nFrames)=0;
    virtual int  GetColorChangeFrames()=0;
};


#endif
