#ifndef OSGFX_CARTOON_
#define OSGFX_CARTOON_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLineWidth.h>

namespace osgFX
{

	/**
	��ͨ��Ⱦ��Ч��ʵ����һ����Ϊ��ͨ��ɫ��Cel-Shading���ķ������Ӷ�����һ�ֿ�ͨʽ��
	������ʵ�У���ȾЧ������Ҫ����ͨ��֧�֣���һ�����ڻ���ʵ����棬�ڶ������ڻ��������ߡ�
	����Ч��Ҫʹ�ö�����ɫ���������������꣬�Ա�������ʱ���ɵ�����Ԫ0��ʵ��һ�ּ����
	����Ч������ҪARB_vertex_program��չ����OpenGL��ɫ���Ե�֧�֡�
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

        // ����/��ȡ�����ߵ���ɫ
		inline const osg::Vec4& getOutlineColor() const     { return _wf_mat->getEmission(osg::Material::FRONT_AND_BACK); }
        inline void setOutlineColor(const osg::Vec4& color) { _wf_mat->setEmission(osg::Material::FRONT_AND_BACK, color); }
        
        // ���á���ȡ�����ߵĿ��
        inline float getOutlineLineWidth() const { return _wf_lw->getWidth(); }
        inline void setOutlineLineWidth(float w) {  _wf_lw->setWidth(w); }
        
         // ����/��ȡ��Դ����ͨ��С��8����
		inline int getLightNumber() const { return _lightnum; }
        inline void setLightNumber(int n) { _lightnum = n; dirtyTechniques(); }

    protected:
        virtual ~Cartoon() {}
        Cartoon& operator=(const Cartoon&) { return *this; }

        bool define_techniques();

    private:
        ref_ptr<osg::Material>  _wf_mat;  // �����Ĳ�������
        ref_ptr<osg::LineWidth> _wf_lw;   // �������߿�����
        int _lightnum;
    };


}

#endif
