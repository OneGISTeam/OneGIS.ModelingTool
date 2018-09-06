#ifndef OSGPARTICLE_SEGMENT_PLACER
#define OSGPARTICLE_SEGMENT_PLACER 1

#include <VBF_Engine/VBF_Particle/VBF_PSPlacer.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>

namespace osgParticle {

    // 线段放置器：用户指定两点形成线段，粒子沿着这条线段出生
    class SegmentPlacer: public Placer 
	{
    public:
        inline SegmentPlacer();
        inline SegmentPlacer(const SegmentPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, SegmentPlacer);

		// 获取/设置线段端点A
        inline const osg::Vec3& getVertexA() const;
        inline void setVertexA(const osg::Vec3& v);
        inline void setVertexA(float x, float y, float z);
        
        // 获取/设置线段端点B
        inline const osg::Vec3& getVertexB() const;
        inline void setVertexB(const osg::Vec3& v);
        inline void setVertexB(float x, float y, float z);
        
        // 设置线段的两个端点
        inline void setSegment(const osg::Vec3& A, const osg::Vec3& B);
        
        // 放置一个粒子，该函数有Emitter自动调用，不能被手工调用
        inline void place(Particle* P) const;

        // 返回线段的长度
        inline float volume() const;
        
        // 返回控制点
        inline osg::Vec3 getControlPosition() const;

    protected:
        virtual ~SegmentPlacer() {}
        SegmentPlacer& operator=(const SegmentPlacer&) { return *this; }        

    private:
        osg::Vec3 _vertexA;
        osg::Vec3 _vertexB;
    };

    // INLINE FUNCTIONS
    
    inline SegmentPlacer::SegmentPlacer()
    : Placer(), _vertexA(-1, 0, 0), _vertexB(1, 0, 0)
    {
    }
    
    inline SegmentPlacer::SegmentPlacer(const SegmentPlacer& copy, const osg::CopyOp& copyop)
    : Placer(copy, copyop), _vertexA(copy._vertexA), _vertexB(copy._vertexB)
    {
    }

    inline const osg::Vec3& SegmentPlacer::getVertexA() const
    {
        return _vertexA;
    }

    inline const osg::Vec3& SegmentPlacer::getVertexB() const
    {
        return _vertexB;
    }

    inline void SegmentPlacer::setSegment(const osg::Vec3& A, const osg::Vec3& B)
    {
        _vertexA = A;
        _vertexB = B;
    }

    inline void SegmentPlacer::place(Particle* P) const
    {
        P->setPosition(rangev3(_vertexA, _vertexB).get_random());
    }
    
    inline float SegmentPlacer::volume() const
    {
        return (_vertexB - _vertexA).length();
    }
    
    inline void SegmentPlacer::setVertexA(const osg::Vec3& v)
    {
        _vertexA = v;
    }
    
    inline void SegmentPlacer::setVertexA(float x, float y, float z)
    {
        _vertexA.set(x, y, z);
    }
    
    inline void SegmentPlacer::setVertexB(const osg::Vec3& v)
    {
        _vertexB = v;
    }

    inline void SegmentPlacer::setVertexB(float x, float y, float z)
    {
        _vertexB.set(x, y, z);
    }    
    
    inline osg::Vec3 SegmentPlacer::getControlPosition() const
    {
        return (_vertexA+_vertexB)*0.5f;
    }


}

#endif
