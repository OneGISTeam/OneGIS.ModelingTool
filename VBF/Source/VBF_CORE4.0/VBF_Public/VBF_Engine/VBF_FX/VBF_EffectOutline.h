#ifndef OSGFX_OUTLINE_
#define OSGFX_OUTLINE_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

namespace osgFX
{
    /**
     ��������Ч������Ч�ڶ�����Χ����һ������stencil buffer�������ߡ�
	 ��Ч������GC����������stencil buffer������ÿ�λ���ǰ��գ�0��   
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

        // ����/��ȡ�����ߵĿ��
        void  setWidth(float w);
        float getWidth() const { return _width; }

        // ����/��ȡ�����ߵ���ɫ
        void setColor(const osg::Vec4& color);
        const osg::Vec4& getColor() const { return _color; }

    protected:

        virtual ~Outline() { }

        bool define_techniques();

    private:

        float _width;     // �����ߵĿ��
        osg::Vec4 _color; // �����ߵ���ɫ

        class OutlineTechnique;
        OutlineTechnique* _technique;
    };

}

#endif
