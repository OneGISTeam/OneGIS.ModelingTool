#ifndef VBF_MANIPULATOR_FE_FIRST_PERSION_H
#define VBF_MANIPULATOR_FE_FIRST_PERSION_H

#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>

#include <VBF_3DMapAux/VBF_3DManipulator/VBF_3DManipulator_Global.h>
#include <VBF_3DMapAux/VBF_3DManipulator/VBF_IntersectUtil.h>
#include <VBF_3DMapAux/VBF_3DManipulator/VBF_ManipulatorContext.h>


void writeNodeToFile( FeMath::COctreeTriangleSelector::SOctreeNode* node,std::string fileName);

void writeNodeToFileImp( FeMath::COctreeTriangleSelector::SOctreeNode* node,std::fstream& fs);

class VBF_3DMANIPULATORSHARED_EXPORT FeFirstPersonManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
	struct ModelProjMatCallback : public osg::CullSettings::ClampProjectionMatrixCallback
	{
		ModelProjMatCallback(FeFirstPersonManipulator* em);
		virtual bool clampProjectionMatrixImplementation(osg::Matrixf& projection, double& znear, double& zfar) const;
		virtual bool clampProjectionMatrixImplementation(osg::Matrixd& projection, double& znear, double& zfar) const;

		FeFirstPersonManipulator* m_pFeFirstPersonManipulator;
	};

	struct MyPathData
	{
		osg::Vec3 pathPosition;
		float     pathHead;
		float     pathTilt;
	};

public:
	FeFirstPersonManipulator(CVBF_ManipulatorContext* rc);
	~FeFirstPersonManipulator();

	virtual void setByMatrix(const osg::Matrixd& matrix);
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);

	virtual osg::Matrixd getMatrix() const;
	virtual osg::Matrixd getInverseMatrix() const;

	virtual void home(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&);

	virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

	void setHomePosition(osg::Vec3d spherePos,float degreeHead = 0,float degreeTilt = 0);

	bool init(osg::IVBF_SGNode* modelNode,std::string octFileName = "");
	bool initOctFile(std::string octFileName, Matrix worldMatirx);

	CVBF_ManipulatorContext* getContext()
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

	void writeNodeToFile( FeMath::COctreeTriangleSelector::SOctreeNode* node,std::string fileName);
	void writeNodeToFileImp( FeMath::COctreeTriangleSelector::SOctreeNode* node,std::fstream& fs);
	bool isInitialized() { return m_initialized; }

    //fix
    /**
     * @brief  通过相机观察矩阵计算相机的中心点、偏航角、俯仰角
     * @author HG
     * @time   20170628
     */
    void setHomePositionFromMatrix(osg::Matrixd &,osg::NodeCallback* pCB = 0);
    void getHomePositionFromCam();
    //fix
private:
	void updateCamera();
	void updateLookDir();
	void updatePosition();
	void checkClampProjectionMatrixCallback();
	void resetCamera();
	void setNearFar();

private:
	osg::Matrix             m_viewMat;

	ref_ptr<CVBF_ManipulatorContext> m_ipRenderContext;
	FeMath::COctreeTriangleSelector m_triangleSelector;
	FeMath::CSceneCollisionManager m_collisionManager;
	bool                    m_initialized;
	bool                    m_initLocalCenter;


	ref_ptr<ModelProjMatCallback> m_rpProjCallback;
	double                  m_dClipNear;
	double                  m_dClipFar;


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

	osg::Vec3d              m_vNormal; // 法线

	bool                    m_pathSaving;
	bool                    m_pathPlaying;
	unsigned int            m_curSavePathStep;
	typedef std::vector<MyPathData> SavePathList;
	SavePathList            m_savePathList;
	unsigned int            m_maxSavePathSize;
    //fix
    float                   m_heightOffset;
    osg::Vec3d              m_eyePos;
    osg::NodeCallback*      m_pFrameFinishCB;       //回调类对象
    //fix
};

#endif
