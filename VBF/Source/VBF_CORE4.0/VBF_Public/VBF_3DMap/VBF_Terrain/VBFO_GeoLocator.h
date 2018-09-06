//**********************************************************************************
// 文件名：  VBFO_GeoLocator.h
// 描述：    
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBFO_GEO_LOCATOR_H__
#define __VBFO_GEO_LOCATOR_H__

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_Engine/VBF_Terrain/Locator>
#include <VBF_3DMap/VBF_Terrain/VBF_MapInfo.h>

using namespace osgEarth;

/**
    * Locator that stores the extent of its source data (which might be different
    * than the extent of the locator's transform). This locator can also automatically
    * crop out a section of the source image.
    */
class OSGEARTH_EXPORT CVBFO_GeoLocator : public osgTerrain::Locator
{
public:
    CVBFO_GeoLocator();
    CVBFO_GeoLocator( const CVBF_GeoExtent& dataExtent );
    CVBFO_GeoLocator( const osgTerrain::Locator& prototype, const CVBF_GeoExtent& dataExtent );


    CVBFO_GeoLocator( const osgTerrain::Locator& prototype, const CVBF_GeoExtent& dataExtent, const CVBF_GeoExtent& displayExtent );
    virtual ~CVBFO_GeoLocator() { }

    static CVBFO_GeoLocator* createForKey(const class CVBF_TileKey& key, const class CVBF_MapInfo& mapInfo);
    static CVBFO_GeoLocator* createForExtent(const CVBF_GeoExtent& extent, const class CVBF_MapInfo& mapInfo);

    void setDataExtent( const CVBF_GeoExtent& extent );
    const CVBF_GeoExtent& getDataExtent() const;

    virtual CVBFO_GeoLocator* getGeographicFromGeocentric() const;

    virtual bool isEquivalentTo( const CVBFO_GeoLocator& rhs ) const;

    // generates linear (evenly-spaced) coordinates
    virtual bool isLinear() const { return true; }

public: // better-sounding functions.

    bool modelToUnit(const osg::Vec3d& model, osg::Vec3d& unit) const 
	{
        return convertModelToLocal(model, unit);
    }
        
    bool unitToModel(const osg::Vec3d& unit, osg::Vec3d& model) const 
	{
        return convertLocalToModel(unit, model);
    }
        
public: // Locator
    virtual bool convertModelToLocal(const osg::Vec3d& world, osg::Vec3d& local) const;

protected:
    void cropLocal( osg::Vec3d& local ) const;

    bool _inverseCalculated;

private:
    CVBF_GeoExtent	_dataExtent;
    double		_x0, _y0, _x1, _y1;
};

    
/**
    * A terrain locator that generates texture coordinates that warp a Mercator image.
    *
    * Note: the CVBFO_GeoLocatorMercator doesn't have a "cropping" variation b/c it automatically
    * self-crops as necessary.
    */
class OSGEARTH_EXPORT CVBFO_GeoLocatorMercator : public CVBFO_GeoLocator
{
public:
    CVBFO_GeoLocatorMercator(const CVBF_GeoExtent& dataExtent );
    CVBFO_GeoLocatorMercator(const osgTerrain::Locator& prototype, const CVBF_GeoExtent& dataExtent );

    //virtual bool convertLocalToModel(const osg::Vec3d& local, osg::Vec3d& model) const;
    virtual bool convertModelToLocal(const osg::Vec3d& world, osg::Vec3d& local) const;
        
    /** Clones the current locator, applying a new display (i.e. crop) extent. */
    //virtual CVBFO_GeoLocator* cloneAndCrop( const osgTerrain::Locator& prototype, const CVBF_GeoExtent& displayExtent );

    virtual CVBFO_GeoLocator* getGeographicFromGeocentric() const;

    // does NOT generate linear coordinates
    virtual bool isLinear() const { return false; }

private:
    void postInit();

private:
    CVBF_GeoExtent	_geoDataExtent;
};


#endif 
