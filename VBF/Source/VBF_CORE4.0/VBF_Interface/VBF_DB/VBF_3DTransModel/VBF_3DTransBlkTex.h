//*******************************************************************
// FileName��  VBF_3DTransBlkTex.h
// Function��  3D��������ģ�ͣ��������ݿ� (ֻ�洢��ѹ����ʽ��32λ���ɫ��RGBA)
// Author:     ��Ө
// Date:       2011-07-23
//*******************************************************************

#ifndef __VBF_3DTRANS_BLK_TEX_H__
#define __VBF_3DTRANS_BLK_TEX_H__

#include "VBF_3DTransBlk.h"

class CVBF_TransBlkTex : public CVBF_TransBlk
{
public:
	CVBF_TransBlkTex();
	virtual ~CVBF_TransBlkTex();	

	// �Ƿ�Ϊ����
	bool IsFull()				{ return m_bFull; }
	void SetFull(bool bFull)	{ m_bFull = bFull; }

	// ����/��ȡ����ĳߴ�
	void SetSize(int nSizeX, int nSizeY);
	int  GetSizeX()				{ return m_nSizeX; }
	int  GetSizeY()				{ return m_nSizeY; }	

	// ����/��ȡδѹ�����������ݼ����С	
	bool  SetDataRGBA(BYTE* pBufRGBA);
	BYTE* GetBufRGBA()			{ return m_pBufRGBA; }
	int   GetBytesRGBA()		{ return m_nSizeRGBA; }	

	// �Ƿ�������
	bool HasData()	{ return (m_nSizeX>0 && m_nSizeY>0 && m_pBufRGBA!=NULL); }

private:
	
	// ������е�����
	void Clear();	

private:
	bool		m_bFull;			// �Ƿ�Ϊ����
	int			m_nSizeX;
	int			m_nSizeY;

	// ���б�������δѹ����RGBA��������
	int			m_nSizeRGBA;
	BYTE*		m_pBufRGBA;
};


//================================== ʵ�ֲ��� =================================

inline CVBF_TransBlkTex::CVBF_TransBlkTex()
	: CVBF_TransBlk(VBF_BLK_TEX)
{
	m_bFull			= false;
	m_nSizeX		= 0;
	m_nSizeY		= 0;

	// ���б�������δѹ������������ (ֻ������¼���ݣ��������л�)
	m_nSizeRGBA		= 0;
	m_pBufRGBA		= NULL;
}

inline CVBF_TransBlkTex::~CVBF_TransBlkTex()
{
	Clear();
}

//----------------------------------------------------------------------------------------
// ������Clear()
// �������ͷ��ڴ�
//----------------------------------------------------------------------------------------
inline void CVBF_TransBlkTex::Clear()
{
	SAFE_DELETE_ARRAY(m_pBufRGBA);

	m_nSizeX        = 0;
	m_nSizeY        = 0;
	m_nSizeRGBA		= 0;
}

//----------------------------------------------------------------------------------------
// ������SetSize()
// ��������������ߴ�
//----------------------------------------------------------------------------------------
inline void CVBF_TransBlkTex::SetSize(int nSizeX, int nSizeY)
{
	Clear();

	m_nSizeX = nSizeX;
	m_nSizeY = nSizeY;
}

//----------------------------------------------------------------------------------------
// ������SetDataRGBA()
// ����������δѹ�����������ݼ����С
//----------------------------------------------------------------------------------------
inline bool CVBF_TransBlkTex::SetDataRGBA(BYTE* pBufRGBA)
{
	if(NULL==pBufRGBA) return false;

	// �����Сδ�䣬����Ҫ���·����ڴ�
	if(NULL==m_pBufRGBA)
	{
		int nNumPixels = m_nSizeX *  m_nSizeY;
		m_nSizeRGBA = nNumPixels * sizeof(BYTE) * 4;
		m_pBufRGBA = new BYTE[m_nSizeRGBA];
	}

	memcpy(m_pBufRGBA, pBufRGBA, m_nSizeRGBA);

	return true;
}

#endif