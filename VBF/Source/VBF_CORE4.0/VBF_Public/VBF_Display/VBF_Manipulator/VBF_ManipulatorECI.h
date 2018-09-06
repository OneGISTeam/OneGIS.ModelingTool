#ifndef OSGGA_UFO_MANIPULATOR_DEF
#define OSGGA_UFO_MANIPULATOR_DEF 1

#include <iostream>

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <Types/VBF_Matrix.h>


namespace osgGA {


    // �ع�����ϵ

    class OSGGA_EXPORT CVBF_ManipulatorECI : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
	{
	public:
        CVBF_ManipulatorECI();

		virtual const char* className() const;

		// 1���̳���IVBF_CameraManipulator�ĺ���
		virtual void setByMatrix( const osg::Matrixd &matrix ) ;
		virtual void setByInverseMatrix( const osg::Matrixd &invmat);
		virtual osg::Matrixd getMatrix() const;
		virtual osg::Matrixd getInverseMatrix() const ;


		virtual void setNode(osg::IVBF_SGNode* node);
		virtual const osg::IVBF_SGNode* getNode() const;
		virtual osg::IVBF_SGNode* getNode();


        virtual void computeHomePosition();
        virtual void home(const osgGA::GUIEventAdapter&, ::IVBF_GUIActionAdapter&) ;
        void home(double);

        virtual void init(const GUIEventAdapter& ,::IVBF_GUIActionAdapter&);

        bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter &aa);

        void GetUsage(::ApplicationUsage& usage) const;

        void getCurrentPositionAsLookAt( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up );



    protected:

    virtual ~CVBF_ManipulatorECI();

    void _frame(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter &);

    osg::Vec3d m_vEyeGeoECI;// �ع�ϵ�µ����λ�ã���γ�ߣ�

    double m_dTimeUTC;// ����ʱ����λ���룩
    osg::EllipsoidModel m_Ellipsoid;
};

}

#endif
