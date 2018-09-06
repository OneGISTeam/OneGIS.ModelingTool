#ifndef OSGEARTH_MAP_NODE_OPTIONS_H
#define OSGEARTH_MAP_NODE_OPTIONS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_HTTPClient.h>
#include <VBF_3DMap/VBF_Terrain/VBF_ConfigOptionsTerrain.h>
#include <set>


// MapNode��������
class OSGEARTH_EXPORT CVBF_OptionsMapNode : public CVBF_Options
{
public:
    CVBF_OptionsMapNode( const CVBF_Config& conf =CVBF_Config() );
    CVBF_OptionsMapNode( const CVBF_OptionsTerrain& terrainOpts );
    CVBF_OptionsMapNode( const CVBF_OptionsMapNode& rhs );
    virtual ~CVBF_OptionsMapNode();

    CVBF_OptionsMapNode& operator = ( const CVBF_OptionsMapNode& rhs );

	// �����������������/�˿ڣ�hostname/port��������HTTPͨ�š�Ĭ��Ϊû�д���Default = no proxy��
    const CVBF_Optional<CVBF_ProxySettings>& proxySettings() const { return _proxySettings; }
		  CVBF_Optional<CVBF_ProxySettings>& proxySettings() { return _proxySettings; }

	// �Ƿ��ͼ���û��棬Ĭ��Ϊfalse����Whether the map should be run exclusively off of the cache��
	const CVBF_Optional<bool>& cacheOnly() const { return m_boCacheOnly; }
		  CVBF_Optional<bool>& cacheOnly() { return m_boCacheOnly; }

	// �Ƿ����ù���
    const CVBF_Optional<bool>& enableLighting() const { return m_boEnableLighting; } 
		  CVBF_Optional<bool>& enableLighting() { return m_boEnableLighting; }

	// �Ƿ����û��on the overlay decorator subgraph. See CVBFO_SGNodeDecoratorTerrainOverlay
    const CVBF_Optional<bool>& overlayBlending() const { return m_boOverlayBlending; }
          CVBF_Optional<bool>& overlayBlending() { return m_boOverlayBlending; }

	// RTT����ĸ�������Ĵ�С
    const CVBF_Optional<unsigned>& overlayTextureSize() const { return m_noOverlayTextureSize; }
		  CVBF_Optional<unsigned>& overlayTextureSize() { return m_noOverlayTextureSize; }

	// ���������Ƿ�ʹ��MipMap
    const CVBF_Optional<bool>& overlayMipMapping() const { return m_boOverlayMipMapping; }
		  CVBF_Optional<bool>& overlayMipMapping() { return m_boOverlayMipMapping; }


	// �Ƿ��RTT���������ģ�建��
    const CVBF_Optional<bool>& overlayAttachStencil() const { return m_boOverlayAttachStencil; }
          CVBF_Optional<bool>& overlayAttachStencil() { return m_boOverlayAttachStencil; }

	// ��ȡ/���õ������棨��Ⱦ���α��棩
    const CVBF_OptionsTerrain& getTerrainOptions() const;
    void setTerrainOptions( const CVBF_OptionsTerrain& options );
    
public:
	// ��ȡ����/�ϲ�
    virtual CVBF_Config getConfig() const;
    virtual void mergeConfig( const CVBF_Config& conf );

//    static std::string OPTIONS_TAG;

private:            

    CVBF_Optional<bool>					m_boCacheOnly;			// �Ƿ��ͼ���û���
    CVBF_Optional<bool>					m_boEnableLighting;		// �Ƿ����ù���

    CVBF_Optional<bool>					m_boOverlayVertexWarping;
    CVBF_Optional<bool>					m_boOverlayBlending;
    CVBF_Optional<unsigned>				m_noOverlayTextureSize;
    CVBF_Optional<bool>					m_boOverlayMipMapping;
    CVBF_Optional<bool>					m_boOverlayAttachStencil;

    CVBF_Optional<CVBF_ProxySettings>	_proxySettings;    
	CVBF_Optional<CVBF_Config>			_terrainOptionsConf;
    CVBF_OptionsTerrain*			m_pTerrainOptions;
};


#endif // OSGEARTH_MAP_NODE_OPTIONS_H
