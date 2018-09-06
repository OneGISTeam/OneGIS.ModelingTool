#ifndef OSGEARTH_OVERLAY_DECORATOR
#define OSGEARTH_OVERLAY_DECORATOR

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeTerrainEngine.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTexGen.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Engine/VBF_SGUtil/CullVisitor>

class CVBFO_SGNodeTerrainEngine;
class CVBF_TechOverlay;
    

// 贴地表节点，使用多种技术把geometry覆盖到地形上
class OSGEARTH_EXPORT CVBFO_SGNodeDecoratorTerrainOverlay : public CVBFO_SGNodeDecoratorTerrain
{
public:
    CVBFO_SGNodeDecoratorTerrainOverlay();

	// 添加一个新的技术
    void addTechnique( CVBF_TechOverlay* technique );

	// 获取采用特定覆盖技术的节点
    template<typename T>
    osg::IVBF_SGNodeGroup* getGroup() 
	{
        for(unsigned i=0; i<_techniques.size(); ++i ) 
		{
            if ( dynamic_cast<T*>(_techniques[i].get()) )
                return _overlayGroups[i].get();
        }
        return 0L;
    }

	// 设置遍历覆盖节点时使用的掩码
    void setOverlayGraphTraversalMask( unsigned mask );

    double getMaxHorizonDistance() const;
    void setMaxHorizonDistance( double horizonDistance );


public: // CVBFO_SGNodeDecoratorTerrain
    virtual void onInstall( CVBFO_SGNodeTerrainEngine* engine );
    virtual void onUninstall( CVBFO_SGNodeTerrainEngine* engine );

public: // osg::Node
    void traverse( osg::NodeVisitor& nv );

public: // NotiferGroup listener interface
    void onGroupChanged(osg::IVBF_SGNodeGroup* group);

protected:
    virtual ~CVBFO_SGNodeDecoratorTerrainOverlay() { }

public:

    // 覆盖技术所用的RTT相机参数，每种技术每个视图拥有一个该参数
    struct TechRTTParams
    {
        osg::IVBF_Camera*             _mainCamera;       // Camera to which this per-view data is attached
        ref_ptr<osg::IVBF_Camera>     _ipCameraRTT;        // RTT camera.
        osg::Matrixd                  _matViewRTT;    // View matrix of RTT camera
        osg::Matrixd                  _matProjRTT;    // Projection matrix of RTT camera
        osg::IVBF_SGNodeGroup*        _group;            // contains the overlay graphics
        osg::StateSet*                _terrainStateSet;  // same object as in PerViewData (shared across techniques)
        ref_ptr<CVBF_Referenced>      _techniqueData;    // technique sets this if needed
        const double*                 _horizonDistance;  // points to the PVD horizon distance.
        osg::IVBF_SGNodeGroup*        _terrainParent;    // the terrain is in getChild(0).
    };

    // 每个视图（相机）所拥有的数据
    struct PerViewData
    {
        osg::IVBF_Camera*          _camera;      // Camera to which this per-view data is attached
        std::vector<TechRTTParams> _techParams;       // Pre-view data for each technique
        ref_ptr<osg::StateSet> _sharedTerrainStateSet; // shared state set to apply to the terrain traversal
        double                 _sharedHorizonDistance; // horizon distnace (not used?)
        osg::Matrix            _prevViewMatrix;        // last frame's view matrix
    };

private:
    CVBF_Optional<int>                 _explicitTextureUnit;
    CVBF_Optional<int>                 _textureUnit;
    CVBF_Optional<int>                 _textureSize;
    bool                          _useShaders;
    bool                          _isGeocentric;
    double                        _maxProjectedMapExtent;
    bool                          _mipmapping;
    bool                          _rttBlending;
    bool                          _updatePending;
    unsigned                      _rttTraversalMask;
        
    double                        _maxHorizonDistance;
    bool                          _attachStencil;
        
    unsigned int                   _totalOverlayChildren;

    ref_ptr<const CVBF_SpatialReference>    _srs;
    ref_ptr<const osg::EllipsoidModel> _ellipsoid;
    observer_ptr<CVBFO_SGNodeTerrainEngine>    _engine;

    // Mapping of each RTT camera params vector to a Camera (per view data)
    typedef std::map<osg::IVBF_Camera*, PerViewData> PerViewDataMap;

    PerViewDataMap _perViewData;
    CVBF_ReadWriteMutex _perViewDataMutex;

    typedef std::vector< ref_ptr<CVBF_TechOverlay> > Techniques;
    Techniques _techniques;             // 保存使用的技术
    Techniques _unsupportedTechniques;  // 保存未被支持的技术

    typedef std::vector< ref_ptr<osg::IVBF_SGNodeGroup> > Groups;
    Groups _overlayGroups;


private:
    void cullTerrainAndCalculateRTTParams( osgUtil::CullVisitor* cv, PerViewData& pvd );
    void initializePerViewData( PerViewData&, osg::IVBF_Camera* );
    PerViewData& getPerViewData( osg::IVBF_Camera* key );

public:
    struct InternalNodeVisitor : public osg::NodeVisitor 
	{
        InternalNodeVisitor(const osg::NodeVisitor::TraversalMode& mode =osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) : 
            osg::NodeVisitor(mode) 
		{ 
		}
    };

    //debugging:
    void requestDump() { _dumpRequested = true; }
    osg::IVBF_SGNode* getDump() { osg::IVBF_SGNode* r = _dump.release(); _dump = 0L; return r; }
    ref_ptr<osg::IVBF_SGNode> _dump;
    bool _dumpRequested;
};


// 覆盖（贴地表）技术的接口
class CVBF_TechOverlay : public ::CVBF_Referenced
{
protected:
    bool _supported;
    CVBF_TechOverlay() : _supported(true) { }
    virtual ~CVBF_TechOverlay() { }

public:
    virtual bool supported() { return _supported; }

    virtual bool hasData(CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params) const { return true; }

    virtual void onInstall(CVBFO_SGNodeTerrainEngine* engine ) { }

    virtual void onUninstall(CVBFO_SGNodeTerrainEngine* engine ) { }

    virtual void reestablish(CVBFO_SGNodeTerrainEngine* engine ) { }

    virtual void preCullTerrain(CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv) { }

    virtual void cullOverlayGroup(CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv) { }
};



#endif //OSGEARTH_OVERLAY_DECORATOR
