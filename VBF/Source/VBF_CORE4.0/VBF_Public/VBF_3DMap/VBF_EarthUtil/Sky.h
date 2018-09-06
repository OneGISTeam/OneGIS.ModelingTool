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

#ifndef OSGEARTHUTIL_SKY
#define OSGEARTHUTIL_SKY

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_EarthUtil/Ephemeris.h>
#include <VBF_Common/VBF_Utils/VBF_DateTime.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>

class CVBFO_SGNodeMap;

namespace osgEarth {
    class UpdateLightingUniformsHelper;
}
namespace osgDB {
    class Options;
}

namespace osgEarth { namespace Util 
{
    using namespace osgEarth;


    /**
     * Base Options structure for loading an environment node from
     * a plugin.
     */
    class SkyOptions : public CVBF_OptionsDriver // DriverConfigOptions
    {
    public:

        /** Time of day - Hours [0..24] component of DateTime */
        CVBF_Optional<float>& hours() { return _hours; }
        const CVBF_Optional<float>& hours() const { return _hours; }

        /** Ambient light level [0..1] */
        CVBF_Optional<float>& ambient() { return _ambient; }
        const CVBF_Optional<float>& ambient() const { return _ambient; }

    public:
        SkyOptions( const CVBF_Options& options =CVBF_Options() ) : CVBF_OptionsDriver(options) 
		{
            fromConfig(m_conf);
        }
        virtual ~SkyOptions() { }

        virtual CVBF_Config getConfig() const 
		{
            CVBF_Config conf = CVBF_OptionsDriver::getConfig();
            conf.addIfSet("hours", _hours);
            conf.addIfSet("ambient", _ambient);
            return conf;
        }

    protected:
        virtual void mergeConfig( const CVBF_Config& conf ) 
		{
            CVBF_OptionsDriver::mergeConfig( conf );
            fromConfig( conf );
        }
        
    private:
        void fromConfig( const CVBF_Config& conf ) 
		{
            conf.getIfSet("hours", _hours);
            conf.getIfSet("ambient", _ambient);
        }
        
        CVBF_Optional<float>	_hours;
        CVBF_Optional<float>	_ambient;
    };


    /**
    * Interface for classes that provide sky, lighting, and other 
    * environmental effect.
    */
    class OSGEARTHUTIL_EXPORT SkyNode : public CVBF_SGNodeGroup
    {
    public:
        /**
         * Creates a new SkyNode with the default built-in sky driver
         * and default options.
         */
        static SkyNode* create(CVBFO_SGNodeMap* mapNode);
        
        /**
         * Creates a new SkyNode with custom options.
         */
        static SkyNode* create(const SkyOptions& options, CVBFO_SGNodeMap* mapNode);
        
        /**
         * Creates a new SkyNode with a named driver.
         */
        static SkyNode* create(const std::string& driver, CVBFO_SGNodeMap* mapNode);

    protected:
        // CTOR (abstract base class)
        SkyNode();
        SkyNode(const SkyOptions& options);

        // protected DTOR (heap-only)
        virtual ~SkyNode();

    public:
        /**
         * Gets/Sets the Ephemeris used to position the sun and the moon
         * based on date/time.
         */
        void setEphemeris(Ephemeris* ephemeris);
        const Ephemeris* getEphemeris() const;

        /**
         * The ephemeris reference point for projected maps. Not applicable
         * for geocentric maps.
         */
        void setReferencePoint(const GeoPoint& point);
        const GeoPoint& getReferencePoint() const { return *_refpoint; }
       
        /**
         * Whether the sky lights its subgraph.
         */
        void setLighting(osg::StateAttribute::OverrideValue value);
        osg::StateAttribute::OverrideValue getLighting() const { return _lightingValue; }

        /**
         * Gets the date/time for which the enviroment is configured.
         * Pass in an optional View to get the date/time specific to
         * that View.
         */
        void setDateTime(const CVBF_DateTime& dt);
        const CVBF_DateTime& getDateTime() const { return _dateTime; }

        /** Whether the sun is visible */
        void setSunVisible(bool value);
        bool getSunVisible() const { return _sunVisible; }

        /** Whether the moon is visible */
        void setMoonVisible(bool value);
        bool getMoonVisible() const { return _moonVisible; }

        /** Whether the stars are visible */
        void setStarsVisible(bool value);
        bool getStarsVisible() const { return _starsVisible; }

        /** Access the osg::Light representing the sun */
        virtual osg::Light* getSunLight() = 0;

    public:
        
        /** Attaches this sky node to a view (placing a sky light). Optional */
        virtual void attach(IVBF_View* view, int lightNum) { }
        void attach(IVBF_View* view) { attach(view, 0); }

    public: // osg::Node

        virtual void traverse(osg::NodeVisitor&);

    protected:

        // impl class can override these events.
        virtual void onSetEphemeris() { }
        virtual void onSetDateTime() { }
        virtual void onSetReferencePoint() { }
        virtual void onSetMoonVisible() { }
        virtual void onSetStarsVisible() { }
        virtual void onSetSunVisible() { }

    private:
        ref_ptr<Ephemeris>			_ephemeris;
        CVBF_DateTime				_dateTime;
        bool						_sunVisible;
        bool						_moonVisible;
        bool						_starsVisible;
        CVBF_Optional<GeoPoint>     _refpoint;

        osg::StateAttribute::OverrideValue		_lightingValue;
        ref_ptr<osg::Uniform>					_lightingUniform;
        ref_ptr<UpdateLightingUniformsHelper>	_lightingUniformsHelper;

        void baseInit(const SkyOptions&);
    };


    /**
     * Base class for an sky driver plugin implementation.
     */
    class OSGEARTHUTIL_EXPORT SkyDriver : public osgDB::ReaderWriter
    {
    protected:
        CVBFO_SGNodeMap* getMapNode(const osgDB::Options* opt) const;
        const SkyOptions& getSkyOptions(const osgDB::Options* opt) const;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_SKY
