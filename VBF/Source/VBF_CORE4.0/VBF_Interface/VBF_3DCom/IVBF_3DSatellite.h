//*******************************************************************
// FileName��IVBF_3DSatellite.h
// Function���������ǹ���ӿ�
// Author:   ��Ө
// Date:     2013-12-31
//*******************************************************************

#ifndef __IVBF_3DSATELLITE_H__
#define __IVBF_3DSATELLITE_H__

#include <string>
#include <Types/Vec4f>
#include <VBF_Base/VBF_Referenced.h>


class IVBF_MarkModelSatellite;

// ����������ID��
const char VBF_COMPONENT_3DSATELLITE[]	= "Component: 3DSatellite";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DSATELLITE[]	= "�������ǹ���";	

// ���幤��ID��
const char VBF_TOOL_SELECT_SATELLITE[]	= "Tool: Select Satellite";	 // ѡ������


class IVBF_3DSatellite : public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DSatellite() {}

	// ��xml�����ļ��м������ǣ�ͬʱ�������ǵ���ɫ����С�������ļ�������Ϊ�գ�
	// ���ͬʱ��������ɫ����������ʹ����˷�ʽ���л��
	virtual bool LoadData(const std::string& strFileName, const osg::Vec4f& color, float fSize, const std::string& strTexFileName="")=0;

	// ����Ѿ����ص�����
	virtual void Clear()=0;

    // ��ȡ��ǰѡ�е�����ģ��
    virtual IVBF_MarkModelSatellite* GetSatelliteModel()=0;
};

#endif 
