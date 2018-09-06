#ifndef OSGFX_BUMPMAPPING_
#define OSGFX_BUMPMAPPING_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>

namespace osgFX
{
	/**
	��͹��ͼ��Ч�����Դ���һ�ְ�͹��ƽ�ı���Ч�������ӽڵ����ʹ����������һ������������ɫ��
	��һ���Ƿ�����ͼ������ʹ��nVIDIA�ķ�����ͼ���������������ߣ����ݸ߶�ͼ�Զ����ɣ���
	���⣬����Ҫ�������пռ䣨tangent-space���Ļ�������basis vectors�������������ÿ��Geometry
	�������ϣ���һ�����Ե���BumpMapping::prepareChildren()����Ѹ�����ɣ���
	ע�⣺Geometry�������������ɫ�ͷ�����ͼ����������ǰ����ö�Ӧ��UV��ͼ������Ч�Ƽ�ʹ��һ������
	��ARB�����Ƭ����ɫ���ļ��������⣬��������һ�ֲ�ʹ��Ƭ����ɫ���ļ������޷��������;�����������㣩��
	*/
   
    class OSGFX_EXPORT BumpMapping: public Effect 
	{
    public:
        BumpMapping();
        BumpMapping(const BumpMapping& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Effect(osgFX, BumpMapping, 
        
            "Bump Mapping", 
            
            "This effect makes surfaces appear bumpy. Children nodes must use two textures, "
            "one for diffuse color and one for the normal map (which can be created "
            "from a height map with tools like nVIDIA's normal map generator). Furthermore, "
            "tangent-space basis vectors must be created and assigned to each Geometry; this "
            "can be done quickly by calling BumpMapping::prepareChildren(). Note that both "
            "diffuse and normal map textures must have corresponding UV maps defined in "
            "Geometry objects.\n"
            "This effect defines a preferred technique which uses ARB vertex & fragment "
            "programs, and a fallback technique which doesn't use fragment programs. The "
            "latter is more limited though since it can't handle ambient and specular "
            "components.",
            
            "Marco Jez");
            
        
        // ����/��ȡ��Դ����ͨ��С��8����
		inline int getLightNumber() const { return _lightnum; }
        inline void setLightNumber(int n) { _lightnum = n; dirtyTechniques(); }
        
        // ����/��ȡ����������Ԫ��Ĭ��Ϊ1��
		inline int getDiffuseTextureUnit() const { return _diffuse_unit; }
        inline void setDiffuseTextureUnit(int n) { _diffuse_unit = n; dirtyTechniques(); }

 		// ����/��ȡ��������Ԫ��Ĭ��Ϊ0��
        inline int getNormalMapTextureUnit() const { return _normal_unit; }
        inline void setNormalMapTextureUnit(int n) { _normal_unit = n; dirtyTechniques(); }
        
		// ����/��������overrides���ӽڵ������������
		inline osg::Texture2D* getOverrideDiffuseTexture()             { return _diffuse_tex.get(); }
		inline const osg::Texture2D* getOverrideDiffuseTexture() const { return _diffuse_tex.get(); }
		inline void setOverrideDiffuseTexture(osg::Texture2D* texture) { _diffuse_tex = texture; dirtyTechniques(); }
        
        // ����/��������overrides���ӽڵ�ķ�������
        inline osg::Texture2D* getOverrideNormalMapTexture()             { return _normal_tex.get(); }
        inline const osg::Texture2D* getOverrideNormalMapTexture() const { return _normal_tex.get(); }
        inline void setOverrideNormalMapTexture(osg::Texture2D* texture) { _normal_tex = texture; dirtyTechniques(); }
        
        // ׼��һ��Geometry����ʵ�ְ�͹��ͼ�����пռ䣨tangent-space���Ļ�������������������Geometry
        void prepareGeometry(osg::Geometry* geo);
        
        /** prepare a IVBF_SGNode for bump lighting, calling prepareGeometry() for each Geometry */
        void prepareNode(osg::IVBF_SGNode* node);
        
        /** prepare children for bump lighting. Actually calls prepareNode() for each child */
        void prepareChildren();
        
        // ����Ĭ�ϵ�������ͷ�����ͼ����
        void setUpDemo();

    protected:
        virtual ~BumpMapping() {}
        BumpMapping &operator=(const BumpMapping &) { return *this; }

        bool define_techniques();

    private:
        int _lightnum;          // ��Դ����
        int _diffuse_unit;      // ����������Ԫ
        int _normal_unit;       // ��������Ԫ
        ref_ptr<osg::Texture2D> _diffuse_tex;  // ����������
        ref_ptr<osg::Texture2D> _normal_tex;   // ��������
    };

  
    
}

#endif
