#ifndef OSGEARTH_ELEVATIONLOD_H
#define OSGEARTH_ELEVATIONLOD_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>


// 装饰节点，仅当相机位于给定的高度范围或实现距离时才显示其子节点
class OSGEARTH_EXPORT CVBFO_SGNodeLODElevation : public osg::CVBF_SGNodeGroup
{
public:
    META_Node(osgEarth, CVBFO_SGNodeLODElevation);

    CVBFO_SGNodeLODElevation();
    CVBFO_SGNodeLODElevation(const CVBFO_SGNodeLODElevation& rhs, const osg::CopyOp& op);
    CVBFO_SGNodeLODElevation(const CVBF_SpatialReference* srs);
    CVBFO_SGNodeLODElevation(const CVBF_SpatialReference* srs, double minElevation, double maxElevation);

    double getMinElevation() const;
    void setMinElevation( double minElevation );

    double getMaxElevation() const;
    void setMaxElevation(double maxElevation );

    void setElevations( double minElevation, double maxElevation );

    float getMinRange() const;
    void setMinRange(float minRange);

    float getMaxRange() const;
    void setMaxRange(float maxRange);

    void setRanges( float minRange, float maxRange );

    // 杜莹添加：2016-05-20
    bool IsMinElevationSet()    { return _minElevation.isSet(); }
    bool IsMaxElevationSet()    { return _maxElevation.isSet(); }
    bool IsMinRangeSet()        { return _minRange.isSet(); }
    bool IsMaxRangeSet()        { return _maxRange.isSet(); }

    const CVBF_SpatialReference* GetSRS() { return _srs.get(); }

public: // osg::Node

    virtual void traverse( osg::NodeVisitor& nv);

protected:

    virtual ~CVBFO_SGNodeLODElevation();

private:
    ref_ptr< const CVBF_SpatialReference > _srs;
    CVBF_Optional<double> _minElevation;
    CVBF_Optional<double> _maxElevation;
    CVBF_Optional<float>  _minRange;
    CVBF_Optional<float>  _maxRange;
};



#endif // OSGEARTH_ELEVATIONLOD_H
