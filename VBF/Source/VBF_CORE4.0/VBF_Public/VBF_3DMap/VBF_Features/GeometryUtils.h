#ifndef OSGEARTHFEATURES_FEATURE_GEOMETRYUTILS
#define OSGEARTHFEATURES_FEATURE_GEOMETRYUTILS 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>


namespace osgEarth { namespace Features
{
    using namespace osgEarth::Symbology;

    namespace GeometryUtils
    {
        extern OSGEARTHFEATURES_EXPORT std::string geometryToWKT( Geometry* geometry );
        extern OSGEARTHFEATURES_EXPORT Geometry*   geometryFromWKT( const std::string& wkt );

        extern OSGEARTHFEATURES_EXPORT std::string geometryToGeoJSON( Geometry* geometry );
        extern OSGEARTHFEATURES_EXPORT std::string geometryToKML( Geometry* geometry );
        extern OSGEARTHFEATURES_EXPORT std::string geometryToGML( Geometry* geometry );
        extern OSGEARTHFEATURES_EXPORT double getGeometryArea( Geometry* geometry );
    }

} } // namespace osgEarth::Features

#endif

