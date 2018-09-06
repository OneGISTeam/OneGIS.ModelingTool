
#ifndef OSGEARTHUTIL_AUTOCLIPPLANEHANDLER_H
#define OSGEARTHUTIL_AUTOCLIPPLANEHANDLER_H

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_3DMap/VBF_Terrain/Utils.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Manipulator/VBF_EventVisitor.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <Types/VBF_Optional.h>

class CVBFO_SGNodeMap;

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

    // 自动调整远近裁剪面的CullCallback，用法getCamera()->addCullCallback( new AutoClipPlaneCallback(map) )
    class OSGEARTHUTIL_EXPORT AutoClipPlaneCullCallback : public osg::NodeCallback
    {
    public:    
		// 参数是为了获取椭球信息，如果为空，采用WGS84的值
        AutoClipPlaneCullCallback( CVBFO_SGNodeMap* pMapNode =0L );
        virtual ~AutoClipPlaneCullCallback();
        void SetMapNode(CVBFO_SGNodeMap* pMapNode);

        // 设置最小的near/far比例。当相机高度为0时，该值起作用 
        void setMinNearFarRatio( double value ) { m_dNearFarRatioMin = value; }
        double getMinNearFarRatio() const { return m_dNearFarRatioMin; }

        // 设置最大的near/far比例。当相机高度为高度阈值时，该值起作用
        void setMaxNearFarRatio( double value ) { m_dNearFarRatioMax = value; }
        double getMaxNearFarRatio() const { return m_dNearFarRatioMax; }

		// 设置相机的高度阈值（above ellipsoide），在该高度near/far比例达到最大
        void setHeightThreshold( double value ) { m_dHaeThreshold = value; }
        double getHeightThreshold() const { return m_dHaeThreshold; }

		// 是否把远裁剪面截取到视野范围
        void setClampFarClipPlane( bool value ) { m_bAutoFarPlaneClamping = value; }
        bool getClampFarClipPlane() const { return m_bAutoFarPlaneClamping; }

        //h00017
        void setCustomNearFar(double near,double far);
    public:
        virtual void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv );
        
    protected:
        bool   m_bActive;
        double m_dNearFarRatioMin, m_dNearFarRatioMax;
        double m_dHaeThreshold;
        double m_dR2, m_dR; // 地球半径及平方
        bool   m_bAutoFarPlaneClamping;



        //h00017
        double m_dNearCustom;
        double m_dFarCustom;
        bool   m_bNeedCustomNearFar;
        //h00017

        observer_ptr<CVBFO_SGNodeMap> m_opMapNode;
        CVBF_PerObjectMap< osg::IVBF_Camera*, ref_ptr<osg::CullSettings::ClampProjectionMatrixCallback> > _clampers;
    };



} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_AUTOCLIPPLANEHANDLER_H
