//**********************************************************************************
// �ļ�����  VBF_Capabilities.h
// ������    ��ȡ�Կ��ĸ�����Ⱦ������Ϣ������Ϣ��Ϊ��ʵ����ʽ�洢��osgEarth::Registry��
// ����:     ��Ө
// ����:     2013-06-21
//**********************************************************************************

#ifndef __VBF_CAPABILITIES_H__
#define __VBF_CAPABILITIES_H__


#include <VBF_3DMap/VBF_Terrain/Export>
#include <VBF_Base/VBF_Referenced.h>
#include <string>


// ����ʹ����Ԫ��
namespace osgEarth
{
	class Registry;
}

class OSGEARTH_EXPORT CVBF_Capabilities : public ::CVBF_Referenced
{
public:
        
	/** ��ȡ�̶�������֧�ֵ��������Ԫ�� ��maximum # of texture units�� */
    int getMaxFFPTextureUnits() const { return _maxFFPTextureUnits; }
        
	/** ��ȡƬ����ɫ����֧�ֵ��������ͼ��Ԫ����maximum # of texture image units�� */
    int getMaxGPUTextureUnits() const { return _maxGPUTextureUnits; }
        
	/** ��ȡƬ����ɫ����֧�ֵ�����������꼯������maximum # of texture coordinate sets�� */
    int getMaxGPUTextureCoordSets() const { return _maxGPUTextureCoordSets; }
        
	/** ��ȡ�Կ�֧�ֵ��������ߴ磨��λ�����أ� */
    int getMaxTextureSize() const { return _maxTextureSize; }
        
	/** ��ȡ�Կ�֧�ֵġ��ֲ���Ӱ����ȾЧ�ʵ��������ߴ磬ͬʱ�ֲ���Ӱ����ȾЧ�ʣ���λ�����أ���ֵ���Կ������йأ� */
    int getMaxFastTextureSize() const { return _maxFastTextureSize; }
       
	/** ��ȡ�Կ�֧�ֵ��������� */
    int getMaxLights() const { return _maxLights; }
        
	/** ��ȡ�Կ�֧�ֵ���Ȼ����bitλ�� */
    int getDepthBufferBits() const { return _depthBits; }
       
	/** �ж��Կ��Ƿ�֧����ɫ������GLSL */
    bool supportsGLSL(float minimumVersion =1.0f) const { return _supportsGLSL && _GLSLversion >= minimumVersion; }
        
	/** ��ȡGLSL�İ汾 */
    float getGLSLVersion() const { return _GLSLversion; }
        
	/** ��ȡ�Կ����̣���"NVIDIA Corporation" */
    const std::string& getVendor() const { return _vendor; }

    /** ��ȡ�Կ��ͺţ���"GeForce GT 650M/PCIe/SSE2" */
    const std::string& getRenderer() const { return _renderer; }
        
	/** ��ȡ�Կ������İ汾 */
    const std::string& getVersion() const { return _version; }
        
	/** �ж��Կ��Ƿ�֧���������� */
    bool supportsTextureArrays() const { return _supportsTextureArrays; }

    /** �ж��Կ��Ƿ�֧��3D���� */
    bool supportsTexture3D() const { return _supportsTexture3D; }

    /** �ж��Կ��Ƿ�֧�ֶ����� */
    bool supportsMultiTexture() const { return _supportsMultiTexture; }
        
	/** �ж��Կ��Ƿ�֧��OpenGL��չ��GL_EXT_stencil_wrap */
    bool supportsStencilWrap() const { return _supportsStencilWrap; }
        
	/** �ж��Կ��Ƿ�֧��OpenGL��չ��GL_EXT_stencil_two_side */
    bool supportsTwoSidedStencil() const { return _supportsTwoSidedStencil; }
        
	/** �ж��Կ��Ƿ�֧��OpenGL��չ��GL_ARB_shader_texture_lod */
    bool supportsTexture2DLod() const { return _supportsTexture2DLod; }
        
	/** �ж��Կ��Ƿ�֧����һ���µ�mipmapͼ�����һ�����е����� */
    bool supportsMipmappedTextureUpdates() const { return _supportsMipmappedTextureUpdates; }
        
	/** �ж��Կ��Ƿ�֧��OpenGL��չ��GL_EXT_packed_depth_stencil �� GL_OES_packed_depth_stencil */
    bool supportsDepthPackedStencilBuffer() const { return _supportsDepthPackedStencilBuffer; }
        
	/** �ж��Կ��Ƿ�֧��OpenGL��չ��GL_ARB_occlusion_query */
    bool supportsOcclusionQuery() const { return _supportsOcclusionQuery; }
        
	/** �ж��Կ��Ƿ�֧��DrawInstanced��Ⱦ��ʽ */
    bool supportsDrawInstanced() const { return _supportsDrawInstanced; }
        
	/** �ж��Կ��Ƿ�֧��Uniform Buffer Objects */
    bool supportsUniformBufferObjects() const { return _supportsUniformBufferObjects; }
        
	/** ��ȡ�Կ�֧�ֵ�uniform buffer block������ֽ��� */
    int getMaxUniformBlockSize() const { return _maxUniformBlockSize; }
        
	/** �������ݻ�������ļ��ζ����Ƿ�����ʹ����ʾ�б���VBO��ȣ�*/
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
