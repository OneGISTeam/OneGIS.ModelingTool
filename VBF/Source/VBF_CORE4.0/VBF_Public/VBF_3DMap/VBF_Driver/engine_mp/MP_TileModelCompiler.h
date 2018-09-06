#ifndef OSGEARTH_ENGINE_MP_TILE_MODEL_COMPILER
#define OSGEARTH_ENGINE_MP_TILE_MODEL_COMPILER 1

#include "Common"
#include "MP_TileModel.h"
#include "MP_ConfigOptionsTerrain.h"

#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_GeoLocator.h>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SceneGraph/Array>

using namespace osgEarth;


// CMP_TileModelCompiler使用的缓存，可以在编译过程中共享公共数据。
// 编译器是thread-locked的，因此每个编译器有一个独立的缓存
// 重要提示：任何存储在缓存中的数组必须有自己独有的VBO。调用array->setVertexBufferObject( new osg::VertexBufferObject() )
// 进行设置，可以阻止非线程安全的buffer object共享

struct CMP_CompilerCache
{
	// 纹理坐标数组 缓存定义
	struct TexCoordTableKey 
	{
		ref_ptr<const CVBFO_GeoLocator> _locator;

		osg::Vec4d _mat;
		unsigned   _cols, _rows;
	};

	typedef std::pair< TexCoordTableKey, ref_ptr<osg::Vec2Array> > LocatorTexCoordPair;

	struct TexCoordArrayCache : public std::list<LocatorTexCoordPair>
	{
		ref_ptr<osg::Vec2Array>& get( const osg::Vec4d& mat, unsigned cols, unsigned rows );
	};

	TexCoordArrayCache _surfaceTexCoordArrays;
	TexCoordArrayCache _skirtTexCoordArrays;
};



// 瓦片数据模型编译器，建立真正的瓦片叶节点。和KeyNodeFactory一起使用，每个线程有一个本类的实例
class CMP_TileModelCompiler : public ::CVBF_Referenced
{
public:
	CMP_TileModelCompiler( const CVBF_LayersMask& masks,int textureImageUnit, 
		bool optimizeTriangleOrientation, const CMP_ConfigOptionsTerrain& options);


	// 编译一个瓦片模型，加入到场景图（节点），该节点将包括一个MatrixTransform坐标变换节点来定位瓦片数据
	bool compile( const CMP_TileModel* model, osg::IVBF_SGNode*& out_node, osg::StateSet*&  out_stateSet );

protected:
	const CVBF_LayersMask&                    _masks;
	int                                       _textureImageUnit;
	bool                                      _optimizeTriOrientation;
	const CMP_ConfigOptionsTerrain&        _options;
	ref_ptr<osg::Drawable::CullCallback> _cullByTraversalMask;
	CMP_CompilerCache                             _cache;
};

#endif // OSGEARTH_ENGINE_MP_TILE_MODEL_COMPILER
