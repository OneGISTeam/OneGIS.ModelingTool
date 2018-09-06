
#ifndef OSGGA_ANIMATION_PATH_MANIPULATOR
#define OSGGA_ANIMATION_PATH_MANIPULATOR 1

#include <VBF_Engine/VBF_SceneGraph/AnimationPath.h>
#include <VBF_Base/VBF_Notify.h>
#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>

namespace osgGA{

// 动画路径操作器，回放一个动画路径
// 动画路径文件为ascii格式，每行8个浮点数，分别为：
// time  px py pz ax ay az aw
// 其中:
//    time = 从动画开始到当前的时间（单位：秒）
//    px py pz = 世界坐标（笛卡尔坐标系）
//    ax ay az aw = 朝向(姿态)，四元数

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
        
        // 通过矩阵/逆矩阵设置操作器
        virtual void setByMatrix(const osg::Matrixd& matrix) { _matrix = matrix; }
        virtual void setByInverseMatrix(const osg::Matrixd& matrix) { _matrix.invert(matrix); }
        // 获取操作器的矩阵/逆矩阵
        virtual osg::Matrixd getMatrix() const { return _matrix; }
        virtual osg::Matrixd getInverseMatrix() const { return osg::Matrixd::inverse(_matrix); } 


        void setAnimationPath( osg::AnimationPath* animationPath ) { _animationPath=animationPath; }   
        osg::AnimationPath* getAnimationPath() { return _animationPath.get(); }      
        const osg::AnimationPath* getAnimationPath() const { return _animationPath.get(); }

        bool valid() const { return _animationPath.valid(); }


        // 与默认位置相关的函数,含义见接口
        void init(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        void home(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);
        void home(double currentTime);

        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        // 获取该操作器鼠标和键盘的用法
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
