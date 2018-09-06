#ifndef OSGEARTHFEATURES_FEATURE_DISPLAY_LAYOUT_H
#define OSGEARTHFEATURES_FEATURE_DISPLAY_LAYOUT_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <vector>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;

	// Level��ϸ�ڲ�Σ�LOD

	// ʸ�����ݵ�LOD��һ��L��Level��
    class OSGEARTHFEATURES_EXPORT FeatureLevel
    {
    public:
        FeatureLevel( const CVBF_Config& config );
        FeatureLevel( float minRange, float maxRange );
        FeatureLevel( float minRange, float maxRange, const std::string& styleName );

		// ��С�������ʾ����
        float minRange() const { return *_minRange; }
        float maxRange() const { return *_maxRange; }

 		// ��Level������Style����style selector��
        CVBF_Optional<std::string>& styleName() { return _styleName; }
        const CVBF_Optional<std::string>& styleName() const { return _styleName; }

        virtual ~FeatureLevel() { }

    public:
        CVBF_Config getConfig() const;

    protected:
        void fromConfig( const CVBF_Config& conf );

        CVBF_Optional<float>       _minRange;
        CVBF_Optional<float>       _maxRange;
        CVBF_Optional<std::string> _styleName;
    };

   
	// ����һ��ʸ�����ݲ��multi-LOD layout
    class OSGEARTHFEATURES_EXPORT FeatureDisplayLayout : public ::CVBF_Referenced
    {
    public:
        FeatureDisplayLayout( const CVBF_Config& conf =CVBF_Config() );
        virtual ~FeatureDisplayLayout() { }


        // �ɼ���������Ƭ�뾶�ı��ʣ�Ĭ��ֵ��15�����Ӹ�ֵ����������С����Ƭ���ڸ��������߾����ϣ������ٸ�ֵ�����
		// ���ٸ��󣨷�Χ�󣩵���Ƭ���磬factor=15�����߾���Ϊ120,000m�����������Ƭ�뾶Ϊ8,000m(120,000/15=8,000).
        CVBF_Optional<float>& tileSizeFactor() { return _tileSizeFactor; }
        const CVBF_Optional<float>& tileSizeFactor() const { return _tileSizeFactor; }

        // �����ӷ�Χ����tileSizeFactor�ļ������
        CVBF_Optional<float>& maxRange() { return _maxRange;}
        const CVBF_Optional<float>& maxRange() const { return _maxRange;}

		// ������Ƭ����С�Ŀ��ӷ�Χ
         CVBF_Optional<float>& minRange() { return _minRange; }
         const CVBF_Optional<float>& minRange() const { return _minRange; }

         // ����һ�����ݷֵ�������ʱ��Ϊ����Ӧ����cell���ķ�Χ���Ƿ�ü�������
         // Ĭ��ֵΪfalse����ζ�����һ��feature��ͼ����cell�У��������feature��
         // ����Ϊtrue����ζ�����feature���κβ��ֽ��뵱ǰ��cell����feature��Ҫ���ü���cell�ķ�Χ��ʹ����
        CVBF_Optional<bool>& cropFeatures() { return _cropFeatures; }
        const CVBF_Optional<bool>& cropFeatures() const { return _cropFeatures; }

        // ����ƫ���������ڼ�����Ƭ��ҳ���ȼ���������ֵ��Ӱ�����������ڳ�����������ҳ����(����κ�������ʸ��ͼ��)�����ȼ�
        CVBF_Optional<float>& priorityOffset() { return _priorityOffset; }
        const CVBF_Optional<float>& priorityOffset() const { return _priorityOffset; }

        // ���ñ��������ڼ�����Ƭ��ҳ���ȼ���Ĭ��Ϊ1.0
        CVBF_Optional<float>& priorityScale() { return _priorityScale; }
        const CVBF_Optional<float>& priorityScale() const { return _priorityScale; }

		// ���һ��ϸ�ڲ��
        void addLevel( const FeatureLevel& level );

		// ��ȡϸ�ڲ�εĸ���
        unsigned getNumLevels() const;

		// ��ȡ��i��ϸ�ڲ��
        const FeatureLevel* getLevel( unsigned i ) const;

        // �Ը�����Level������"��õ�"�Ĳ���LOD
        unsigned chooseLOD( const FeatureLevel& level, double fullExtentRadius ) const;

    public:
        CVBF_Config getConfig() const;

    protected:
        CVBF_Optional<float> _tileSizeFactor;
        CVBF_Optional<float> _minRange;
        CVBF_Optional<float> _maxRange;
        CVBF_Optional<bool>  _cropFeatures;
        CVBF_Optional<float> _priorityOffset;
        CVBF_Optional<float> _priorityScale;
        typedef std::multimap<float,FeatureLevel> Levels;
        Levels _levels;

        void fromConfig( const CVBF_Config& conf );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_DISPLAY_LAYOUT_H
