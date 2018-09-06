//**********************************************************************************
// �ļ�����  VBF_SpatialReferenceLTP.h
// ������    �ռ�ο�ϵ���ֲ���ƽ��
// ����:     ��Ө
// ����:     2013-06-24
//**********************************************************************************

#ifndef __VBF_SPATIAL_REFERENCE_LTP_H__
#define __VBF_SPATIAL_REFERENCE_LTP_H__

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_GeoLocator.h>


// �ֲ���ƽ��SRS������CVBF_SpatialReference::createLTP()���й���
class CVBF_SpatialReferenceLTP : public CVBF_SpatialReference
{
public:
    CVBF_SpatialReferenceLTP(void* handle, const osg::Vec3d& originLLA);
    virtual ~CVBF_SpatialReferenceLTP() { }

    // CUBE is a projected coordinate system.
    virtual bool isGeographic() const { return false; }
    virtual bool isProjected() const { return true; }

    // This SRS uses a WGS84 lat/long SRS under the hood for reprojection. So we need the
    // pre/post transforms to move from LTP to Geodetic and back.
    virtual bool preTransform(double& x, double& y, double& z, void* context) const;
    virtual bool postTransform(double& x, double& y, double& z, void* context) const;

protected: // CVBF_SpatialReference overrides

    void _init();
        
    bool _isEquivalentTo( const CVBF_SpatialReference* srs ) const;

private:
    osg::Vec3d   _originLLA;
    osg::Matrixd _local2world, _world2local;
};


#endif 
