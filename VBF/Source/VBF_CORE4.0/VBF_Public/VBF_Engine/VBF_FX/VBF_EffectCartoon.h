#ifndef OSGFX_CARTOON_
#define OSGFX_CARTOON_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLineWidth.h>

namespace osgFX
{

	/**
	卡通渲染特效，实现了一种名为卡通着色（Cel-Shading）的方法，从而产生一种卡通式的
	（非真实感）渲染效果。需要两个通道支持：第一个用于绘制实体表面，第二个用于绘制轮廓线。
	该特效需要使用顶点着色器来设置纹理坐标，以便在运行时生成的纹理单元0上实现一种尖锐的
	光照效果。需要ARB_vertex_program扩展或者OpenGL着色语言的支持。
	*/
    class OSGFX_EXPORT Cartoon: public Effect 
	{
    public:
        Cartoon();
        Cartoon(const Cartoon& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Effect( osgFX, Cartoon, 
            
            "Cartoon", 
            
            "This effect implements a technique called 'Cel-Shading' to produce a "
            "cartoon-style (non photorealistic) rendering. Two passes are required: "
            "the first one draws solid surfaces, the second one draws the outlines. "
            "A vertex program is used to setup texture coordinates for a sharp lighting "
            "texture on unit 0 which is generated on-the-fly.\n"
            "This effect requires the ARB_vertex_program extension "
            "or OpenGL Shading Language.",
            
            "Marco Jez; OGLSL port by Mike Weiblen");

        // 设置/获取轮廓线的颜色
		inline const osg::Vec4& getOutlineColor() const     { return _wf_mat->getEmission(osg::Material::FRONT_AND_BACK); }
        inline void setOutlineColor(const osg::Vec4& color) { _wf_mat->setEmission(osg::Material::FRONT_AND_BACK, color); }
        
        // 设置。获取轮廓线的宽度
        inline float getOutlineLineWidth() const { return _wf_lw->getWidth(); }
        inline void setOutlineLineWidth(float w) {  _wf_lw->setWidth(w); }
        
         // 设置/获取光源数。通常小于8个。
		inline int getLightNumber() const { return _lightnum; }
        inline void setLightNumber(int n) { _lightnum = n; dirtyTechniques(); }

    protected:
        virtual ~Cartoon() {}
        Cartoon& operator=(const Cartoon&) { return *this; }

        bool define_techniques();

    private:
        ref_ptr<osg::Material>  _wf_mat;  // 轮廓的材质属性
        ref_ptr<osg::LineWidth> _wf_lw;   // 轮廓的线宽属性
        int _lightnum;
    };


}

#endif
