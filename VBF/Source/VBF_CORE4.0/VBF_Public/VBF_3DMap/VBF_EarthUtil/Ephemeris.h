/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
* Copyright 2008-2014 Pelican Mapping
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

// ∂≈”®Ã·»°◊‘osgEarth-2.6

#ifndef OSGEARTHUTIL_EPHEMERIS
#define OSGEARTHUTIL_EPHEMERIS

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_Common/VBF_Utils/VBF_DateTime.h>
#include <Types/Vec3d>

namespace osgEarth { namespace Util 
{
    using namespace osgEarth;

    /**
     * An Ephemeris gives the positions of naturally occurring astronimical
     * objects; in that case, the sun and the moon. Also includes some
     * related utility functions.
     */
    class OSGEARTHUTIL_EXPORT Ephemeris : public CVBF_Referenced
    {
    public:
        /**
        * Gets the moon position in ECEF coordinates at the given time
        */
        virtual osg::Vec3d getMoonPositionECEF(const CVBF_DateTime& dt) const;

        /**
        * Gets the sun position in ECEF coordinates at the given time
        */
        virtual osg::Vec3d getSunPositionECEF(const CVBF_DateTime& dt) const;
        
        /**
         * Gets an ECEF position from the right ascension, declination and range
         *
         * @param ra    Right ascension in radians
         * @param decl  Declination in radians
         * @param range Range in meters
         */
        osg::Vec3d getECEFfromRADecl(double ra, double decl, double range) const;
    };
    
} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_EPHEMERIS
