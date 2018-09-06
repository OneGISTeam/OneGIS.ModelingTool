#ifndef OSGPARTICLE_BOX_PLACER
#define OSGPARTICLE_BOX_PLACER 1

#include <VBF_Engine/VBF_Particle/VBF_PSPlacerCentered.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>
#include <VBF_Engine/VBF_Particle/range>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>
#include <VBF_Common/VBF_Math/VBF_Math.h>

namespace osgParticle
{
    // 一个box形状的放置器，该放射器把粒子的初始位置随机放置在一个盒子的立体空间范围内
    class BoxPlacer: public CenteredPlacer
    {
    public:
        inline BoxPlacer();
        inline BoxPlacer(const BoxPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        // 设置/获取沿X轴的可能范围
        inline const rangef& getXRange() const;
        inline void setXRange(const rangef& r);
        inline void setXRange(float r1, float r2);
        
        // 设置/获取沿Y轴的可能范围
        inline const rangef& getYRange() const;        
        inline void setYRange(const rangef& r);
        inline void setYRange(float r1, float r2);    

        // 设置/获取沿Z轴的可能范围
        inline const rangef& getZRange() const;   
        inline void setZRange(const rangef& r);
        inline void setZRange(float r1, float r2);  

        META_Object(osgParticle, BoxPlacer);
        

        inline void place(Particle* P) const;
        inline float volume() const;
        inline osg::Vec3 getControlPosition() const;

    protected:
        virtual ~BoxPlacer() {}
        BoxPlacer& operator=(const BoxPlacer&) { return *this; }        
        
    private:
        rangef _x_range;
        rangef _y_range;
        rangef _z_range;
    };

    
    inline BoxPlacer::BoxPlacer()
    : CenteredPlacer(), _x_range(-1, 1), _y_range(-1, 1), _z_range(-1, 1)
    {
    }
    
    inline BoxPlacer::BoxPlacer(const BoxPlacer& copy, const osg::CopyOp& copyop)
    : CenteredPlacer(copy, copyop), 
    _x_range(copy._x_range), _y_range(copy._y_range), _z_range(copy._z_range)
    {
    }
    
    inline const rangef& BoxPlacer::getXRange() const
    {
        return _x_range;
    }

    inline void BoxPlacer::setXRange(const rangef& r)
    {
        _x_range = r;
    }
    
    inline void BoxPlacer::setXRange(float r1, float r2)
    {
        _x_range.minimum = r1;
        _x_range.maximum = r2;
    }

    inline const rangef& BoxPlacer::getYRange() const
    {
        return _y_range;
    }
    
    inline void BoxPlacer::setYRange(const rangef& r)
    {
        _y_range = r;
    }
    
    inline void BoxPlacer::setYRange(float r1, float r2)
    {
        _y_range.minimum = r1;
        _y_range.maximum = r2;
    }

    inline const rangef& BoxPlacer::getZRange() const
    {
        return _z_range;
    }

    inline void BoxPlacer::setZRange(const rangef& r)
    {
        _z_range = r;
    }
    
    inline void BoxPlacer::setZRange(float r1, float r2)
    {
        _z_range.minimum = r1;
        _z_range.maximum = r2;
    }

    inline void BoxPlacer::place(Particle* P) const
    {
        const osg::Vec3& vCenter = getCenter();
        osg::Vec3 pos(  vCenter.x() + _x_range.get_random(),
                        vCenter.y() + _y_range.get_random(),
                        vCenter.z() + _z_range.get_random() );
        
        P->setPosition(pos);
    }
    
    inline float BoxPlacer::volume() const
    {
        return (_x_range.maximum - _x_range.minimum) *
               (_y_range.maximum - _y_range.minimum) *
               (_z_range.maximum - _z_range.minimum);
    }

    inline osg::Vec3 BoxPlacer::getControlPosition() const
    {
        return getCenter();
    }

}

#endif
