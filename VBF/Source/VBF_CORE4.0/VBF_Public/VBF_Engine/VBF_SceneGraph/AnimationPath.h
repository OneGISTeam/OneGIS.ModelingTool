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

// ·������
// ����·������װ�˶Զ���·����һϵ�в������綯��ģʽ������·���ĵ����뵼����������ʱ�䡢
// �����Ĺؼ��㼰��ֵ����·���ȡ������ڸ��������λ�ú�ģ��Ŀ���λ�á�
class OSG_EXPORT AnimationPath : public virtual osg::CVBF_Object
{
    public:
    // IE���ܴ���
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
        

		// ����һ��ʱ��㣬��������任����
        bool getMatrix(double time,Matrixf& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getMatrix(matrix);
            return true;
        }

        // ����һ��ʱ��㣬��������任����
        bool getMatrix(double time,Matrixd& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getMatrix(matrix);
            return true;
        }
		// ����һ��ʱ��㣬��������任����������
        bool getInverse(double time,Matrixf& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getInverse(matrix);
            return true;
        }
        // ����һ��ʱ��㣬��������任����������
        bool getInverse(double time,Matrixd& matrix) const
        {
            ControlPoint cp;
            if (!getInterpolatedControlPoint(time,cp)) return false;
            cp.getInverse(matrix);
            return true;
        }

        // ����һ��ʱ��㣬����the local ControlPoint frame for a point
        virtual bool getInterpolatedControlPoint(double time,ControlPoint& controlPoint) const;
        
		// ����·���Ŀ��Ƶ�
        void insert(double time,const ControlPoint& controlPoint);
        
		// ��ȡ����������ʱ��
		// ·��������ʱ���ȡ�Ǳ�Ҫ�ģ��򶯻��Ľ������ܻᴥ��һ���µĶ����򳡾���û���ж϶��������ĺ�����
		// ��������һ����ʱ�����Ӷ�����ʼ��ʱ�����ݶ�������ʱ��ĳ����ж϶����Ƿ������
        double getFirstTime() const { if (!_timeControlPointMap.empty()) return _timeControlPointMap.begin()->first; else return 0.0;}
        double getLastTime() const { if (!_timeControlPointMap.empty()) return _timeControlPointMap.rbegin()->first; else return 0.0;}
        double getPeriod() const { return getLastTime()-getFirstTime();}
        
		
        enum LoopMode // ����ѭ��ģʽ
        {
            SWING,		// ����
            LOOP,		// ѭ��
            NO_LOOPING	// ��ѭ��
        };
        
		// ����/��ȡ����ѭ��ģʽ
        void setLoopMode(LoopMode lm) { _loopMode = lm; }        
        LoopMode getLoopMode() const { return _loopMode; }


        typedef std::map<double,ControlPoint> TimeControlPointMap;
        
        void setTimeControlPointMap(TimeControlPointMap& tcpm) { _timeControlPointMap=tcpm; }

        TimeControlPointMap& getTimeControlPointMap() { return _timeControlPointMap; }
        
        const TimeControlPointMap& getTimeControlPointMap() const { return _timeControlPointMap; }
        
        bool empty() const { return _timeControlPointMap.empty(); }
        
        void clear() { _timeControlPointMap.clear(); }

        // ��ȡ/д�붯��·������/��ASCII�ļ���
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
// ����·����AnimationPath���Ļص���������װ�˶Զ���·���Ĺ�����ʱ��ƫ�ơ�����ִ���ٶȡ���Ⱦ��ͣ״̬��
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
 
            
		// ����/��ȡ����·��
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
        
		// ����/��ȡʱ��Ŵ��ʣ��Զ���ִ�е��ٶȽ��п���
        void setTimeMultiplier(double multiplier) { _timeMultiplier = multiplier; }
        double getTimeMultiplier() const { return _timeMultiplier; }


		// ���á���ͣ���Զ������Ž��п���
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
