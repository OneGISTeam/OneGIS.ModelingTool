#ifndef OSGFX_OUTLINE_
#define OSGFX_OUTLINE_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

namespace osgFX
{
    /**
     轮廓线特效，该特效在对象周围绘制一个基于stencil buffer的轮廓线。
	 生效条件：GC必须设置了stencil buffer，并在每次绘制前清空（0）   
     osg::DisplaySettings::instance()->setMinimumNumStencilBits(1);
     camera->setClearMask(clearMask | GL_STENCIL_BUFFER_BIT);
     camera->setClearStencil(0);
     */
    class OSGFX_EXPORT Outline : public Effect
    {
    public:
        Outline();

        Outline(const Outline& copy, const osg::CopyOp& op = osg::CopyOp::SHALLOW_COPY) : Effect(copy, op) 
		{
            _width = copy._width;
            _color = copy._color;
            _technique = copy._technique;
        }

        META_Effect(osgFX, Outline, 

			"Outline",

            "Stencil buffer based object outline effect.\n"
            "This effect needs a properly setup stencil buffer.",

            "Ulrich Hertlein");

        // 设置/获取轮廓线的宽度
        void  setWidth(float w);
        float getWidth() const { return _width; }

        // 设置/获取轮廓线的颜色
        void setColor(const osg::Vec4& color);
        const osg::Vec4& getColor() const { return _color; }

    protected:

        virtual ~Outline() { }

        bool define_techniques();

    private:

        float _width;     // 轮廓线的宽度
        osg::Vec4 _color; // 轮廓线的颜色

        class OutlineTechnique;
        OutlineTechnique* _technique;
    };

}

#endif
