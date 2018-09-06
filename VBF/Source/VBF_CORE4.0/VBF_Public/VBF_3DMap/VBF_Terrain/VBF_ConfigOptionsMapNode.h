#ifndef OSGEARTH_MAP_NODE_OPTIONS_H
#define OSGEARTH_MAP_NODE_OPTIONS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_HTTPClient.h>
#include <VBF_3DMap/VBF_Terrain/VBF_ConfigOptionsTerrain.h>
#include <set>


// MapNode的配置项
class OSGEARTH_EXPORT CVBF_ConfigOptionsMapNode : public CVBF_ConfigOptions
{
public:
    CVBF_ConfigOptionsMapNode( const CVBF_Config& conf =CVBF_Config() );
    CVBF_ConfigOptionsMapNode( const CVBF_ConfigOptionsTerrain& terrainOpts );
    CVBF_ConfigOptionsMapNode( const CVBF_ConfigOptionsMapNode& rhs );
    virtual ~CVBF_ConfigOptionsMapNode();

	// 代理服务器的主机名/端口（hostname/port），用于HTTP通信。默认为没有代理（Default = no proxy）
    const CVBF_Optional<CVBF_ProxySettings>& proxySettings() const { return _proxySettings; }
		  CVBF_Optional<CVBF_ProxySettings>& proxySettings() { return _proxySettings; }

	// 是否地图仅用缓存，默认为false。（Whether the map should be run exclusively off of the cache）
	const CVBF_Optional<bool>& cacheOnly() const { return m_boCacheOnly; }
		  CVBF_Optional<bool>& cacheOnly() { return m_boCacheOnly; }

	// 是否启用光照
    const CVBF_Optional<bool>& enableLighting() const { return m_boEnableLighting; } 
		  CVBF_Optional<bool>& enableLighting() { return m_boEnableLighting; }

	// 是否启用混合on the overlay decorator subgraph. See CVBFO_SGNodeDecoratorTerrainOverlay
    const CVBF_Optional<bool>& overlayBlending() const { return m_boOverlayBlending; }
          CVBF_Optional<bool>& overlayBlending() { return m_boOverlayBlending; }

	// RTT相机的覆盖纹理的大小
    const CVBF_Optional<unsigned>& overlayTextureSize() const { return m_noOverlayTextureSize; }
		  CVBF_Optional<unsigned>& overlayTextureSize() { return m_noOverlayTextureSize; }

	// 覆盖纹理是否使用MipMap
    const CVBF_Optional<bool>& overlayMipMapping() const { return m_boOverlayMipMapping; }
		  CVBF_Optional<bool>& overlayMipMapping() { return m_boOverlayMipMapping; }


	// 是否把RTT相机关联到模板缓冲
    const CVBF_Optional<bool>& overlayAttachStencil() const { return m_boOverlayAttachStencil; }
          CVBF_Optional<bool>& overlayAttachStencil() { return m_boOverlayAttachStencil; }

	// 获取/设置地形引擎（渲染地形表面）
    const CVBF_ConfigOptionsTerrain& getTerrainOptions() const;
    void setTerrainOptions( const CVBF_ConfigOptionsTerrain& options );
    
public:
	// 获取配置/合并
    virtual CVBF_Config getConfig() const;
    virtual void mergeConfig( const CVBF_Config& conf );

//    static std::string OPTIONS_TAG;

private:            

    CVBF_Optional<bool>					m_boCacheOnly;			// 是否地图仅用缓存
    CVBF_Optional<bool>					m_boEnableLighting;		// 是否启用光照

    CVBF_Optional<bool>					m_boOverlayVertexWarping;
    CVBF_Optional<bool>					m_boOverlayBlending;
    CVBF_Optional<unsigned>				m_noOverlayTextureSize;
    CVBF_Optional<bool>					m_boOverlayMipMapping;
    CVBF_Optional<bool>					m_boOverlayAttachStencil;

    CVBF_Optional<CVBF_ProxySettings>	_proxySettings;    
	CVBF_Optional<CVBF_Config>			_terrainOptionsConf;
    CVBF_ConfigOptionsTerrain*			m_pTerrainOptions;
};


#endif // OSGEARTH_MAP_NODE_OPTIONS_H
