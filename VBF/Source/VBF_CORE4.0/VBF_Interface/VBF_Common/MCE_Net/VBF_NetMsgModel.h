//*******************************************************************
// FileName：  VBF_NetMsgModel.h
// Function：  网络中的消息，记录Model参数
// Author:     
// Date:       
//*******************************************************************

#ifndef __VBF_NET_MSG_MODEL_H__
#define __VBF_NET_MSG_MODEL_H__

#include "VBF_Common/MCE_Net/MCE_NetMsgBase.h"
#include "Types/Vec3d"

#define VBFVECTOR3D osg::Vec3d
class IMCE_NetMsg;

class CVBF_NetMsgModel : public CMCE_NetMsgBase 
{
public:
	CVBF_NetMsgModel(){}
	virtual ~CVBF_NetMsgModel()
	{
	}

	virtual IMCE_NetMsg* Clone()
	{
		CVBF_NetMsgModel* pMsg = new CVBF_NetMsgModel;

		CloneTo(pMsg);
		return pMsg;
	}
	virtual void CloneTo(IMCE_NetMsg* pMsg)
	{
		CMCE_NetMsgBase::CloneTo(pMsg);

		CVBF_NetMsgModel* pMsgT = (CVBF_NetMsgModel*)pMsg;	

		pMsgT->m_sID        = m_sID;
		pMsgT->m_sModelID   = m_sModelID;
		pMsgT->m_vPtGeo     = m_vPtGeo;

		pMsgT->m_fRotateX   = m_fRotateX;
		pMsgT->m_fRotateY   = m_fRotateY;
		pMsgT->m_fRotateZ   = m_fRotateZ;
	}

	virtual void Serialize(CArchive& ar)
	{
		CMCE_NetMsgBase::Serialize(ar);	
		
		if( ar.IsStoring() )
		{
			ar << m_sID;
			ar << m_sModelID;
			ar << m_vPtGeo.x;
			ar << m_vPtGeo.y;
			ar << m_vPtGeo.z;
			ar << m_fRotateX;
			ar << m_fRotateY;
			ar << m_fRotateZ;
		}
		else
		{
			ar >> m_sID;
			ar >> m_sModelID;
			ar >> m_vPtGeo.x;
			ar >> m_vPtGeo.y;
			ar >> m_vPtGeo.z;
			ar >> m_fRotateX;
			ar >> m_fRotateY;
			ar >> m_fRotateZ;
		}			
	}
	virtual UINT GetType() { return VBF_NETMSG_MODEL; }


public:

	CString       m_sID;
	CString       m_sModelID;
	VBFVECTOR3D	  m_vPtGeo;
	float         m_fRotateX;
	float         m_fRotateY;
	float         m_fRotateZ;
};

#endif 
