#ifndef OSGEARTH_ANNOTATION_ANNOTATION_DATA_H
#define OSGEARTH_ANNOTATION_ANNOTATION_DATA_H 1

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;

    // 保存注记的元数据或额外数据，被记录在节点的UserData container中
    class OSGEARTHANNO_EXPORT AnnotationData : public ::CVBF_Referenced
    {
    public:
        AnnotationData();
        AnnotationData( const CVBF_Config& conf );

    public:
        void setName( const std::string& value ) { m_sName = value; }
        const std::string& getName() const { return m_sName; }

        // 注记的可读性描述
        void setDescription( const std::string& value ) { _description = value; }
        const std::string& getDescription() const { return _description; }

        // 优先级
        void setPriority( float value ) { _priority = value; }
        float getPriority() const { return _priority; }

        // 与注记相关联的视点（焦点）
        const CVBF_Viewpoint* getViewpoint() const { return _viewpoint; }
        void setViewpoint( const CVBF_Viewpoint& vp )
        {
            if ( _viewpoint ) delete _viewpoint;
            _viewpoint = new CVBF_Viewpoint(vp);
        }


    public: // serialization

        virtual void mergeConfig(const CVBF_Config& conf);
        CVBF_Config getConfig() const;

    public:
        virtual ~AnnotationData();

    protected:
        std::string m_sName;
        std::string _description;
        float       _priority;
        CVBF_Viewpoint*  _viewpoint;
    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_ANNOTATION_DATA_H
