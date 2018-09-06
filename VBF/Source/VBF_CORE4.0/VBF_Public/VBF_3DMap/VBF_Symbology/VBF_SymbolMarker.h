#ifndef OSGEARTHSYMBOLOGY_MARKER_SYMBOL_H
#define OSGEARTHSYMBOLOGY_MARKER_SYMBOL_H 1

#include <climits>

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>
#include <Types/Vec3f>

namespace osgEarth { namespace Symbology
{
    class InstanceSymbol;

    // MarkerSymbol用"markers"替代几何体，marker是另一个对象（如3D模型或图像）
    class OSGEARTHSYMBOLOGY_EXPORT MarkerSymbol : public Symbol
    {
    public:
		// 模型的定位位置
        enum Placement
        {
            PLACEMENT_CENTROID, // 放在中心上
            PLACEMENT_VERTEX,   // 放在每一个点上
            PLACEMENT_INTERVAL, // 把模型实例按规则的间隔沿几何体（线）放置或在内部均匀排列，间隔与密度相关
            PLACEMENT_RANDOM    // 根据密度，沿模型/在模型内随机散射排列
        };

        // 对齐方式，与osgText::Text::AlignmentType类似
        enum Alignment 
		{
            ALIGN_LEFT_TOP,
            ALIGN_LEFT_CENTER,
            ALIGN_LEFT_BOTTOM,

            ALIGN_CENTER_TOP,
            ALIGN_CENTER_CENTER,
            ALIGN_CENTER_BOTTOM,

            ALIGN_RIGHT_TOP,
            ALIGN_RIGHT_CENTER,
            ALIGN_RIGHT_BOTTOM,
        };

    public:
        META_Symbol(MarkerSymbol);

        MarkerSymbol( const CVBF_Config& conf =CVBF_Config() );

        /** Since MarkerSymbol is deprecated, this conveneince function will convert to an InstanceSymbol */
        class InstanceSymbol* convertToInstanceSymbol() const;

        virtual ~MarkerSymbol();

		// 替代物模型的URI
        CVBF_Optional<StringExpression>& url() { return _url; }
        const CVBF_Optional<StringExpression>& url() const { return _url; }     

        /** Name of the resource library to use with this symbol (optional) */
        CVBF_Optional<StringExpression>& libraryName() { return _libraryName; }
        const CVBF_Optional<StringExpression>& libraryName() const { return _libraryName; }   

        /** How to map feature geometry to model placement. (default is PLACEMENT_CENTROID) */
        CVBF_Optional<Placement>& placement() { return _placement; }
        const CVBF_Optional<Placement>& placement() const { return _placement; }

        /** For PLACEMENT_RANDOM/INTERVAL, the scattering density in instances per sqkm */
        CVBF_Optional<float>& density() { return _density; }
        const CVBF_Optional<float>& density() const { return _density; }

        /** Model instance scale factor */
        CVBF_Optional<NumericExpression>& scale() { return _scale; }
        const CVBF_Optional<NumericExpression>& scale() const { return _scale; }

        /** Orientation in HPR degrees */
        CVBF_Optional<osg::Vec3f>& orientation() { return _orientation; }
        const CVBF_Optional<osg::Vec3f>& orientation() const { return _orientation; }

        /** Seeding value for the randomizer */
        CVBF_Optional<unsigned>& randomSeed() { return _randomSeed; }
        const CVBF_Optional<unsigned>& randomSeed() const { return _randomSeed; }

        /** Hint as to whether the marker is an icon vs. a 3D model */
        CVBF_Optional<bool>& isModel() { return _isModelHint; }
        const CVBF_Optional<bool>& isModel() const { return _isModelHint; }

        /** Alignment of the marker relative to center pixels */
        CVBF_Optional<Alignment>& alignment() { return _alignment; }
        const CVBF_Optional<Alignment>& alignment() const { return _alignment; }
        
    public: // non-serialized properties (for programmatic use only)

        /** Explicit image to use for 2D icon placemet */
        void setImage( osg::Image* image ) { _image = image; }
        osg::Image* getImage( unsigned maxSize =INT_MAX ) const;

        /** Explicit model to use for model placement */
        void setModel( osg::IVBF_SGNode* node ) { _node = node; }
        osg::IVBF_SGNode* getModel() const { return _node.get(); }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<StringExpression>   _url;
        CVBF_Optional<StringExpression>   _libraryName;
        CVBF_Optional<NumericExpression>  _scale;
        CVBF_Optional<Placement>          _placement;
        CVBF_Optional<osg::Vec3f>         _orientation;
        CVBF_Optional<float>              _density;
        CVBF_Optional<unsigned>           _randomSeed;
        CVBF_Optional<bool>               _isModelHint;
        CVBF_Optional<Alignment>         _alignment;

        ref_ptr<osg::IVBF_SGNode>      _node;
        mutable ref_ptr<osg::Image> _image;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MARKER_SYMBOL_H
