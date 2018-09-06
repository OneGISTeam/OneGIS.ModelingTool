//*******************************************************************
// FileName��  IVBF_Blk.h
// Function��  VBF���ݿ飬��Dem/����/ע��
// Author:     ��Ө
// Date:       2011-07-06
//*******************************************************************

#ifndef __IVBF_BLK_H__
#define __IVBF_BLK_H__

#include "VBF_Common/VBF_ImgUtil/VBF_ImgCoderDataTypes.h"
#include "VBF_DB/VBF_3DTransModel/VBF_3DTransBlkDataTypes.h"
#include "VBF_DB/VBF_DemTexDataType.h"

//..\include,.\include,..\..\..\VBF_CORE4.0\VBF_Interface\VBF_DB\VBF_3DRasterDB,..\..\VBF_Common\MCE_ImgUtilDll\Include,..\..\MCE_Public,..\MCE_UtilDll\Include


#include <stdio.h>

// ������Ͷ�Ӧ���ļ���׺
static char* gs_szBlkFileExt[] =
{
	"δ֪��ʽ", 
	"demx", 
	"texx",
	"notx"
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_3DBlk
// �ӿ�������VBF���ݿ�
//--------------------------------------------------------------------
class IVBF_Blk
{
public:	
	virtual ~IVBF_Blk() {}	

	// ��ȡ���ݿ������	 
	virtual VBF_BLK_TYPE GetBlkType()=0;

	// �������ݿ��Lod��ȫ��Ψһ���XY 
	virtual bool SetBlkNo(int nLod, int nBlkNoX, int nBlkNoY)=0;

	// ��ȡ���ݿ��Lod��ȫ��Ψһ���XY 
	virtual int GetLod()=0;
	virtual int GetBlkNoX()=0;
	virtual int GetBlkNoY()=0;	

	// ��ȡ���ݿ龭γ�ȷ�Χ
	virtual double GetBlkL0()=0;
	virtual double GetBlkB0()=0;
	virtual double GetBlkL1()=0;
	virtual double GetBlkB1()=0;

	// �Ƿ�������
	virtual bool HasData()=0;
	
	// �Ӹ������ڴ������н�������Ϣ
	virtual bool FromBuf(BYTE* pBuf, int nBufSize)=0;

	// �������������ָ�����ڴ���
	virtual bool ToBuf(BYTE*& pBuf, int& nBufSize)=0;

	// ��ȡ����ֽ����� (��д�뵽�ļ��е��ֽ���)
	virtual int GetBytesBlk()=0;

	// д��������
	virtual bool Write(FILE* pFile)=0;

	// ������е�����
	virtual void Clear()=0;

	// ���ƿ�
	virtual IVBF_Blk* Clone()=0;
};


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_3DBlkDem
// �ӿ�������VBF���ݿ飺Dem
//--------------------------------------------------------------------
class IVBF_BlkDem : public IVBF_Blk
{
public:	
	virtual ~IVBF_BlkDem() {}

	// ����/��ȡDem�ĳߴ�
	virtual void SetSize(int nSizeX, int nSizeY)=0;
	virtual int  GetSizeX()=0;
	virtual int  GetSizeY()=0;

	// �Ƿ�Ϊ����
    virtual void SetFull(bool bFull)=0;
    virtual bool IsFull()=0;

	// ����/��ȡDem�����и̵߳�
	virtual bool   SetDataDem(float* pDem)=0;
	virtual float* GetBufDem()=0;
	virtual int    GetBytesDem()=0;

	// ����Dem�����и̵߳�

	/* ���ܣ���ȡָ��λ�õĸ߳�ֵ
	   ������nNoX -- ��������X���꣬���к�
             nNoY -- ��������Y���꣬���к�
	   ˵���������λ��û�����ݣ�ֱ�ӷ���false
	*/
	virtual bool GetDem(int nNoX, int nNoY, float* pfValue)=0;

	// ����/��ȡ�����С�߳�ֵ
	virtual void  CalHeightMinMax()=0;
	virtual float GetHeightMin()=0;
	virtual float GetHeightMax()=0;
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_3DBlkTex
// �ӿ�������VBF���ݿ飺����
//--------------------------------------------------------------------
class IVBF_BlkTex : public IVBF_Blk
{
public:	
	virtual ~IVBF_BlkTex() {}

	// �Ƿ�Ϊ����
    virtual bool IsFull()=0;
    virtual void SetFull(bool bFull)=0;

	// ����/��ȡ����ĳߴ�
	virtual void SetSize(int nSizeX, int nSizeY)=0;
	virtual int  GetSizeX()=0;
	virtual int  GetSizeY()=0;

	// ����/��ȡ������뷽ʽ
	virtual bool SetCodeType(VBF_IMGCODETYPE nCodeType)=0;
	virtual VBF_IMGCODETYPE  GetCodeType()=0;

	// ����/��ȡѹ������������ݼ����С
	virtual bool  SetDataCoded(BYTE* pBuf, int nBufSize)=0;
	virtual bool  GetDataCoded(BYTE*& pBuf, int& nBufSize)=0;
	virtual BYTE* GetBufCoded()=0;
	virtual int   GetBytesCoded()=0;

	// ����/��ȡ����ͼ���ݼ����С
	virtual bool  SetDataMask(BYTE* pBuf, int nBufSize)=0;
	virtual bool  GetDataMask(BYTE*& pBuf, int& nBufSize)=0;
	virtual BYTE* GetBufMask()=0;
	virtual int   GetBytesMask()=0;

	// ����/��ȡδѹ�����������ݼ����С	
	virtual bool  SetDataRGBA(BYTE* pBuf, int nBufSize)=0;
	virtual bool  GetDataRGBA(BYTE*& pBuf, int& nBufSize)=0;
	virtual BYTE* GetBufRGBA()=0;
	virtual int   GetBytesRGBA()=0;

	// ������룺����RGBA���ݣ�����ѹ�����ݺ�Mask���ݣ�����pOptinos��ʾ����ѡ���JPGѹ�������ȣ�����ΪNULL
	virtual bool  Encode(void* pOptinos=NULL)=0;

	// ������룺����ѹ�����ݺ�Mask���ݣ�����RGBA����
	virtual bool  Decode()=0;
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_3DBlkNote
// �ӿ�������VBF���ݿ飺ע��
//--------------------------------------------------------------------
class IVBF_BlkNote : public IVBF_Blk
{
public:	
	virtual ~IVBF_BlkNote() {}	

	// ����ע������
	virtual bool SetNoteData(int nNumNotes, VBF_NOTEDATA** pNoteData)=0;	

	// ��ȡע������
	virtual int             GetNumNotes()=0;	
	virtual VBF_NOTEDATA**  GetNoteData()=0;	
};


#endif 
