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


// CMP_TileModelCompilerʹ�õĻ��棬�����ڱ�������й��������ݡ�
// ��������thread-locked�ģ����ÿ����������һ�������Ļ���
// ��Ҫ��ʾ���κδ洢�ڻ����е�����������Լ����е�VBO������array->setVertexBufferObject( new osg::VertexBufferObject() )
// �������ã�������ֹ���̰߳�ȫ��buffer object����

struct CMP_CompilerCache
{
	// ������������ ���涨��
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



// ��Ƭ����ģ�ͱ�������������������ƬҶ�ڵ㡣��KeyNodeFactoryһ��ʹ�ã�ÿ���߳���һ�������ʵ��
class CMP_TileModelCompiler : public ::CVBF_Referenced
{
public:
	CMP_TileModelCompiler( const CVBF_LayersMask& masks,int textureImageUnit, 
		bool optimizeTriangleOrientation, const CMP_ConfigOptionsTerrain& options);


	// ����һ����Ƭģ�ͣ����뵽����ͼ���ڵ㣩���ýڵ㽫����һ��MatrixTransform����任�ڵ�����λ��Ƭ����
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
