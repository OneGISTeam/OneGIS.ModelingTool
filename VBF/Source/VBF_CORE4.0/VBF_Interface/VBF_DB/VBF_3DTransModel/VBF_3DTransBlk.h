//*******************************************************************
// FileName��  VBF_3DTransBlk.h
// Function��  3D��������ģ�ͣ����ݿ�Ļ���
// Author:     ��Ө
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

	// ��ȡ���ݿ������	 
	virtual VBF_BLK_TYPE GetBlkType() { return m_nBlkType; }

	// �������ݿ��Lod��ȫ��Ψһ���XY 
	virtual bool SetBlkNo(int nLod, int nBlkNoX, int nBlkNoY);

	// ��ȡ���ݿ��Lod��ȫ��Ψһ���XY 
	virtual int GetLod()			{ return m_nLod; }
	virtual int GetBlkNoX()			{ return m_nBlkNoX; }
	virtual int GetBlkNoY() 		{ return m_nBlkNoY; }

	// ��ȡ���ݿ龭γ�ȷ�Χ
	virtual bool   SetBlkBound(double dL0, double dB0, double dL1, double dB1);
	virtual double GetBlkL0()		{ return m_dL0; }
	virtual double GetBlkB0()		{ return m_dB0; }
	virtual double GetBlkL1()		{ return m_dL1; }
	virtual double GetBlkB1()		{ return m_dB1; }

	// �Ƿ�������
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


//================================== ʵ�ֲ��� =================================

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
// ������SetBlkNo()
// ���������ÿ��ȫ��Ψһ���
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
// ������SetBlkBound()
// ���������ÿ�ľ�γ�ȷ�Χ
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