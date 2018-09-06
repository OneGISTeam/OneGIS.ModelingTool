#ifndef OSGEARTH_ANNOTATION_DECLUTTER_RENDER_BIN_H
#define OSGEARTH_ANNOTATION_DECLUTTER_RENDER_BIN_H 1

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SGUtil/RenderLeaf>
#include <limits.h>


// ���һ������ͼʹ��"decluttering"�㷨���������Decluttering::setEnabled( node->getOrCreateStateSet(), true );

#define OSGEARTH_DECLUTTER_BIN "declutter"

namespace osgEarth { namespace Annotation 
{

    // ��ʶ�࣬����ָʾ֧��ע���ڸǴ���
    class SupportsDecluttering
    {
        //nop
    };


    // �Զ���ĺ������Ƚ�����RenderLeaf������������ȼ��߷���TRUE�����򷵻�FALSE
    // ����ʹ��setDeclutterPriorityFunctor()�����Զ�������ȼ�������
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

    // ע��ѹ�Ǵ��������������
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

        // ȫ�ڵ���fully-occluded���������СAlphaֵ
        CVBF_Optional<float>& minAnimationAlpha() { return _minAnimAlpha; }
        const CVBF_Optional<float>& minAnimationAlpha() const { return _minAnimAlpha; }

        // ȫ�ڵ��������С����
        CVBF_Optional<float>& minAnimationScale() { return _minAnimScale; }
        const CVBF_Optional<float>& minAnimationScale() const { return _minAnimScale; }

        // һ������ӱ��ڵ��任���ɼ����õ�ʱ�䣨�룩
        CVBF_Optional<float>& inAnimationTime() { return _inAnimTime; }
        const CVBF_Optional<float>& inAnimationTime() const { return _inAnimTime; }

        // һ������ӿɼ��任�����ڵ����õ�ʱ�䣨��
        CVBF_Optional<float>& outAnimationTime() { return _outAnimTime; }
        const CVBF_Optional<float>& outAnimationTime() const { return _outAnimTime; }

        // �Ƿ񼤻�AnnotationData�����ȼ�����
        CVBF_Optional<bool>& sortByPriority() { return _sortByPriority; }
        const CVBF_Optional<bool>& sortByPriority() const { return _sortByPriority; }

        // �������Ƶ���������
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

    // ע��ѹ�Ǵ���
    struct OSGEARTHANNO_EXPORT Decluttering
    {
        // ��һ��״̬������/�ر�ע��ѹ�Ǵ���
        static void setEnabled( osg::StateSet* stateSet, bool enabled, int binNum =INT_MAX );

        // ����/�ر�ȫ��ע��ѹ�Ǵ���
        static void setEnabled( bool enabled );

        // �����ڸ�����ĺ�����ȷ����Ⱦҳ���ȼ�
        static void setSortFunctor( DeclutterSortFunctor* f );

        // ���ʹ��setDeclutterPriorityFunctor���õ��Զ�������ȼ�������ȥ��Ĭ�ϵ���Ϊ�����ݵ�����ľ�������
        static void clearSortFunctor();

        // ����������
        static void setOptions( const DeclutteringOptions& options );

        // ��ȡ��ǰ��������
        static const DeclutteringOptions& getOptions();
    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_DECLUTTER_RENDER_BIN_H
