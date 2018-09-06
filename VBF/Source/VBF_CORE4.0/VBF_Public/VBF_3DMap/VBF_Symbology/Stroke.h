#ifndef OSGEARTHSYMBOLOGY_STROKE_H
#define OSGEARTHSYMBOLOGY_STROKE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <Types/VBF_Color.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>


namespace osgEarth { namespace Symbology
{
	// ���ʲ����������ΪPen��
    class OSGEARTHSYMBOLOGY_EXPORT Stroke
    {
    public:

		// ����β�˵���ʽ
        enum LineCapStyle
        {
            LINECAP_FLAT,   /** no endcap. the line ends at the terminal point. */
            LINECAP_SQUARE, /** endcap extends width()/2 past the terminal point and is squared off. */
            LINECAP_ROUND   /** endcap extends width()/2 past the terminal point and is rounded off. */
        };

		// �߶�֮�����ӵ���ʽ
        enum LineJoinStyle
        {
            LINEJOIN_MITRE, /** outside joins form a sharp point. */
            LINEJOIN_ROUND  /** outside joins form an arc. */
        };

    public:
        Stroke();
        Stroke(float r, float g, float b, float a );
        Stroke(const VBFCOLOR& color );
        Stroke(const CVBF_Config& conf );
        Stroke(const Stroke& rhs);

        virtual ~Stroke();

        // ��ɫ
        VBFCOLOR& color() { return _color; }
        const VBFCOLOR& color() const { return _color; }

    	// ����β�˵���ʽ
        CVBF_Optional<LineCapStyle>& lineCap() { return _lineCap; }
        const CVBF_Optional<LineCapStyle>& lineCap() const { return _lineCap; }

        // �߶�֮�����ӵ���ʽ
        CVBF_Optional<LineJoinStyle>& lineJoin() { return _lineJoin; }
        const CVBF_Optional<LineJoinStyle>& lineJoin() const { return _lineJoin; }

		// �ߵĿ��
        CVBF_Optional<float>& width() { return _width; }
        const CVBF_Optional<float>& width() const { return _width; }

		// �߿�ĵ�λ��Ĭ��Ϊ����CVBF_Units::PIXELS
        CVBF_Optional<CVBF_Units>& widthUnits() { return _widthUnits; }
        const CVBF_Optional<CVBF_Units>& widthUnits() const { return _widthUnits; }

		// ��С���߿���λ���أ���Ĭ��ֵΪ0.0����û����Сֵ����Ҫ��Ϊ�˱�֤��ʼ�տɼ�
        CVBF_Optional<float>& minPixels() { return _minPixels; }
        const CVBF_Optional<float>& minPixels() const { return _minPixels; }

		// �㻮��ʽ����ʵ�ߣ�
        CVBF_Optional<unsigned short>& stipple() { return _stipple;}
        const CVBF_Optional<unsigned short>& stipple() const { return _stipple; }

        CVBF_Optional<unsigned int>& factor() { return _factor;}
        const CVBF_Optional<unsigned int>& factor() const { return _factor; }

        /** Rounding ratio - when rounding corners/caps, this is the ratio
            of rounded-segment length to width(). The smaller this value,
            the more detailed the rounding will be. (Default is 0.4) */
        CVBF_Optional<float>& roundingRatio() { return _roundingRatio; }
        const CVBF_Optional<float>& roundingRatio() const { return _roundingRatio; }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );

    protected:
        VBFCOLOR                    _color;
        CVBF_Optional<LineCapStyle>   _lineCap;
        CVBF_Optional<LineJoinStyle>  _lineJoin;
        CVBF_Optional<float>          _width;
        CVBF_Optional<CVBF_Units>     _widthUnits;
        CVBF_Optional<unsigned short> _stipple;
        CVBF_Optional<float>          _roundingRatio;
        CVBF_Optional<float>          _minPixels;
        CVBF_Optional<unsigned int>   _factor;

        void init();
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_STROKE_H
