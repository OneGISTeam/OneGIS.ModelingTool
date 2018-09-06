#ifndef OSG_CLIPNODE
#define OSG_CLIPNODE 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupClip.h>

namespace osg {



/** IVBF_SGNode for defining the position of ClipPlanes in the scene.*/
class OSG_EXPORT CVBF_SGNodeGroupClip : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupClip>
{
    public:

        CVBF_SGNodeGroupClip();

        CVBF_SGNodeGroupClip(const CVBF_SGNodeGroupClip& es, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, CVBF_SGNodeGroupClip);
    
  
        
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


        /** Creates six clip planes corresponding to the given BoundingBox. */
        void createClipBox(const BoundingBox& bb,unsigned int clipPlaneNumberBase=0);

        /** Adds the clipplane. Returns true on success, and false if the plane
          * has already been added, or if clipplane is NULL. */
        bool addClipPlane(ClipPlane* clipplane);

        /** Removes the clipplane. Returns true on success, false if clipplane
         * isn't in this CVBF_SGNodeGroupClip.*/
        bool removeClipPlane(ClipPlane* clipplane);

        /** Remove the ClipPlane with the given index. Returns true on success,
          * false if pos is not a valid plane index. */
        bool removeClipPlane(unsigned int pos);

        /** Returns the number of ClipPlanes. */
        inline unsigned int getNumClipPlanes() const { return _planes.size(); }


        /** Get ClipPlane at the given index position. */
        inline ClipPlane* getClipPlane(unsigned int pos) { return _planes[pos].get(); }

        /** Get const ClipPlane at the given index position. */
        inline const ClipPlane* getClipPlane(unsigned int pos) const { return _planes[pos].get(); }

        /** Set the ClipPlaneList. */
        inline void setClipPlaneList(const ClipPlaneList& cpl) { _planes=cpl; }

        /** Get the ClipPlaneList. */
        inline ClipPlaneList& getClipPlaneList() { return _planes; }

        /** Get the const ClipPlaneList. */
        inline const ClipPlaneList& getClipPlaneList() const { return _planes; }






        /** Set the GLModes for all ClipPlanes, on the StateSet. */
        void setStateSetModes(StateSet&,StateAttribute::GLModeValue) const;

        /** Set up the local StateSet. */
        void setLocalStateSetModes(StateAttribute::GLModeValue=StateAttribute::ON);

        virtual BoundingSphere computeBound() const;

    protected:

        virtual ~CVBF_SGNodeGroupClip();

        StateAttribute::GLModeValue     _value;
        ClipPlaneList                   _planes;
        
        ReferenceFrame                  _referenceFrame;
};

}

#endif
