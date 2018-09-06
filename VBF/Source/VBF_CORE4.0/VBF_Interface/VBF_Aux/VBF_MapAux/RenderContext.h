#ifndef SCENE_RENDER_CONTEXT_H
#define SCENE_RENDER_CONTEXT_H
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>



//#include <FeUtils/Export.h>
//#include <FeUtils/FreeViewPoint.h>

namespace FeUtil
{
	/**
	* @class CRenderContext
	* @brief ��װ��Ⱦϵͳ�Ļ���
	* @note ��װ����ά��Ⱦϵͳ����ײ㻷��������������ڲ�ʹ�ã�����Ϊϵͳ�ⲿʹ�á�
	* @author l00008
	*/

        class VBF_MAPAUX_EXPORT CRenderContext : public CVBF_Referenced
	{
	public:
		CRenderContext();
                CRenderContext(IVBF_View* pView, osg::IVBF_SGNodeGroup* pRoot, CVBFO_SGNodeMap* pMapNode);

		virtual ~CRenderContext(void);

	public:
		/**
		*@note: ���View����View�����ӿ�View
		*/
                virtual IVBF_View* GetView();
                virtual void SetView(IVBF_View* pView);

		/**
		*@note: �����Root������ڵ�������������Root�ڵ㣬һ�㲻�Ƽ��������
		*/
                virtual osg::IVBF_SGNodeGroup* GetRoot();
                virtual void SetRoot(osg::IVBF_SGNodeGroup* pRoot);

		/**
		*@note: ���osgEarth��mapNode
		*/
                virtual CVBFO_SGNodeMap* GetMapNode();
                virtual void SetMapNode(CVBFO_SGNodeMap* pMapNode);

		/**
		*@note:���ͶӰ����ʵ�Ǵ�MapNode���
		*/
                virtual const CVBF_SpatialReference* GetMapSRS();

		/**
		*@note: ����Լ����ó�����Ⱦϵͳ����ϵͳ�������֮����Ҫ�趨��Ⱦϵͳ
		*/
		virtual osg::GraphicsContext* GetGraphicsWindow();

		/**
		*@note: ��������
		*/
                osg::IVBF_Camera* GetCamera();

                typedef std::list<observer_ptr<osg::IVBF_SGNode> > OceanReflectionList;
                /**
                *@note: ��ú�����ڵ��б�
                */
                OceanReflectionList& GetOceanReflectionList()
                {
                    return m_oceanReflectionList;
                }
	public:

		/**  
		* @brief ע����Ƴ��¼�����Handler
		* @note ͳһ����ע����Ƴ������¼���Handler
		* @return �ɹ�true��ʧ��false
		*/
		bool AddEventHandler(osgGA::GUIEventHandler* pHandler);
		bool RemoveEventHandler(osgGA::GUIEventHandler* pHandler);

	protected:
                observer_ptr<osg::IVBF_SGNodeGroup>					m_opRoot;    //root�ڵ�
                observer_ptr<CVBFO_SGNodeMap>			m_opMapNode;     //���򳡾��ڵ�
                observer_ptr<IVBF_View>				m_opView;    //�����Ӿ���
                OceanReflectionList                             m_oceanReflectionList; //������ڵ��б�
	};

        class CRenderContextObserver
	{
	public:
		CRenderContextObserver(CRenderContext* pContext):m_opRenderContext(pContext){};

		virtual ~CRenderContextObserver(){};

	public:
		virtual CRenderContext* GetRenderContext(){return m_opRenderContext.get();}

		virtual  void SetRenderContext(CRenderContext* pContext ){m_opRenderContext = pContext;}

	protected:
                observer_ptr<CRenderContext>      m_opRenderContext;
	};

        class CRenderContextRefPtr
    {
    public:
        CRenderContextRefPtr(CRenderContext* pContext):m_opRenderContext(pContext){};

        virtual ~CRenderContextRefPtr(){};

    public:
        virtual CRenderContext* GetRenderContext(){return m_opRenderContext.get();}

        virtual  void SetRenderContext(CRenderContext* pContext ){m_opRenderContext = pContext;}

    protected:
        ref_ptr<CRenderContext>      m_opRenderContext;
    };
}

#endif//SCENE_SHELL_SYSTEM_SERVICE_H
