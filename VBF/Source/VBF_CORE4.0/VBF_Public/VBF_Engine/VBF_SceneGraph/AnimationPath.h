#ifndef OSG_ANIMATIONPATH
#define OSG_ANIMATIONPATH 1

#include <map>
#include <istream>
#include <float.h>

#include <Types/VBF_Matrixf.h>
#include <Types/VBF_Matrixd.h>
#include <Types/VBF_Quat.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>

namespace osg {

// 路径动画
// 动画路径：封装了对动画路径的一系列操作，如动画模式、动画路径的导入与导出、动画的时间、
// 动画的关键点及插值生成路径等。可用于更改相机的位置和模型目标的位置。
class OSG_EXPORT AnimationPath : public virtual osg::CVBF_Object
{
    public:
    // IE可能错误
        AnimationPath():_loopMode(LOOP) {}

        AnimationPath(const AnimationPath& ap, const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            CVBF_Object(ap,copyop),
            _timeControlPointMap(ap._timeControlPointMap),
            _loopMode(ap._loopMode) {}

        META_Object(osg,AnimationPath);

        class ControlPoint
        {
        public:
            ControlPoint(): _scale(1.0,1.0,1.0) {}

            ControlPoint(const osg::Vec3d& position):
                _position(position),
                _rotation(),
                _scale(1.0,1.0,1.0) {}

            ControlPoint(const osg::Vec3d& position, const osg::Quat& rotation):
                _position(position),
                _rotation(rotation),
                _scale(1.0,1.0,1.0) {}

            ControlPoint(const osg::Vec3d& position, const osg::Quat& rotation, const osg::Vec3d& scale):
                _position(position),
                _rotation(rotation),
                _scale(scale) {}
        
            void setPosition(const osg::Vec3d& position) { _position = position; }
            const osg::Vec3d& getPosition() const { return _position; }

            void setRotation(const osg::Quat& rotation) { _rotation = rotation; }
            const osg::Quat& getRotation() const { return _rotation; }

            void setScale(const osg::Vec3d& scale) { _scale = scale; }
            const osg::Vec3d& getScale() const { return _scale; }

            inline void interpolate(float ratio,const ControlPoint& first, const ControlPoint& second)
            {
                float one_minus_ratio = 1.0f-ratio;
                _position = first._position*one_minus_ratio + second._position*ratio;
                _rotation.slerp(ratio,first._rotation,second._rotation);
                _scale = first._scale*one_minus_ratio + second._scale*ratio;
            }
            
            inline void interpolate(double ratio,const ControlPoint& first, const ControlPoint& second)
            {
                double one_minus_ratio = 1.0f-ratio;
                _position = first._position*one_minus_ratio + second._position*ratio;
                _rotation.slerp(ratio,first._rotation,second._rotation);
                _scale = first._scale*one_minus_ratio + second._scale*ratio;
            }

            inline void getMatrix(Matrixf& matrix) const
            {
                matrix.makeRotate(_rotation);
                matrix.preMultScale(_scale);
                matrix.postMultTranslate(_position);
            }

            inline void getMatrix(Matrixd& matrix) const
            {
                matrix.makeRotate(_rotation);
                matrix.preMultScale(_scale);
                matrix.postMultTranslate(_position);
            }

            inline void getInverse(Matrixf& matrix) const
            {
                matrix.makeRotate(_rotation.inverse());
                matrix.postMultScale(osg::Vec3d(1.0/_scale.x(),1.0/_scale.y(),1.0/_scale.z()));
                matrix.preMultTranslate(-_position);
            }

            inline void getInverse(Matrixd& matrix) const
            {
                matrix.makeRotate(_rotation.inverse());
                matrix.postMultScale(osg::Vec3d(1.0/_scale.x(),1.0/_scale.y(),1.0/_scale.z()));
                matrix.preMultTranslate(-_position);
            }

        protected:

            osg::Vec3d _position;
            osg::Quat  _rotation;
            osg::Vec3d _scale;

        };
        

		// 给定一个时间点，返回坐标变换矩阵
        bool getMatrix(double time,Matrixf& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getMatrix(matrix);
            return true;
        }

        // 给定一个时间点，返回坐标变换矩阵
        bool getMatrix(double time,Matrixd& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getMatrix(matrix);
            return true;
        }
		// 给定一个时间点，返回坐标变换矩阵的逆矩阵
        bool getInverse(double time,Matrixf& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getInverse(matrix);
            return true;
        }
        // 给定一个时间点，返回坐标变换矩阵的逆矩阵
        bool getInverse(double time,Matrixd& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getInverse(matrix);
            return true;
        }

        // 给定一个时间点，返回the local ControlPoint frame for a point
        virtual bool getInterpolatedControlPoint(double time,ControlPoint& controlPoint) const;
        
		// 插入路径的控制点
        void insert(double time,const ControlPoint& controlPoint);
        
		// 获取动画持续的时间
		// 路径动画的时间获取是必要的，因动画的结束可能会触发一个新的动作或场景。没有判断动画结束的函数，
		// 可以设置一个计时器，从动画开始计时，根据动画持续时间的长短判断动画是否结束。
        double getFirstTime() const { if (!_timeControlPointMap.empty()) return _timeControlPointMap.begin()->first; else return 0.0;}
        double getLastTime() const { if (!_timeControlPointMap.empty()) return _timeControlPointMap.rbegin()->first; else return 0.0;}
        double getPeriod() const { return getLastTime()-getFirstTime();}
        
		
        enum LoopMode // 动画循环模式
        {
            SWING,		// 单摆
            LOOP,		// 循环
            NO_LOOPING	// 非循环
        };
        
		// 设置/获取动画循环模式
        void setLoopMode(LoopMode lm) { _loopMode = lm; }        
        LoopMode getLoopMode() const { return _loopMode; }


        typedef std::map<double,ControlPoint> TimeControlPointMap;
        
        void setTimeControlPointMap(TimeControlPointMap& tcpm) { _timeControlPointMap=tcpm; }

        TimeControlPointMap& getTimeControlPointMap() { return _timeControlPointMap; }
        
        const TimeControlPointMap& getTimeControlPointMap() const { return _timeControlPointMap; }
        
        bool empty() const { return _timeControlPointMap.empty(); }
        
        void clear() { _timeControlPointMap.clear(); }

        // 读取/写入动画路径（从/到ASCII文件）
        void read(std::istream& in);
        void write(std::ostream& out) const;

        /** Write the control point to a flat ASCII file stream. */
        void write(TimeControlPointMap::const_iterator itr, std::ostream& out) const;

    protected:
    
        virtual ~AnimationPath() {}

        TimeControlPointMap _timeControlPointMap;
        LoopMode            _loopMode;

};
// AnimationPathCallback can be attached directly to Transform nodes to move subgraphs around the scene.
// 动画路径（AnimationPath）的回调函数，封装了对动画路径的管理，如时间偏移、动画执行速度、渲染暂停状态等
class OSG_EXPORT AnimationPathCallback : public NodeCallback
{
    public:

