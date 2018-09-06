#ifndef OSGEARTH_GEOID_H
#define OSGEARTH_GEOID_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/Bounds.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_Shape.h>


namespace osgEarth
{
	// 水准面
    class OSGEARTH_EXPORT Geoid : public ::CVBF_Referenced
    {
    public:
        Geoid();
        virtual ~Geoid() { }

        // 设置/获取名称
        void setName( const std::string& value );
        const std::string& getName() const { return m_sName; }

		// 设置/获取高度场，必须是经纬度网格（带有用"度"表示的原点和间隔），高度值为相对于参考椭球面的
        void setHeightField( osg::HeightField* hf );
        const osg::HeightField* getHeightField() const { return _hf.get(); }

		// 获取给定点（地理坐标）的高程偏移
        float getHeight( double lat_deg, double lon_deg, const ElevationInterpolation& interp =INTERP_BILINEAR) const;

        const CVBF_Units& getUnits() const { return _units; } // 高程值的单位
        void setUnits( const CVBF_Units& value );

        bool isValid() const { return _valid; } // 是否有效

        bool isEquivalentTo( const Geoid& rhs ) const; // 判断两个Geoid是否相等

    private:
        std::string    m_sName;
        CVBF_Units     _units;
        bool           _valid;
        Bounds         _bounds;

        ref_ptr<osg::HeightField> _hf;

        void validate();
    };
}

#endif
