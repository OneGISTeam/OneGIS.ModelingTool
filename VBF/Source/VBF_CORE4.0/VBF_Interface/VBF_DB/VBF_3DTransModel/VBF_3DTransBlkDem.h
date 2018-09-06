//*******************************************************************
// FileName��  VBF_3DTransBlkDem.h
// Function��  3D��������ģ�ͣ�Dem���ݿ�
// Author:     ��Ө
// Date:       2011-07-23
//*******************************************************************

#ifndef __VBF_3DTRANS_BLK_DEM_H__
#define __VBF_3DTRANS_BLK_DEM_H__

#include "VBF_3DTransBlk.h"
#include "VBF_Macros.h"

class CVBF_TransBlkDem : public CVBF_TransBlk
{
public:
	CVBF_TransBlkDem();
	virtual ~CVBF_TransBlkDem();

	// ����/��ȡDem�ĳߴ�
	void SetSize(int nSizeX, int nSizeY);
	int  GetSizeX()				{ return m_nSizeX; }
	int  GetSizeY()				{ return m_nSizeY; }

	// �Ƿ�Ϊ����
	void SetFull(bool bFull)	{ m_bFull = bFull; }	
	bool IsFull()				{ return m_bFull; }		

	// ����/��ȡDem�����и̵߳�
	bool   SetDataDem(float* pDem);
	float* GetBufDem()			{ return m_pDem; }
	int    GetBytesDem()		{ return m_nSizeData; }	

	// ��ȡ�����С�߳�ֵ
	float GetHeightMin()		{ return (float)m_dHeightMin; }
	float GetHeightMax()		{ return (float)m_dHeightMax; }
	
	// �Ƿ�������
	bool HasData()              { return (m_nSizeX>0 && m_nSizeY>0 && m_pDem!=NULL); }	

private:
	void	Clear();

private:
	bool		m_bFull;
	int			m_nSizeX;
	int			m_nSizeY;
	
	double		m_dHeightMin;
	double		m_dHeightMax;

	float*		m_pDem;
	int			m_nSizeData;
};


//================================== ʵ�ֲ��� =================================

inline CVBF_TransBlkDem::CVBF_TransBlkDem()
	: CVBF_TransBlk(VBF_BLK_DEM)
{
	m_bFull		  = false;
	m_nSizeX      = 0;
	m_nSizeY      = 0;
	m_dHeightMin  = 0.0;
	m_dHeightMax  = 0.0;

	m_nSizeData   = 0;
	m_pDem        = NULL;
}

inline CVBF_TransBlkDem::~CVBF_TransBlkDem()
{
	Clear();
}

//----------------------------------------------------------------------------------------
// ������Clear()
// �������ͷ��ڴ�
//----------------------------------------------------------------------------------------
inline void CVBF_TransBlkDem::Clear()
{
	SAFE_DELETE(m_pDem);

	m_nSizeX	= 0;
	m_nSizeY	= 0;	
	m_nSizeData	= 0;
}

//----------------------------------------------------------------------------------------
// ������SetSize()
// ����������Dem�Ĵ�С�������·����ڴ�
//----------------------------------------------------------------------------------------
inline void CVBF_TransBlkDem::SetSize(int nSizeX, int nSizeY)
{
	Clear();

	m_nSizeX = nSizeX;
	m_nSizeY = nSizeY;
}

//----------------------------------------------------------------------------------------
// ������SetDataDem()
// ����������Dem������
//----------------------------------------------------------------------------------------
inline bool CVBF_TransBlkDem::SetDataDem(float* pDem)
{
	if(m_nSizeX<=0 || m_nSizeY<=0) return false;

	// �����ڴ�
	if(NULL==m_pDem)
	{
		int nNumPoints = m_nSizeX *  m_nSizeY;
		m_nSizeData = nNumPoints * sizeof(float);
		m_pDem = new float[nNumPoints];
	}

	memcpy(m_pDem, pDem, m_nSizeData);
	return true;
}


#endif