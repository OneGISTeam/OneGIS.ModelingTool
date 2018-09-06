#ifndef VBF_RENDER_CONTEXT_H
#define VBF_RENDER_CONTEXT_H

#include <VBF_3DMapAux/VBF_3DManipulator/VBF_3DManipulator_Global.h>

#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

/**
* @class CVBF_ManipulatorContext
* @brief 封装渲染系统的环境
* @note 封装了三维渲染系统的最底层环境，此类仅仅供内部使用，不作为系统外部使用。
* @author l00008
*/
class VBF_3DMANIPULATORSHARED_EXPORT CVBF_ManipulatorContext : public CVBF_Referenced
{
public:
	CVBF_ManipulatorContext();
	CVBF_ManipulatorContext(IVBF_View* pView, osg::IVBF_SGNodeGroup* pRoot, CVBFO_SGNodeMap* pMapNode);

	virtual ~CVBF_ManipulatorContext(void);

public:
	/**
	*@note: 获得View，此View是主视口View
	*/
	virtual IVBF_View* GetView();
	virtual void SetView(IVBF_View* pView);

	/**
	*@note: 获得主Root，这个节点是整个场景的Root节点，一般不推荐对其操作
	*/
	virtual osg::IVBF_SGNodeGroup* GetRoot();
	virtual void SetRoot(osg::IVBF_SGNodeGroup* pRoot);

	/**
	*@note: 获得osgEarth的mapNode
	*/
	virtual CVBFO_SGNodeMap* GetMapNode();
	virtual void SetMapNode(CVBFO_SGNodeMap* pMapNode);

	/**
	*@note:获得投影，其实是从MapNode获得
	*/
	virtual const CVBF_SpatialReference* GetMapSRS();

	/**
	*@note: 获得以及设置场景渲染系统，在系统构建完成之后需要设定渲染系统
	*/
	virtual osg::GraphicsContext* GetGraphicsWindow();

	/**
	*@note: 获得主相机
	*/
	osg::IVBF_Camera* GetCamera();

	typedef std::list<observer_ptr<osg::IVBF_SGNode> > OceanReflectionList;
	/**
	*@note: 获得海洋反射节点列表
	*/
	OceanReflectionList& GetOceanReflectionList()
	{
		return m_oceanReflectionList;
	}
public:

	/**  
	* @brief 注册和移除事件处理Handler
	* @note 统一管理注册和移除处理事件的Handler
	* @return 成功true，失败false
	*/
	bool AddEventHandler(osgGA::GUIEventHandler* pHandler);
	bool RemoveEventHandler(osgGA::GUIEventHandler* pHandler);

protected:
	observer_ptr<osg::IVBF_SGNodeGroup>					m_opRoot;    //root节点
	observer_ptr<CVBFO_SGNodeMap>			m_opMapNode;     //地球场景节点
	observer_ptr<IVBF_View>				m_opView;    //场景视景器
	OceanReflectionList                             m_oceanReflectionList; //海洋反射节点列表
};

#endif//SCENE_SHELL_SYSTEM_SERVICE_H
