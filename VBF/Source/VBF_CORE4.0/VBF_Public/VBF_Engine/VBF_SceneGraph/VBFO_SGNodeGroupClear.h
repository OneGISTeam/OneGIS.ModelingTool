#ifndef OSG_CLEARNODE
#define OSG_CLEARNODE 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupClear.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <Types/Vec4>

namespace osg {

/** A Group node for clearing the color and depth buffers. Use setClearColor
  * to change the clear color, and setRequiresClear to disable/enable the call
  * clearing. You might want to disable clearing if you perform your clear by
  * drawing fullscreen geometry. If you do this, add child nodes to perform
  * such drawing. The default StateSet associated with this node places
  * children in render bin -1 to ensure that children are rendered prior to
  * the rest of the scene graph.
*/


class OSG_EXPORT CVBF_SGNodeGroupClear : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupClear>
{
    public :
        
        CVBF_SGNodeGroupClear();

        CVBF_SGNodeGroupClear(const CVBF_SGNodeGroupClear& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY);


        META_Node(osg, CVBF_SGNodeGroupClear);

        /** Enable/disable clearing via glClear. */
        inline void setRequiresClear(bool requiresClear) { _requiresClear = requiresClear; }
	    inline bool getRequiresClear() const { return _requiresClear; }

        /** Sets the clear color. */
        inline void setClearColor(const Vec4& color) { _clearColor = color; }
        inline const Vec4& getClearColor() const { return _clearColor; }
        
        /** Set the clear mask used in glClear(..).
          * Defaults to GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT. */
        inline void setClearMask(GLbitfield mask) { _clearMask = mask; }
        inline GLbitfield getClearMask() const { return _clearMask; }

    protected :
    
        virtual ~CVBF_SGNodeGroupClear() {}// IE¿ÉÄÜ´íÎó
        
        bool        _requiresClear;
        Vec4        _clearColor;
        GLbitfield  _clearMask;
};

}

#endif
