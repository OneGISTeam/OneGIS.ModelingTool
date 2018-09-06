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

/** 场景：是视图中的数据文档 */
class OSGVIEWER_EXPORT Scene : public ::CVBF_Referenced
{
    public:

        virtual const char* className() const { return "Scene"; }
		
		// 设置/获取场景图形根节点
        void setSceneData(osg::IVBF_SGNode* node);
        osg::IVBF_SGNode* getSceneData();
        const osg::IVBF_SGNode* getSceneData() const;

		// 设置/获取分页数据库
        void setDatabasePager(osgDB::DatabasePager* dp);
        osgDB::DatabasePager* getDatabasePager() { return _databasePager.get(); }
        const osgDB::DatabasePager* getDatabasePager() const { return _databasePager.get(); }

		// 设置/获取分页图像库
        void setImagePager(osgDB::ImagePager* ip);
        osgDB::ImagePager* getImagePager() { return _imagePager.get(); }
        const osgDB::ImagePager* getImagePager() const { return _imagePager.get(); }

		// 更新
        void updateSceneGraph(osg::NodeVisitor& updateVisitor);


        /** 从缓存中获取根节点为指定节点的场景，如果找不到返回0 */
        static Scene* getScene(osg::IVBF_SGNode* node);
public:

        Scene();
    protected:
        friend class CVBF_View;

		// 仅可以在CVBF_View中创建
        virtual ~Scene();

        /** 从缓存中查找与指定了（根）节点对应的场景，不存在则创建一个 */
        static Scene* getOrCreateScene(osg::IVBF_SGNode* node);
        
    
        ref_ptr<osg::IVBF_SGNode>             _sceneData;		// 场景图形根节点

		// 分页调度器。在构造函数中创建，也可以在外部设置替换默认的。
        ref_ptr<osgDB::DatabasePager>  _databasePager;   // 分页数据库
        ref_ptr<osgDB::ImagePager>     _imagePager;	  // 分页图像库
};


}

#endif
