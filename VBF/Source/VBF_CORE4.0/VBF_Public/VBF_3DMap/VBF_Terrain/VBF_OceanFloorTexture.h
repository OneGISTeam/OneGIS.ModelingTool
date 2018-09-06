#ifndef __VBF_OCEAN_FLOOR_TEXTURE_H__
#define __VBF_OCEAN_FLOOR_TEXTURE_H__


#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Base/observer_ptr>


// 细节纹理：在海底使用细节纹理，表现焦散效果
class OSGEARTH_EXPORT CVBF_OceanFloorTexture
{
public:
    CVBF_OceanFloorTexture();
    virtual ~CVBF_OceanFloorTexture();

	// 是否开启海底纹理效果（只有加载了海洋组件时才能开启）
	void Enable(bool bEnable);
	bool IsEnabled()  { return m_bEnable; }

	// 设置着色器文件的路径
    void SetShaderFilePath(const std::string& strPath) { m_strShaderFilePath = strPath; }

    // 把细节纹理关联到地形，设置NULL解除关联细节纹理
    void SetTerrainNode(osg::IVBF_SGNode* pTerrainNode);

	// 设置相机目前是否位于水下（每帧都需要由外部调用）
    void SetUnderWater(bool bUnderWater);

    // 设置/获取开始使用细节纹理的LOD级
    void SetBaseLod(unsigned int nLod);
    unsigned int GetBaseLod() const { return m_nBaseLod; }

    // 设置/获取亮度(0=none, 1=full)
    void SetIntensity( float value );
    float GetIntensity() const { return m_fIntensity; }

    // 设置/获取需要与细节纹理相混合的颜色（与细节纹理的RGB为相乘关系）
    void SetBlendColor(const osg::Vec3f& color);
    osg::Vec3f GetBlendColor() { return m_colorBlend; }

    // 设置/获取细节纹理的图像
    void SetImage(const osg::Image* pImage);
    const osg::Image* GetImage() const { return m_ipTexture->getImage(); }

    // 设置/获取GPU使用的纹理单元（默认为2）
    // 注意：由于CVBF_TechOverlayDraping占用了纹理单元1，所以此处只能使用纹理单元2
    void SetTextureUnit( unsigned unit );
    unsigned SetTextureUnit() const { return m_nTextureUnit; }
	

protected:
	bool						m_bEnable;				// 是否开启海底纹理效果
    std::string                 m_strShaderFilePath;    // 着色器文件所在的路径
    unsigned int                m_nTextureUnit;			// 纹理所在的单元
    ref_ptr<osg::Texture2D>     m_ipTexture;			// 纹理指针
    float                       m_fIntensity;			// 纹理亮度
    unsigned int                m_nBaseLod;				// 开启纹理时的最小Lod
    osg::Vec3                   m_colorBlend;			// 纹理混色

	// 着色器变量
    ref_ptr<osg::Uniform>       m_ipUniformIntensity;
    ref_ptr<osg::Uniform>       m_ipUniformBaseLod;
    ref_ptr<osg::Uniform>       m_ipUniformTexture;
    ref_ptr<osg::Uniform>       m_ipUniformUnderWater;  // 相机目前是否位于水下
    ref_ptr<osg::Uniform>       m_ipUniformBlendColor;  // 需要与细节纹理相混合的颜色

	// 记录细节纹理所绑定的渲染状态，以便在析构函数中卸载相关内容
	ref_ptr<osg::StateSet>		m_ipStateSet;
};

#endif
