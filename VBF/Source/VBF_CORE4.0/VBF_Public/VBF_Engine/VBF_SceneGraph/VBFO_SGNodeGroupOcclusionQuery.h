#ifndef OSG_OCCLUSION_QUERY_NODE
#define OSG_OCCLUSION_QUERY_NODE 1

#include <VBF_Engine/VBF_SceneGraph/Export>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>


namespace osg {

// Create and return a StateSet appropriate for performing an occlusion
//   query test (disable lighting, texture mapping, etc). Probably some
//   room for improvement here. Could disable shaders, for example.
osg::StateSet* initOQState();

// Create and return a StateSet for rendering a debug representation of query geometry.
osg::StateSet* initOQDebugState();

// TestResult -- stores (per context) results of an occlusion query
//   test performed by QueryGeometry. An OcclusionQueryNode has a
//   Geode owning a single QueryGeometry that
//   draws the occlusion query geometry. QueryGeometry keeps a
//   TestResult per context to store the result/status of each query.
// Accessed during the cull and draw traversals.
class TestResult : public ::CVBF_Referenced
{
public:
    TestResult() : _init( false ), _id( 0 ), _contextID( 0 ), _active( false ), _numPixels( 0 ) {}
    ~TestResult() {}

    bool _init;

    // Query ID for this context.
    GLuint _id;
    // Context ID owning this query ID.
    unsigned int _contextID;

    // Set to true when a query gets issued and set to
    //   false when the result is retrieved.
    mutable bool _active;

    // Result of last query.
    GLint _numPixels;
};

// QueryGeometry -- A Drawable that performs an occlusion query,
//   using its geometric data as the query geometry.
class QueryGeometry : public osg::Geometry
{
public:
    QueryGeometry( const std::string& oqnName=std::string("") );
    ~QueryGeometry();

    void reset();

    // TBD implement copy constructor

    virtual void drawImplementation( osg::RenderInfo& renderInfo ) const;

    unsigned int getNumPixels( const osg::IVBF_Camera* cam );

    virtual void releaseGLObjects( osg::State* state = 0 ) const;
    
    static void deleteQueryObject( unsigned int contextID, GLuint handle );
    static void flushDeletedQueryObjects( unsigned int contextID, double currentTime, double& availableTime );
    static void discardDeletedQueryObjects( unsigned int contextID );
    
protected:
    typedef std::map< const osg::IVBF_Camera*, TestResult > ResultMap;
    mutable ResultMap _results;
    mutable OpenThreads::Mutex _mapMutex;

    // Needed for debug only
    std::string _oqnName;
};

class IVBF_SGNodeGroupOcclusionQuery : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupOcclusionQuery(){}
	IVBF_SGNodeGroupOcclusionQuery(const IVBF_SGNodeGroupOcclusionQuery& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupOcclusionQuery(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}


    // When disabled, OQN doesn't perform occlusion queries, and simply
    //   renders its children.
    virtual void setQueriesEnabled( bool enable=true )=0;
    virtual bool getQueriesEnabled() const=0;


 
    virtual void setVisibilityThreshold( unsigned int pixels )=0;
    virtual unsigned int getVisibilityThreshold() const=0;

    // Specifies how many frames to wait before issuing another query.
    virtual void setQueryFrameCount( unsigned int frames )=0;
    virtual unsigned int getQueryFrameCount() const =0;

    // Indicate whether or not the bounding box used in the occlusion query test
    //   should be rendered. Handy for debugging and development.
    // Should only be called outside of cull/draw. No thread issues.
    virtual void setDebugDisplay( bool enable )=0;
    virtual bool getDebugDisplay() const=0;


    // Set and get the StateSet used by the OcclusionQueryNode
    //   when rendering the query geometry. OQN creates its own by
    //   default, but if you use many OQNs you might want to use
    //   this method to set all OQNs to use the same StateSet
    //   for more efficient processing.
    virtual void setQueryStateSet( osg::StateSet* ss )=0;
    virtual osg::StateSet* getQueryStateSet()=0;
    virtual const osg::StateSet* getQueryStateSet() const=0;

    // Set and get the StateSet used by the OcclusionQueryNode
    //   when rendering the debug query geometry (see setDebugDisplay).
    virtual void setDebugStateSet( osg::StateSet* ss )=0;
    virtual osg::StateSet* getDebugStateSet()=0;
    virtual const osg::StateSet* getDebugStateSet() const=0;

    // For statistics gathering, e.g., by a NodeVisitor.
    virtual bool getPassed() const=0;
    
    
    // These methods are public so that osgUtil::CullVisitor can access them.
    // Not intended for application use.
    virtual bool getPassed( const osg::IVBF_Camera* camera, osg::NodeVisitor& nv )=0;
    virtual void traverseQuery( const osg::IVBF_Camera* camera, osg::NodeVisitor& nv )=0;
    virtual void traverseDebug( osg::NodeVisitor& nv )=0;


};
// This IVBF_SGNode performs occlusion query testing on its children.
//   You can use it directly to occlusion query test a portion
//   of your scene graph, or you can use it implicitly with an
//   OcclusionQueryRoot, which places OcclusionQueryNodes where
//   needed and acts as a master control.
class OSG_EXPORT OcclusionQueryNode : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupOcclusionQuery>
{
public:
    OcclusionQueryNode();

