/**************************************************************************************************
* @file VolumeRendering.h
* @note 体渲染
* @author h00017
* @data 2017-2-9
**************************************************************************************************/
#ifndef FE_VOLUME_RENDER_H
#define FE_VOLUME_RENDER_H

#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture2D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture1D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture3D.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include "../Export.h"



namespace FeVolumeRender
{

    // 可渲染对象，继承于osg::Geometry,用于绘制体渲染的立方体盒子
	class CVolumeRenderGeometry : public osg::Geometry
	{
	public:
        CVolumeRenderGeometry();
	};



    // 利用光线追踪技术，实现体数据的渲染
	class VBF_EFFECT_AUX_EXPORT CVolumeRenderNode : public osg::CVBF_SGNodeGroup
	{
	public:
        CVolumeRenderNode(IVBF_View* pIView, const std::string& transferTexFile, const std::string& volumeTexFile);

	public:
		void SetStepSize(float fSize);
        void SetSampleNum(int num);

        void Update();// 更新回调函数，负责参数的更新

    private:

        // 测试渲染到纹理的效果
        //void AddHud();

        // 创建用于体渲染的立方体盒子
		void CreateGeometry();

        // 初始化纹理相机，用于保存盒子背面的位置
		void InitTexCamera();

        // 初始化体纹理，创建体纹理对象，并将体数据存入体纹理中。
        void InitVolumeTexture(std::string fileName);

        // 初始化颜色表纹理，创建一维纹理对象，并将颜色表数据存入其中
        void InitColorTableTexture(std::string fileName);


	private:
        observer_ptr<IVBF_View> m_opView;
        ref_ptr<CVolumeRenderGeometry> m_ipVolumeGeometry;

        ref_ptr<osg::Camera>    m_ipBoxCamera;
        ref_ptr<osg::Texture2D> m_ipBoxTex; // 纹理，用于保存盒子背面的位置

        ref_ptr<osg::Texture1D> m_ipColorTableTexture; // 颜色表纹理
        ref_ptr<osg::Texture3D> m_ipVolumeTexture;     // 体数据纹理
//!!		ref_ptr<osg::Camera> m_rpHud;
        ref_ptr<osg::MatrixTransform> m_ipMatWorld;


        float m_stepSize; // 光线前进的步长？

        // 视口的大小，也就是纹理的大小
        int m_texWidth;
		int m_texHeight;
//		osg::Vec3 m_boxSize;
		std::string m_transferTexName;
		std::string m_volumeTexName;
		std::string m_eleDataName;


        // 体数据值的范围
		float m_minVolumeValue;
		float m_maxVolumeValue;

        int m_numSample;
	};

}


#endif

