//**********************************************************************************
// 文件名：  VBF_Capabilities.h
// 描述：    获取显卡的各种渲染能力信息，该信息以为单实例方式存储在osgEarth::Registry中
// 作者:     杜莹
// 日期:     2013-06-21
//**********************************************************************************

#ifndef __VBF_CAPABILITIES_H__
#define __VBF_CAPABILITIES_H__


#include <VBF_3DMap/VBF_Terrain/Export>
#include <VBF_Base/VBF_Referenced.h>
#include <string>


// 便于使用友元类
namespace osgEarth
{
	class Registry;
}

class OSGEARTH_EXPORT CVBF_Capabilities : public ::CVBF_Referenced
{
public:
        
	/** 获取固定管线中支持的最大纹理单元数 （maximum # of texture units） */
    int getMaxFFPTextureUnits() const { return _maxFFPTextureUnits; }
        
	/** 获取片段着色器中支持的最大纹理图像单元数（maximum # of texture image units） */
    int getMaxGPUTextureUnits() const { return _maxGPUTextureUnits; }
        
	/** 获取片段着色器中支持的最大纹理坐标集合数（maximum # of texture coordinate sets） */
    int getMaxGPUTextureCoordSets() const { return _maxGPUTextureCoordSets; }
        
	/** 获取显卡支持的最大纹理尺寸（单位：像素） */
    int getMaxTextureSize() const { return _maxTextureSize; }
        
	/** 获取显卡支持的、又不会影响渲染效率的最大纹理尺寸，同时又不会影响渲染效率（单位：像素，该值与显卡厂商有关） */
    int getMaxFastTextureSize() const { return _maxFastTextureSize; }
       
	/** 获取显卡支持的最大光照数 */
    int getMaxLights() const { return _maxLights; }
        
	/** 获取显卡支持的深度缓存的bit位数 */
    int getDepthBufferBits() const { return _depthBits; }
       
	/** 判断显卡是否支持着色器语言GLSL */
    bool supportsGLSL(float minimumVersion =1.0f) const { return _supportsGLSL && _GLSLversion >= minimumVersion; }
        
	/** 获取GLSL的版本 */
    float getGLSLVersion() const { return _GLSLversion; }
        
	/** 获取显卡厂商，如"NVIDIA Corporation" */
    const std::string& getVendor() const { return _vendor; }

    /** 获取显卡型号，如"GeForce GT 650M/PCIe/SSE2" */
    const std::string& getRenderer() const { return _renderer; }
        
	/** 获取显卡驱动的版本 */
    const std::string& getVersion() const { return _version; }
        
	/** 判断显卡是否支持纹理数组 */
    bool supportsTextureArrays() const { return _supportsTextureArrays; }

    /** 判断显卡是否支持3D纹理 */
    bool supportsTexture3D() const { return _supportsTexture3D; }

    /** 判断显卡是否支持多纹理 */
    bool supportsMultiTexture() const { return _supportsMultiTexture; }
        
	/** 判断显卡是否支持OpenGL扩展：GL_EXT_stencil_wrap */
    bool supportsStencilWrap() const { return _supportsStencilWrap; }
        
	/** 判断显卡是否支持OpenGL扩展：GL_EXT_stencil_two_side */
    bool supportsTwoSidedStencil() const { return _supportsTwoSidedStencil; }
        
	/** 判断显卡是否支持OpenGL扩展：GL_ARB_shader_texture_lod */
    bool supportsTexture2DLod() const { return _supportsTexture2DLod; }
        
	/** 判断显卡是否支持用一个新的mipmap图像更新一个现有的纹理 */
    bool supportsMipmappedTextureUpdates() const { return _supportsMipmappedTextureUpdates; }
        
	/** 判断显卡是否支持OpenGL扩展：GL_EXT_packed_depth_stencil 或 GL_OES_packed_depth_stencil */
    bool supportsDepthPackedStencilBuffer() const { return _supportsDepthPackedStencilBuffer; }
        
	/** 判断显卡是否支持OpenGL扩展：GL_ARB_occlusion_query */
    bool supportsOcclusionQuery() const { return _supportsOcclusionQuery; }
        
	/** 判断显卡是否支持DrawInstanced渲染方式 */
    bool supportsDrawInstanced() const { return _supportsDrawInstanced; }
        
	/** 判断显卡是否支持Uniform Buffer Objects */
    bool supportsUniformBufferObjects() const { return _supportsUniformBufferObjects; }
        
	/** 获取显卡支持的uniform buffer block的最大字节数 */
    int getMaxUniformBlockSize() const { return _maxUniformBlockSize; }
        
	/** 对于数据基本不变的几何对象，是否优先使用显示列表（与VBO相比）*/
    bool preferDisplayListsForStaticGeometry() const { return _preferDLforStaticGeom; }

protected:
    CVBF_Capabilities();
    virtual ~CVBF_Capabilities() { }

private:
    int					_maxFFPTextureUnits;
    int					_maxGPUTextureUnits;
    int					_maxGPUTextureCoordSets;
    int					_maxTextureSize;
    int					_maxFastTextureSize;
    int					_maxLights;
    int					_depthBits;
    bool				_supportsGLSL;
    float				_GLSLversion;
    bool				_supportsTextureArrays;
    bool				_supportsTexture3D;
    bool				_supportsMultiTexture;
    bool				_supportsStencilWrap;
    bool				_supportsTwoSidedStencil;
    bool				_supportsTexture2DLod;
    bool				_supportsMipmappedTextureUpdates;
    bool				_supportsDepthPackedStencilBuffer;
    bool				_supportsOcclusionQuery;
    bool				_supportsDrawInstanced;
    bool				_supportsUniformBufferObjects;
    int					_maxUniformBlockSize;
    bool				_preferDLforStaticGeom;
    std::string			_vendor;
    std::string			_renderer;
    std::string			_version;

public:
    friend class osgEarth::Registry;
};


#endif 
