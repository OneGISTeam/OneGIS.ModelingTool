//*******************************************************************
// FileName��IVBF_MarkModelVolumeRayCasting.h
// Function��������ģ�ͽӿڣ�����Ͷ�䷨��
// Author:   ��Ө
// Date:     2018-03-31
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_VOLUME_RAY_CASTING_H__
#define __IVBF_MARK_MODEL_VOLUME_RAY_CASTING_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec4ub>
#include <map>


// ������ɫӳ���������������
typedef std::map< float, osg::Vec4ub, less<float> >	CVBF_ColorMap;


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelVolumeRayCasting
// �ӿ�������������ģ�ͽӿڣ�����Ͷ�䷨��
//--------------------------------------------------------------------
class IVBF_MarkModelVolumeRayCasting : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelVolumeRayCasting() {}

	// ����/��ȡ�������ļ���
	// ˵����1��Ŀǰֻ֧��.fld��ʽ���������ļ�����ÿ�����ݵ��ֵ����Ϊdouble��
	//      2����·���±�����һ��ͬ���Һ�׺Ϊ.inf����Ϣ�ļ�����ʽΪxml��ע���������ݵľ�γ�ȷ�Χ����Ϣ
    virtual bool SetVolumeFileName(const std::string& strFileName)=0;
	virtual const std::string& GetVolumeFileName()=0;

	// ����/��ȡ��ɫ��key=��ɫ�ؼ�����ֵ��value=��Ӧ����ɫ���ؼ�����ֵ��С����
	virtual void SetColorTable(const CVBF_ColorMap& mapColorTable)=0;
	virtual const CVBF_ColorMap& GetColorTable()=0;
};


#endif 
