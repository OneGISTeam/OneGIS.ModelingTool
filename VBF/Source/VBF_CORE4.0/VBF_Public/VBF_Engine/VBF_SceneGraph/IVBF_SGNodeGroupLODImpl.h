#ifndef IVBF_SG_NODE_GROUP_LOD_IMPL_H
#define IVBF_SG_NODE_GROUP_LOD_IMPL_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLOD.h>

namespace osg {

/** LOD - Level Of Detail group node which allows switching between children
    depending on distance from eye point.
    Typical uses are for load balancing - objects further away from
    the eye point are rendered at a lower level of detail, and at times
    of high stress on the graphics pipeline lower levels of detail can
    also be chosen by adjusting the viewers's Camera/CullSettings LODScale value.
    Each child has a corresponding valid range consisting of a minimum
    and maximum distance. Given a distance to the viewer (d), LOD displays
    a child if min <= d < max. LOD may display multiple children simultaneously
    if their corresponding ranges overlap. Children can be in any order,
    and don't need to be sorted by range or amount of detail. If the number of
    ranges (m) is less than the number of children (n), then children m+1 through
    n are ignored.
*/

template<class T>
class IVBF_SGNodeGroupLODImpl : public IVBF_SGNodeGroupImpl<T>
{
private:
    typedef IVBF_SGNodeGroupImpl<T> _Base;

    public :
    
        IVBF_SGNodeGroupLODImpl();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        IVBF_SGNodeGroupLODImpl(const IVBF_SGNodeGroupLODImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

//        META_Node(osg, LOD);

 
        virtual void traverse(NodeVisitor& nv);
        
        virtual bool addChild(IVBF_SGNode *child);

        virtual bool addChild(IVBF_SGNode *child, float min, float max);

        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove=1);


      
        /** Modes which control how the center of object should be determined when computing which child is active.*/
 

        /** Set how the center of object should be determined when computing which child is active.*/
        void setCenterMode(IVBF_SGNodeGroupLOD::CenterMode mode) { _centerMode=mode; }

        /** Get how the center of object should be determined when computing which child is active.*/
        IVBF_SGNodeGroupLOD::CenterMode getCenterMode() const { return _centerMode; }

        /** Sets the object-space point which defines the center of the osg::LOD.  
            center is affected by any transforms in the hierarchy above the osg::LOD.*/
        virtual void setCenter(const IVBF_SGNodeGroupLOD::vec_type& center) { _centerMode=IVBF_SGNodeGroupLOD::USER_DEFINED_CENTER; _userDefinedCenter = center; }
        
        /** return the LOD center point. */
        virtual const IVBF_SGNodeGroupLOD::vec_type& getCenter() const { if (_centerMode==IVBF_SGNodeGroupLOD::USER_DEFINED_CENTER) return _userDefinedCenter; else return IVBF_SGNodeImpl<T>::getBound().center(); }


        /** Set the object-space reference radius of the volume enclosed by the LOD. 
          * Used to determine the bounding sphere of the LOD in the absence of any children.*/
        virtual void setRadius(IVBF_SGNodeGroupLOD::value_type radius) { _radius = radius; }
        
        /** Get the object-space radius of the volume enclosed by the LOD.*/
        virtual IVBF_SGNodeGroupLOD::value_type getRadius() const { return _radius; }


        /** Set how the range values should be interpreted when computing which child is active.*/
        void setRangeMode(IVBF_SGNodeGroupLOD::RangeMode mode) { _rangeMode = mode; }

        /** Get how the range values should be interpreted when computing which child is active.*/
        IVBF_SGNodeGroupLOD::RangeMode getRangeMode() const { return _rangeMode; }


        /** Sets the min and max visible ranges of range of specific child.
            Values are floating point distance specified in local objects coordinates.*/
        void setRange(unsigned int childNo, float min,float max);
        
        /** returns the min visible range for specified child.*/
        virtual float getMinRange(unsigned int childNo) const { return _rangeList[childNo].first; }

        /** returns the max visible range for specified child.*/
        virtual float getMaxRange(unsigned int childNo) const { return _rangeList[childNo].second; }
        
        /** returns the number of ranges currently set. 
          * An LOD which has been fully set up will have getNumChildren()==getNumRanges(). */
        virtual unsigned int getNumRanges() const { return _rangeList.size(); }

        /** set the list of MinMax ranges for each child.*/
        virtual void setRangeList(const IVBF_SGNodeGroupLOD::RangeList& rangeList) { _rangeList=rangeList; }

        /** return the list of MinMax ranges for each child.*/
        virtual const IVBF_SGNodeGroupLOD::RangeList& getRangeList() const { return _rangeList; }

        virtual BoundingSphere computeBound() const;

    protected :
        virtual ~IVBF_SGNodeGroupLODImpl() {}

        IVBF_SGNodeGroupLOD::CenterMode                      _centerMode;
        IVBF_SGNodeGroupLOD::vec_type                        _userDefinedCenter;
        IVBF_SGNodeGroupLOD::value_type                      _radius;

        IVBF_SGNodeGroupLOD::RangeMode                       _rangeMode;
        IVBF_SGNodeGroupLOD::RangeList                       _rangeList;

};

}
#include "IVBF_SGNodeGroupLODImpl.inl"
#endif
