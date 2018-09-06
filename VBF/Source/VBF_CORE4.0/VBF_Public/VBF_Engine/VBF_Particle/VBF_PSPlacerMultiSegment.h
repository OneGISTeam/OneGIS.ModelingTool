#ifndef OSGPARTICLE_MULTISEGMENT_PLACER
#define OSGPARTICLE_MULTISEGMENT_PLACER 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/VBF_PSPlacer.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <vector>
#include <utility>

#include <VBF_Base/VBF_Notify.h>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>

namespace osgParticle {

	// 多段放置器：用户指定一系列的点，粒子沿着这些点定义的线段出生
    class OSGPARTICLE_EXPORT MultiSegmentPlacer: public Placer 
	{
    public:
        MultiSegmentPlacer();
        MultiSegmentPlacer(const MultiSegmentPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, MultiSegmentPlacer);

        // 获取定义线段的顶点的数量
        inline int numVertices() const;
        
        // 获得/设置一个顶点
        inline const osg::Vec3& getVertex(int i) const;
        inline void setVertex(int i, const osg::Vec3& v);
        inline void setVertex(int i, float x, float y, float z);
        
        // 添加/移除一个节点
        inline void addVertex(const osg::Vec3& v);
        inline void addVertex(float x, float y, float z);
        inline void removeVertex(int i);
        

        void place(Particle* P) const;// 放置一个粒子，该函数有Emitter自动调用，不能被手工调用
        inline float volume() const;// 返回多线段的长度
        inline osg::Vec3 getControlPosition() const;// 返回控制点

    protected:
        virtual ~MultiSegmentPlacer() {}
        MultiSegmentPlacer& operator=(const MultiSegmentPlacer&) { return *this; }        

    private:
        typedef std::pair<osg::Vec3, float> Vertex_data;// 顶点、到该点的总长
        typedef std::vector<Vertex_data> Vertex_vector;
        
        Vertex_vector _vx;    // 线段的坐标数据
        float _total_length;  // 总长度
        
        void recompute_length();
    };

    // INLINE FUNCTIONS
    

    inline int MultiSegmentPlacer::numVertices() const
    {
        return static_cast<int>(_vx.size());
    }

    inline const osg::Vec3& MultiSegmentPlacer::getVertex(int i) const
    {
        return _vx[i].first;
    }

    inline void MultiSegmentPlacer::setVertex(int i, const osg::Vec3& v)
    {
        _vx[i].first = v;
        recompute_length();
    }

    inline void MultiSegmentPlacer::setVertex(int i, float x, float y, float z)
    {
        _vx[i].first.set(x, y, z);
        recompute_length();
    }

    inline void MultiSegmentPlacer::addVertex(const osg::Vec3& v)
    {
        float l = 0;        
        if (_vx.size() > 0) 
		{
            l = (v - _vx.back().first).length();
        }                
        _total_length += l;
        _vx.push_back(std::make_pair(v, _total_length));        
    }

    inline void MultiSegmentPlacer::addVertex(float x, float y, float z)
    {
        addVertex(osg::Vec3(x, y, z));
    }

    inline void MultiSegmentPlacer::removeVertex(int i)
    {
        _vx.erase(_vx.begin()+i);
        recompute_length();
    }
    
    inline float MultiSegmentPlacer::volume() const
    {
        return _total_length;
    }
    
    inline osg::Vec3 MultiSegmentPlacer::getControlPosition() const
    {
        return _vx.empty() ? osg::Vec3(0.0f,0.0f,0.0f) : _vx[0].first;
    }

}
#endif
