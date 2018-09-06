
#ifndef OSGEARTH_UTIL_LATLONG_FORMATTER_H
#define OSGEARTH_UTIL_LATLONG_FORMATTER_H

#include <VBF_3DMap/VBF_EarthUtil/VBF_Formatter.h>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

    // ��ʽ���������꣨��γ�ȣ�
    class OSGEARTHUTIL_EXPORT LatLongFormatter : public Formatter
    {
    public:
        enum AngularFormat // ��ʽ
		{
            FORMAT_DEFAULT,
            FORMAT_DECIMAL_DEGREES,         // �ȣ���С����
            FORMAT_DEGREES_DECIMAL_MINUTES, // �ȡ��֣���С����
            FORMAT_DEGREES_MINUTES_SECONDS  // �ȡ��֡���
        };

        // ��ʽѡ��
        enum Options
        {
            USE_SYMBOLS     = 1 << 0,   // �Ƿ�ʹ�÷���
            USE_COLONS      = 1 << 1,   // �Ƿ���ð�ŷָ�
            USE_SPACES      = 1 << 2    // �Ƿ��ÿո�ָ�
        };

    public:
        LatLongFormatter( const AngularFormat& defaultFormat =FORMAT_DECIMAL_DEGREES, unsigned optionsMask=0u );
        virtual ~LatLongFormatter() { }

        // ����ʮ�������ľ��ȣ�Ĭ����5��
        void setPrecision( int value ) { _prec = value; }

        // ���ø�ʽѡ��
        void setOptions( const Options& options ) { _options = options; }

        // ��ʽ��һ���Ƕ�
        std::string format( const Angular& angle, int precision =-1,
            const AngularFormat& outputFormat =FORMAT_DEFAULT) const;

        // ����һ����ʽ�����ַ�����ת��Ϊ�Ƕ�
        bool parseAngle( const std::string& input, Angular& out_value );

    public: // Formatter
        virtual std::string format( const GeoPoint& p ) const;

    protected:
        unsigned      _options;
        AngularFormat _defaultFormat;
        int           _prec;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTH_UTIL_LATLONG_FORMATTER_H
