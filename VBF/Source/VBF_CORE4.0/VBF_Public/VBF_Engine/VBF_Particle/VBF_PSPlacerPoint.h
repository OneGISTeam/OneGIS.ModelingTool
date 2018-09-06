#ifndef OSGPARTICLE_POINT_PLACER
#define OSGPARTICLE_POINT_PLACER 1

#include <VBF_Engine/VBF_Particle/VBF_PSPlacerCentered.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

namespace osgParticle
{
	// ������������е����Ӵ�ͬһ�����
    class PointPlacer: public CenteredPlacer 
	{
    public:
        PointPlacer(): CenteredPlacer() {}
        PointPlacer(const PointPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY): CenteredPlacer(copy, copyop) {}

        META_Object(osgParticle, PointPlacer);
        
  		// ����һ�����ӣ��ú�����Emitter�Զ����ã����ܱ��ֹ�����
        void place(Particle* P) const
        {
            P->setPosition(getCenter());
        }

        // ���ؿ��Ƶ�
        osg::Vec3 getControlPosition() const { return getCenter(); }

    protected:
        virtual ~PointPlacer() {}
        PointPlacer& operator=(const PointPlacer&) { return *this; }        
    };


}


#endif
