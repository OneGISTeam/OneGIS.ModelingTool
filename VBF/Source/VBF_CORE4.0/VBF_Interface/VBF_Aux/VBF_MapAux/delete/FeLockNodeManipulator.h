#ifndef FELOCKNODEMANIPULATOR_H
#define FELOCKNODEMANIPULATOR_H

//#include <osgGA/CameraManipulator>
#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>
#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>
//#include <FeKits/Export.h>
//#include <FeUtils/RenderContext.h>
#include <VBF_Aux/VBF_MapAux/RenderContext.h>
//#include <FeUtils/logger/LoggerDef.h>
#include <VBF_Aux/VBF_MapAux/FreeEarthManipulatorBase.h>

namespace FeKit
{
    class VBF_MAPAUX_EXPORT FeLockNodeManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator> ,FeKit::FreeEarthManipulatorBase
	{
		
	public:

        enum VBF_MAPAUX_EXPORT LockType
		{
			FIRSTPERSON    = 1<<0,
			THIRDPERSON    = 1<<1	
		};

		FeLockNodeManipulator(FeUtil::CRenderContext* rc);
		~FeLockNodeManipulator();

		/** set the position of the matrix manipulator using a 4x4 Matrix.*/
		virtual void setByMatrix(const osg::Matrixd& matrix){};

		/** set the position of the matrix manipulator using a 4x4 Matrix.*/
		virtual void setByInverseMatrix(const osg::Matrixd& matrix){};

		/** get the position of the manipulator as 4x4 Matrix.*/
		virtual osg::Matrixd getMatrix() const;

		/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
        virtual osg::Matrixd getInverseMatrix() const;

        virtual void home(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&);

        virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

//        virtual void updateCamera(IVBF_Camera& camera);

        void setThirdPersonHomeParam(double lockDis,float degreeHead = 0.0,float degreeTilt = -70.0);
        void setFirstPersonHomeParam(float degreeTilt = -90.0,float degreeHead = 0.0);

        void setLockNode(osg::IVBF_SGNode* lockNode)
		{
			m_opLockNode = lockNode;
		}
        osg::IVBF_SGNode* getLockNode()
		{
			return m_opLockNode.get();
		}
		LockType getLockType()
		{
			return m_lockType;
		}
		void setLockType(LockType tp)
		{
			m_lockType = tp;
			resetCamera();
		}

		void resetCamera();
	protected:
		void computeViewMatrix();
		void computeLocalAxis(const osg::Vec3d& center,osg::Vec3d& northDir,osg::Vec3d& upDir,osg::Vec3d& rightDir);
		void checkClampProjectionMatrixCallback();
		void modifyNearFar(double& inputNear,double &inputFar);
		void modifyFirstPersonNearFar(double& inputNear,double &inputFar);
        osg::IVBF_SGNode * RecursionNode(osg::IVBF_SGNode *node, const std::string &strName);
	protected:
//        observer_ptr<FeUtil::CRenderContext> m_opRenderContext;
        observer_ptr<osg::IVBF_SGNode> m_opLockNode;
		osg::Matrix m_viewMatrix;
		double m_minLockDis;
		double m_maxLockDis;
		LockType m_lockType;
		osg::Matrix m_worldTransMat;

		float m_homeHead;
		float m_homeTilt;
		double m_homeLockDis;

		float m_firstHomeHead;
		float m_firstHomeTilt;

		float m_curHead;
		float m_curTilt;
		double m_curLockDis;

        float m_lastThirdHead;
        float m_lastThirdTilt;
        double m_lastThirdLockDis;

		osg::Vec3d m_lookDir;
		osg::Vec3d m_rightDir;
		osg::Vec3d m_upDir;

		float  m_lastX;
		float  m_lastY;
		float  m_dirRate;
		float  m_zoomRate;
		int    m_xDirParam;
        int    m_yDirParam;

        public:
        static double s_dRollRadianAngle;
	};

}

#endif //FELOCKNODEMANIPULATOR_H
