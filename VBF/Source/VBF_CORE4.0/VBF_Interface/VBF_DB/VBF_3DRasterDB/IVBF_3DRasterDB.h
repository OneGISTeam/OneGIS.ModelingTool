//*******************************************************************
// FileName��  IVBF_3DRasterDB.h
// Function��  3Dդ�����ݿ⣬����VBF���ݿ�Ķ�ȡ��д��
// Author:     ��Ө
// Date:       2011-07-06
//*******************************************************************

#ifndef __IVBF_3DRASTERDB_H__
#define __IVBF_3DRASTERDB_H__

#include "VBF_3DRasterDBExport.h"
#include "IVBF_Blk.h"

#include <Types/VBF_Rect.h>

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_3DRasterDB
// �ӿ�������3Dդ�����ݿ⣬����VBF���ݿ�Ķ�ȡ��д��
//--------------------------------------------------------------------
class IVBF_3DRasterDB 
{
public:	
	virtual ~IVBF_3DRasterDB() {}

	/* ���ܣ���һ�����ݿ�
       ������szURL -- ���ݿ�ȫ·��������Ǳ����ļ���ʽ�����ļ�·�������������·������htp://��ftp://
       ���أ��ɹ�����true�����򷵻�false
	*/
	virtual bool Open(const char* szURL)=0;

	/* ���ܣ��ر�һ�����ݿ�
       ���أ��ɹ�����true�����򷵻�false
	*/
	virtual bool Close()=0;

	/* ���ܣ���ȡ�Ѵ����ݿ��ȫ·��
       ���أ����ݿ�ȫ·��������Ǳ����ļ���ʽ�����ļ�·�������������·������htp://��ftp://
	*/
	virtual const char* GetURL()=0;

	/* ���ܣ�����һ�����ݿ�
	   ������nBlkType -- ���ݿ������			 
	   ���أ����������ݿ飬NULL��ʾ����ʧ��
	*/
	virtual IVBF_Blk* CreateBlk(VBF_BLK_TYPE nBlkType)=0;	
	
	/* ���ܣ�д��һ�����ݿ�
	   ������pIBlk	 -- ��д������ݿ�
	   ���أ��ɹ�����true�����򷵻�false
	*/
	virtual bool WriteBlk(IVBF_Blk* pIBlk)=0;	

	/* ���ܣ���ȡһ�����ݿ�
	   ������pIBlk	   -- ����ȡ�����ݿ�
	         bReadOnly -- �ÿ��Ƿ�ֻ������ȡ
	   ���أ��ɹ�����true�����򷵻�false
	*/
	virtual bool ReadBlk(IVBF_Blk* pIBlk, bool bReadOnly)=0;
	
	/* ���ܣ���ȡ���ݿ����ڵ��ļ��� (������·��)
	   ������pIBlk	    -- ���ݿ�ָ�룬����ΪNULL
	         szFileName -- ���洢�ļ������ڴ���������ΪNULL
	   ���أ��ɹ�����true�����򷵻�false
	*/
	virtual bool GetBlkFileName(IVBF_Blk* pIBlk, char* szFileName)=0;

	/* ���ܣ����ݵ������꣬���Ҵ����������ݵ����Lod����
	   ���������������еľ��Ⱥ�γ�� (��λ����)
	   ���أ������괦�������ݵ����Lod����
	*/
	virtual int GetLodMaxOfDataTex(double L, double B)=0;

	/* ���ܣ���ȡ�������ݵ���С/���Lod���𣨲��������ݵĸ��Ƿ�Χ��
	   ���أ������ݿ����������ݵ���С/���Lod����
	*/
	virtual int GetLodMinOfDataTex()=0;
	virtual int GetLodMaxOfDataTex()=0;

	/* ���ܣ���ȡDen���ݵ���С/���Lod���𣨲��������ݵĸ��Ƿ�Χ��
	   ���أ������ݿ���Dem���ݵ���С/���Lod����
	*/
	virtual int GetLodMinOfDataDem()=0;
	virtual int GetLodMaxOfDataDem()=0;

    virtual bool LoadBlkDem(double dGeoX0, double dGeoX1, double dGeoY0, double dGeoY1, int nLod,
                            int& nRow, int& nCol, float**& pDem, CVBF_RectD& rBlkGeo)=0;
	virtual bool GetGeoDem(double dGeoX, double dGeoY, int nLod, float& fDem)=0;
};


// ȫ�ֺ���: ����/�ͷ�һ��3Dդ�����ݿ�
VBF_3DRASTERDB_EXPORT IVBF_3DRasterDB*  VBF_Create3DRasterDB();
VBF_3DRASTERDB_EXPORT void              VBF_Release3DRasterDB(IVBF_3DRasterDB*& pIDB);



#endif 
