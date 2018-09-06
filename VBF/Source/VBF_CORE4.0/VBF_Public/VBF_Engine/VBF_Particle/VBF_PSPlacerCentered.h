#ifndef OSGPARTICLE_CENTERED_PLACER
#define OSGPARTICLE_CENTERED_PLACER 1

#include <VBF_Engine/VBF_Particle/VBF_PSPlacer.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>

namespace osgParticle
{
	// 中心放置器：具有一个明确的中心位置的放置器的基类，子类包括点放置器和扇形放置器（球形放置器）
    class CenteredPlacer: public Placer 
	{
    public:
        inline CenteredPlacer();
        inline CenteredPlacer(const CenteredPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const   { return "CenteredPlacer"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Placer* >(obj) != 0; }        
    
        // 设置/获取中心点
        inline const osg::Vec3& getCenter() const;
        inline void setCenter(const osg::Vec3& v);
        inline void setCenter(float x, float y, float z);
        
    protected:
        virtual ~CenteredPlacer() {}
        
    private:
        osg::Vec3 m_vCenter;
    };
    

    inline CenteredPlacer::CenteredPlacer()
    : Placer(), m_vCenter(0, 0, 0)
    {
    }
    
    inline CenteredPlacer::CenteredPlacer(const CenteredPlacer& copy, const osg::CopyOp& copyop)
    : Placer(copy, copyop), m_vCenter(copy.m_vCenter)
    {
    }
    
    inline const osg::Vec3& CenteredPlacer::getCenter() const
    {
        return m_vCenter;
    }
    
    inline void CenteredPlacer::setCenter(const osg::Vec3& v)
    {
        m_vCenter = v;
    }
    
    inline void CenteredPlacer::setCenter(float x, float y, float z)
    {
        m_vCenter.set(x, y, z);
    }

}


#endif
