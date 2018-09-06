#ifndef OSGEARTH_ENGINE_MP_TILE_NODE_REGISTRY
#define OSGEARTH_ENGINE_MP_TILE_NODE_REGISTRY 1

#include "Common"
#include "MP_TileNode.h"
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <map>

using namespace osgEarth;

// ��������������������ÿ����Ƭ�ڵ������
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


	void add( CMP_TileNode* tile );	// ���һ����Ƭ�ڵ�
	void add( const TileNodeVector& tiles ); // ��Ӷ����Ƭ�ڵ�
	void remove( CMP_TileNode* tile );// �Ƴ�һ����Ƭ�ڵ�

	bool get( const CVBF_TileKey& key, ref_ptr<CMP_TileNode>& out_tile );// ����һ����Ƭ�ڵ�
	bool take( const CVBF_TileKey& key, ref_ptr<CMP_TileNode>& out_tile ); // ���Ҳ�ȡ��һ����Ƭ�ڵ�

	bool empty() const;// �Ƿ�Ϊ��

	// ����һ����������������Ƭ���ϣ�
	void run( Operation& op );

	// ����һ��������������Ƭ���ϣ�
	void run( const ConstOperation& op ) const;

protected:

	std::string                 m_sName;
	TileNodeMap                 _tiles;
	mutable CVBF_ReadWriteMutex _tilesMutex;
};

#endif // OSGEARTH_ENGINE_MP_TILE_NODE_REGISTRY
