//*******************************************************************
// FileName：IVBF_3DBuilding.h
// Function：接口：单个的地面建筑物模型
// Author:   杜莹
// Date:     2012-06-12
//*******************************************************************


#ifndef __IVBF_3DBUILDING_H__
#define __IVBF_3DBUILDING_H__


#include <VBF_Base/VBF_Referenced.h>
#include<string.h>
#include<stdio.h>
// 定义建筑物模型的级别总数
#define VBF_NUM_MODELLEVELS		3

//---------------------------------------------------------------------
// 定义结构体：VBF_BUILDINGINFO
// 结构体描述：单个地面建筑物模型的信息（该信息从数据库中读取）
//---------------------------------------------------------------------
typedef struct _tagVBFBuildingInfo
{
	int			nID;				// 编号
	char		szName[64];			// 名称	
	char		szType[32];			// 类型，数字，如"标志性建筑的type为10001"，目前共?种
	double		dLon;				// 模型定位点经度
	double		dLat;				// 模型定位点纬度	
	double		dAltitude;			// 模型定位点高程
	float		fRotation;			// 模型方向 正北为0，顺时针为正，逆时针为负
	float		fScale;				// 缩放比

	// 各个级别模型的文件名（相对路径）
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

	// 判断信息是否有效
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
