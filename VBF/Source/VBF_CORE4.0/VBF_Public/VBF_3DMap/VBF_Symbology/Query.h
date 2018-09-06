#ifndef OSGEARTHSYMBOLOGY_QUERY_H
#define OSGEARTHSYMBOLOGY_QUERY_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>

namespace osgEarth { namespace Symbology
{
    // ���ݲ�ѯ������
    class OSGEARTHSYMBOLOGY_EXPORT Query
    {
    public:
        Query( const CVBF_Config& conf =CVBF_Config() );

        virtual ~Query();
        Query& operator = (const Query& rhs);

    public: // properties

         // ��ѯ�Ŀռ䷶Χ
        CVBF_Optional<Bounds>& bounds() { return _bounds; }
        const CVBF_Optional<Bounds>& bounds() const { return _bounds; }

        // ��ѯ�ı��ʽ
        CVBF_Optional<std::string>& expression() { return _expression; }
        const CVBF_Optional<std::string>& expression() const { return _expression; }

        // ��ѯ����ı��ʽ
        CVBF_Optional<std::string>& orderby() { return _orderby; }
        const CVBF_Optional<std::string>& orderby() const { return _orderby; }

        /** Sets a driver-specific query expression. */
        CVBF_Optional<CVBF_TileKey>& tileKey() { return _tileKey; }
        const CVBF_Optional<CVBF_TileKey>& tileKey() const { return _tileKey; }
        
        // ����һ��Query�ϲ�
        Query combineWith( const Query& other ) const;

    public:
        virtual CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    protected:
        CVBF_Optional<Bounds> _bounds;
        CVBF_Optional<std::string> _expression;
        CVBF_Optional<std::string> _orderby;
        CVBF_Optional<CVBF_TileKey> _tileKey;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_QUERY_H
