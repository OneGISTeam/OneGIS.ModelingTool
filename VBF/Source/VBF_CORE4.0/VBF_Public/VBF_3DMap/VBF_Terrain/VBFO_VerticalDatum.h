#ifndef OSGEARTH_VERTICAL_DATUM_H
#define OSGEARTH_VERTICAL_DATUM_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/Geoid.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_Shape.h>

namespace osgEarth
{
    class OSGEARTH_EXPORT CVBF_GeoExtent;
}

using namespace osgEarth;

/** 
    * Reference information for vertical (height) information.
    */
class OSGEARTH_EXPORT CVBFO_VerticalDatum : public osg::CVBF_Object
{
public:
    META_Object(osgEarth, CVBFO_VerticalDatum);

    /**
        * Creates an vertical datum from an initialization string. This method
        * uses an internal cache so that there is only ever one instance or each
        * unique vertical datum.
        */
    static CVBFO_VerticalDatum* get( const std::string& init );


public: // static transform methods

    /**
        * Transforms a Z coordinate from one vertical datum to another.
        */
    static bool transform(
        const CVBFO_VerticalDatum* from,
        const CVBFO_VerticalDatum* to,
        double               lat_deg,
        double               lon_deg,
        double&              in_out_z );

    /**
        * Transforms a Z coordinate from one vertical datum to another.
        */
    static bool transform(
        const CVBFO_VerticalDatum* from,
        const CVBFO_VerticalDatum* to,
        double               lat_deg,
        double               lon_deg,
        float&               in_out_z );

    /**
        * Transforms the values in a height field from one vertical datum to another.
        */
    static bool transform( const CVBFO_VerticalDatum* from, const CVBFO_VerticalDatum* to, const CVBF_GeoExtent& extent, osg::HeightField* hf );


public: // raw transformations

    /**
        * Converts an MSL value (height relative to a mean sea level model) to the
        * corresponding HAE value (height above the model's reference ellipsoid)
        */
	// 海拔高转大地高？
    double msl2hae( double lat_deg, double lon_deg, double msl ) const;

    /**
        * Converts an HAE value (height above the model's reference ellipsoid) to the
        * corresponding MSL value (height relative to a mean sea level model)
        */
    double hae2msl( double lat_deg, double lon_deg, double hae ) const;


public: // properties

    /** Gets the readable name of this SRS. */
    const std::string& getName() const { return m_sName; }

    /** Gets the linear units of height values */
    const CVBF_Units& getUnits() const { return _units; }

    /** Gets the string that was used to initialize this SRS */
    const std::string& getInitString() const { return _initString; }

    /** Gets the underlying geoid */
    const Geoid* getGeoid() const { return _geoid.get(); }

    /** Tests this SRS for equivalence with another. */
    virtual bool isEquivalentTo( const CVBFO_VerticalDatum* rhs ) const;
        
public:

    /** Creates a geoid-based VSRS. */
    CVBFO_VerticalDatum(
        const std::string& name,
        const std::string& initString,
        Geoid*             geoid =0L );

    /** Creates a simple ellipsoidal VSRS. */
    CVBFO_VerticalDatum( const CVBF_Units& units );

    /** dtor */
    virtual ~CVBFO_VerticalDatum() { }

protected:
    // required by META_Object, but not used.
    CVBFO_VerticalDatum() { }
    CVBFO_VerticalDatum(const CVBFO_VerticalDatum& rhs, const osg::CopyOp& op) { }

    std::string         m_sName;
    std::string         _initString;
    ref_ptr<Geoid> _geoid;
    CVBF_Units               _units;
};

//--------------------------------------------------------------------

/**
    * Creates a geoid instance based on an initialization string.
    */
class OSGEARTH_EXPORT VerticalDatumFactory
{   
public:
    static CVBFO_VerticalDatum* create( const std::string& id );
};


#endif // OSGEARTH_VERTICAL_DATUM_H
