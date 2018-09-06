#ifndef OSGEARTH_ENGINE_MP_TILE_NODE
#define OSGEARTH_ENGINE_MP_TILE_NODE 1

#include "Common"
#include "MP_TileModel.h"
#include "MP_TileModelCompiler.h"
#include <VBF_3DMap/VBF_Terrain/VBFO_GeoLocator.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <vector>

using namespace osgEarth;

// ��Ƭ�ڵ㣬��Ӧһ��Ψһ�ļ�ֵ
class CMP_TileNode : public osg::CVBF_SGNodeGroup
{
public:
	CMP_TileNode( const CVBF_TileKey& key, CVBFO_GeoLocator* keyLocator );

	// ��Ƭ�ļ�ֵ
	const CVBF_TileKey& getKey() const { return _key; }

	// �����ڵ㼸���壨geometry��������ģ��
	void setTileModel( CMP_TileModel* model );
	CMP_TileModel* getTileModel() { return _model.get(); }

	/**
	* @param[in ] compiler     Compiler that will compiler the model
	* @param[in ] releaseModel Whether to deallocate the tile model after compilation
	*/
	// ����Ƭ����ģ�ͱ���Ϊ�����壨geometry��
	bool compile( CMP_TileModelCompiler* compiler, bool releaseModel =true );

	// ��Ƭ������Ķ�λ��
	CVBFO_GeoLocator* getLocator() const { return _locator.get(); }

	// �������Ƭģ�͹����Ĺ������ݼ�
	osg::StateSet* getPublicStateSet() const { return _publicStateSet; }

	// �ڵ�����غ���
	virtual void traverse( class osg::NodeVisitor& nv );

protected:

	virtual ~CMP_TileNode();

	bool                      _cullTraversed;
	CVBF_TileKey              _key;
	ref_ptr<CVBFO_GeoLocator>  _locator;
	ref_ptr<CMP_TileModel>		   _model;
	osg::StateSet*            _publicStateSet;
	osg::Uniform*             _born;
};


typedef std::vector< ref_ptr<CMP_TileNode> > TileNodeVector;


// Marker class
class CMP_TileNodeGroup : public osg::CVBF_SGNodeGroup
{
public:
	CMP_TileNodeGroup() : osg::CVBF_SGNodeGroup() { }
};

#endif // OSGEARTH_ENGINE_MP_TILE_NODE
