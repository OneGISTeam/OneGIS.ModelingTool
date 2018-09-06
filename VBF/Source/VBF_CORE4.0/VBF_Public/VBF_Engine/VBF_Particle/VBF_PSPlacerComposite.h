#ifndef OSGPARTICLE_COMPOSITEPLACER
#define OSGPARTICLE_COMPOSITEPLACER

#include <VBF_Engine/VBF_Particle/VBF_PSPlacer.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

namespace osgParticle
{

// 组合放置器	 
class CompositePlacer : public Placer
{
public:
    CompositePlacer() : Placer() {}
    
    CompositePlacer( const CompositePlacer& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY )
							: Placer(copy, copyop), _placers(copy._placers) {}
    
    META_Object( osgParticle, CompositePlacer );
    
    // 设置一个子放置器
    void setPlacer( unsigned int i, Placer* p )
    {
        if (i<_placers.size()) _placers[i] = p;
        else                   addPlacer(p);
    }
    
    // 添加/移除一个子放置器
    void addPlacer( Placer* p ) { _placers.push_back(p); }
    void removePlacer( unsigned int i ) { if (i<_placers.size()) _placers.erase(_placers.begin()+i); }
    
    // 获取一个子放置器
    Placer* getPlacer( unsigned int i ) { return _placers[i].get(); }
    const Placer* getPlacer( unsigned int i ) const { return _placers[i].get(); }
    unsigned int getNumPlacers() const { return _placers.size(); }// 获取子放置器的数量

    inline void place( Particle* P ) const;// 放置一个粒子，该函数有Emitter自动调用，不能被手工调用
    inline float volume() const;
    inline osg::Vec3 getControlPosition() const;// 返回线段的长度
    
protected:
    virtual ~CompositePlacer() {}
    CompositePlacer& operator=( const CompositePlacer& ) { return *this; }
    
    typedef std::vector< ref_ptr<Placer> > PlacerList;
    PlacerList _placers;
};

// INLINE METHODS

inline void CompositePlacer::place( Particle* P ) const
{
    rangef sizeRange( 0.0f, volume() );
    float current = 0.0f, selected = sizeRange.get_random();
    for ( PlacerList::const_iterator itr=_placers.begin(); itr!=_placers.end(); ++itr )
    {
        current += (*itr)->volume();
        if ( selected<=current ) (*itr)->place( P );
    }
}

inline float CompositePlacer::volume() const
{
    float total_size = 0.0f;
    for ( PlacerList::const_iterator itr=_placers.begin(); itr!=_placers.end(); ++itr )
        total_size += (*itr)->volume();
    return total_size;
}

inline osg::Vec3 CompositePlacer::getControlPosition() const
{
    if ( !_placers.size() ) return osg::Vec3();
    return _placers.front()->getControlPosition();
}


}

#endif
