
#ifndef OSGGA_ANIMATION_PATH_MANIPULATOR
#define OSGGA_ANIMATION_PATH_MANIPULATOR 1

#include <VBF_Engine/VBF_SceneGraph/AnimationPath.h>
#include <VBF_Base/VBF_Notify.h>
#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>

namespace osgGA{

// ����·�����������ط�һ������·��
// ����·���ļ�Ϊascii��ʽ��ÿ��8�����������ֱ�Ϊ��
// time  px py pz ax ay az aw
// ����:
//    time = �Ӷ�����ʼ����ǰ��ʱ�䣨��λ���룩
//    px py pz = �������꣨�ѿ�������ϵ��
//    ax ay az aw = ����(��̬)����Ԫ��

class OSGGA_EXPORT AnimationPathManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
    public:  
        AnimationPathManipulator( osg::AnimationPath* animationPath=0 );
        AnimationPathManipulator( const std::string& filename );
        
        virtual const char* className() const { return "AnimationPath"; }

        void setTimeScale(double s) { _timeScale = s; }
        double getTimeScale() const { return _timeScale; }
        
        void setTimeOffset(double o) { _timeOffset = o; }
        double getTimeOffset() const { return _timeOffset; }

        struct AnimationCompletedCallback : public virtual CVBF_Referenced
        {
            virtual void completed(const AnimationPathManipulator* apm) = 0;
        };

        void setAnimationCompletedCallback(AnimationCompletedCallback* acc) { _animationCompletedCallback = acc; }
        AnimationCompletedCallback* getAnimationCompletedCallback() { return _animationCompletedCallback.get(); }
        const AnimationCompletedCallback* getAnimationCompletedCallback() const { return _animationCompletedCallback.get(); }

        void setPrintOutTimingInfo(bool printOutTimingInfo) { _printOutTimingInfo=printOutTimingInfo; }
        bool getPrintOutTimingInfo() const { return _printOutTimingInfo; }
        
        // ͨ������/��������ò�����
        virtual void setByMatrix(const osg::Matrixd& matrix) { _matrix = matrix; }
        virtual void setByInverseMatrix(const osg::Matrixd& matrix) { _matrix.invert(matrix); }
        // ��ȡ�������ľ���/�����
        virtual osg::Matrixd getMatrix() const { return _matrix; }
        virtual osg::Matrixd getInverseMatrix() const { return osg::Matrixd::inverse(_matrix); } 


        void setAnimationPath( osg::AnimationPath* animationPath ) { _animationPath=animationPath; }   
        osg::AnimationPath* getAnimationPath() { return _animationPath.get(); }      
        const osg::AnimationPath* getAnimationPath() const { return _animationPath.get(); }

        bool valid() const { return _animationPath.valid(); }


        // ��Ĭ��λ����صĺ���,������ӿ�
        void init(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        void home(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);
        void home(double currentTime);

        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        // ��ȡ�ò��������ͼ��̵��÷�
        virtual void GetUsage(::ApplicationUsage& usage) const;
            
    protected:

        bool _valid;
        
        bool _printOutTimingInfo;

        void handleFrame( double time );

        ref_ptr<osg::AnimationPath> _animationPath;
        
        double  _timeOffset;
        double  _timeScale;

        ref_ptr<AnimationCompletedCallback> _animationCompletedCallback;

        double  _pauseTime;
        bool    _isPaused;
        
        double  _realStartOfTimedPeriod;
        double  _animStartOfTimedPeriod;
        int     _numOfFramesSinceStartOfTimedPeriod;
        
        osg::Matrixd _matrix;

};

}

#endif
