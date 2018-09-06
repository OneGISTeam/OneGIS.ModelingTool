/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
* Copyright 2008-2013 Pelican Mapping
* http://osgearth.org
*
* osgEarth is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef OSGEARTHFEATURES_FEATURE_OGR_UTILS
#define OSGEARTHFEATURES_FEATURE_OGR_UTILS 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>
#include <VBF_Base/VBF_Notify.h>
#include <gdal/ogr_api.h>

using namespace osgEarth;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;

struct OSGEARTHFEATURES_EXPORT OgrUtils
{
    static void populate( OGRGeometryH geomHandle, Symbology::Geometry* target, int numPoints );
    
    static Symbology::Polygon* createPolygon( OGRGeometryH geomHandle );
       
    static Symbology::Geometry* createGeometry( OGRGeometryH geomHandle );

    static OGRGeometryH encodePart( osgEarth::Symbology::Geometry* geometry, OGRwkbGeometryType part_type );

    static OGRGeometryH encodeShape( osgEarth::Symbology::Geometry* geometry, OGRwkbGeometryType shape_type, OGRwkbGeometryType part_type );    

    static OGRGeometryH createOgrGeometry(osgEarth::Symbology::Geometry* geometry, OGRwkbGeometryType requestedType = wkbUnknown);
    
    static Feature* createFeature( OGRFeatureH handle, const CVBF_SpatialReference* srs );
    
    static AttributeType getAttributeType( OGRFieldType type );    
};


#endif // OSGEARTHFEATURES_FEATURE_OGR_GEOM_UTILS

