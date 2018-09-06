#ifndef OSG_SEQUENCE
#define OSG_SEQUENCE 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>

// 帧动画，是常见的动画形式，就是逐帧播放。通常有图片帧动画、模型帧动画、文字帧动画等。
// 资源消耗较大，但非常灵活，几乎可以表现任何内容， 类似于电影的播放模式，很适合与表演细腻的动画，如说话，飘动等

namespace osg 
{
class IVBF_SGNodeGroupSequence : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupSequence(){}
	IVBF_SGNodeGroupSequence(const IVBF_SGNodeGroupSequence& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupSequence(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}
    
	/*
	virtual bool addChild( IVBF_SGNode *child)=0;     
	virtual bool addChild( IVBF_SGNode *child, double t)=0;
    virtual bool insertChild( unsigned int index, IVBF_SGNode *child)=0;
    virtual bool insertChild( unsigned int index, IVBF_SGNode *child, double t)=0;
    virtual bool removeChild( IVBF_SGNode *child )=0;
    virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove)=0;
	*/

	// 设置/获取那个子节点将要被播放
	virtual void setValue(int value)=0;
	virtual int getValue() const=0;

	// 设置/获取子节点的时间（秒）
	virtual void setTime(unsigned int frame, double t)=0;
	virtual double getTime(unsigned int frame) const=0;

	// 设置/获取子节点列表的时间（秒）
	virtual void setTimeList(const std::vector<double>& timeList)=0;
	virtual const std::vector<double>& getTimeList() const=0;

	// 设置/获取新的子节点的默认时间（如果t<0，t=0）
	virtual void setDefaultTime(double t) =0;
	virtual double getDefaultTime(void) const =0;

	// 设置/获取循环的最后一帧之后的时间（如果t<= 0，忽略）
	virtual void setLastFrameTime(double t)=0;
	virtual double getLastFrameTime(void) const =0;

	// 获取帧数
	virtual unsigned int getNumFrames() const =0;

	enum LoopMode // 动画循环模式
	{
		LOOP,	// 循环，重复从1-N帧
		SWING	// 单摆，重复1->N，(N-1)->1
	};

	// 设置动画循环模式
	virtual void setLoopMode(LoopMode mode)=0;
	virtual LoopMode getLoopMode() const =0;


	// 设置/获取间隔（幕间休息）（interval）是否开始
	virtual void setBegin(int begin) =0;
	virtual int getBegin() const=0;

	// 设置/获取间隔（幕间休息）（interval）是否结束
	virtual void setEnd(int end)=0;
	virtual int getEnd() const=0;

	/** Set sequence mode & interval (range of children to be displayed). */
	virtual void setInterval(LoopMode mode, int begin, int end)=0;
	virtual void getInterval(LoopMode& mode, int& begin, int& end) const=0;

	// 设置/获取动画的速度
	virtual void setSpeed(float speed)=0;
	virtual float getSpeed() const=0;

	// 设置/获取动画的重复次数（-1表示无限次）
	virtual void setNumRepeats(int nreps) =0;
	virtual int getNumRepeats() const =0;

	// 设置/获取动画的速度和重复次数（默认值-1表示无限次）
	virtual void setDuration(float speed, int nreps = -1)=0;
	virtual void getDuration(float& speed, int& nreps) const=0;

	enum SequenceMode // 动画的播放模式
	{
		START,	// 开始
		STOP,	// 停止
		PAUSE,	// 暂停
		RESUME	// 继续
	};

	// 设置/获取动画的播放模式
	virtual void setMode(SequenceMode mode)=0;
	virtual SequenceMode getMode() const =0;

	// 设置/获取是否同步。
	virtual void setSync(bool sync)=0;
	virtual bool getSync() const =0;

	// 设置/获取停止后是否清除所有子节点
	virtual void setClearOnStop(bool clearOnStop)=0;
	virtual bool getClearOnStop() const =0;
};

// Sequence主要负责帧动画的管理渲染操作，如加入节点、设置动画模式、设置动画状态及速度等
// 可以根据时间在各子节点之间切换，从而形成动画效果
// 图片可以创建一个四边形纹理、文字可以添加到Geode，模型可以直接添加。
class OSG_EXPORT Sequence : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupSequence>
{
    public :

        Sequence();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Sequence(const Sequence&, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, Sequence);

        virtual void traverse(NodeVisitor& nv);

        // the relationship between the _frameTime vector and the _children
        // vector is a bit of a mess.  This is how it was in previous versions,
        // and there's no way out of it if upward compatibility needs to be
        // maintained.  New code should set defaultTime and use addChild, and
        // not mess with the setTime method

        virtual bool addChild( IVBF_SGNode *child);
        virtual bool addChild( IVBF_SGNode *child, double t);

        virtual bool insertChild( unsigned int index, IVBF_SGNode *child);
        virtual bool insertChild( unsigned int index, IVBF_SGNode *child, double t);

