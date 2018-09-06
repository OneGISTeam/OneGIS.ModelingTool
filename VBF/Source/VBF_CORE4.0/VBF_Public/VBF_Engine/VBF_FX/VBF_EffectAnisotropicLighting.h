#ifndef OSGFX_ANISOTROPICLIGHTING_
#define OSGFX_ANISOTROPICLIGHTING_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>

namespace osgFX
{
	/**
	各向异性光照特效，使用单一通道。它使用了一种各向异性的光照来替代OpenGL的普通光照模型。
	几何顶点的颜色不是直接计算的，而是纹理映射到用户指定的光照图版（lighting image map）的结果。
	使用顶点着色器计算纹理坐标s和t的值：s = (N dot H) ; t = (N dot L)。
	N表示法线，L表示光到顶点的向量，H表示中间向量（half-way vector）。 这种特效很好的演示了
	State::getInitialViewMatrix() 方法的使用，它可以直接获取视口的初始矩阵并实现直接与视口相关的特效。
	该特效需要ARB_vertex_program扩展。
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
            
        
        // 设置/获取光照贴图
		inline osg::Image* getLightingMap()             { return _texture->getImage(); }
        inline const osg::Image* getLightingMap() const { return _texture->getImage(); }
        inline void setLightingMap(osg::Image* image)   { _texture->setImage(image); }

        // 设置/获取光源数。通常小于8个。
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
