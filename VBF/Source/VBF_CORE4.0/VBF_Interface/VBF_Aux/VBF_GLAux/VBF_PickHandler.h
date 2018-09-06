//***************************************************************************************
// FileName��VBF_PickHandler.h
// Function���ڵ�ѡȡ���޷�ѡȡ�߶�
// Author:   ��Ө
// Date:     2012-04-24
//***************************************************************************************

#ifndef __VBF_PICK_HANDLER_H__
#define __VBF_PICK_HANDLER_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Engine/VBF_SGUtil/LineSegmentIntersector>
#include <VBF_Engine/VBF_SGUtil/PolytopeIntersector>


//------------------------------------------------------------------------
// ����ö�٣�EVBF_INTERSECT_METHOD
// ö���������󽻵ļ��㷽��
//------------------------------------------------------------------------
enum EVBF_INTERSECT_METHOD
{
	VBF_INTERSECT_METHOD_POLYTOPE		= 0,	// �����壨Ĭ��ֵ��
	VBF_INTERSECT_METHOD_LINESEGMENT	= 1,	// �߶�
};


class VBF_GLAUX_EXPORT CVBF_PickHandler : public osgGA::GUIEventHandler 
{
public:
	CVBF_PickHandler();

	// �����󽻵ļ��㷽����Ĭ��ֵΪVBF_INTERSECT_METHOD_POLYTOPE��
	void                  SetIntersectMethod(EVBF_INTERSECT_METHOD nMethod) { m_nIntersectMethod = nMethod; }
	EVBF_INTERSECT_METHOD GetIntersectMethod()			{ return m_nIntersectMethod; }

	// ��ѡȡ�޶���ָ���������£������ڶ������󽻣�
	void RestrictToSubgraph(osg::IVBF_SGNode* pGraphRoot) { m_piRootNode = pGraphRoot; }

	// ����ѡ���¼����������߶��󽻣�
	virtual bool ProcessPicked(const osgUtil::LineSegmentIntersector::Intersections& results) { return false; }

	// ����ѡ���¼��������ڶ������󽻣�
	virtual bool ProcessPicked(const osgUtil::PolytopeIntersector::Intersections& results) { return false; }

	// ����δѡȡ�¼�
	virtual bool ProcessUnPicked() { return false; }

	// ��������ѡȡ������¼����ͣ�Ĭ��Ϊ���˫����ֻ��ʹ�ã�PUSH/RELEASE/DOUBLECLICK
	bool SetMouseEventType(osgGA::GUIEventAdapter::EventType nType);

	// ��������¼��İ�����Ĭ��Ϊ������
	bool SetMouseButton(int nButton);
	
	virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

protected:

	// �û����������ѡȡ����갴��
	osgGA::GUIEventAdapter::EventType	m_nMouseEventType;
	int									m_nMouseButton;

	// �󽻵ļ��㷽��
	EVBF_INTERSECT_METHOD				m_nIntersectMethod;
	ref_ptr<osg::IVBF_SGNode>			m_piRootNode;
};


#endif
