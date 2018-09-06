#ifndef OSGPARTICLE_RANDOMRATE_COUNTER
#define OSGPARTICLE_RANDOMRATE_COUNTER 1

#include <VBF_Engine/VBF_Particle/VBF_PSCounterVariableRate.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

namespace osgParticle
{

	// 允许用户指定每帧产生粒子的最大和最小数
    class RandomRateCounter: public VariableRateCounter 
	{
    public:
        inline RandomRateCounter();
        inline RandomRateCounter(const RandomRateCounter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Object(osgParticle, RandomRateCounter);
    
        // 本帧产生的粒子的数量
        inline int numParticlesToCreate(double dt) const;
        
    protected:
        virtual ~RandomRateCounter() {}
        
        mutable float _np;
    };
    
    // INLINE FUNCTIONS
    
    inline RandomRateCounter::RandomRateCounter()
    : VariableRateCounter(), _np(0)
    {
    }
    
    inline RandomRateCounter::RandomRateCounter(const RandomRateCounter& copy, const osg::CopyOp& copyop)
    : VariableRateCounter(copy, copyop), _np(copy._np)
    {
    }
    
    inline int RandomRateCounter::numParticlesToCreate(double dt) const
    {
        // compute the number of new particles, clamping it to 1 second of particles at the maximum rate
        float numNewParticles = osg::minimum(static_cast<float>(dt * getRateRange().get_random()), getRateRange().maximum);

        // add the number of new particles to value carried over from the previous call
       _np += numNewParticles;

        // round down the number of particles.
        int n = static_cast<int>(_np);

        // take away the number of rounded number of particles leaving the decimal place
        // this is done so that two frames of 0.5's will results in first frame 0 new particles, second frame 1
        _np -= n;

        // return the rounded number of particles to be created
        return n;
    }

}


#endif
