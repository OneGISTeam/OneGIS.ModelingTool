//*******************************************************************
// FileName：  VBF_3DTransBlkTex.h
// Function：  3D交换数据模型：纹理数据块 (只存储非压缩格式的32位真彩色，RGBA)
// Author:     杜莹
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

	// 是否为满块
	bool IsFull()				{ return m_bFull; }
	void SetFull(bool bFull)	{ m_bFull = bFull; }

	// 设置/获取纹理的尺寸
	void SetSize(int nSizeX, int nSizeY);
	int  GetSizeX()				{ return m_nSizeX; }
	int  GetSizeY()				{ return m_nSizeY; }	

	// 设置/获取未压缩的纹理数据及其大小	
	bool  SetDataRGBA(BYTE* pBufRGBA);
	BYTE* GetBufRGBA()			{ return m_pBufRGBA; }
	int   GetBytesRGBA()		{ return m_nSizeRGBA; }	

	// 是否有数据
	bool HasData()	{ return (m_nSizeX>0 && m_nSizeY>0 && m_pBufRGBA!=NULL); }

private:
	
	// 清除块中的数据
	void Clear();	

private:
	bool		m_bFull;			// 是否为满块
	int			m_nSizeX;
	int			m_nSizeY;

	// 下列变量用于未压缩的RGBA纹理数据
	int			m_nSizeRGBA;
	BYTE*		m_pBufRGBA;
};


//================================== 实现部分 =================================

inline CVBF_TransBlkTex::CVBF_TransBlkTex()
	: CVBF_TransBlk(VBF_BLK_TEX)
{
	m_bFull			= false;
	m_nSizeX		= 0;
	m_nSizeY		= 0;

	// 下列变量用于未压缩的纹理数据 (只用来记录数据，不作串行化)
	m_nSizeRGBA		= 0;
	m_pBufRGBA		= NULL;
}

inline CVBF_TransBlkTex::~CVBF_TransBlkTex()
{
	Clear();
}

//----------------------------------------------------------------------------------------
// 函数：Clear()
// 描述：释放内存
//----------------------------------------------------------------------------------------
inline void CVBF_TransBlkTex::Clear()
{
	SAFE_DELETE_ARRAY(m_pBufRGBA);

	m_nSizeX        = 0;
	m_nSizeY        = 0;
	m_nSizeRGBA		= 0;
}

//----------------------------------------------------------------------------------------
// 函数：SetSize()
// 描述：设置纹理尺寸
//----------------------------------------------------------------------------------------
inline void CVBF_TransBlkTex::SetSize(int nSizeX, int nSizeY)
{
	Clear();

	m_nSizeX = nSizeX;
	m_nSizeY = nSizeY;
}

//----------------------------------------------------------------------------------------
// 函数：SetDataRGBA()
// 描述：设置未压缩的纹理数据及其大小
//----------------------------------------------------------------------------------------
inline bool CVBF_TransBlkTex::SetDataRGBA(BYTE* pBufRGBA)
{
	if(NULL==pBufRGBA) return false;

	// 如果大小未变，不需要重新分配内存
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