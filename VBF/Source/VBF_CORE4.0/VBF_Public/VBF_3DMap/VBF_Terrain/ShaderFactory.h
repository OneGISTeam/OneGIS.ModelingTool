#ifndef OSGEARTH_SHADER_FACTORY_H
#define OSGEARTH_SHADER_FACTORY_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VirtualProgram.h>

namespace osgEarth
{
    // 为地形引擎生成着色器，把着色器分成了几个阶段。默认的ShaderFactory存在于Earth的注册器中，可以用自定义的替换它
    class OSGEARTH_EXPORT ShaderFactory : public ::CVBF_Referenced
    {
    public:
		// 创建顶点着色器主函数
        virtual osg::Shader* createVertexShaderMain( const ShaderComp::FunctionLocationMap& functions) const;
		// 创建片元着色器主函数
        virtual osg::Shader* createFragmentShaderMain( const ShaderComp::FunctionLocationMap& functions) const;
		// 获取与纹理单元对应的采样器uniform/shader的名称
        virtual std::string getSamplerName( unsigned texImageUnit ) const;
		// 在VirtualProgram中安装光照着色器
        virtual void installLightingShaders(VirtualProgram* vp) const;
		// 建立一个着色器，实现颜色过滤链的功能
        virtual osg::Shader* createColorFilterChainFragmentShader( const std::string& function, const ColorFilterChain& chain ) const;

        // 获取与模式和值对应的uniform
        virtual osg::Uniform* createUniformForGLMode( osg::StateAttribute::GLMode mode, osg::StateAttribute::GLModeValue value ) const;

        virtual ~ShaderFactory() { }
    };


} // namespace osgEarth

#endif // OSGEARTH_SHADER_FACTORY_H
