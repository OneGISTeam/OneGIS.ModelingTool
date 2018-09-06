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

	// Level，细节层次，LOD

	// 矢量数据的LOD的一个L（Level）
    class OSGEARTHFEATURES_EXPORT FeatureLevel
    {
    public:
        FeatureLevel( const CVBF_Config& config );
        FeatureLevel( float minRange, float maxRange );
        FeatureLevel( float minRange, float maxRange, const std::string& styleName );

		// 最小和最大显示距离
        float minRange() const { return *_minRange; }
        float maxRange() const { return *_maxRange; }

 		// 该Level关联的Style（或style selector）
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

   
	// 定义一个矢量数据层的multi-LOD layout
    class OSGEARTHFEATURES_EXPORT FeatureDisplayLayout : public ::CVBF_Referenced
    {
    public:
        FeatureDisplayLayout( const CVBF_Config& conf =CVBF_Config() );
        virtual ~FeatureDisplayLayout() { }


        // 可见距离与瓦片半径的比率，默认值是15。增加该值会产生更多更小的瓦片（在给定的视线距离上），减少该值会产生
		// 更少更大（范围大）的瓦片。如，factor=15，视线距离为120,000m，则产生的瓦片半径为8,000m(120,000/15=8,000).
        CVBF_Optional<float>& tileSizeFactor() { return _tileSizeFactor; }
        const CVBF_Optional<float>& tileSizeFactor() const { return _tileSizeFactor; }

        // 最大可视范围，与tileSizeFactor的计算相关
        CVBF_Optional<float>& maxRange() { return _maxRange;}
        const CVBF_Optional<float>& maxRange() const { return _maxRange;}

		// 所有瓦片的最小的可视范围
         CVBF_Optional<float>& minRange() { return _minRange; }
         const CVBF_Optional<float>& minRange() const { return _minRange; }

         // 当把一个数据分到网格中时，为了适应网格（cell）的范围，是否裁剪几何体
         // 默认值为false，意味着如果一个feature的图心在cell中，则包含该feature。
         // 设置为true，意味着如果feature的任何部分进入当前的cell，该feature将要被裁剪到cell的范围并使用它
        CVBF_Optional<bool>& cropFeatures() { return _cropFeatures; }
        const CVBF_Optional<bool>& cropFeatures() const { return _cropFeatures; }

        // 设置偏移量，用于计算瓦片分页优先级。调整该值将影响该数据相对于场景中其他分页数据(如地形和其他的矢量图层)的优先级
        CVBF_Optional<float>& priorityOffset() { return _priorityOffset; }
        const CVBF_Optional<float>& priorityOffset() const { return _priorityOffset; }

        // 设置比例，用于计算瓦片分页优先级，默认为1.0
        CVBF_Optional<float>& priorityScale() { return _priorityScale; }
        const CVBF_Optional<float>& priorityScale() const { return _priorityScale; }

		// 添加一个细节层次
        void addLevel( const FeatureLevel& level );

		// 获取细节层次的个数
        unsigned getNumLevels() const;

		// 获取第i个细节层次
        const FeatureLevel* getLevel( unsigned i ) const;

        // 对给定的Level，计算"最好的"四叉树LOD
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
