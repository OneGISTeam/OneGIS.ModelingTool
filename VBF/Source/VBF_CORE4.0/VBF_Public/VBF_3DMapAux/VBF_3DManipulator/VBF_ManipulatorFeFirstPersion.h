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
     * @brief  ͨ������۲���������������ĵ㡢ƫ���ǡ�������
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

	osg::Vec3d              m_vNormal; // ����

	bool                    m_pathSaving;
	bool                    m_pathPlaying;
	unsigned int            m_curSavePathStep;
	typedef std::vector<MyPathData> SavePathList;
	SavePathList            m_savePathList;
	unsigned int            m_maxSavePathSize;
    //fix
    float                   m_heightOffset;
    osg::Vec3d              m_eyePos;
    osg::NodeCallback*      m_pFrameFinishCB;       //�ص������
    //fix
};

#endif
