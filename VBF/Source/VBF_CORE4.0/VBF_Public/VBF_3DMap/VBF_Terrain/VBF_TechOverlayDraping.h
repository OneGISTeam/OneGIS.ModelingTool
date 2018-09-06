#ifndef OSGEARTH_OVERLAY_DRAPING_TECHNIQUE
#define OSGEARTH_OVERLAY_DRAPING_TECHNIQUE

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeDecoratorTerrainOverlay.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTexGen.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

class CVBFO_SGNodeTerrainEngine;



// ���Ǽ��������ر���һ�����ǣ����ӣ�����ͶӰ�������ǵ�ģ�ͣ��磬���ر�Ч����
// ���θ��ǽڵ�ڵ��Զ���װ�ڵ�ͼ�ڵ��£�������ʾ�����ر�����Ϊtrue��ʸ������

class OSGEARTH_EXPORT CVBF_TechOverlayDraping : public CVBF_TechOverlay
{
public:
    CVBF_TechOverlayDraping();

	// ��ȷָ����������ռ�õ�����Ԫ�����Ѹö������CVBFO_SGNodeMapʱ�����Զ�����һ�����е�����Ԫ������ͨ������²�����øú���
    void setTextureUnit( int unit );
    int getTextureUnit() const { return *_textureUnit; }

	// ��������Ĵ�С��Ĭ��Ϊ4096���Կ������֧�ֳߴ�
    void setTextureSize( int texSize );
    int getTextureSize() const { return *_textureSize; }

	// ��ͶӰ��������Ƿ�����MipMap�����ÿ�������Ӿ�Ч������ռ�ø�����Դ棬��Ӱ�����ܣ�������Ϊ��̬ʱ������ĳЩGPU�������������ͣ��磬Intel GMA��
    void setMipMapping( bool value );
    bool getMipMapping() const { return _mipmapping; }

	// ��RTT����Ƿ����û�ϣ�blending����Ĭ��Ϊtrue��������ηǳ���ʱ���ָܷ�Ӱ����ܻ�ص����
    void setOverlayBlending( bool value );
    bool getOverlayBlending() const { return _rttBlending; }

	// ����/��ȡ�Ƿ�� RTT���������ģ�建�棨stencil buffer����Ĭ��Ϊtrue��һЩ���Կ�֧�ֵĲ���
    void setAttachStencil( bool value );
    bool getAttachStencil() const;


public: // CVBF_TechOverlay

    virtual bool hasData( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params) const;

    void reestablish( CVBFO_SGNodeTerrainEngine* engine );

    void preCullTerrain( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv );

    void cullOverlayGroup( CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params, osgUtil::CullVisitor* cv );

    void onInstall( CVBFO_SGNodeTerrainEngine* engine );
    void onUninstall( CVBFO_SGNodeTerrainEngine* engine );


protected:
    virtual ~CVBF_TechOverlayDraping() { }

private:
    CVBF_Optional<int>                 m_opExplicitTextureUnit;
    CVBF_Optional<int>                 _textureUnit;
    CVBF_Optional<int>                 _textureSize;
    bool                          _useShaders;
    bool                          _mipmapping;
    bool                          _rttBlending;
    bool                          _attachStencil;

    struct TechData : public ::CVBF_Referenced
    {
        ref_ptr<osg::Uniform>    _texGenUniform;
        ref_ptr<osg::TexGen>     _texGen;
    };

private:
        
    void setUpCamera(CVBFO_SGNodeDecoratorTerrainOverlay::TechRTTParams& params);
};



#endif //OSGEARTH_OVERLAY_DRAPING_TECHNIQUE
