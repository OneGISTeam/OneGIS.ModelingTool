#ifndef OSGEARTH_TERRAIN_H
#define OSGEARTH_TERRAIN_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBF_ConfigOptionsTerrain.h>
#include <VBF_Engine/VBF_SceneGraph/OperationThread>

class CVBF_SpatialReference;
class CVBF_Terrain;
    

// ����εĻص�����������������Ϣ
class CVBF_TerrainCallbackContext
{
public:
    CVBF_TerrainCallbackContext(CVBF_Terrain* terrain) : _remove(false), _terrain(terrain) { }
	virtual ~CVBF_TerrainCallbackContext() { }

public:
    const CVBF_Terrain* getTerrain() const { return _terrain; }

    // ��ʾ��callback���ᱻ�����Ƴ�
    void remove() { _remove = true; }

     // �û��Ƿ����remove()
    bool markedForRemoval() const { return _remove; }

protected:
    bool			_remove;
    CVBF_Terrain*	_terrain;

    friend class CVBF_Terrain;
};


// ���յ��θı���Ϣ�Ļص��ӿڣ�
class IVBF_TerrainCallback : public ::CVBF_Referenced
{
public:
	virtual ~IVBF_TerrainCallback() {}
    virtual void onTileAdded(const CVBF_TileKey& key, osg::IVBF_SGNode* tile, CVBF_TerrainCallbackContext& context)=0;
};

// ���θ߳��ṩ�߽ӿ�
class IVBF_TerrainHeightProvider
{
public:
	virtual ~IVBF_TerrainHeightProvider() {}

    virtual bool getHeight( const CVBF_SpatialReference* srs, double x, double y,
							double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const =0;
};


/**CVBF_Terrain���ں�live terrain graph�Ľ�����CVBF_Map��¼��֧�ֵ��εĲ����������ݣ� CVBF_Terrain��¼���ڴ���ʵ�ʵ�geometry��
	���з��ص�����ֵ������getSRS()�еĿռ�ο������� */
class OSGEARTH_EXPORT CVBF_Terrain : public ::CVBF_Referenced, public IVBF_TerrainHeightProvider
{
public:

    // ��ȡ��ص�ͼ�ĸ�Ҫ��Ϣ
    const CVBF_Profile* getProfile() const { return _profile.get(); }

    // ��ȡ��ص�ͼ�Ŀռ�ο�
    const CVBF_SpatialReference* getSRS() const { return _profile->getSRS(); }

    // �Ƿ���ECEF����ϵ
    bool isGeocentric() const { return _geocentric; }


public: // Intersection Utilities

    // ��ȡָ����ĸ̣߳�out_heightAboveMSLֵ�������MSL (mean sea level)�ĸ߶ȣ�out_heightAboveEllipsoid������ڲο�������ĸ߳�
    bool getHeight( const CVBF_SpatialReference* srs, double x, double y, 
			        double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const;

    // ͬ�ϣ���ָ����a subgraph patch
    bool getHeight( osg::IVBF_SGNode*  patch, const CVBF_SpatialReference* srs, double x, double y,
					double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const;

    // ��ȡ������������꣨mx��myΪ������꣩
    bool getWorldCoordsUnderMouse( osg::IVBF_ViewBrief* view, float mx, float my, osg::Vec3d& out_world ) const;

    bool getWorldCoordsUnderMouse( osg::IVBF_ViewBrief* view, float mx, float my, osg::Vec3d& out_world, ref_ptr<osg::IVBF_SGNode>& out_node ) const;

public:

    // ���/�Ƴ����θ��»ص�
    void addTerrainCallback(IVBF_TerrainCallback* callback);
    void removeTerrainCallback(IVBF_TerrainCallback* callback);
        

public:

    // ���ܽڵ����
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


//һ��CVBF TerrainPatch�ǵ��ε�һ���������Ӽ��������ڸ̲߳�ѯ�����̰߳�ȫ�ġ����Ƿ���ģ����Բ��ڳ���ͼ�С�
class OSGEARTH_EXPORT CVBF_TerrainPatch : public IVBF_TerrainHeightProvider
{
public:
    CVBF_TerrainPatch( osg::IVBF_SGNode* patch, const CVBF_Terrain* terrain );

    // ��ѯָ����ĸ߳�
    bool getHeight( const CVBF_SpatialReference* srs, double x, double y, 
					double* out_heightAboveMSL, double* out_heightAboveEllipsoid =0L) const;

protected:
    ref_ptr<osg::IVBF_SGNode>	_patch;
    ref_ptr<const CVBF_Terrain>	_terrain;
};


#endif // OSGEARTH_TERRAIN_H
