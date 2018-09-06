//*******************************************************************
// FileName：  IVBF_Blk.h
// Function：  VBF数据块，如Dem/纹理/注记
// Author:     杜莹
// Date:       2011-07-06
//*******************************************************************

#ifndef __IVBF_BLK_H__
#define __IVBF_BLK_H__

#include "VBF_Common/VBF_ImgUtil/VBF_ImgCoderDataTypes.h"
#include "VBF_DB/VBF_3DTransModel/VBF_3DTransBlkDataTypes.h"
#include "VBF_DB/VBF_DemTexDataType.h"

//..\include,.\include,..\..\..\VBF_CORE4.0\VBF_Interface\VBF_DB\VBF_3DRasterDB,..\..\VBF_Common\MCE_ImgUtilDll\Include,..\..\MCE_Public,..\MCE_UtilDll\Include


#include <stdio.h>

// 与块类型对应的文件后缀
static char* gs_szBlkFileExt[] =
{
	"未知格式", 
	"demx", 
	"texx",
	"notx"
};

//--------------------------------------------------------------------
// 定义接口：IVBF_3DBlk
// 接口描述：VBF数据块
//--------------------------------------------------------------------
class IVBF_Blk
{
public:	
	virtual ~IVBF_Blk() {}	

	// 获取数据块的类型	 
	virtual VBF_BLK_TYPE GetBlkType()=0;

	// 设置数据块的Lod和全球唯一编号XY 
	virtual bool SetBlkNo(int nLod, int nBlkNoX, int nBlkNoY)=0;

	// 获取数据块的Lod和全球唯一编号XY 
	virtual int GetLod()=0;
	virtual int GetBlkNoX()=0;
	virtual int GetBlkNoY()=0;	

	// 获取数据块经纬度范围
	virtual double GetBlkL0()=0;
	virtual double GetBlkB0()=0;
	virtual double GetBlkL1()=0;
	virtual double GetBlkB1()=0;

	// 是否有数据
	virtual bool HasData()=0;
	
	// 从给定的内存数据中解析块信息
	virtual bool FromBuf(BYTE* pBuf, int nBufSize)=0;

	// 将块数据输出到指定的内存区
	virtual bool ToBuf(BYTE*& pBuf, int& nBufSize)=0;

	// 获取块的字节总数 (即写入到文件中的字节数)
	virtual int GetBytesBlk()=0;

	// 写入块的数据
	virtual bool Write(FILE* pFile)=0;

	// 清除块中的数据
	virtual void Clear()=0;

	// 复制块
	virtual IVBF_Blk* Clone()=0;
};


//--------------------------------------------------------------------
// 定义接口：IVBF_3DBlkDem
// 接口描述：VBF数据块：Dem
//--------------------------------------------------------------------
class IVBF_BlkDem : public IVBF_Blk
{
public:	
	virtual ~IVBF_BlkDem() {}

	// 设置/获取Dem的尺寸
	virtual void SetSize(int nSizeX, int nSizeY)=0;
	virtual int  GetSizeX()=0;
	virtual int  GetSizeY()=0;

	// 是否为满块
    virtual void SetFull(bool bFull)=0;
    virtual bool IsFull()=0;

	// 设置/获取Dem的所有高程点
	virtual bool   SetDataDem(float* pDem)=0;
	virtual float* GetBufDem()=0;
	virtual int    GetBytesDem()=0;

	// 设置Dem的所有高程点

	/* 功能：获取指定位置的高程值
	   参数：nNoX -- 数据区的X坐标，即列号
             nNoY -- 数据区的Y坐标，即行号
	   说明：如果该位置没有数据，直接返回false
	*/
	virtual bool GetDem(int nNoX, int nNoY, float* pfValue)=0;

	// 计算/获取最大最小高程值
	virtual void  CalHeightMinMax()=0;
	virtual float GetHeightMin()=0;
	virtual float GetHeightMax()=0;
};

//--------------------------------------------------------------------
// 定义接口：IVBF_3DBlkTex
// 接口描述：VBF数据块：纹理
//--------------------------------------------------------------------
class IVBF_BlkTex : public IVBF_Blk
{
public:	
	virtual ~IVBF_BlkTex() {}

	// 是否为满块
    virtual bool IsFull()=0;
    virtual void SetFull(bool bFull)=0;

	// 设置/获取纹理的尺寸
	virtual void SetSize(int nSizeX, int nSizeY)=0;
	virtual int  GetSizeX()=0;
	virtual int  GetSizeY()=0;

	// 设置/获取纹理编码方式
	virtual bool SetCodeType(VBF_IMGCODETYPE nCodeType)=0;
	virtual VBF_IMGCODETYPE  GetCodeType()=0;

	// 设置/获取压缩后的纹理数据及其大小
	virtual bool  SetDataCoded(BYTE* pBuf, int nBufSize)=0;
	virtual bool  GetDataCoded(BYTE*& pBuf, int& nBufSize)=0;
	virtual BYTE* GetBufCoded()=0;
	virtual int   GetBytesCoded()=0;

	// 设置/获取掩码图数据及其大小
	virtual bool  SetDataMask(BYTE* pBuf, int nBufSize)=0;
	virtual bool  GetDataMask(BYTE*& pBuf, int& nBufSize)=0;
	virtual BYTE* GetBufMask()=0;
	virtual int   GetBytesMask()=0;

	// 设置/获取未压缩的纹理数据及其大小	
	virtual bool  SetDataRGBA(BYTE* pBuf, int nBufSize)=0;
	virtual bool  GetDataRGBA(BYTE*& pBuf, int& nBufSize)=0;
	virtual BYTE* GetBufRGBA()=0;
	virtual int   GetBytesRGBA()=0;

	// 纹理编码：根据RGBA数据，生成压缩数据和Mask数据，参数pOptinos表示编码选项，如JPG压缩质量等，可以为NULL
	virtual bool  Encode(void* pOptinos=NULL)=0;

	// 纹理解码：根据压缩数据和Mask数据，生成RGBA数据
	virtual bool  Decode()=0;
};

//--------------------------------------------------------------------
// 定义接口：IVBF_3DBlkNote
// 接口描述：VBF数据块：注记
//--------------------------------------------------------------------
class IVBF_BlkNote : public IVBF_Blk
{
public:	
	virtual ~IVBF_BlkNote() {}	

	// 设置注记数据
	virtual bool SetNoteData(int nNumNotes, VBF_NOTEDATA** pNoteData)=0;	

	// 获取注记数据
	virtual int             GetNumNotes()=0;	
	virtual VBF_NOTEDATA**  GetNoteData()=0;	
};


#endif 