    // Copy constructor using CopyOp to manage deep vs shallow copy.
    OcclusionQueryNode( const OcclusionQueryNode& oqn, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY );

    META_Node( osg, OcclusionQueryNode );

    virtual osg::BoundingSphere computeBound() const;

    virtual void releaseGLObjects( osg::State* state = 0 ) const;
    
    
    // When disabled, OQN doesn't perform occlusion queries, and simply
    //   renders its children.
    void setQueriesEnabled( bool enable=true );
    bool getQueriesEnabled() const { return _enabled; }


    // Sets/gets the visibility threshold. If the test indicates that
    //   the number of visible pixels is less than the specified
    //   threshold, don't draw the actual geometry.
    void setVisibilityThreshold( unsigned int pixels ) { _visThreshold = pixels; }
    unsigned int getVisibilityThreshold() const { return _visThreshold; }

    // Specifies how many frames to wait before issuing another query.
    void setQueryFrameCount( unsigned int frames ) { _queryFrameCount = frames; }
    unsigned int getQueryFrameCount() const { return _queryFrameCount; }

    // Indicate whether or not the bounding box used in the occlusion query test
    //   should be rendered. Handy for debugging and development.
    // Should only be called outside of cull/draw. No thread issues.
    void setDebugDisplay( bool enable );
    bool getDebugDisplay() const;


    // Set and get the StateSet used by the OcclusionQueryNode
    //   when rendering the query geometry. OQN creates its own by
    //   default, but if you use many OQNs you might want to use
    //   this method to set all OQNs to use the same StateSet
    //   for more efficient processing.
    void setQueryStateSet( osg::StateSet* ss );
    osg::StateSet* getQueryStateSet();
    const osg::StateSet* getQueryStateSet() const;

    // Set and get the StateSet used by the OcclusionQueryNode
    //   when rendering the debug query geometry (see setDebugDisplay).
    void setDebugStateSet( osg::StateSet* ss );
    osg::StateSet* getDebugStateSet();
    const osg::StateSet* getDebugStateSet() const;

    // For statistics gathering, e.g., by a NodeVisitor.
    bool getPassed() const;
    
    
    // These methods are public so that osgUtil::CullVisitor can access them.
    // Not intended for application use.
    virtual bool getPassed( const osg::IVBF_Camera* camera, osg::NodeVisitor& nv );
    void traverseQuery( const osg::IVBF_Camera* camera, osg::NodeVisitor& nv );
    void traverseDebug( osg::NodeVisitor& nv );


    // Delete unused query IDs for this contextID.
    static void flushDeletedQueryObjects( unsigned int contextID, double currentTime, double& availableTime );

    // discard all the cached query objects which need to be deleted
    // in the OpenGL context related to contextID.
    // Note, unlike flush no OpenGL calls are made, instead the handles are all removed.
    // this call is useful for when an OpenGL context has been destroyed.
    static void discardDeletedQueryObjects( unsigned int contextID );

protected:
    virtual ~OcclusionQueryNode();

    virtual void createSupportNodes();

    ref_ptr< osg::IVBF_SGNodeGeometry > _queryGeode;
    ref_ptr< osg::IVBF_SGNodeGeometry > _debugGeode;

    bool _enabled;

    // Tracks the last frame number that we performed a query.
    // User can set how many times  (See setQueryFrameCount).
    typedef std::map< const osg::IVBF_Camera*, unsigned int > FrameCountMap;
    FrameCountMap _frameCountMap;
    mutable OpenThreads::Mutex _frameCountMutex;

    // For statistics gathering
    bool _passed;

    // User-settable variables
    unsigned int _visThreshold;
    unsigned int _queryFrameCount;
    bool _debugBB;


    // Required to ensure that computeBound() is thread-safe.
    mutable OpenThreads::Mutex _computeBoundMutex;
};

}


#endif
