#ifndef OSG_NODEVISITOR
#define OSG_NODEVISITOR 1

#include <VBF_Engine/VBF_SceneGraph/Export>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>
//#include <Types/VBF_Matrix.h>
#include <VBF_Base/VBF_FrameStamp.h>

namespace osg {

class IVBF_SGNode;
class IVBF_SGNodeGeometryBillboard;
class IVBF_SGNodeGroupClear;
class IVBF_SGNodeGroupClip;
class IVBF_SGNodeGroupCoordSys;
class IVBF_SGNodeGeometry;
class IVBF_SGNodeGroup;
class IVBF_SGNodeGroupLightSource;
class IVBF_SGNodeGroupLOD;
class IVBF_SGNodeGroupTransformMatrix;
class IVBF_SGNodeGroupOccluder;
class IVBF_SGNodeGroupOcclusionQuery;
class IVBF_SGNodeGroupLODPaged;
class IVBF_SGNodeGroupTransformPositionAttitude;
class IVBF_SGNodeGroupProjection;
class IVBF_SGNodeGroupProxy;
class IVBF_SGNodeGroupSequence;
class IVBF_SGNodeGroupSwitch;
class IVBF_SGNodeGroupTexGen;
class IVBF_SGNodeGroupTransform;
class IVBF_Camera;
class IVBF_SGNodeGroupTransformCameraView;

const unsigned int UNINITIALIZED_FRAME_NUMBER=0xffffffff;

#define META_NodeVisitor(library,name) \
        virtual const char* libraryName() const { return #library; }\
        virtual const char* className() const { return #name; }

/** 节点访问器，基于访问器设计模式。
		访问器是对多个抽象的对象群的一种特殊处理，使用访问器模式可以在不改变这些类的前提下
	定义这些类的新操作。
		有何多种类对象，它们有不同的接口，想对这些对象实施一些依赖于具体类的同一种操作，
	将这些操作集中在一个类中，这个类就是访问器模式

	注意：节点访问器使用了一种"双派遣"（double dispatch）技术，以便调用恰当的apply(..)方法。
	因此，必须用root->accept(myVisitor)代替myVisitor.apply(*root)，
	后者将绕过双派遣机制，无法调用合适的NodeVisitor::apply(..)
*/ 



class OSG_EXPORT NodeVisitor : public virtual ::CVBF_Referenced
{
    public:

        enum TraversalMode
        {
            TRAVERSE_NONE,				// 仅传递到当前节点
            TRAVERSE_PARENTS,			// 传递给当前节点和父节点
            TRAVERSE_ALL_CHILDREN,		// 传递给所有子节点
            TRAVERSE_ACTIVE_CHILDREN	// 传递给所有Actived子节点
        };
        
        enum VisitorType // 访问器类型
        {
            NODE_VISITOR = 0,			// 访问器（仅遍历）
            UPDATE_VISITOR,				// 访问器（更新操作）
            EVENT_VISITOR,				// 访问器（事件相应）
            COLLECT_OCCLUDER_VISITOR,	// 访问器（收集遮挡板）
            CULL_VISITOR				// 访问器（筛选）
        };

        NodeVisitor(TraversalMode tm=TRAVERSE_NONE);       
        NodeVisitor(VisitorType type,TraversalMode tm=TRAVERSE_NONE);
        
        virtual ~NodeVisitor();
        
        // 返回所在的库的名字
        virtual const char* libraryName() const { return "osg"; }
        // 返回类的名字
        virtual const char* className() const { return "NodeVisitor"; }

		// 重置。如果访问器在遍历过程中积累了状态，并想重用visitor，在每次遍历前调用该函数清理（flush）状态
        virtual void reset() {}


		// 设置/获取访问器的类型，用于遍历场景过程中区分不同的访问器，典型的应用是在IVBF_SGNode::traverse()函数中
		// 根据不同的类型选择使用哪种行为
        inline void setVisitorType(VisitorType type) { _visitorType = type; }
        inline VisitorType getVisitorType() const { return _visitorType; }

		// 设置/获取遍历number，典型应用是指示帧数
        inline void setTraversalNumber(unsigned int fn) { _traversalNumber = fn; }
        inline unsigned int getTraversalNumber() const { return _traversalNumber; }

        // 设置/获取本次遍历对应的帧戳
        inline void setFrameStamp(::CVBF_FrameStamp* fs) { _frameStamp = fs; }
        inline const ::CVBF_FrameStamp* getFrameStamp() const { return _frameStamp.get(); }
	
		// TraversalMask和OverrideMask，用于限定节点访问器能够访问哪些节点。
		// 节点是否能被访问器访问取决于：TraversalMask & ( OverrideMask | NodeMask )


        /** Set the TraversalMask of this NodeVisitor.
          * TraversalMask用于NodeVisitor::validNodeMask()，确定是否操作某节点及其子图。
          * validNodeMask()在IVBF_SGNode::accept()中自动调用 before
          * any call to NodeVisitor::apply(), apply() is only ever called if validNodeMask
          * returns true. Note, if NodeVisitor::_traversalMask is 0 then all operations
          * will be switched off for all nodes.  Whereas setting both _traversalMask and
          * _nodeMaskOverride to 0xffffffff will allow a visitor to work on all nodes
          * regardless of their own IVBF_SGNode::_nodeMask state.*/
        inline void setTraversalMask(IVBF_SGNode::NodeMask mask) { _traversalMask = mask; }

        /** Get the TraversalMask.*/
        inline IVBF_SGNode::NodeMask getTraversalMask() const { return _traversalMask; }

        /** Set the NodeMaskOverride mask.
          * Used in validNodeMask() to determine whether to operate on a node or its 
          * subgraph, by OR'ing NodeVisitor::_nodeMaskOverride with the IVBF_SGNode's own IVBF_SGNode::_nodeMask.
          * Typically used to force on nodes which may have
          * been switched off by their own IVBF_SGNode::_nodeMask.*/
        inline void setNodeMaskOverride(IVBF_SGNode::NodeMask mask) { _nodeMaskOverride = mask; }

        /** Get the NodeMaskOverride mask.*/
        inline IVBF_SGNode::NodeMask getNodeMaskOverride() const { return _nodeMaskOverride; }
        
        /** Method to called by IVBF_SGNode and its subclass' IVBF_SGNode::accept() method, if the result is true
          * it is used to cull operations of nodes and their subgraphs.
          * Return true if the result of a bit wise and of the NodeVisitor::_traversalMask
          * with the bit or between NodeVistor::_nodeMaskOverride and the IVBF_SGNode::_nodeMask.
          * default values for _traversalMask is 0xffffffff, _nodeMaskOverride is 0x0,
          * and osg::IVBF_SGNode::_nodeMask is 0xffffffff. */
        inline bool validNodeMask(const osg::IVBF_SGNode& node) const
        {
            return (getTraversalMask() & (getNodeMaskOverride() | node.getNodeMask()))!=0;
        }

		// 设置获取节点遍历的模式，以决定哪些子节点被遍历。
        inline void setTraversalMode(TraversalMode mode) { _traversalMode = mode; }      
        inline TraversalMode getTraversalMode() const { return _traversalMode; }

 		// 设置/获取用户数据，必须支持引用计数以便内存管理，如果用户数据不是从引用计数继承的则需创建一个适配对象管理内存
        inline void setUserData(CVBF_Referenced* obj) { _userData = obj; }
        inline CVBF_Referenced* getUserData() { return _userData.get(); }
        inline const CVBF_Referenced* getUserData() const { return _userData.get(); }


        /** Method for handling traversal of a nodes.
            If you intend to use the visitor for actively traversing 
            the scene graph then make sure the accept() methods call
            this method unless they handle traversal directly.*/
		
		// 遍历节点
        inline void traverse(IVBF_SGNode& node)
        {
            if (_traversalMode==TRAVERSE_PARENTS) node.ascend(*this);
            else if (_traversalMode!=TRAVERSE_NONE) node.traverse(*this);
        }
        
        /** Method called by osg::IVBF_SGNode::accept() method before
          * a call to the NodeVisitor::apply(..).  The back of the list will,
          * therefore, be the current node being visited inside the apply(..),
          * and the rest of the list will be the parental sequence of nodes 
          * from the top most node applied down the graph to the current node.
          * Note, the user does not typically call pushNodeOnPath() as it
          * will be called automatically by the IVBF_SGNode::accept() method.*/
        inline void pushOntoNodePath(IVBF_SGNode* node) { if (_traversalMode!=TRAVERSE_PARENTS) _nodePath.push_back(node); else _nodePath.insert(_nodePath.begin(),node); }
        
        /** Method called by osg::IVBF_SGNode::accept() method after
          * a call to NodeVisitor::apply(..).
          * Note, the user does not typically call popFromNodePath() as it
          * will be called automatically by the IVBF_SGNode::accept() method.*/
        inline void popFromNodePath()            { if (_traversalMode!=TRAVERSE_PARENTS) _nodePath.pop_back(); else _nodePath.erase(_nodePath.begin()); }
        
        /** Get the non const CVBF_SGNodePath from the top most node applied down
          * to the current IVBF_SGNode being visited.*/
        osg::CVBF_SGNodePath& getNodePath() { return _nodePath; }

        /** Get the const CVBF_SGNodePath from the top most node applied down
          * to the current IVBF_SGNode being visited.*/
        const osg::CVBF_SGNodePath& getNodePath() const { return _nodePath; }
        
        /** Get the eye point in local coordinates.
          * Note, not all NodeVisitor implement this method, it is mainly cull visitors which will implement.*/
        virtual osg::Vec3 getEyePoint() const { return Vec3(0.0f,0.0f,0.0f); }

        /** Get the view point in local coordinates.
          * Note, not all NodeVisitor implement this method, it is mainly cull visitors which will implement.*/
        virtual osg::Vec3 getViewPoint() const { return getEyePoint(); }

        /** Get the distance from a point to the eye point, distance value in local coordinate system.
          * Note, not all NodeVisitor implement this method, it is mainly cull visitors which will implement.
          * If the getDistanceFromEyePoint(pos) is not implemented then a default value of 0.0 is returned.*/
        virtual float getDistanceToEyePoint(const Vec3& /*pos*/, bool /*useLODScale*/) const { return 0.0f; }

        /** Get the distance of a point from the eye point, distance value in the eye coordinate system.
          * Note, not all NodeVisitor implement this method, it is mainly cull visitors which will implement.
          * If the getDistanceFromEyePoint(pos) is not implemented than a default value of 0.0 is returned.*/
        virtual float getDistanceFromEyePoint(const Vec3& /*pos*/, bool /*useLODScale*/) const { return 0.0f; }

        /** Get the distance from a point to the view point, distance value in local coordinate system.
          * Note, not all NodeVisitor implement this method, it is mainly cull visitors which will implement.
          * If the getDistanceToViewPoint(pos) is not implemented then a default value of 0.0 is returned.*/
        virtual float getDistanceToViewPoint(const Vec3& /*pos*/, bool /*useLODScale*/) const { return 0.0f; }
        

        virtual void apply(IVBF_SGNode& node);
        
        virtual void apply(IVBF_SGNodeGeometry& node);
        virtual void apply(IVBF_SGNodeGeometryBillboard& node);
        
        virtual void apply(IVBF_SGNodeGroup& node);

        virtual void apply(IVBF_SGNodeGroupProxy& node);

        virtual void apply(IVBF_SGNodeGroupProjection& node);

        virtual void apply(IVBF_SGNodeGroupCoordSys& node);

        virtual void apply(IVBF_SGNodeGroupClip& node);
        virtual void apply(IVBF_SGNodeGroupTexGen& node);
        virtual void apply(IVBF_SGNodeGroupLightSource& node);

        virtual void apply(IVBF_SGNodeGroupTransform& node);
        virtual void apply(IVBF_Camera& node);
        virtual void apply(IVBF_SGNodeGroupTransformCameraView& node);
        virtual void apply(IVBF_SGNodeGroupTransformMatrix& node);
        virtual void apply(IVBF_SGNodeGroupTransformPositionAttitude& node);

        virtual void apply(IVBF_SGNodeGroupSwitch& node);
        virtual void apply(IVBF_SGNodeGroupSequence& node);
        virtual void apply(IVBF_SGNodeGroupLOD& node);
        virtual void apply(IVBF_SGNodeGroupLODPaged& node);
        virtual void apply(IVBF_SGNodeGroupClear& node);
        virtual void apply(IVBF_SGNodeGroupOccluder& node);
        virtual void apply(IVBF_SGNodeGroupOcclusionQuery& node);


        /** Callback for managing database paging, such as generated by PagedLOD nodes.*/
        class DatabaseRequestHandler : public ::CVBF_Referenced
        {
        public:
            DatabaseRequestHandler(): CVBF_Referenced(true) {}
            virtual void requestNodeFile(const std::string& fileName, osg::CVBF_SGNodePath& nodePath, float priority, const ::CVBF_FrameStamp* framestamp, ref_ptr<CVBF_Referenced>& databaseRequest, const CVBF_Referenced* options=0) = 0;

			virtual void requestNodeFile(const std::string& fileName, osg::CVBF_SGNodePath& nodePath, const CVBF_Referenced* options=0) = 0;
        protected:
            virtual ~DatabaseRequestHandler() {}
        };

        /** Set the handler for database requests.*/
        void setDatabaseRequestHandler(DatabaseRequestHandler* handler) { _databaseRequestHandler = handler; }

        /** Get the handler for database requests.*/
        DatabaseRequestHandler* getDatabaseRequestHandler() { return _databaseRequestHandler.get(); }

        /** Get the const handler for database requests.*/
        const DatabaseRequestHandler* getDatabaseRequestHandler() const { return _databaseRequestHandler.get(); }


        /** Callback for managing image paging, such as generated by PagedLOD nodes.*/
        class ImageRequestHandler : public ::CVBF_Referenced
        {
        public:       
            ImageRequestHandler(): CVBF_Referenced(true) {}

            virtual double getPreLoadTime() const = 0;
            
            virtual osg::Image* readImageFile(const std::string& fileName) = 0;
        
            virtual void requestImageFile(const std::string& fileName,osg::CVBF_Object* attachmentPoint, int attachmentIndex, double timeToMergeBy, const ::CVBF_FrameStamp* framestamp) = 0;
            
        protected:
            virtual ~ImageRequestHandler() {}
        };
        
        /** Set the handler for image requests.*/
        void setImageRequestHandler(ImageRequestHandler* handler) { _imageRequestHandler = handler; }
        
        /** Get the handler for image requests.*/
        ImageRequestHandler* getImageRequestHandler() { return _imageRequestHandler.get(); }

        /** Get the const handler for image requests.*/
        const ImageRequestHandler* getImageRequestHandler() const { return _imageRequestHandler.get(); }



    protected:

        VisitorType                     _visitorType;
        unsigned int                    _traversalNumber;
        
        ref_ptr< ::CVBF_FrameStamp >             _frameStamp;     // 帧戳
        
        TraversalMode                   _traversalMode;
        IVBF_SGNode::NodeMask           _traversalMask;  // 还有OverrideMask，用于限定节点访问器能够访问哪些节点。缺省值为0xffffffff。
		                                                 // 节点是否能被访问器访问取决于：TraversalMask & ( OverrideMask | NodeMask )
        IVBF_SGNode::NodeMask           _nodeMaskOverride;
        
        osg::CVBF_SGNodePath            _nodePath;

        ref_ptr<CVBF_Referenced>             _userData;

        ref_ptr<DatabaseRequestHandler> _databaseRequestHandler;
        ref_ptr<ImageRequestHandler>    _imageRequestHandler;

};


/** Convenience functor for assisting visiting of arrays of osg::IVBF_SGNode's.*/ 
class NodeAcceptOp
{
    public:
        NodeAcceptOp(NodeVisitor& nv):_nv(nv) {}
        NodeAcceptOp(const NodeAcceptOp& naop):_nv(naop._nv) {}

        void operator () (IVBF_SGNode* node) { node->accept(_nv); }
        void operator () (ref_ptr<IVBF_SGNode> node) { node->accept(_nv); }

    protected:

        NodeAcceptOp& operator = (const NodeAcceptOp&) { return *this; }

        NodeVisitor& _nv;
};

}

#endif
