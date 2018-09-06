//***************************************************************************************
// FileName：VBF_PickHandler.h
// Function：节点选取，无法选取线段
// Author:   杜莹
// Date:     2012-04-24
//***************************************************************************************

#ifndef __VBF_PICK_HANDLER_H__
#define __VBF_PICK_HANDLER_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Engine/VBF_SGUtil/LineSegmentIntersector>
#include <VBF_Engine/VBF_SGUtil/PolytopeIntersector>


//------------------------------------------------------------------------
// 定义枚举：EVBF_INTERSECT_METHOD
// 枚举描述：求交的计算方法
//------------------------------------------------------------------------
enum EVBF_INTERSECT_METHOD
{
	VBF_INTERSECT_METHOD_POLYTOPE		= 0,	// 多面体（默认值）
	VBF_INTERSECT_METHOD_LINESEGMENT	= 1,	// 线段
};


class VBF_GLAUX_EXPORT CVBF_PickHandler : public osgGA::GUIEventHandler 
{
public:
	CVBF_PickHandler();

	// 设置求交的计算方法（默认值为VBF_INTERSECT_METHOD_POLYTOPE）
	void                  SetIntersectMethod(EVBF_INTERSECT_METHOD nMethod) { m_nIntersectMethod = nMethod; }
	EVBF_INTERSECT_METHOD GetIntersectMethod()			{ return m_nIntersectMethod; }

	// 将选取限定在指定的子树下（仅用于多面体求交）
	void RestrictToSubgraph(osg::IVBF_SGNode* pGraphRoot) { m_piRootNode = pGraphRoot; }

	// 处理选中事件（仅用于线段求交）
	virtual bool ProcessPicked(const osgUtil::LineSegmentIntersector::Intersections& results) { return false; }

	// 处理选中事件（仅用于多面体求交）
	virtual bool ProcessPicked(const osgUtil::PolytopeIntersector::Intersections& results) { return false; }

	// 处理未选取事件
	virtual bool ProcessUnPicked() { return false; }

	// 设置用于选取的鼠标事件类型，默认为鼠标双击，只能使用：PUSH/RELEASE/DOUBLECLICK
	bool SetMouseEventType(osgGA::GUIEventAdapter::EventType nType);

	// 设置鼠标事件的按键，默认为鼠标左键
	bool SetMouseButton(int nButton);
	
	virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

protected:

	// 用户定义的用于选取的鼠标按键
	osgGA::GUIEventAdapter::EventType	m_nMouseEventType;
	int									m_nMouseButton;

	// 求交的计算方法
	EVBF_INTERSECT_METHOD				m_nIntersectMethod;
	ref_ptr<osg::IVBF_SGNode>			m_piRootNode;
};


#endif
