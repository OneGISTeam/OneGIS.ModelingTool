#ifndef __VBF_OCEAN_FLOOR_TEXTURE_H__
#define __VBF_OCEAN_FLOOR_TEXTURE_H__


#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Base/observer_ptr>


// ϸ�������ں���ʹ��ϸ���������ֽ�ɢЧ��
class OSGEARTH_EXPORT CVBF_OceanFloorTexture
{
public:
    CVBF_OceanFloorTexture();
    virtual ~CVBF_OceanFloorTexture();

	// �Ƿ�����������Ч����ֻ�м����˺������ʱ���ܿ�����
	void Enable(bool bEnable);
	bool IsEnabled()  { return m_bEnable; }

	// ������ɫ���ļ���·��
    void SetShaderFilePath(const std::string& strPath) { m_strShaderFilePath = strPath; }

    // ��ϸ��������������Σ�����NULL�������ϸ������
    void SetTerrainNode(osg::IVBF_SGNode* pTerrainNode);

	// �������Ŀǰ�Ƿ�λ��ˮ�£�ÿ֡����Ҫ���ⲿ���ã�
    void SetUnderWater(bool bUnderWater);

    // ����/��ȡ��ʼʹ��ϸ�������LOD��
    void SetBaseLod(unsigned int nLod);
    unsigned int GetBaseLod() const { return m_nBaseLod; }

    // ����/��ȡ����(0=none, 1=full)
    void SetIntensity( float value );
    float GetIntensity() const { return m_fIntensity; }

    // ����/��ȡ��Ҫ��ϸ���������ϵ���ɫ����ϸ�������RGBΪ��˹�ϵ��
    void SetBlendColor(const osg::Vec3f& color);
    osg::Vec3f GetBlendColor() { return m_colorBlend; }

    // ����/��ȡϸ�������ͼ��
    void SetImage(const osg::Image* pImage);
    const osg::Image* GetImage() const { return m_ipTexture->getImage(); }

    // ����/��ȡGPUʹ�õ�����Ԫ��Ĭ��Ϊ2��
    // ע�⣺����CVBF_TechOverlayDrapingռ��������Ԫ1�����Դ˴�ֻ��ʹ������Ԫ2
    void SetTextureUnit( unsigned unit );
    unsigned SetTextureUnit() const { return m_nTextureUnit; }
	

protected:
	bool						m_bEnable;				// �Ƿ�����������Ч��
    std::string                 m_strShaderFilePath;    // ��ɫ���ļ����ڵ�·��
    unsigned int                m_nTextureUnit;			// �������ڵĵ�Ԫ
    ref_ptr<osg::Texture2D>     m_ipTexture;			// ����ָ��
    float                       m_fIntensity;			// ��������
    unsigned int                m_nBaseLod;				// ��������ʱ����СLod
    osg::Vec3                   m_colorBlend;			// �����ɫ

	// ��ɫ������
    ref_ptr<osg::Uniform>       m_ipUniformIntensity;
    ref_ptr<osg::Uniform>       m_ipUniformBaseLod;
    ref_ptr<osg::Uniform>       m_ipUniformTexture;
    ref_ptr<osg::Uniform>       m_ipUniformUnderWater;  // ���Ŀǰ�Ƿ�λ��ˮ��
    ref_ptr<osg::Uniform>       m_ipUniformBlendColor;  // ��Ҫ��ϸ���������ϵ���ɫ

	// ��¼ϸ���������󶨵���Ⱦ״̬���Ա�������������ж���������
	ref_ptr<osg::StateSet>		m_ipStateSet;
};

#endif
