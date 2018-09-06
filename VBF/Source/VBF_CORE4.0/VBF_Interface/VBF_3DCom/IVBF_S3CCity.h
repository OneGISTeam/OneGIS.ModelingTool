//********************************************************************************
// FileName��IVBF_S3CCity.h
// Function����ά���й���ӿڣ����ճ��С����򡢵ؿ鷽ʽ������֯������ģ�͸�ʽΪ.osgb��
//           S3C: Smart 3D Capture
// Author:   ��Ө
// Date:     2016-01-11
//********************************************************************************


#ifndef __IVBF_S3C_CITY__H__
#define __IVBF_S3C_CITY__H__


#include <VBF_Base/VBF_Referenced.h>
#include <string>
#include <Types/Vec3d>

// ����������ID��
const char VBF_COMPONENT_S3CCITY[]  = "Component: S3CCity";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_S3CCITY[]  = "S3C���й���ӿ�";

// ��б��Ӱ���ܽӿ� ID ��
const char VBF_INTERFACE_TILE_MODEL[]  = "��б��Ӱ�ӿ�";


class IVBF_S3CCity : public CVBF_Referenced
{
public:	
    virtual ~IVBF_S3CCity() {}

    // ���һ����������������Ѿ����ڣ�����false
    // ������strRegionID    -- �������ΨһID�ţ��������ظ�
    //      strDataPath    -- �������ģ������·��
    //      ptGeo          -- ������ģ�͵Ķ�λ��
    //      L0, L1, B0, B1 -- ������ľ�γ�ȷ�Χ
    //      nNumTileRows   -- ������ķֿ�����
    //      nNumTileCols   -- �ó��еķֿ�����
    //      bModelToCache  -- �Ƿ���Ҫ����ȡ��ģ�ͷ��뻺��
    virtual bool AddRegion(const std::string& strRegionID, const std::string& strDataPath, const osg::Vec3d& ptGeo,
                           double L0, double L1, double B0, double B1, int nNumTileRows, int nNumTileCols, bool bModelToCache=false)=0;

    // �Ƴ�һ��������������򲻴��ڣ�����false���ú�������ж�������ڵ�����ģ�����ݣ�
    virtual bool RemoveRegion(const std::string& strRegionID)=0;

    // ����ĳ������Ŀɼ��ԣ���������򲻴��ڣ�����false���ú�������ж�������ڵ�����ģ�����ݣ�
    virtual bool SetRegionVisible(const std::string& strRegionID, bool bVisible)=0;
};




class IVBF_TiltModel : public CVBF_Referenced
{
public:
	virtual ~IVBF_TiltModel(){}
	 
public:
	virtual bool AddTilt(const std::string& strTiltID, const std::string& strTiltFile) = 0;

	virtual bool RemoveTilt(const std::string& strTiltID) = 0;

	virtual bool ClearTilts() = 0;

	virtual bool SetTiltVisible(const std::string& strTiltID, bool bState) = 0;

	virtual bool GetTiltVisible(const std::string& strTiltID) = 0;

	virtual bool SetTiltPosition(const std::string& strTiltID, osg::Vec3d vecLBH) = 0;

	virtual osg::Vec3d GetTiltPosition(const std::string& strTiltID) = 0;

	virtual bool SetTiltScale(const std::string& strTiltID, osg::Vec3d vecScale) = 0;

	virtual osg::Vec3d GetTiltScale(const std::string& strTiltID) = 0;

	virtual bool SetTiltRotate(const std::string& strTiltID, osg::Vec3d vecRotate) = 0;

	virtual osg::Vec3d GetTiltRotate(const std::string& strTiltID) = 0;
};

#endif
