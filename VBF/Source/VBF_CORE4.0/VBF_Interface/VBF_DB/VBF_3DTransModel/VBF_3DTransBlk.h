//*******************************************************************
// FileName：  VBF_3DTransBlk.h
// Function：  3D交换数据模型：数据块的基类
// Author:     杜莹
// Date:       2011-07-23
//*******************************************************************

#ifndef __VBF_3DTRANS_BLK_H__
#define __VBF_3DTRANS_BLK_H__

#include "VBF_DB\\VBF_3DTransModel\\VBF_3DTransBlkDataTypes.h"


class CVBF_TransBlk
{
public:
	CVBF_TransBlk(VBF_BLK_TYPE nBlkType);
	virtual ~CVBF_TransBlk();

	// 获取数据块的类型	 
	virtual VBF_BLK_TYPE GetBlkType() { return m_nBlkType; }

	// 设置数据块的Lod和全球唯一编号XY 
	virtual bool SetBlkNo(int nLod, int nBlkNoX, int nBlkNoY);

	// 获取数据块的Lod和全球唯一编号XY 
	virtual int GetLod()			{ return m_nLod; }
	virtual int GetBlkNoX()			{ return m_nBlkNoX; }
	virtual int GetBlkNoY() 		{ return m_nBlkNoY; }

	// 获取数据块经纬度范围
	virtual bool   SetBlkBound(double dL0, double dB0, double dL1, double dB1);
	virtual double GetBlkL0()		{ return m_dL0; }
	virtual double GetBlkB0()		{ return m_dB0; }
	virtual double GetBlkL1()		{ return m_dL1; }
	virtual double GetBlkB1()		{ return m_dB1; }

	// 是否有数据
	virtual bool HasData()=0;		

protected:
	VBF_BLK_TYPE	m_nBlkType;	
	int				m_nLod;
	int				m_nBlkNoX;
	int				m_nBlkNoY;

	double			m_dL0;
	double			m_dB0;
	double			m_dL1;
	double			m_dB1;
};


//================================== 实现部分 =================================

inline CVBF_TransBlk::CVBF_TransBlk(VBF_BLK_TYPE nBlkType)
{
	m_nBlkType	= nBlkType;	
	m_nLod		= -1;
	m_nBlkNoX	= -1;
	m_nBlkNoY	= -1;

	m_dL0		= 0.0;
	m_dB0		= 0.0;
	m_dL1		= 0.0;
	m_dB1		= 0.0;
}

inline CVBF_TransBlk::~CVBF_TransBlk()
{
}

//----------------------------------------------------------------------------------------
// 函数：SetBlkNo()
// 描述：设置块的全球唯一编号
//----------------------------------------------------------------------------------------
inline bool CVBF_TransBlk::SetBlkNo(int nLod, int nBlkNoX, int nBlkNoY)
{
	if(nLod<0 || nLod>30) return false;

	m_nLod		= nLod;
	m_nBlkNoX	= nBlkNoX;
	m_nBlkNoY	= nBlkNoY;	

	return true;
}

//----------------------------------------------------------------------------------------
// 函数：SetBlkBound()
// 描述：设置块的经纬度范围
//----------------------------------------------------------------------------------------
inline bool CVBF_TransBlk::SetBlkBound(double dL0, double dB0, double dL1, double dB1)
{
	if(dL0<-180.0 || dB0<-90.0 || dL1>180.0 || dB1>90.0) return false;

	m_dL0	= dL0;
	m_dB0	= dB0;
	m_dL1	= dL1;
	m_dB1	= dB1;

	return true;
}

#endif