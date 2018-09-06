//*******************************************************************
// FileName：  IVBF_3DRasterDB.h
// Function：  3D栅格数据库，负责VBF数据块的读取和写入
// Author:     杜莹
// Date:       2011-07-06
//*******************************************************************

#ifndef __IVBF_3DRASTERDB_H__
#define __IVBF_3DRASTERDB_H__

#include "VBF_3DRasterDBExport.h"
#include "IVBF_Blk.h"

#include <Types/VBF_Rect.h>

//--------------------------------------------------------------------
// 定义接口：IVBF_3DRasterDB
// 接口描述：3D栅格数据库，负责VBF数据块的读取和写入
//--------------------------------------------------------------------
class IVBF_3DRasterDB 
{
public:	
	virtual ~IVBF_3DRasterDB() {}

	/* 功能：打开一个数据库
       参数：szURL -- 数据库全路径；如果是本地文件格式，用文件路径；如果是网络路径，用htp://或ftp://
       返回：成功返回true，否则返回false
	*/
	virtual bool Open(const char* szURL)=0;

	/* 功能：关闭一个数据库
       返回：成功返回true，否则返回false
	*/
	virtual bool Close()=0;

	/* 功能：获取已打开数据库的全路径
       返回：数据库全路径；如果是本地文件格式，用文件路径；如果是网络路径，用htp://或ftp://
	*/
	virtual const char* GetURL()=0;

	/* 功能：创建一个数据块
	   参数：nBlkType -- 数据块的类型			 
	   返回：创建的数据块，NULL表示创建失败
	*/
	virtual IVBF_Blk* CreateBlk(VBF_BLK_TYPE nBlkType)=0;	
	
	/* 功能：写入一个数据块
	   参数：pIBlk	 -- 待写入的数据块
	   返回：成功返回true，否则返回false
	*/
	virtual bool WriteBlk(IVBF_Blk* pIBlk)=0;	

	/* 功能：读取一个数据块
	   参数：pIBlk	   -- 待读取的数据块
	         bReadOnly -- 该块是否只用来读取
	   返回：成功返回true，否则返回false
	*/
	virtual bool ReadBlk(IVBF_Blk* pIBlk, bool bReadOnly)=0;
	
	/* 功能：获取数据块所在的文件名 (含完整路径)
	   参数：pIBlk	    -- 数据块指针，不能为NULL
	         szFileName -- 待存储文件名的内存区，不能为NULL
	   返回：成功返回true，否则返回false
	*/
	virtual bool GetBlkFileName(IVBF_Blk* pIBlk, char* szFileName)=0;

	/* 功能：根据地理坐标，查找存在纹理数据的最大Lod级别
	   参数：地理坐标中的经度和纬度 (单位：度)
	   返回：该坐标处纹理数据的最大Lod级别
	*/
	virtual int GetLodMaxOfDataTex(double L, double B)=0;

	/* 功能：获取纹理数据的最小/最大Lod级别（不考虑数据的覆盖范围）
	   返回：该数据库中纹理数据的最小/最大Lod级别
	*/
	virtual int GetLodMinOfDataTex()=0;
	virtual int GetLodMaxOfDataTex()=0;

	/* 功能：获取Den数据的最小/最大Lod级别（不考虑数据的覆盖范围）
	   返回：该数据库中Dem数据的最小/最大Lod级别
	*/
	virtual int GetLodMinOfDataDem()=0;
	virtual int GetLodMaxOfDataDem()=0;

    virtual bool LoadBlkDem(double dGeoX0, double dGeoX1, double dGeoY0, double dGeoY1, int nLod,
                            int& nRow, int& nCol, float**& pDem, CVBF_RectD& rBlkGeo)=0;
	virtual bool GetGeoDem(double dGeoX, double dGeoY, int nLod, float& fDem)=0;
};


// 全局函数: 创建/释放一个3D栅格数据库
VBF_3DRASTERDB_EXPORT IVBF_3DRasterDB*  VBF_Create3DRasterDB();
VBF_3DRASTERDB_EXPORT void              VBF_Release3DRasterDB(IVBF_3DRasterDB*& pIDB);



#endif 
