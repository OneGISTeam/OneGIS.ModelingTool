#ifndef OSGEARTH_ANNOTATION_DECLUTTER_RENDER_BIN_H
#define OSGEARTH_ANNOTATION_DECLUTTER_RENDER_BIN_H 1

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SGUtil/RenderLeaf>
#include <limits.h>


// 想对一个场景图使用"decluttering"算法，仅需调用Decluttering::setEnabled( node->getOrCreateStateSet(), true );

#define OSGEARTH_DECLUTTER_BIN "declutter"

namespace osgEarth { namespace Annotation 
{

    // 标识类，用于指示支持注记掩盖处理
    class SupportsDecluttering
    {
        //nop
    };


    // 自定义的函数，比较两个RenderLeaf，如果左侧的优先级高返回TRUE，否则返回FALSE
    // 可以使用setDeclutterPriorityFunctor()设置自定义的优先级排序函数
    struct DeclutterSortFunctor : public ::CVBF_Referenced
    {
        virtual bool operator() ( const osgUtil::RenderLeaf* lhs, const osgUtil::RenderLeaf* rhs ) const =0;
        virtual ~DeclutterSortFunctor() { }
    };

    /**
     * A decluttering functor that sorts by the priority field in AnnotationData.
     * AnnotationData should be attached to each Drawable's user data.
     */
    struct OSGEARTHANNO_EXPORT DeclutterByPriority : public DeclutterSortFunctor
    {
        virtual bool operator()(const osgUtil::RenderLeaf* lhs, const osgUtil::RenderLeaf* rhs ) const;
        virtual ~DeclutterByPriority() { }
    };

    // 注记压盖处理引擎的配置项
    class OSGEARTHANNO_EXPORT DeclutteringOptions
    {
    public:
        DeclutteringOptions( const CVBF_Config& conf =CVBF_Config() )
            : _minAnimAlpha         ( 0.35f ),
              _minAnimScale         ( 0.45f ),
              _inAnimTime           ( 0.40f ),
              _outAnimTime          ( 0.00f ),
              _sortByPriority       ( false ),
              _maxObjects           ( INT_MAX )
        {
            fromConfig(conf);
        }

        virtual ~DeclutteringOptions() { }

        // 全遮挡（fully-occluded）对象的最小Alpha值
        CVBF_Optional<float>& minAnimationAlpha() { return _minAnimAlpha; }
        const CVBF_Optional<float>& minAnimationAlpha() const { return _minAnimAlpha; }

        // 全遮挡对象的最小比例
        CVBF_Optional<float>& minAnimationScale() { return _minAnimScale; }
        const CVBF_Optional<float>& minAnimationScale() const { return _minAnimScale; }

        // 一个对象从被遮挡变换到可见所用的时间（秒）
        CVBF_Optional<float>& inAnimationTime() { return _inAnimTime; }
        const CVBF_Optional<float>& inAnimationTime() const { return _inAnimTime; }

        // 一个对象从可见变换到被遮挡所用的时间（秒
        CVBF_Optional<float>& outAnimationTime() { return _outAnimTime; }
        const CVBF_Optional<float>& outAnimationTime() const { return _outAnimTime; }

        // 是否激活AnnotationData的优先级排序
        CVBF_Optional<bool>& sortByPriority() { return _sortByPriority; }
        const CVBF_Optional<bool>& sortByPriority() const { return _sortByPriority; }

        // 排序后绘制的最大对象数
        CVBF_Optional<unsigned>& maxObjects() { return _maxObjects; }
        const CVBF_Optional<unsigned>& maxObjects() const { return _maxObjects; }

    public:
        CVBF_Config getConfig() const;

    protected:
        CVBF_Optional<float>    _minAnimAlpha;
        CVBF_Optional<float>    _minAnimScale;
        CVBF_Optional<float>    _inAnimTime;
        CVBF_Optional<float>    _outAnimTime;
        CVBF_Optional<bool>     _sortByPriority;
        CVBF_Optional<unsigned> _maxObjects;

        void fromConfig( const CVBF_Config& conf );
    };

    // 注记压盖处理
    struct OSGEARTHANNO_EXPORT Decluttering
    {
        // 对一个状态集启用/关闭注记压盖处理
        static void setEnabled( osg::StateSet* stateSet, bool enabled, int binNum =INT_MAX );

        // 启用/关闭全局注记压盖处理
        static void setEnabled( bool enabled );

        // 设置掩盖排序的函数，确定渲染页优先级
        static void setSortFunctor( DeclutterSortFunctor* f );

        // 清除使用setDeclutterPriorityFunctor设置的自定义的优先级函数，去掉默认的行为（根据到相机的距离排序）
        static void clearSortFunctor();

        // 设置配置项
        static void setOptions( const DeclutteringOptions& options );

        // 获取当前的配置项
        static const DeclutteringOptions& getOptions();
    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_DECLUTTER_RENDER_BIN_H
