#ifndef OSGGA_CameraManipulator
#define OSGGA_CameraManipulator 1

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>


#define NEW_HOME_POSITION

// ���������������Ļ��࣬���ڶ�����������Ľӿں�Ĭ�Ϻ���

//class OSGGA_EXPORT IVBF_CameraManipulatorImpl : public IVBF_CameraManipulator
template<class T>
class IVBF_CameraManipulatorImpl : public T
{
     public:
        virtual const char* className() const { return "CameraManipulator"; }

		// 1������ϵ��ؽӿ�

        // ����/��ȡ"����ϵ�ص�"���ûص����߲������ϡ�����������
        virtual void setCoordinateFrameCallback(IVBF_CoordinateFrameCallback* cb) { _coordinateFrameCallback = cb; }
        IVBF_CoordinateFrameCallback* getCoordinateFrameCallback() { return _coordinateFrameCallback.get(); }
        const IVBF_CoordinateFrameCallback* getCoordinateFrameCallback() const { return _coordinateFrameCallback.get(); }

        virtual void SetCallback(IVBF_ManipulatorCB* cb){ m_ipCallback = cb; }

        osg::CoordinateFrame getCoordinateFrame(const osg::Vec3d& position) const;// ��ȡ����ϵ

		// ��ȡ���ϡ���ǰ����෽�������
        osg::Vec3d getSideVector(const osg::CoordinateFrame& cf) const { return osg::Vec3d(cf(0,0),cf(0,1),cf(0,2)); }
        osg::Vec3d getFrontVector(const osg::CoordinateFrame& cf) const { return osg::Vec3d(cf(1,0),cf(1,1),cf(1,2)); }
        osg::Vec3d getUpVector(const osg::CoordinateFrame& cf) const { return osg::Vec3d(cf(2,0),cf(2,1),cf(2,2)); }

		// 2��������ؽӿ�

		// 3���ռ��ںϾ��룬����˫Ŀ����
        virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return osgUtil::SceneView::PROPORTIONAL_TO_SCREEN_DISTANCE; }
        virtual float getFusionDistanceValue() const { return 1.0f; }

		// 4������/��ȡ�󽻱���������      
        void setIntersectTraversalMask(unsigned int mask) { m_nIntersectTraversalMask = mask; }
        unsigned int getIntersectTraversalMask() const { return m_nIntersectTraversalMask; }

		// 5����ڵ���صĺ�������Щ��������Ҫ������٣�����Щ����Ҫ��
        virtual void setNode(osg::IVBF_SGNode*) {}
        virtual const osg::IVBF_SGNode* getNode() const { return NULL; }
        virtual osg::IVBF_SGNode* getNode() { return NULL; }


		// 6����Ĭ��λ����صĺ���
        virtual void setHomePosition(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up, bool autoComputeHomePosition=false);
        virtual void getHomePosition(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const;
		
        virtual void setAutoComputeHomePosition(bool flag) { m_bAutoComputeHomePosition = flag; } // �����Ƿ��Զ������������Ĭ��λ��
        bool getAutoComputeHomePosition() const { return m_bAutoComputeHomePosition; }			// ��ȡ�Ƿ��Զ������������Ĭ��λ��
		
        virtual void computeHomePosition(const osg::IVBF_Camera* camera = NULL, bool useBoundingBox = false);// ����Ĭ��λ��

        virtual void home(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&) {} // ������Ƶ�Ĭ��λ��
        virtual void home(double /*currentTime*/) {}						 // ������Ƶ�Ĭ��λ��


        // 7���������ھ������
        virtual void init(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&) {}    // ���ã���ʼ����
        virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);// �����¼�����������˷���true�����򷵻�false��

        // �Ƿ�̶�Զ���ü��棬����ٲ���������һ�˳����β���������ʻ��������
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

        unsigned int    m_nIntersectTraversalMask; // �󽻱����������ڿ��Ƴ���ͼ���Ĳ��ֽ��������㣬���ڲ������λ���ײ���

		// Home����Ϣ
        bool    m_bAutoComputeHomePosition; // �Ƿ��Զ�����Home��
        osg::Vec3d  m_vHomeEye;             // �ӵ�
        osg::Vec3d  m_vHomeCenter;          // Ŀ���
        osg::Vec3d  m_vHomeUp;              // ��������


        ref_ptr<IVBF_CoordinateFrameCallback> _coordinateFrameCallback;

        ref_ptr<IVBF_ManipulatorCB> m_ipCallback;

        // �̶�Զ���ü��棬������ϵͳ�Զ�����
        bool   m_bFixedNearFar; //
        double m_dFixedNear; // ���ü���
        double m_dFixedFar;  // Զ�ü���

};

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulatorImpl.inl>

#endif
