#ifndef OSGFX_SPECULARHIGHLIGHTS_
#define OSGFX_SPECULARHIGHLIGHTS_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

namespace osgFX
{

	/**
	����ͼ����߹���Ч����Ƭ�β㼶��ragment level���ϣ�������OpenGLͨ���Ķ���㼶��Ӧ���˾���߹⣬
	ʹ��������ӳ��ͼ�ͷ����������ɣ�reflective texgen���ļ���������Ҫ��������������ʵ������ӳ��ͼ
	���Զ���ת���������۴ӹ۲�ķ���͹��յ�λ������˵��������Ч����ʼ�ձ��ֲ��䡣�û�����ѡ��ʹ��
	���ֹ������������������ҪGL_ARB_texture_env_add��չ���Լ�����һ������ӳ��ͼ��չ
	��GL_EXT_texture_cube_map, GL_ARB_texture_cube_map �� OpenGL v1.3����
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
            
        
		// ����/��ȡ��Դ����ͨ��С��8����
		inline int getLightNumber() const { return _lightnum; }
		inline void setLightNumber(int n) { _lightnum = n; dirtyTechniques(); }
        
		// ����/��ȡ����Ԫ����������ӳ��ͼ
        inline int getTextureUnit() const { return _unit; }
        inline void setTextureUnit(int n) { _unit = n; dirtyTechniques(); }
        
		// ����/��ȡ����߹����ɫ
        inline const osg::Vec4& getSpecularColor() const     { return _color; }
        inline void setSpecularColor(const osg::Vec4& color) { _color = color; dirtyTechniques(); }
        
        // ����/��ȡ����߹�ָ��
        inline float getSpecularExponent() const { return _sexp; }
        inline void setSpecularExponent(float e) { _sexp = e; dirtyTechniques(); }

    protected:
        virtual ~SpecularHighlights() {}
        SpecularHighlights& operator=(const SpecularHighlights&) { return *this; }

        bool define_techniques();

    private:
        int _lightnum;   // ��Դ����
        int _unit;       // ����Ԫ����������ӳ��ͼ
        osg::Vec4 _color;// ����߹⣨����⣩��ɫ
        float _sexp;     // ����߹�ָ��
    };

 
  
}

#endif
