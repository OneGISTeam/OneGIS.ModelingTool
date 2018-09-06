#ifndef OSGEARTH_TERRAIN_H
#define OSGEARTH_TERRAIN_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBF_ConfigOptionsTerrain.h>
#include <VBF_Engine/VBF_SceneGraph/OperationThread>

class CVBF_SpatialReference;
class CVBF_Terrain;
    

// 向地形的回调函数传递上下文信息
class CVBF_TerrainCallbackContext
{
public:
    CVBF_TerrainCallbackContext(CVBF_Terrain* terrain) : _remove(false), _terrain(terrain) { }
	virtual ~CVBF_TerrainCallbackContext() { }

public:
    const CVBF_Terrain* getTerrain() const { return _terrain; }

    // 表示该callback将会被立即移除
    void remove() { _remove = true; }

     // 用户是否调用remove()
    bool markedForRemoval() const { return _remove; }

protected:
    bool			_remove;
    CVBF_Terrain*	_terrain;

    friend class CVBF_Terrain;
};


// 接收地形改变信息的回调接口，
class IVBF_TerrainCallback : public ::CVBF_Referenced
{
public:
	virtual ~IVBF_TerrainCallback() {}
    virtual void onTileAdded(const CVBF_TileKey& key, osg::IVBF_SGNode* tile, CVBF_TerrainCallbackContext& context)=0;
};

// 地形高程提供者接口
class IVBF_TerrainHeightProvider
{
public:
	virtual ~IVBF_TerrainHeightProvider() {}

    virtual bool getHeight( const CVBF_SpatialReference* srs, double x, double y,
							double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const =0;
};


/**CVBF_Terrain用于和live terrain graph的交互。CVBF_Map记录了支持地形的参数化的数据， CVBF_Terrain记录了内存中实际的geometry。
	所有返回的坐标值都是由getSRS()中的空间参考决定的 */
class OSGEARTH_EXPORT CVBF_Terrain : public ::CVBF_Referenced, public IVBF_TerrainHeightProvider
{
public:

    // 获取相关地图的概要信息
    const CVBF_Profile* getProfile() const { return _profile.get(); }

    // 获取相关地图的空间参考
    const CVBF_SpatialReference* getSRS() const { return _profile->getSRS(); }

    // 是否是ECEF坐标系
    bool isGeocentric() const { return _geocentric; }


public: // Intersection Utilities

    // 获取指定点的高程，out_heightAboveMSL值是相对于MSL (mean sea level)的高度，out_heightAboveEllipsoid是相对于参考椭球面的高程
    bool getHeight( const CVBF_SpatialReference* srs, double x, double y, 
			        double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const;

    // 同上，但指定了a subgraph patch
    bool getHeight( osg::IVBF_SGNode*  patch, const CVBF_SpatialReference* srs, double x, double y,
					double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const;

    // 获取鼠标点的世界坐标（mx，my为鼠标坐标）
    bool getWorldCoordsUnderMouse( osg::IVBF_ViewBrief* view, float mx, float my, osg::Vec3d& out_world ) const;

    bool getWorldCoordsUnderMouse( osg::IVBF_ViewBrief* view, float mx, float my, osg::Vec3d& out_world, ref_ptr<osg::IVBF_SGNode>& out_node ) const;

public:

    // 添加/移除地形更新回调
    void addTerrainCallback(IVBF_TerrainCallback* callback);
    void removeTerrainCallback(IVBF_TerrainCallback* callback);
        

public:

    // 接受节点遍历
    void accept( osg::NodeVisitor& nv );

    // access the raw terrain graph
    osg::IVBF_SGNode* getGraph() { return _graph.get(); }
        
    // queues the onTileAdded callback (internal)
    void notifyTileAdded( const CVBF_TileKey& key, osg::IVBF_SGNode* tile );

    // fires the onTileAdded callback (internal)
    void fireTileAdded( const CVBF_TileKey& key, osg::IVBF_SGNode* tile );

    virtual ~CVBF_Terrain();

private:
    CVBF_Terrain( osg::IVBF_SGNode* graph, const CVBF_Profile* profile, bool geocentric, const CVBF_OptionsTerrain& options );

    friend class CVBFO_SGNodeTerrainEngine;

    typedef std::list< ref_ptr<IVBF_TerrainCallback> > CallbackList;

    CallbackList					_callbacks;
    CVBF_ReadWriteMutex				_callbacksMutex;
    ref_ptr<const CVBF_Profile>		_profile;
    observer_ptr<osg::IVBF_SGNode>	_graph;
    bool							_geocentric;
    const CVBF_OptionsTerrain&		_terrainOptions;

    observer_ptr<osg::OperationQueue>	_updateOperationQueue;
};


//一个CVBF TerrainPatch是地形的一个独立的子集，可用于高程查询，是线程安全的。它是分离的，可以不在场景图中。
class OSGEARTH_EXPORT CVBF_TerrainPatch : public IVBF_TerrainHeightProvider
{
public:
    CVBF_TerrainPatch( osg::IVBF_SGNode* patch, const CVBF_Terrain* terrain );

    // 查询指定点的高程
    bool getHeight( const CVBF_SpatialReference* srs, double x, double y, 
					double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const;

protected:
    ref_ptr<osg::IVBF_SGNode>	_patch;
    ref_ptr<const CVBF_Terrain>	_terrain;
};


#endif // OSGEARTH_TERRAIN_H
