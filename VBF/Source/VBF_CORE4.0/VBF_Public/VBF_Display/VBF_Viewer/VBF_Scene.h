#ifndef OSGVIEWER_SCENE
#define OSGVIEWER_SCENE 1

//#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
//#include <VBF_Display/VBF_Manipulator/VBF_EventVisitor.h>
#include <VBF_Engine/VBF_SGDB/DatabasePager>
#include <VBF_Engine/VBF_SGDB/ImagePager>

#include <VBF_Display/VBF_Viewer/Export>

#include <list>

class CVBF_View;

namespace osgViewer{

/** ����������ͼ�е������ĵ� */
class OSGVIEWER_EXPORT Scene : public ::CVBF_Referenced
{
    public:

        virtual const char* className() const { return "Scene"; }
		
		// ����/��ȡ����ͼ�θ��ڵ�
        void setSceneData(osg::IVBF_SGNode* node);
        osg::IVBF_SGNode* getSceneData();
        const osg::IVBF_SGNode* getSceneData() const;

		// ����/��ȡ��ҳ���ݿ�
        void setDatabasePager(osgDB::DatabasePager* dp);
        osgDB::DatabasePager* getDatabasePager() { return _databasePager.get(); }
        const osgDB::DatabasePager* getDatabasePager() const { return _databasePager.get(); }

		// ����/��ȡ��ҳͼ���
        void setImagePager(osgDB::ImagePager* ip);
        osgDB::ImagePager* getImagePager() { return _imagePager.get(); }
        const osgDB::ImagePager* getImagePager() const { return _imagePager.get(); }

		// ����
        void updateSceneGraph(osg::NodeVisitor& updateVisitor);


        /** �ӻ����л�ȡ���ڵ�Ϊָ���ڵ�ĳ���������Ҳ�������0 */
        static Scene* getScene(osg::IVBF_SGNode* node);
public:

        Scene();
    protected:
        friend class CVBF_View;

		// ��������CVBF_View�д���
        virtual ~Scene();

        /** �ӻ����в�����ָ���ˣ������ڵ��Ӧ�ĳ������������򴴽�һ�� */
        static Scene* getOrCreateScene(osg::IVBF_SGNode* node);
        
    
        ref_ptr<osg::IVBF_SGNode>             _sceneData;		// ����ͼ�θ��ڵ�

		// ��ҳ���������ڹ��캯���д�����Ҳ�������ⲿ�����滻Ĭ�ϵġ�
        ref_ptr<osgDB::DatabasePager>  _databasePager;   // ��ҳ���ݿ�
        ref_ptr<osgDB::ImagePager>     _imagePager;	  // ��ҳͼ���
};


}

#endif
