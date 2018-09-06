#ifndef OSGGA_CameraManipulator
#define OSGGA_CameraManipulator 1

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>


#define NEW_HOME_POSITION

// 相机操作器，抽象的基类，用于定义相机操作的接口和默认函数

//class OSGGA_EXPORT IVBF_CameraManipulatorImpl : public IVBF_CameraManipulator
template<class T>
class IVBF_CameraManipulatorImpl : public T
{
     public:
        virtual const char* className() const { return "CameraManipulator"; }

		// 1、坐标系相关接口

        // 设置/获取"坐标系回调"，该回调告诉操作器上、东、北方向
        virtual void setCoordinateFrameCallback(IVBF_CoordinateFrameCallback* cb) { _coordinateFrameCallback = cb; }
        IVBF_CoordinateFrameCallback* getCoordinateFrameCallback() { return _coordinateFrameCallback.get(); }
        const IVBF_CoordinateFrameCallback* getCoordinateFrameCallback() const { return _coordinateFrameCallback.get(); }

        virtual void SetCallback(IVBF_ManipulatorCB* cb){ m_ipCallback = cb; }

        osg::CoordinateFrame getCoordinateFrame(const osg::Vec3d& position) const;// 获取坐标系

		// 获取向上、向前、向侧方向的向量
        osg::Vec3d getSideVector(const osg::CoordinateFrame& cf) const { return osg::Vec3d(cf(0,0),cf(0,1),cf(0,2)); }
        osg::Vec3d getFrontVector(const osg::CoordinateFrame& cf) const { return osg::Vec3d(cf(1,0),cf(1,1),cf(1,2)); }
        osg::Vec3d getUpVector(const osg::CoordinateFrame& cf) const { return osg::Vec3d(cf(2,0),cf(2,1),cf(2,2)); }

		// 2、矩阵相关接口

		// 3、空间融合距离，用于双目立体
        virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return osgUtil::SceneView::PROPORTIONAL_TO_SCREEN_DISTANCE; }
        virtual float getFusionDistanceValue() const { return 1.0f; }

		// 4、设置/获取求交遍历的掩码      
        void setIntersectTraversalMask(unsigned int mask) { m_nIntersectTraversalMask = mask; }
        unsigned int getIntersectTraversalMask() const { return m_nIntersectTraversalMask; }

		// 5、与节点相关的函数（有些操作器需要（如跟踪），有些不需要）
        virtual void setNode(osg::IVBF_SGNode*) {}
        virtual const osg::IVBF_SGNode* getNode() const { return NULL; }
        virtual osg::IVBF_SGNode* getNode() { return NULL; }


		// 6、与默认位置相关的函数
        virtual void setHomePosition(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up, bool autoComputeHomePosition=false);
        virtual void getHomePosition(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const;
		
        virtual void setAutoComputeHomePosition(bool flag) { m_bAutoComputeHomePosition = flag; } // 设置是否自动计算操作器的默认位置
        bool getAutoComputeHomePosition() const { return m_bAutoComputeHomePosition; }			// 获取是否自动计算操作器的默认位置
		
        virtual void computeHomePosition(const osg::IVBF_Camera* camera = NULL, bool useBoundingBox = false);// 计算默认位置

        virtual void home(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&) {} // 把相机移到默认位置
        virtual void home(double /*currentTime*/) {}						 // 把相机移到默认位置


        // 7、重载用于具体操作
        virtual void init(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&) {}    // 重置（初始化）
        virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);// 处理事件（如果处理了返回true，否则返回false）

        // 是否固定远近裁剪面，如跟踪操作器、第一人称漫游操作器、驾驶操作器等
        virtual bool IsFixedNearFar(){ return m_bFixedNearFar;}
        virtual void SetFixedNearFar(bool bFixed) { m_bFixedNearFar = bFixed; }

        virtual double GetFixedNear() { return m_dFixedNear; }
        virtual void   SetFixedNear(double dNear) { m_dFixedNear = dNear; }

        virtual double GetFixedFar() { return m_dFixedFar; }
        virtual void   SetFixedFar (double dFar ) { m_dFixedFar  = dFar; }
    protected:

        IVBF_CameraManipulatorImpl();
        IVBF_CameraManipulatorImpl(const IVBF_CameraManipulatorImpl& mm, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY);
        virtual ~IVBF_CameraManipulatorImpl();

        std::string getManipulatorName() const;

        unsigned int    m_nIntersectTraversalMask; // 求交遍历掩码用于控制场景图的哪部分进行求交运算，用于操作地形或碰撞检测

		// Home点信息
        bool    m_bAutoComputeHomePosition; // 是否自动计算Home点
        osg::Vec3d  m_vHomeEye;             // 视点
        osg::Vec3d  m_vHomeCenter;          // 目标点
        osg::Vec3d  m_vHomeUp;              // 向上向量


        ref_ptr<IVBF_CoordinateFrameCallback> _coordinateFrameCallback;

        ref_ptr<IVBF_ManipulatorCB> m_ipCallback;

        // 固定远近裁剪面，而不是系统自动计算
        bool   m_bFixedNearFar; //
        double m_dFixedNear; // 近裁剪面
        double m_dFixedFar;  // 远裁剪面

};

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulatorImpl.inl>

#endif
