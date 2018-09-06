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

#ifndef OSGEARTHFEATURES_RESAMPLE_FILTER_H
#define OSGEARTHFEATURES_RESAMPLE_FILTER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;


    // 重采样，限制每个线段采样后的最大、最小长度，避免线上点太密或太稀
    class OSGEARTHFEATURES_EXPORT ResampleFilter : public FeatureFilter
    {
    public:
        static bool isSupported();    
    public:
        ResampleFilter();
        ResampleFilter( double minLength, double maxLength );
        ResampleFilter( const CVBF_Config& conf );
        virtual ~ResampleFilter() { }

        virtual CVBF_Config getConfig() const;

    public:
        CVBF_Optional<double>& minLength() { return _minLen; }
        const CVBF_Optional<double>& minLength() const { return _minLen; }

        CVBF_Optional<double>& maxLength() { return _maxLen; }
        const CVBF_Optional<double>& maxLength() const { return _maxLen; }

        CVBF_Optional<double>& perturbationThreshold() { return _perturbThresh; }
        const CVBF_Optional<double>& perturbationThreshold() const { return _perturbThresh; }

        enum ResampleMode
        {
            RESAMPLE_LINEAR,
            RESAMPLE_GREATCIRCLE,
            RESAMPLE_RHUMB
        };

        CVBF_Optional<ResampleMode>& resampleMode() { return _resampleMode;}
        const CVBF_Optional<ResampleMode>& resampleMode() const { return _resampleMode;}

    public:
        virtual FilterContext push( FeatureList& input, FilterContext& context );

    protected:
        CVBF_Optional<double> _minLen, _maxLen, _perturbThresh;
        CVBF_Optional<ResampleMode> _resampleMode;

        bool push( Feature* input, FilterContext& context );
    };

} }

#endif
