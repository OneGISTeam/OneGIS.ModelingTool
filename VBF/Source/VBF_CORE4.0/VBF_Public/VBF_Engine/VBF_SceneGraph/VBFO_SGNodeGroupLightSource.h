#ifndef OSG_LIGHTSOURCE
#define OSG_LIGHTSOURCE 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLightSource.h>

namespace osg {


class OSG_EXPORT CVBF_SGNodeGroupLightSource : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupLightSource>
{
    public:
    
        CVBF_SGNodeGroupLightSource();

        /** Copy constructor using CopyOp to manage deep vs shallow copy. */
        CVBF_SGNodeGroupLightSource(const CVBF_SGNodeGroupLightSource& ls, const CopyOp& copyop=CopyOp::SHALLOW_COPY);



        META_Node(osg, CVBF_SGNodeGroupLightSource);

   
        /** Set the light sources's ReferenceFrame, either to be relative to its
          * parent reference frame, or relative to an absolute coordinate
          * frame. RELATIVE_RF is the default.
          * Note: setting the ReferenceFrame to be ABSOLUTE_RF will
          * also set the CullingActive flag on the light source, and hence all
          * of its parents, to false, thereby disabling culling of it and
          * all its parents.  This is necessary to prevent inappropriate
          * culling, but may impact cull times if the absolute light source is
          * deep in the scene graph.  It is therefore recommended to only use
          * absolute light source at the top of the scene.
        */
        void setReferenceFrame(ReferenceFrame rf);
        
        ReferenceFrame getReferenceFrame() const { return _referenceFrame; }

        // 设置/获取灯光
        void setLight(Light* light);
		inline Light* getLight() { return _light.get(); }
		inline const Light* getLight() const { return _light.get(); }

        /** Set the GLModes on StateSet associated with the CVBF_SGNodeGroupLightSource. */
        void setStateSetModes(StateSet&,StateAttribute::GLModeValue) const;

        /** Set up the local StateSet. */
        void setLocalStateSetModes(StateAttribute::GLModeValue value = StateAttribute::ON);

        /** Set whether to use a mutex to ensure ref() and unref() are thread safe.*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        virtual BoundingSphere computeBound() const;

    protected:

        virtual ~CVBF_SGNodeGroupLightSource();

        StateAttribute::GLModeValue     _value;
        ref_ptr<Light>                  _light;

        ReferenceFrame                  _referenceFrame;
};

}

#endif
