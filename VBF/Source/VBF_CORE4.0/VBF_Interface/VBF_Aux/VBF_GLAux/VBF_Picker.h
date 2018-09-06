//***************************************************************************************
// FileName：VBF_Picker.h
// Function：节点选取，可以选取线段
// Author:   杜莹
// Date:     2012-12-24
//***************************************************************************************

#ifndef __VBF_PICKER_H__
#define __VBF_PICKER_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Engine/VBF_SGUtil/PolytopeIntersector>



class VBF_GLAUX_EXPORT CVBF_Picker
{
public:

    typedef osgUtil::PolytopeIntersector::Intersection  Hit;
    typedef osgUtil::PolytopeIntersector::Intersections Hits;

	enum Limit
	{
		NO_LIMIT,
		LIMIT_ONE_PER_DRAWABLE,
		LIMIT_ONE,
		LIMIT_NEAREST
	};

public:
    /**
     * Constructs a picker that will pick data from the given view,
     * and restrict its search to the given graph.
     *
     * @param view          View under which to pick
     * @param graph         Subgraph within which to restrict the pick
     * @param traversalMask Node mask to apply to the pick visitor
     * @param buffer        Pick buffer around the click (pixels)
     */
    CVBF_Picker( IVBF_View* view, osg::IVBF_SGNode* graph =0L, unsigned traversalMask =~0,
                float buffer=5.0f, Limit limit =LIMIT_ONE);

    virtual ~CVBF_Picker() { }

    // 设置/获取x和y方向的buffer
    void SetBuffer(float fBufferX, float fBufferY)     { m_fBufferX = fBufferX; m_fBufferY = fBufferY; }
    void GetBuffer(float& fBufferX, float& fBufferY)   { fBufferX = m_fBufferX; fBufferY = m_fBufferY; }

    /**
     * Picks geometry under the specified viewport coordinates. The results
     * are stores in "results". You can typically get the mouseX and mouseY
     * from osgGA::GUIEventAdapter getX() and getY().
     */
    bool pick( float mouseX, float mouseY, Hits& results ) const;

    /**
     * Finds and returns the lowest node of type "T" in a hit, or 0L if no such
     * node exists.
     */
    template<typename T>
    T* getNode( const Hit& hit ) const
    {
        for( osg::CVBF_SGNodePath::const_reverse_iterator i = hit.nodePath.rbegin(); i != hit.nodePath.rend(); ++i )
        {
           T* node = dynamic_cast<T*>(*i);
           if ( node ) return node;
        }
        return 0L;
    }


protected:
    IVBF_View*                      m_pIView;
    ref_ptr<osg::IVBF_SGNode>       m_piRootNode;
    osg::CVBF_SGNodePath            m_NodePath;
    unsigned                        m_nTravMask;
    float                           m_fBufferX;
    float                           m_fBufferY;
    Limit                           m_nLimitType;
};

#endif
