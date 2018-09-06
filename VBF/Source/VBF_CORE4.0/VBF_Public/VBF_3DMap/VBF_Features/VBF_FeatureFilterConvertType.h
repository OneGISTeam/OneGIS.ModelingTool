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

#ifndef OSGEARTHFEATURES_CONVERT_TYPE_FILTER_H
#define OSGEARTHFEATURES_CONVERT_TYPE_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;

    // 把几何体从一种类型转换到另一种类型
    class OSGEARTHFEATURES_EXPORT ConvertTypeFilter : public FeatureFilter
    {
    public:
        static bool isSupported() { return true; }

    public:
        ConvertTypeFilter();
        ConvertTypeFilter( const Symbology::Geometry::Type& toType );
        ConvertTypeFilter( const ConvertTypeFilter& rhs );
        ConvertTypeFilter( const CVBF_Config& conf );

        virtual CVBF_Config getConfig() const;

        virtual ~ConvertTypeFilter() { }

    public:
        Symbology::Geometry::Type& toType() { return _toType; }
        const Symbology::Geometry::Type& toType() const { return _toType; }

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& context );

    protected:
        Symbology::Geometry::Type _toType;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_CONVERT_TYPE_FILTER_H
