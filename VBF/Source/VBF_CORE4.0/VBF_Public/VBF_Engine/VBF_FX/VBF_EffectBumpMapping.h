#ifndef OSGFX_BUMPMAPPING_
#define OSGFX_BUMPMAPPING_

#include <VBF_Engine/VBF_FX/Export>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>

#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>

namespace osgFX
{
	/**
	凹凸贴图特效，可以创建一种凹凸不平的表面效果。其子节点必须使用两种纹理，一种是漫反射颜色，
	另一种是法线贴图（可以使用nVIDIA的发现贴图生成器或其他工具，根据高度图自动生成）。
	此外，还需要创建正切空间（tangent-space）的基向量（basis vectors）并将其关联到每个Geometry
	几何体上（这一步可以调用BumpMapping::prepareChildren()方法迅速生成）。
	注意：Geometry对象的漫反射颜色和法线贴图纹理都必须提前定义好对应的UV贴图。该特效推荐使用一种运用
	了ARB顶点和片段着色器的技术，另外，还定义了一种不使用片段着色器的技术（无法处理环境和镜面组件的运算）。
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
            
        
        // 设置/获取光源数。通常小于8个。
		inline int getLightNumber() const { return _lightnum; }
        inline void setLightNumber(int n) { _lightnum = n; dirtyTechniques(); }
        
        // 设置/获取漫反射纹理单元，默认为1。
		inline int getDiffuseTextureUnit() const { return _diffuse_unit; }
        inline void setDiffuseTextureUnit(int n) { _diffuse_unit = n; dirtyTechniques(); }

 		// 设置/获取法线纹理单元，默认为0。
        inline int getNormalMapTextureUnit() const { return _normal_unit; }
        inline void setNormalMapTextureUnit(int n) { _normal_unit = n; dirtyTechniques(); }
        
		// 设置/获得替代（overrides）子节点的漫反射纹理
		inline osg::Texture2D* getOverrideDiffuseTexture()             { return _diffuse_tex.get(); }
		inline const osg::Texture2D* getOverrideDiffuseTexture() const { return _diffuse_tex.get(); }
		inline void setOverrideDiffuseTexture(osg::Texture2D* texture) { _diffuse_tex = texture; dirtyTechniques(); }
        
        // 设置/获得替代（overrides）子节点的法线纹理
        inline osg::Texture2D* getOverrideNormalMapTexture()             { return _normal_tex.get(); }
        inline const osg::Texture2D* getOverrideNormalMapTexture() const { return _normal_tex.get(); }
        inline void setOverrideNormalMapTexture(osg::Texture2D* texture) { _normal_tex = texture; dirtyTechniques(); }
        
        // 准备一个Geometry用来实现凹凸贴图。正切空间（tangent-space）的基向量被创建并关联到Geometry
        void prepareGeometry(osg::Geometry* geo);
        
        /** prepare a IVBF_SGNode for bump lighting, calling prepareGeometry() for each Geometry */
        void prepareNode(osg::IVBF_SGNode* node);
        
        /** prepare children for bump lighting. Actually calls prepareNode() for each child */
        void prepareChildren();
        
        // 设置默认的漫反射和法线贴图环境
        void setUpDemo();

    protected:
        virtual ~BumpMapping() {}
        BumpMapping &operator=(const BumpMapping &) { return *this; }

        bool define_techniques();

    private:
        int _lightnum;          // 光源数量
        int _diffuse_unit;      // 漫反射纹理单元
        int _normal_unit;       // 法线纹理单元
        ref_ptr<osg::Texture2D> _diffuse_tex;  // 漫反射纹理
        ref_ptr<osg::Texture2D> _normal_tex;   // 法线纹理
    };

  
    
}

#endif
