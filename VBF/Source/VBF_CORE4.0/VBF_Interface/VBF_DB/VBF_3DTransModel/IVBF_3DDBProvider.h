//***************************************************************************************
// FileName：IVBF_3DDBProvider.h
// Function：地形数据提供者接口
//           每个需要注册到组件容器的地形数据提供者都要实现该接口
// Author:   龚桂荣
// Date:     2010-7-23
//***************************************************************************************

#ifndef __IVBF_3DDB_PROVIDER_H__
#define __IVBF_3DDB_PROVIDER_H__

#include "VBF_DB\\VBF_3DTransModel\\VBF_3DTransBlkDem.h"
#include "VBF_DB\\VBF_3DTransModel\\VBF_3DTransBlkTex.h"
#include "VBF_DB\\VBF_3DTransModel\\VBF_3DTransBlkNote.h"
#include "VBF_DB\\VBF_3DTransModel\\VBF_3DDataSetTypes.h"

class IVBF_3DDBProvider
{
public:
	virtual ~IVBF_3DDBProvider() {}

public:	

 	// 初始化/释放插件
 	virtual void Init(void* pParam=NULL)=0;
 	virtual void Release()=0;	
	
	/* 功能：装载地形数据交换模型
       参数：bFromLower为是否从上层数据强行载入
       返回：成功返回true，否则返回false
	*/
	virtual bool  LoadBlkDem(VBF_3DDATASETDEM* pDS,   CVBF_TransBlkDem* pTransBlkDem, bool bFromLower=false)=0;
	virtual bool  LoadBlkTex(VBF_3DDATASETTEX* pDS,   CVBF_TransBlkTex* pTransBlkTex, bool bFromLower=false )=0;
	virtual bool  LoadBlkNote(VBF_3DDATASETNOTE* pDS, CVBF_TransBlkNote* pTransBlkNote, bool bFromLower=false)=0;

	// 根据地理坐标，查找存在数据的最大级别
	virtual int   GetMaxLodOfDataSetTex(VBF_3DDATASETTEX* pDS, double L, double B)=0;
};


#endif

