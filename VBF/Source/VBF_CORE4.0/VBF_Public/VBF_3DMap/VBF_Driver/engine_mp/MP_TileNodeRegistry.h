#ifndef OSGEARTH_ENGINE_MP_TILE_NODE_REGISTRY
#define OSGEARTH_ENGINE_MP_TILE_NODE_REGISTRY 1

#include "Common"
#include "MP_TileNode.h"
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <map>

using namespace osgEarth;

// 持有数据驱动器创建的每个瓦片节点的引用
class CMP_TileNodeRegistry : public ::CVBF_Referenced
{
public:
	typedef std::map< CVBF_TileKey, ref_ptr<CMP_TileNode> > TileNodeMap;

	// Proprtype for a locked tileset operation (see run)
	struct Operation 
	{
		virtual void operator()( TileNodeMap& tiles ) =0;
	};

	struct ConstOperation 
	{
		virtual void operator()( const TileNodeMap& tiles ) const =0;
	};

public:
	CMP_TileNodeRegistry( const std::string& name );

	virtual ~CMP_TileNodeRegistry() { }


	void add( CMP_TileNode* tile );	// 添加一个瓦片节点
	void add( const TileNodeVector& tiles ); // 添加多个瓦片节点
	void remove( CMP_TileNode* tile );// 移除一个瓦片节点

	bool get( const CVBF_TileKey& key, ref_ptr<CMP_TileNode>& out_tile );// 查找一个瓦片节点
	bool take( const CVBF_TileKey& key, ref_ptr<CMP_TileNode>& out_tile ); // 查找并取出一个瓦片节点

	bool empty() const;// 是否为空

	// 运行一个操作（不锁定瓦片集合）
	void run( Operation& op );

	// 运行一个操作（锁定瓦片集合）
	void run( const ConstOperation& op ) const;

protected:

	std::string                 m_sName;
	TileNodeMap                 _tiles;
	mutable CVBF_ReadWriteMutex _tilesMutex;
};

#endif // OSGEARTH_ENGINE_MP_TILE_NODE_REGISTRY
