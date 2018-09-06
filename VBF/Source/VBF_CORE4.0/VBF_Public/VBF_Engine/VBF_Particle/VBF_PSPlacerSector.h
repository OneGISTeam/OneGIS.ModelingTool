#ifndef OSGPARTICLE_SECTOR_PLACER
#define OSGPARTICLE_SECTOR_PLACER 1

#include <VBF_Engine/VBF_Particle/VBF_PSPlacerCentered.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>
#include <VBF_Engine/VBF_Particle/range>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>
#include <VBF_Common/VBF_Math/VBF_Math.h>

namespace osgParticle
{
	// 扇形放置器：所有的粒子同从一个指定中心点、半径范围和角度范围的扇面出生
    class SectorPlacer: public CenteredPlacer 
	{
    public:
        inline SectorPlacer();
        inline SectorPlacer(const SectorPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
		// 设置/获取半径范围
        inline const rangef& getRadiusRange() const;
        inline void setRadiusRange(const rangef& r);
        inline void setRadiusRange(float r1, float r2);
        
        // 设置/获取角度范围
        inline const rangef& getPhiRange() const;        
        inline void setPhiRange(const rangef& r);
        inline void setPhiRange(float r1, float r2);    

        META_Object(osgParticle, SectorPlacer);
        
        // 放置一个粒子，该函数有Emitter自动调用，不能被手工调用
        inline void place(Particle* P) const;

        // 返回扇面的面积
        inline float volume() const;
        
        // 返回控制点
        inline osg::Vec3 getControlPosition() const;

    protected:
        virtual ~SectorPlacer() {}
        SectorPlacer& operator=(const SectorPlacer&) { return *this; }        
        
    private:
        rangef _rad_range;  // 半径范围
        rangef _phi_range;  // 角度范围
    };

    // INLINE FUNCTIONS
    
    inline SectorPlacer::SectorPlacer()
    : CenteredPlacer(), _rad_range(0, 1), _phi_range(0, osg::PI*2)
    {
    }
    
    inline SectorPlacer::SectorPlacer(const SectorPlacer& copy, const osg::CopyOp& copyop)
    : CenteredPlacer(copy, copyop), _rad_range(copy._rad_range), _phi_range(copy._phi_range)
    {
    }
    
    inline const rangef& SectorPlacer::getRadiusRange() const
    {
        return _rad_range;
    }

    inline const rangef& SectorPlacer::getPhiRange() const
    {
        return _phi_range;
    }

    inline void SectorPlacer::setRadiusRange(const rangef& r)
    {
        _rad_range = r;
    }
    
    inline void SectorPlacer::setRadiusRange(float r1, float r2)
    {
        _rad_range.minimum = r1;
        _rad_range.maximum = r2;
    }
    
    inline void SectorPlacer::setPhiRange(const rangef& r)
    {
        _phi_range = r;
    }
    
    inline void SectorPlacer::setPhiRange(float r1, float r2)
    {
        _phi_range.minimum = r1;
        _phi_range.maximum = r2;
    }

    inline void SectorPlacer::place(Particle* P) const
    {
        float rad = _rad_range.get_random_sqrtf();
        float phi = _phi_range.get_random();
        
        osg::Vec3 pos(
            getCenter().x() + rad * cosf(phi), 
            getCenter().y() + rad * sinf(phi), 
            getCenter().z());
        
        P->setPosition(pos);
    }
    
    inline float SectorPlacer::volume() const
    {
        return 0.5f * (_phi_range.maximum - _phi_range.minimum) *
               (_rad_range.maximum*_rad_range.maximum - _rad_range.minimum*_rad_range.minimum);
    }

    inline osg::Vec3 SectorPlacer::getControlPosition() const
    {
        return getCenter();
    }

}

#endif
