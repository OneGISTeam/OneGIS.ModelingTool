#ifndef OSGPARTICLE_RADIAL_SHOOTER
#define OSGPARTICLE_RADIAL_SHOOTER 1

#include <VBF_Engine/VBF_Particle/VBF_PSShooter.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>
#include <VBF_Engine/VBF_Particle/range>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Common/VBF_Math/VBF_Math.h>

namespace osgParticle
{
	// 放射状发射器：允许用户指定一个速率范围（米/秒）以及弧度值表示的方向，方向由两个角度指定
	// （theta角是与Z轴的夹角，phi角是与XY平面的夹角）
    class RadialShooter: public Shooter
    {
    public:
        inline RadialShooter();
        inline RadialShooter(const RadialShooter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, RadialShooter);

        // 设置/获取theta角的范围
        inline const rangef& getThetaRange() const;
        inline void setThetaRange(const rangef& r);
        inline void setThetaRange(float r1, float r2);
        
        // 设置/获取phi角的范围
        inline const rangef& getPhiRange() const;
        inline void setPhiRange(const rangef& r);
        inline void setPhiRange(float r1, float r2);
        
		// 设置/获取初速度值的范围
        inline const rangef& getInitialSpeedRange() const;        
        inline void setInitialSpeedRange(const rangef& r);
        inline void setInitialSpeedRange(float r1, float r2);

        // 设置/获取初始的回转速度（角速度）的范围
        inline const rangev3& getInitialRotationalSpeedRange() const;        
        inline void setInitialRotationalSpeedRange(const rangev3& r);
        inline void setInitialRotationalSpeedRange(const osg::Vec3& r1, const osg::Vec3& r2);

        // 发射一个粒子
        inline void shoot(Particle* P) const;

    protected:
        virtual ~RadialShooter() {}
        RadialShooter& operator=(const RadialShooter&) { return *this; }

    private:
        rangef _theta_range;
        rangef _phi_range;
        rangef _speed_range;
        rangev3 _rot_speed_range;
    };

    // INLINE FUNCTIONS

    inline RadialShooter::RadialShooter()
    :    Shooter(), 
        _theta_range(0, 0.5f*osg::PI_4), 
        _phi_range(0, 2*osg::PI), 
        _speed_range(10, 10),
        _rot_speed_range(osg::Vec3(0,0,0), osg::Vec3(0,0,0))
    {
    }

    inline RadialShooter::RadialShooter(const RadialShooter& copy, const osg::CopyOp& copyop)
    :    Shooter(copy, copyop), 
        _theta_range(copy._theta_range), 
        _phi_range(copy._phi_range), 
        _speed_range(copy._speed_range),
        _rot_speed_range(copy._rot_speed_range)
    {
    }
    
    inline const rangef& RadialShooter::getThetaRange() const
    {
        return _theta_range;
    }

    inline const rangef& RadialShooter::getPhiRange() const
    {
        return _phi_range;
    }

    inline const rangef& RadialShooter::getInitialSpeedRange() const
    {
        return _speed_range;
    }

    inline const rangev3& RadialShooter::getInitialRotationalSpeedRange() const
    {
        return _rot_speed_range;
    }

    inline void RadialShooter::setThetaRange(const rangef& r)
    {
        _theta_range = r;
    }

    inline void RadialShooter::setThetaRange(float r1, float r2)
    {
        _theta_range.minimum = r1;
        _theta_range.maximum = r2;
    }

    inline void RadialShooter::setPhiRange(const rangef& r)
    {
        _phi_range = r;
    }

    inline void RadialShooter::setPhiRange(float r1, float r2)
    {
        _phi_range.minimum = r1;
        _phi_range.maximum = r2;
    }

    inline void RadialShooter::setInitialSpeedRange(const rangef& r)
    {
        _speed_range = r;
    }

    inline void RadialShooter::setInitialSpeedRange(float r1, float r2)
    {
        _speed_range.minimum = r1;
        _speed_range.maximum = r2;
    }

    inline void RadialShooter::setInitialRotationalSpeedRange(const rangev3& r)
    {
        _rot_speed_range = r;
    }

    inline void RadialShooter::setInitialRotationalSpeedRange(const osg::Vec3& r1, const osg::Vec3& r2)
    {
        _rot_speed_range.minimum = r1;
        _rot_speed_range.maximum = r2;
    }

    inline void RadialShooter::shoot(Particle* P) const
    {
        float theta = _theta_range.get_random();
        float phi = _phi_range.get_random();
        float fSpeed = _speed_range.get_random();
        osg::Vec3 rot_speed = _rot_speed_range.get_random();
        
        P->setVelocity(osg::Vec3( fSpeed * sinf(theta) * cosf(phi),
                                  fSpeed * sinf(theta) * sinf(phi),
                                  fSpeed * cosf(theta) ));
            
        P->setAngularVelocity(rot_speed);
    }

}


#endif