        virtual bool removeChild( IVBF_SGNode *child );
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);


        // 设置/获取那个子节点将要被播放
        void setValue(int value) { _value = value ; }
        int getValue() const { return _value; }

		// 设置/获取子节点的时间（秒）
        void setTime(unsigned int frame, double t);
        double getTime(unsigned int frame) const;
        
        // 设置/获取子节点列表的时间（秒）
        void setTimeList(const std::vector<double>& timeList) { _frameTime = timeList; }
        const std::vector<double>& getTimeList() const { return _frameTime; }

		// 设置/获取新的子节点的默认时间（如果t<0，t=0）
        void setDefaultTime(double t) {_defaultTime = (t<0.?0.:t);}
        double getDefaultTime(void) const {return _defaultTime;};

        // 设置/获取循环的最后一帧之后的时间（如果t<= 0，忽略）
        void setLastFrameTime(double t) {_lastFrameTime = (t<0.?0.:t);}
        double getLastFrameTime(void) const {return _lastFrameTime;};

        // 获取帧数
        inline unsigned int getNumFrames() const { return _frameTime.size(); }

 
        // 设置动画循环模式
        void setLoopMode(LoopMode mode) { _loopMode = mode; _value = -1; }
        LoopMode getLoopMode() const { return _loopMode; }
        
        // 设置/获取间隔（幕间休息）（interval）是否开始
        void setBegin(int begin) { _begin = begin; _value = -1; }
        int getBegin() const { return _begin; }
        
        // 设置/获取间隔（幕间休息）（interval）是否结束
        void setEnd(int end) { _end = end; _value = -1; }
        int getEnd() const { return _end; }

		// 设置循环模式和间隔（子节点显示的幅度（range））
        void setInterval(LoopMode mode, int begin, int end);
        inline void getInterval(LoopMode& mode, int& begin, int& end) const
        {
            mode = _loopMode;
            begin = _begin;
            end = _end;
        }
        
        // 设置/获取动画的速度
        void setSpeed(float speed) { _speed = speed; }
        float getSpeed() const { return _speed; }
        
        // 设置/获取动画的重复次数（-1表示无限次）
        void setNumRepeats(int nreps) { _nreps = (nreps<0?-1:nreps); _nrepsRemain = _nreps; }
        int getNumRepeats() const { return _nreps; }

		// 设置/获取动画的速度和重复次数（默认值-1表示无限次）
        void setDuration(float speed, int nreps = -1);
        inline void getDuration(float& speed, int& nreps) const
        {
            speed = _speed;
            nreps = _nreps;
        }

     

        // 设置/获取动画的播放模式
        void setMode(SequenceMode mode);
        inline SequenceMode getMode() const { return _mode; }

		// 设置/获取是否同步。如果不同步（默认值），frames will not be sync'd to frameTime，否则亦然
        void setSync(bool sync) { _sync = sync; }
        bool getSync() const { return _sync; }

        // 设置/获取停止后是否清除所有子节点
        void setClearOnStop(bool clearOnStop) { _clearOnStop = clearOnStop; }
        bool getClearOnStop() const { return _clearOnStop; }

    protected :

        virtual ~Sequence() {}// IE可能错误

        // get next _value in sequence
        int _getNextValue(void) ;

        // update local variables
        void _update(void) ;

        // init to -1 to mean "restart"
        int _value;

        // current time, set by traverse
        double _now ;

        // time this frame started.  init to -1.0f- means get current time
        double _start;

        // a vector of frame times, one per value
        std::vector<double> _frameTime;

        // the total time for one sequence, from BEGIN to END
        double _totalTime ;

        // true if _totalTime needs to be recalculated because setTime or
        // setInterval was invoked, or a new child was added
        bool _resetTotalTime ;

        // store "loop mde", either LOOP or SWING
        // init to LOOP- set by setInterval
        LoopMode _loopMode;

        // first and last "values" to sequence through
        // begin inits to 0
        // end inits to -1- means to init to number of values
        int _begin, _end;

        // multiplier of real-time clock- set to N to go N times faster
        // init to 0- going nowhere
        float _speed;

        // _nreps: how many times to repeat- default param is -1, repeat forever
        // init to 0, no repetitions
        // _nrepsRemain: set to nreps and counts down every traversal, 
        // stopping when it gets to zero.  init to 0
        int _nreps, _nrepsRemain;

        // frame step (are we stepping forward or backward?)
        int _step;

        // default frame time for newly created frames or children- default is 1.
        // set by setDefaultTime
        double _defaultTime ;

        // special time to display last frame of last loop
        // <= zero means to not do anything special
        double _lastFrameTime ;

        // save the actual time of the last frame, and what value was stored
        double _saveRealLastFrameTime ;
        unsigned int _saveRealLastFrameValue ;

        SequenceMode _mode; // 当前动画的播放模式

        bool _sync ;  // 是否同步

        bool _clearOnStop ; // 停止时，是否清除子节点

};
  
}

#endif
