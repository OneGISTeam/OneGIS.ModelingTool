#ifndef OSGEARTHSYMBOLOGY_GEOS_H
#define OSGEARTHSYMBOLOGY_GEOS_H 1

#include <VBF_3DMap/VBF_Features/Common>

#ifdef OSGEARTH_HAVE_GEOS

#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <geos/geom/Geometry.h>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    class GEOSUtils
    {
    public:
        static Symbology::Geometry*  exportGeometry( const geos::geom::Geometry* input );
        static geos::geom::Geometry* importGeometry( const Symbology::Geometry* input );
    };

} } // namespace osgEarth::Features

#endif // OSGEARTH_HAVE_GEOS

#endif // OSGEARTHSYMBOLOGY_GEOS_H

