#ifndef OSGFX_ANISOTROPICLIGHTING_
#define OSGFX_ANISOTROPICLIGHTING_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>

namespace osgFX
{
	/**
	�������Թ�����Ч��ʹ�õ�һͨ������ʹ����һ�ָ������ԵĹ��������OpenGL����ͨ����ģ�͡�
	���ζ������ɫ����ֱ�Ӽ���ģ���������ӳ�䵽�û�ָ���Ĺ���ͼ�棨lighting image map���Ľ����
	ʹ�ö�����ɫ��������������s��t��ֵ��s = (N dot H) ; t = (N dot L)��
	N��ʾ���ߣ�L��ʾ�⵽�����������H��ʾ�м�������half-way vector���� ������Ч�ܺõ���ʾ��
	State::getInitialViewMatrix() ������ʹ�ã�������ֱ�ӻ�ȡ�ӿڵĳ�ʼ����ʵ��ֱ�����ӿ���ص���Ч��
	����Ч��ҪARB_vertex_program��չ��
	*/

   
    class OSGFX_EXPORT AnisotropicLighting: public Effect 
	{
    public:
        AnisotropicLighting();
        AnisotropicLighting(const AnisotropicLighting& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Effect(osgFX, AnisotropicLighting, 
        
            "Anisotropic Lighting", 
            
            "This single-pass effect implements a sort of anisotropic "
            "lighting that replaces the standard OpenGL lighting model.\n"
            "The final color of vertices is not computed directly, it is "
            "the result of a texture lookup on a user-supplied lighting "
            "image map. A vertex program is used to compute the s and t "
            "texture coordinates as follows: s = (N dot H) ; t = (N dot L) "
            "where N is the vertex normal, L is the light-to-vertex vector, "
            "H is the half-way vector. This is a good example of how you "
            "can use the State::getInitialViewMatrix() method to retrieve "
            "the view matrix and perform view-dependant effects without "
            "fakes of any kind.\n"
            "This effect requires the ARB_vertex_program extension.", 
            
            "Marco Jez");
            
        
        // ����/��ȡ������ͼ
		inline osg::Image* getLightingMap()             { return _texture->getImage(); }
        inline const osg::Image* getLightingMap() const { return _texture->getImage(); }
        inline void setLightingMap(osg::Image* image)   { _texture->setImage(image); }

        // ����/��ȡ��Դ����ͨ��С��8����
		inline int getLightNumber() const { return _lightnum; }
        inline void setLightNumber(int n) { _lightnum = n; dirtyTechniques(); }

    protected:
        virtual ~AnisotropicLighting() {}
        AnisotropicLighting& operator=(const AnisotropicLighting&) { return *this; }

        bool define_techniques();

    private:
        int _lightnum;
        ref_ptr<osg::Texture2D> _texture;
    };

}

#endif
