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

	// ��η��������û�ָ��һϵ�еĵ㣬����������Щ�㶨����߶γ���
    class OSGPARTICLE_EXPORT MultiSegmentPlacer: public Placer 
	{
    public:
        MultiSegmentPlacer();
        MultiSegmentPlacer(const MultiSegmentPlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, MultiSegmentPlacer);

        // ��ȡ�����߶εĶ��������
        inline int numVertices() const;
        
        // ���/����һ������
        inline const osg::Vec3& getVertex(int i) const;
        inline void setVertex(int i, const osg::Vec3& v);
        inline void setVertex(int i, float x, float y, float z);
        
        // ���/�Ƴ�һ���ڵ�
        inline void addVertex(const osg::Vec3& v);
        inline void addVertex(float x, float y, float z);
        inline void removeVertex(int i);
        

        void place(Particle* P) const;// ����һ�����ӣ��ú�����Emitter�Զ����ã����ܱ��ֹ�����
        inline float volume() const;// ���ض��߶εĳ���
        inline osg::Vec3 getControlPosition() const;// ���ؿ��Ƶ�

    protected:
        virtual ~MultiSegmentPlacer() {}
        MultiSegmentPlacer& operator=(const MultiSegmentPlacer&) { return *this; }        

    private:
        typedef std::pair<osg::Vec3, float> Vertex_data;// ���㡢���õ���ܳ�
        typedef std::vector<Vertex_data> Vertex_vector;
        
        Vertex_vector _vx;    // �߶ε���������
        float _total_length;  // �ܳ���
        
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
