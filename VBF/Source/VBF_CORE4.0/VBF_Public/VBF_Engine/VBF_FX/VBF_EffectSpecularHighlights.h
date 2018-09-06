#ifndef OSGFX_SPECULARHIGHLIGHTS_
#define OSGFX_SPECULARHIGHLIGHTS_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

namespace osgFX
{

	/**
	立方图镜面高光特效，在片段层级（ragment level）上（而不是OpenGL通常的顶点层级）应用了镜面高光，
	使用了立方映射图和反射纹理生成（reflective texgen）的技术。首先要计算出纹理矩阵以实现立方映射图
	的自动旋转，这样无论从观察的方向和光照的位置上来说，镜面光的效果都始终保持不变。用户可以选择使用
	何种光照来计算纹理矩阵。需要GL_ARB_texture_env_add扩展，以及任意一种立方映射图扩展
	（GL_EXT_texture_cube_map, GL_ARB_texture_cube_map 或 OpenGL v1.3）。
	*/
    class OSGFX_EXPORT SpecularHighlights: public Effect 
	{
    public:
        SpecularHighlights();
        SpecularHighlights(const SpecularHighlights& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Effect(osgFX, SpecularHighlights, 
        
            "Specular Highlights", 
            
            "This effect applies additive specular highlights at fragment level (instead "
            "of OpenGL's vertex-level lighting) by using a cube map and reflective texgen. "
            "A texture matrix is computed to rotate the cube map automatically; this makes "
            "the specular effect consistent with respect to view direction and light position. "
            "The user can choose which light should be used to compute the texture matrix.\n"
            "This effect requires the GL_ARB_texture_env_add extension and one of the cube map "
            "extensions (GL_EXT_texture_cube_map, GL_ARB_texture_cube_map or OpenGL v1.3).", 
            
            "Marco Jez");
            
        
		// 设置/获取光源数。通常小于8个。
		inline int getLightNumber() const { return _lightnum; }
		inline void setLightNumber(int n) { _lightnum = n; dirtyTechniques(); }
        
		// 设置/获取纹理单元，用于立方映射图
        inline int getTextureUnit() const { return _unit; }
        inline void setTextureUnit(int n) { _unit = n; dirtyTechniques(); }
        
		// 设置/获取镜面高光的颜色
        inline const osg::Vec4& getSpecularColor() const     { return _color; }
        inline void setSpecularColor(const osg::Vec4& color) { _color = color; dirtyTechniques(); }
        
        // 设置/获取镜面高光指数
        inline float getSpecularExponent() const { return _sexp; }
        inline void setSpecularExponent(float e) { _sexp = e; dirtyTechniques(); }

    protected:
        virtual ~SpecularHighlights() {}
        SpecularHighlights& operator=(const SpecularHighlights&) { return *this; }

        bool define_techniques();

    private:
        int _lightnum;   // 光源数量
        int _unit;       // 纹理单元，用于立方映射图
        osg::Vec4 _color;// 镜面高光（反射光）颜色
        float _sexp;     // 镜面高光指数
    };

 
  
}

#endif
