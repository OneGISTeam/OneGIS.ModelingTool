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

        bool                    m_bJump; // 先前（上）跳，跳过某个障碍
        unsigned int            m_jumpStepumped;// 跳跃的高度，每帧递减

		bool                    m_left;
		bool                    m_right;
		bool                    m_up;
		bool                    m_down;


        // 记录home点
        float                   m_homeHead;   // 方位，度
        float                   m_homeTilt;   // 俯仰，度
        osg::Vec3d              m_homeCenter; // 位置，大地直角坐标系

        // 记录当前的点
        osg::Vec3d              m_vCenterWorld;// 当前位置，大地直角坐标系
        float                   m_head;
        float                   m_tilt;

        osg::Vec3d              m_vCenterLocal; // 当前位置，模型坐标系

        osg::Vec3d              m_vDirForward;   // 水平前方，模型坐标系
        osg::Vec3d              m_vDirSide;      // 水平侧方（左侧），模型坐标系
        osg::Vec3d              m_localNorth;    // 向前的方向，模型坐标系



        float                   m_lastX;    // 上一次鼠标的X值
        float                   m_lastY;    // 上一次鼠标的Y值

        float                   m_fRateDirX;    // 比率，X方向
        float                   m_fRateDirY;    // 比率，Y方向
        float                   m_fRateSpeed;   // 比率，速度

        // 用于碰撞检测的参数
		osg::Vec3d              m_radius;
		bool                    m_isFalling;
        float                   m_slidingSpeed; // 横向移动的距离
        osg::Vec3d              m_gravity;

        osg::Matrix             m_matL2W; // 局部到世界变换矩阵
//		osg::Vec3d              m_localSide;
//		osg::Vec3d              m_localUp;

        osg::Vec3d              m_vNormal; // 法线

        bool                    m_pathSaving;
        bool                    m_pathPlaying;
        unsigned int            m_curSavePathStep;
        typedef std::vector<MyPathData> SavePathList;
        SavePathList            m_savePathList;
        unsigned int            m_maxSavePathSize;
	};

}

#endif //MANIPULATOR_UTIL_H
