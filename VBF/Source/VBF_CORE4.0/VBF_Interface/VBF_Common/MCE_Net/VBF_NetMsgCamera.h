//*******************************************************************
// FileName：  VBF_NetMsgCamera.h
// Function：  网络中的消息，记录Camera参数(从服务器端发往客户端)
// Author: 
// Date:       2005-11-16
//*******************************************************************

#ifndef __VBF_NET_MSG_CAMERA_H__
#define __VBF_NET_MSG_CAMERA_H__

#include "VBF_NetMsgBase.h"
#include "Types\VBF_3DMathType.h"

class IMCE_NetMsg;

class CVBF_NetMsgCamera : public CVBF_NetMsgBase 
{
//	DECLARE_SERIAL(CVBF_NetMsgCamera) 

public:
	CVBF_NetMsgCamera(){}
	virtual ~CVBF_NetMsgCamera(){}

	virtual IMCE_NetMsg* Clone()
	{
		CVBF_NetMsgCamera* pMsg = new CVBF_NetMsgCamera;

		CloneTo(pMsg);
		return pMsg;
	}
	virtual void CloneTo(IMCE_NetMsg* pMsg)
	{
		CVBF_NetMsgBase::CloneTo(pMsg);

		CVBF_NetMsgCamera* pMsgT = (CVBF_NetMsgCamera*)pMsg;	

		pMsgT->m_vEyePtGeo = m_vEyePtGeo;
		pMsgT->m_dAngleH   = m_dAngleH;
		pMsgT->m_dAngleV   = m_dAngleV;
	}

	virtual void Serialize(CArchive& ar)
	{
		CVBF_NetMsgBase::Serialize(ar);	
		
		if( ar.IsStoring() )
		{
			ar << m_vEyePtGeo.x;
			ar << m_vEyePtGeo.y;
			ar << m_vEyePtGeo.z;
			ar << m_dAngleH;
			ar << m_dAngleV;		
		}
		else
		{
			ar >> m_vEyePtGeo.x;
			ar >> m_vEyePtGeo.y;
			ar >> m_vEyePtGeo.z;
			ar >> m_dAngleH;
			ar >> m_dAngleV;			
		}			
	}
	virtual UINT GetType() { return VBF_NETMSG_CAMERA; }
	
	// 获取成员变量
	VBFVECTOR3D  GetEyePtGeo() { return m_vEyePtGeo; }
	double      GetAngleH()   { return m_dAngleH; }
	double      GetAngleV()   { return m_dAngleV; }

	// 设置成员变量
	void        SetEyePtGeo(const VBFVECTOR3D& vEyePtGeo) { m_vEyePtGeo = vEyePtGeo; }
	void        SetAngleH(double dAngleH)   { m_dAngleH = dAngleH; }
	void        SetAngleV(double dAngleV)   { m_dAngleV = dAngleV; }


protected:
	VBFVECTOR3D		m_vEyePtGeo;
	double			m_dAngleH;
	double			m_dAngleV;	
};

#endif 
