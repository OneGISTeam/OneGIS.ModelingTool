#ifndef OSGEARTH_SHADER_FACTORY_H
#define OSGEARTH_SHADER_FACTORY_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VirtualProgram.h>

namespace osgEarth
{
    // Ϊ��������������ɫ��������ɫ���ֳ��˼����׶Ρ�Ĭ�ϵ�ShaderFactory������Earth��ע�����У��������Զ�����滻��
    class OSGEARTH_EXPORT ShaderFactory : public ::CVBF_Referenced
    {
    public:
		// ����������ɫ��������
        virtual osg::Shader* createVertexShaderMain( const ShaderComp::FunctionLocationMap& functions) const;
		// ����ƬԪ��ɫ��������
        virtual osg::Shader* createFragmentShaderMain( const ShaderComp::FunctionLocationMap& functions) const;
		// ��ȡ������Ԫ��Ӧ�Ĳ�����uniform/shader������
        virtual std::string getSamplerName( unsigned texImageUnit ) const;
		// ��VirtualProgram�а�װ������ɫ��
        virtual void installLightingShaders(VirtualProgram* vp) const;
		// ����һ����ɫ����ʵ����ɫ�������Ĺ���
        virtual osg::Shader* createColorFilterChainFragmentShader( const std::string& function, const ColorFilterChain& chain ) const;

        // ��ȡ��ģʽ��ֵ��Ӧ��uniform
        virtual osg::Uniform* createUniformForGLMode( osg::StateAttribute::GLMode mode, osg::StateAttribute::GLModeValue value ) const;

        virtual ~ShaderFactory() { }
    };


} // namespace osgEarth

#endif // OSGEARTH_SHADER_FACTORY_H
