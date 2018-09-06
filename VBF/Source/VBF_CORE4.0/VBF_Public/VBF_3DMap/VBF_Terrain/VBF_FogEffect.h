
#ifndef __VBF_FOG_EFFECT_H__
#define __VBF_FOG_EFFECT_H__


#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNode.h>
#include <VBF_Base/observer_ptr>
#include <VBF_Base/VBF_Referenced.h>



 /**
 * Utility class for injecting fog capabilities into a VirtualProgram
 */
class OSGEARTH_EXPORT CVBF_FogEffect : public CVBF_Referenced
{
public:
    /**
     * Creates a new CVBF_FogEffect
     */
    CVBF_FogEffect();

    /**
     * Creates a new  CVBF_FogEffect and attaches it to the stateset.
     */
    CVBF_FogEffect(osg::StateSet* ss);

    /**
     * Attaches this CVBF_FogEffect to the given StateSet
     */
    void Attach(osg::StateSet* ss);

    /**
     * Detatches this CVBF_FogEffect from the given StateSet
     */
    void Detach(osg::StateSet* ss);

    /**
     * Detaches this CVBF_FogEffect from all attached StateSets
     */
    void Detach();

protected:
    virtual ~CVBF_FogEffect();

    typedef std::list< observer_ptr<osg::StateSet> > StateSetList;
    StateSetList    m_StateSetList;
};

#endif
