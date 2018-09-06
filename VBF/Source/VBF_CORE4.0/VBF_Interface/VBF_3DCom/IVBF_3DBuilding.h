//*******************************************************************
// FileName��IVBF_3DBuilding.h
// Function���ӿڣ������ĵ��潨����ģ��
// Author:   ��Ө
// Date:     2012-06-12
//*******************************************************************


#ifndef __IVBF_3DBUILDING_H__
#define __IVBF_3DBUILDING_H__


#include <VBF_Base/VBF_Referenced.h>
#include<string.h>
#include<stdio.h>
// ���彨����ģ�͵ļ�������
#define VBF_NUM_MODELLEVELS		3

//---------------------------------------------------------------------
// ����ṹ�壺VBF_BUILDINGINFO
// �ṹ���������������潨����ģ�͵���Ϣ������Ϣ�����ݿ��ж�ȡ��
//---------------------------------------------------------------------
typedef struct _tagVBFBuildingInfo
{
	int			nID;				// ���
	char		szName[64];			// ����	
	char		szType[32];			// ���ͣ����֣���"��־�Խ�����typeΪ10001"��Ŀǰ��?��
	double		dLon;				// ģ�Ͷ�λ�㾭��
	double		dLat;				// ģ�Ͷ�λ��γ��	
	double		dAltitude;			// ģ�Ͷ�λ��߳�
	float		fRotation;			// ģ�ͷ��� ����Ϊ0��˳ʱ��Ϊ������ʱ��Ϊ��
	float		fScale;				// ���ű�

	// ��������ģ�͵��ļ��������·����
	char		szFileName[VBF_NUM_MODELLEVELS][256];
	
	_tagVBFBuildingInfo()
	{
		nID				= -1;
		dLon			= 0.0;			
		dLat			= 0.0;	
		dAltitude		= 0.0;		
		fRotation		= 0.0f;	
		fScale			= 1.0f;

		szName[0]		= '\0';
		szType[0]		= '\0';

		for(int nLevel=0; nLevel<VBF_NUM_MODELLEVELS; nLevel++)
		{
			szFileName[nLevel][0] = '\0';
		}
	}

	_tagVBFBuildingInfo& operator=(const _tagVBFBuildingInfo& src)
	{
		if(this==&src) return *this;

		nID				= src.nID;
		dLon			= src.dLon;			
		dLat			= src.dLat;	
		dAltitude		= src.dAltitude;		
		fRotation		= src.fRotation;	
		fScale			= src.fScale;

		strcpy(szName, src.szName);
		strcpy(szType, src.szType);

		for(int nLevel=0; nLevel<VBF_NUM_MODELLEVELS; nLevel++)
		{
			strcpy(szFileName[nLevel], src.szFileName[nLevel]);
		}

		return *this;
	}

	// �ж���Ϣ�Ƿ���Ч
	bool IsValid()
	{
		if(nID < 0) return false;
		if(dLon<-180 || dLon>180) return false;
		if(dLat<-90  || dLat>90)  return false;
		if(strlen(szType)==0) return false;

		for(int nLevel=0; nLevel<VBF_NUM_MODELLEVELS; nLevel++)
		{
			if( strlen(szFileName[nLevel]) > 0 ) return true;
		}

		return false;
	}

} VBF_BUILDINGINFO;


class IVBF_3DBuilding : public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DBuilding() {}
};

#endif
