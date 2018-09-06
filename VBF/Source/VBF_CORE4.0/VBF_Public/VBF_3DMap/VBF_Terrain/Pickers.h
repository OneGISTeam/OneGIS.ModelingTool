#ifndef OSGEARTH_PICKING_UTILS_H
#define OSGEARTH_PICKING_UTILS_H

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Engine/VBF_SGUtil/PolytopeIntersector>

namespace osgEarth
{
	// Ê°È¡Æ÷
    class OSGEARTH_EXPORT Picker
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
        Picker( IVBF_View* view, osg::IVBF_SGNode* graph =0L, unsigned traversalMask =~0,
					float buffer =5.0f, Limit limit =LIMIT_ONE);

        virtual ~Picker() { }

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
        IVBF_View*                  _view;
        ref_ptr<osg::IVBF_SGNode>     _root;
        osg::CVBF_SGNodePath          _path;
        unsigned                      _travMask;
        float                         _buffer;
        Limit                         _limit;
    };
}

#endif // OSGEARTH_PICKING_UTILS_H
