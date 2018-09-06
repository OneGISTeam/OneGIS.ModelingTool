#ifndef OSGEARTH_ENGINE_MP_QUICK_RELEASE_GL_OBJECTS
#define OSGEARTH_ENGINE_MP_QUICK_RELEASE_GL_OBJECTS 1

#include "Common"
#include "MP_TileNodeRegistry.h"
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>

// Ƕ�׵�DrawCallback
class CMP_NestingDrawCallback : public osg::Camera::DrawCallback
{
public:
	CMP_NestingDrawCallback( osg::Camera::DrawCallback* pNext ) : m_ipNext(pNext) { }

	virtual void operator()( osg::RenderInfo& renderInfo ) const
	{
		dispatch( renderInfo );
	}

	ref_ptr<osg::Camera::DrawCallback> m_ipNext;

protected:
	void dispatch( osg::RenderInfo& renderInfo ) const
	{
		if ( m_ipNext ) m_ipNext->operator ()( renderInfo );
	}
private:
};

// �ͷ�GL����Ĳ���
class CMP_ReleaseOperation : public CMP_TileNodeRegistry::Operation
{
public:
	CMP_ReleaseOperation( osg::State* state ) : _state(state) { }

	void operator()( CMP_TileNodeRegistry::TileNodeMap& tiles )
	{
		for( CMP_TileNodeRegistry::TileNodeMap::iterator i = tiles.begin(); i != tiles.end(); ++i )
		{
			i->second.get()->releaseGLObjects( _state );
		}
		tiles.clear();
	}
private:
	osg::State* _state;
};
// һ���򵥵Ļ��ƻص������õ�Camera�������ͷ���������Ƭ��GL�ڴ�(instead of wating for OSG to do it in the future).
class CMP_CallbackQuickReleaseGLObjects : public CMP_NestingDrawCallback
{
public:
	CMP_CallbackQuickReleaseGLObjects( CMP_TileNodeRegistry* pTiles, osg::Camera::DrawCallback* nextCB) : CMP_NestingDrawCallback( nextCB ),
		m_ipTilesToRelease(pTiles) 
	{ 
	}

	// ����DrawCallback�ĺ���
	void operator()( osg::RenderInfo& renderInfo ) const
	{
		dispatch( renderInfo );
		if ( m_ipTilesToRelease->empty() ) return;

		CMP_ReleaseOperation op(renderInfo.getState());
		m_ipTilesToRelease->run( op );
	}
private:
	ref_ptr<CMP_TileNodeRegistry> m_ipTilesToRelease;
};

#endif // OSGEARTH_ENGINE_MP_QUICK_RELEASE_GL_OBJECTS