        AnimationPathCallback():
            _pivotPoint(0.0,0.0,0.0),
            _useInverseMatrix(false),
            _timeOffset(0.0),
            _timeMultiplier(1.0),
            _firstTime(DBL_MAX),
            _latestTime(0.0),
            _pause(false),
            _pauseTime(0.0) {}

        AnimationPathCallback(const AnimationPathCallback& apc,const CopyOp& copyop):
            NodeCallback(apc,copyop),
            _animationPath(apc._animationPath),
            _pivotPoint(apc._pivotPoint),
            _useInverseMatrix(apc._useInverseMatrix),
            _timeOffset(apc._timeOffset),
            _timeMultiplier(apc._timeMultiplier),
            _firstTime(apc._firstTime),
            _latestTime(apc._latestTime),
            _pause(apc._pause),
            _pauseTime(apc._pauseTime) {}

        
        META_Object(osg,AnimationPathCallback);

        /** Construct an AnimationPathCallback with a specified animation path.*/
        AnimationPathCallback(AnimationPath* ap,double timeOffset=0.0,double timeMultiplier=1.0):
            _animationPath(ap),
            _pivotPoint(0.0,0.0,0.0),
            _useInverseMatrix(false),
            _timeOffset(timeOffset),
            _timeMultiplier(timeMultiplier),
            _firstTime(DBL_MAX),
            _latestTime(0.0),
            _pause(false),
            _pauseTime(0.0) {}

        /** Construct an AnimationPathCallback and automatically create an animation path to produce a rotation about a point.*/
        AnimationPathCallback(const osg::Vec3d& pivot,const osg::Vec3d& axis,float angularVelocity);
 
            
		// 设置/获取动画路径
        void setAnimationPath(AnimationPath* path) { _animationPath = path; }
        AnimationPath* getAnimationPath() { return _animationPath.get(); }
        const AnimationPath* getAnimationPath() const { return _animationPath.get(); }

		//
        inline void setPivotPoint(const Vec3d& pivot) { _pivotPoint = pivot; }
        inline const Vec3d& getPivotPoint() const { return _pivotPoint; }

        void setUseInverseMatrix(bool useInverseMatrix) { _useInverseMatrix = useInverseMatrix; }
        bool getUseInverseMatrix() const { return _useInverseMatrix; }

        void setTimeOffset(double offset) { _timeOffset = offset; }
        double getTimeOffset() const { return _timeOffset; }
        
		// 设置/获取时间放大倍率，对动画执行的速度进行控制
        void setTimeMultiplier(double multiplier) { _timeMultiplier = multiplier; }
        double getTimeMultiplier() const { return _timeMultiplier; }


		// 重置、暂停。对动画播放进行控制
        virtual void reset();
        void setPause(bool pause);
        bool getPause() const { return _pause; }

        /** Get the animation time that is used to specify the position along
          * the AnimationPath. Animation time is computed from the formula:
          *   ((_latestTime-_firstTime)-_timeOffset)*_timeMultiplier.*/
        virtual double getAnimationTime() const;

        /** Implements the callback. */
        virtual void operator()(IVBF_SGNode* node, NodeVisitor* nv);
        
        void update(osg::IVBF_SGNode& node);

    public:

        ref_ptr<AnimationPath>  _animationPath;
        osg::Vec3d              _pivotPoint;
        bool                    _useInverseMatrix;
        double                  _timeOffset;
        double                  _timeMultiplier;
        double                  _firstTime;
        double                  _latestTime;
        bool                    _pause;
        double                  _pauseTime;

    protected:
    
        ~AnimationPathCallback(){}

};

}

#endif
