/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#ifndef OSG_COLLECTOCCLUDERSVISITOR
#define OSG_COLLECTOCCLUDERSVISITOR 1

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/CullStack>

#include <set>

namespace osg {

class OSG_EXPORT CollectOccludersVisitor : public osg::NodeVisitor, public osg::CullStack
{
    public:


        typedef std::set<ShadowVolumeOccluder> ShadowVolumeOccluderSet;

        CollectOccludersVisitor();
        virtual ~CollectOccludersVisitor();

        META_NodeVisitor("osg","CollectOccludersVisitor")

        virtual CollectOccludersVisitor* cloneType() const { return new CollectOccludersVisitor(); }

        virtual void reset();

        virtual float getDistanceToEyePoint(const Vec3& pos, bool withLODScale) const;
        virtual float getDistanceToViewPoint(const Vec3& pos, bool withLODScale) const;
        
        virtual float getDistanceFromEyePoint(const Vec3& pos, bool withLODScale) const;

        virtual void apply(osg::IVBF_SGNode&);
        virtual void apply(osg::IVBF_SGNodeGroupTransform& node);
        virtual void apply(osg::IVBF_SGNodeGroupProjection& node);

        virtual void apply(osg::IVBF_SGNodeGroupSwitch& node);
        virtual void apply(osg::IVBF_SGNodeGroupLOD& node);
        virtual void apply(osg::IVBF_SGNodeGroupOccluder& node);

        /** Sets the minimum shadow occluder volume that an active occluder
          * must have. vol is units relative the clip space volume where 1.0
          * is the whole clip space. */
        void setMinimumShadowOccluderVolume(float vol) { _minimumShadowOccluderVolume = vol; }
        float getMinimumShadowOccluderVolume() const { return _minimumShadowOccluderVolume; }

        /** Sets the maximum number of occluders to have active for culling
          * purposes. */
        void setMaximumNumberOfActiveOccluders(unsigned int num) { _maximumNumberOfActiveOccluders = num; }
        unsigned int getMaximumNumberOfActiveOccluders() const { return _maximumNumberOfActiveOccluders; }

        void setCreateDrawablesOnOccludeNodes(bool flag) { _createDrawables=flag; }
        bool getCreateDrawablesOnOccludeNodes() const { return _createDrawables; }

        void setCollectedOccluderSet(const ShadowVolumeOccluderSet& svol) { _occluderSet = svol; }
        ShadowVolumeOccluderSet& getCollectedOccluderSet() { return _occluderSet; }
        const ShadowVolumeOccluderSet& getCollectedOccluderSet() const { return _occluderSet; }

        /** Removes occluded occluders for the collected occluders list, then
          * discards all but MaximumNumberOfActiveOccluders of occluders,
          * discarding the occluders with the lowest shadow occluder volume. */
        void removeOccludedOccluders();


    protected:

        /** Prevents unwanted copy construction. */
        //CollectOccludersVisitor(const CollectOccludersVisitor&):osg::NodeVisitor(),osg::CullStack() {}

        /** Prevents unwanted copy operator. */
        CollectOccludersVisitor& operator = (const CollectOccludersVisitor&) { return *this; }
        
        inline void handle_cull_callbacks_and_traverse(osg::IVBF_SGNode& node)
        {
            /*osg::NodeCallback* callback = node.getCullCallback();
            if (callback) (*callback)(&node,this);
            else*/ if (node.getNumChildrenWithOccluderNodes()>0) traverse(node);
        }

        inline void handle_cull_callbacks_and_accept(osg::IVBF_SGNode& node,osg::IVBF_SGNode* acceptNode)
        {
            /*osg::NodeCallback* callback = node.getCullCallback();
            if (callback) (*callback)(&node,this);
            else*/ if (node.getNumChildrenWithOccluderNodes()>0) acceptNode->accept(*this);
        }

        float                       _minimumShadowOccluderVolume;
        unsigned                    _maximumNumberOfActiveOccluders;
        bool                        _createDrawables;
        ShadowVolumeOccluderSet     _occluderSet;

};

}

#endif

