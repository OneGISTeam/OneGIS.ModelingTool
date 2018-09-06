#ifndef FIRSTPERSONMANIPULATOR_UTIL_H
#define FIRSTPERSONMANIPULATOR_UTIL_H

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_Aux/VBF_MapAux/IntersectUtil.h>
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_Aux/VBF_MapAux/RenderContext.h>

void writeNodeToFile( FeMath::COctreeTriangleSelector::SOctreeNode* node,std::string fileName);
void writeNodeToFileImp( FeMath::COctreeTriangleSelector::SOctreeNode* node,std::fstream& fs);


namespace FeKit
{

    class VBF_MAPAUX_EXPORT FirstPersonManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
	{
		struct ModelProjMatCallback : public osg::CullSettings::ClampProjectionMatrixCallback
		{
			ModelProjMatCallback(FirstPersonManipulator* em);
			virtual bool clampProjectionMatrixImplementation(osg::Matrixf& projection, double& znear, double& zfar) const;
			virtual bool clampProjectionMatrixImplementation(osg::Matrixd& projection, double& znear, double& zfar) const;

			FirstPersonManipulator* m_pFirstPersonManipulator;
		};

        struct MyPathData
        {
            osg::Vec3 pathPosition;
            float     pathHead;
            float     pathTilt;
        };

	public:
		FirstPersonManipulator(FeUtil::CRenderContext* rc);
		~FirstPersonManipulator();

		virtual void setByMatrix(const osg::Matrixd& matrix);
		virtual void setByInverseMatrix(const osg::Matrixd& matrix);

		virtual osg::Matrixd getMatrix() const;
		virtual osg::Matrixd getInverseMatrix() const;

        virtual void home(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&);

        virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

		void setHomePosition(osg::Vec3d spherePos,float degreeHead = 0,float degreeTilt = 0);

        bool init(osg::IVBF_SGNode* modelNode,std::string octFileName = "");
        bool initOctFile(std::string octFileName, Matrix worldMatirx);

		FeUtil::CRenderContext* getContext()
		{
            return m_ipRenderContext.get();
		}
		double getNearClip()
		{
            return m_dClipNear;
		}
		double getFarClip()
		{
            return m_dClipFar;
		}
        void stopSaveAndPlayPath();
        void startSavePath();
        bool savePathToFile(std::string fileName);
        bool readPathFromFile(std::string fileName);
        void playSavePath();

        bool isInitialized() { return m_initialized; }
	private:
//**		void setByLookAt(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up);
//**		osg::Matrixd getRotation(const osg::Vec3d& center);
//**		osg::Vec3d getLocalNorth(osg::Vec3d c);
//**		osg::Vec3d getLocalSide(osg::Vec3d c);
        void updateCamera();
		void updateLookDir();
		void updatePosition();
		void checkClampProjectionMatrixCallback();
		void resetCamera();
        void setNearFar();

	private:
		osg::Matrix             m_viewMat;

//**		osg::Quat               m_rotation;
//**		osg::Quat               m_centerRotation;

        ref_ptr<FeUtil::CRenderContext> m_ipRenderContext;
		FeMath::COctreeTriangleSelector m_triangleSelector;
		FeMath::CSceneCollisionManager m_collisionManager;
		bool                    m_initialized;
		bool                    m_initLocalCenter;


        ref_ptr<ModelProjMatCallback> m_rpProjCallback;
        double                  m_dClipNear;
        double                  m_dClipFar;




//		unsigned int            m_stepPerMove;
//		unsigned int            m_curStep;

        bool                    m_bJump; // ��ǰ���ϣ���������ĳ���ϰ�
        unsigned int            m_jumpStepumped;// ��Ծ�ĸ߶ȣ�ÿ֡�ݼ�

		bool                    m_left;
		bool                    m_right;
		bool                    m_up;
		bool                    m_down;


        // ��¼home��
        float                   m_homeHead;   // ��λ����
        float                   m_homeTilt;   // ��������
        osg::Vec3d              m_homeCenter; // λ�ã����ֱ������ϵ

        // ��¼��ǰ�ĵ�
        osg::Vec3d              m_vCenterWorld;// ��ǰλ�ã����ֱ������ϵ
        float                   m_head;
        float                   m_tilt;

        osg::Vec3d              m_vCenterLocal; // ��ǰλ�ã�ģ������ϵ

        osg::Vec3d              m_vDirForward;   // ˮƽǰ����ģ������ϵ
        osg::Vec3d              m_vDirSide;      // ˮƽ�෽����ࣩ��ģ������ϵ
        osg::Vec3d              m_localNorth;    // ��ǰ�ķ���ģ������ϵ



        float                   m_lastX;    // ��һ������Xֵ
        float                   m_lastY;    // ��һ������Yֵ

        float                   m_fRateDirX;    // ���ʣ�X����
        float                   m_fRateDirY;    // ���ʣ�Y����
        float                   m_fRateSpeed;   // ���ʣ��ٶ�

        // ������ײ���Ĳ���
		osg::Vec3d              m_radius;
		bool                    m_isFalling;
        float                   m_slidingSpeed; // �����ƶ��ľ���
        osg::Vec3d              m_gravity;

        osg::Matrix             m_matL2W; // �ֲ�������任����
//		osg::Vec3d              m_localSide;
//		osg::Vec3d              m_localUp;

        osg::Vec3d              m_vNormal; // ����

        bool                    m_pathSaving;
        bool                    m_pathPlaying;
        unsigned int            m_curSavePathStep;
        typedef std::vector<MyPathData> SavePathList;
        SavePathList            m_savePathList;
        unsigned int            m_maxSavePathSize;
	};

}

#endif //MANIPULATOR_UTIL_H
