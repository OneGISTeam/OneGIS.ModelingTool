#ifndef OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD
#define OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD 1

#include "Common"
#include "MP_TileNode.h"
#include "MP_TileNodeRegistry.h"
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapFrame.h>



using namespace osgEarth;

// CMP_Geometry多次绘制它的图元集合，每一个"layer"一次。 一次裁剪（cull）渲染多遍（multipass）数据
class CMP_Geometry : public osg::Geometry
{
public:

	struct Layer
	{
        osgEarth::UID              _layerID;
        ref_ptr<const CVBF_LayerTerrainImage> _imageLayer;
		ref_ptr<osg::Texture>     _tex;
		ref_ptr<osg::Vec2Array>   _texCoords;
		ref_ptr<osg::Vec2Array>   _tileCoords;
		float                     _alphaThreshold;
        ref_ptr<CMP_TileColorData>   m_ColorData;

		// 支持std::find
		inline bool operator == (const osgEarth::UID& rhs) const  { return _layerID == rhs; }
	};

public:
    mutable CVBF_MapFrame           _map;
    mutable std::vector<Layer>      _layers;
	mutable CVBF_Mutex             _mapSyncMutex;
	mutable ref_ptr<osg::Uniform>   _layerUIDUniform;
	mutable ref_ptr<osg::Uniform>   _layerOrderUniform;
	mutable ref_ptr<osg::Uniform>   _opacityUniform;
    int                             _textureImageUnit;

public:

	CMP_Geometry(const CVBF_Map* map, int textureImageUnit);

	// 渲染图元集合（所有的遍（all passes））
	void renderPrimitiveSets(osg::State& state, bool usingVBOs) const;


	// osg::Geometry的重载函数
	void releaseGLObjects(osg::State* state) const;
	void compileGLObjects( osg::RenderInfo& renderInfo ) const;
	void drawImplementation(osg::RenderInfo& renderInfo) const;

        ///XAHG_2016-01-05
        //virtual void accept(osg::PrimitiveFunctor& pf) const;


public:
	META_Object(osgEarth, CMP_Geometry);
	CMP_Geometry() : osg::Geometry(), _map(0L) { }
	CMP_Geometry(const CMP_Geometry& rhs, const osg::CopyOp& cop) : osg::Geometry(rhs, cop), _map(rhs._map) { }
	virtual ~CMP_Geometry() { }
};

#endif // OSGEARTH_ENGINE_MP_CUSTOM_PAGED_LOD
