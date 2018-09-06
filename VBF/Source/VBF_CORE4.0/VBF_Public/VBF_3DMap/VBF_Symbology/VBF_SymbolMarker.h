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

    // MarkerSymbol��"markers"��������壬marker����һ��������3Dģ�ͻ�ͼ��
    class OSGEARTHSYMBOLOGY_EXPORT MarkerSymbol : public Symbol
    {
    public:
		// ģ�͵Ķ�λλ��
        enum Placement
        {
            PLACEMENT_CENTROID, // ����������
            PLACEMENT_VERTEX,   // ����ÿһ������
            PLACEMENT_INTERVAL, // ��ģ��ʵ��������ļ���ؼ����壨�ߣ����û����ڲ��������У�������ܶ����
            PLACEMENT_RANDOM    // �����ܶȣ���ģ��/��ģ�������ɢ������
        };

        // ���뷽ʽ����osgText::Text::AlignmentType����
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

		// �����ģ�͵�URI
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
