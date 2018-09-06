#ifndef OSGPARTICLE_POINT_PLACER
#define OSGPARTICLE_POINT_PLACER 1

#include <VBF_Engine/VBF_Particle/VBF_PSPlacerCentered.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

namespace osgParticle
{
	// 点放置器：所有的粒子从同一点出生
    class PointPlacer: public CenteredPlacer 
	{
    public:
        PointPlacer(): CenteredPlacer() {}
        PointPlacer(const PointPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY): CenteredPlacer(copy, copyop) {}

        META_Object(osgParticle, PointPlacer);
        
  		// 放置一个粒子，该函数有Emitter自动调用，不能被手工调用
        void place(Particle* P) const
        {
            P->setPosition(getCenter());
        }

        // 返回控制点
        osg::Vec3 getControlPosition() const { return getCenter(); }

    protected:
        virtual ~PointPlacer() {}
        PointPlacer& operator=(const PointPlacer&) { return *this; }        
    };


}


#endif
