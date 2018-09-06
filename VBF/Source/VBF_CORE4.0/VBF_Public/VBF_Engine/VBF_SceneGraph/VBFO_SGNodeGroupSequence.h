#ifndef OSG_SEQUENCE
#define OSG_SEQUENCE 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>

// ֡�������ǳ����Ķ�����ʽ��������֡���š�ͨ����ͼƬ֡������ģ��֡����������֡�����ȡ�
// ��Դ���Ľϴ󣬵��ǳ����������Ա����κ����ݣ� �����ڵ�Ӱ�Ĳ���ģʽ�����ʺ������ϸ��Ķ�������˵����Ʈ����

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

	// ����/��ȡ�Ǹ��ӽڵ㽫Ҫ������
	virtual void setValue(int value)=0;
	virtual int getValue() const=0;

	// ����/��ȡ�ӽڵ��ʱ�䣨�룩
	virtual void setTime(unsigned int frame, double t)=0;
	virtual double getTime(unsigned int frame) const=0;

	// ����/��ȡ�ӽڵ��б��ʱ�䣨�룩
	virtual void setTimeList(const std::vector<double>& timeList)=0;
	virtual const std::vector<double>& getTimeList() const=0;

	// ����/��ȡ�µ��ӽڵ��Ĭ��ʱ�䣨���t<0��t=0��
	virtual void setDefaultTime(double t) =0;
	virtual double getDefaultTime(void) const =0;

	// ����/��ȡѭ�������һ֮֡���ʱ�䣨���t<= 0�����ԣ�
	virtual void setLastFrameTime(double t)=0;
	virtual double getLastFrameTime(void) const =0;

	// ��ȡ֡��
	virtual unsigned int getNumFrames() const =0;

	enum LoopMode // ����ѭ��ģʽ
	{
		LOOP,	// ѭ�����ظ���1-N֡
		SWING	// ���ڣ��ظ�1->N��(N-1)->1
	};

	// ���ö���ѭ��ģʽ
	virtual void setLoopMode(LoopMode mode)=0;
	virtual LoopMode getLoopMode() const =0;


	// ����/��ȡ�����Ļ����Ϣ����interval���Ƿ�ʼ
	virtual void setBegin(int begin) =0;
	virtual int getBegin() const=0;

	// ����/��ȡ�����Ļ����Ϣ����interval���Ƿ����
	virtual void setEnd(int end)=0;
	virtual int getEnd() const=0;

	/** Set sequence mode & interval (range of children to be displayed). */
	virtual void setInterval(LoopMode mode, int begin, int end)=0;
	virtual void getInterval(LoopMode& mode, int& begin, int& end) const=0;

	// ����/��ȡ�������ٶ�
	virtual void setSpeed(float speed)=0;
	virtual float getSpeed() const=0;

	// ����/��ȡ�������ظ�������-1��ʾ���޴Σ�
	virtual void setNumRepeats(int nreps) =0;
	virtual int getNumRepeats() const =0;

	// ����/��ȡ�������ٶȺ��ظ�������Ĭ��ֵ-1��ʾ���޴Σ�
	virtual void setDuration(float speed, int nreps = -1)=0;
	virtual void getDuration(float& speed, int& nreps) const=0;

	enum SequenceMode // �����Ĳ���ģʽ
	{
		START,	// ��ʼ
		STOP,	// ֹͣ
		PAUSE,	// ��ͣ
		RESUME	// ����
	};

	// ����/��ȡ�����Ĳ���ģʽ
	virtual void setMode(SequenceMode mode)=0;
	virtual SequenceMode getMode() const =0;

	// ����/��ȡ�Ƿ�ͬ����
	virtual void setSync(bool sync)=0;
	virtual bool getSync() const =0;

	// ����/��ȡֹͣ���Ƿ���������ӽڵ�
	virtual void setClearOnStop(bool clearOnStop)=0;
	virtual bool getClearOnStop() const =0;
};

// Sequence��Ҫ����֡�����Ĺ�����Ⱦ�����������ڵ㡢���ö���ģʽ�����ö���״̬���ٶȵ�
// ���Ը���ʱ���ڸ��ӽڵ�֮���л����Ӷ��γɶ���Ч��
// ͼƬ���Դ���һ���ı����������ֿ�����ӵ�Geode��ģ�Ϳ���ֱ����ӡ�
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


        // ����/��ȡ�Ǹ��ӽڵ㽫Ҫ������
        void setValue(int value) { _value = value ; }
        int getValue() const { return _value; }

		// ����/��ȡ�ӽڵ��ʱ�䣨�룩
        void setTime(unsigned int frame, double t);
        double getTime(unsigned int frame) const;
        
        // ����/��ȡ�ӽڵ��б��ʱ�䣨�룩
        void setTimeList(const std::vector<double>& timeList) { _frameTime = timeList; }
        const std::vector<double>& getTimeList() const { return _frameTime; }

		// ����/��ȡ�µ��ӽڵ��Ĭ��ʱ�䣨���t<0��t=0��
        void setDefaultTime(double t) {_defaultTime = (t<0.?0.:t);}
        double getDefaultTime(void) const {return _defaultTime;};

        // ����/��ȡѭ�������һ֮֡���ʱ�䣨���t<= 0�����ԣ�
        void setLastFrameTime(double t) {_lastFrameTime = (t<0.?0.:t);}
        double getLastFrameTime(void) const {return _lastFrameTime;};

        // ��ȡ֡��
        inline unsigned int getNumFrames() const { return _frameTime.size(); }

 
        // ���ö���ѭ��ģʽ
        void setLoopMode(LoopMode mode) { _loopMode = mode; _value = -1; }
        LoopMode getLoopMode() const { return _loopMode; }
        
        // ����/��ȡ�����Ļ����Ϣ����interval���Ƿ�ʼ
        void setBegin(int begin) { _begin = begin; _value = -1; }
        int getBegin() const { return _begin; }
        
        // ����/��ȡ�����Ļ����Ϣ����interval���Ƿ����
        void setEnd(int end) { _end = end; _value = -1; }
        int getEnd() const { return _end; }

		// ����ѭ��ģʽ�ͼ�����ӽڵ���ʾ�ķ��ȣ�range����
        void setInterval(LoopMode mode, int begin, int end);
        inline void getInterval(LoopMode& mode, int& begin, int& end) const
        {
            mode = _loopMode;
            begin = _begin;
            end = _end;
        }
        
        // ����/��ȡ�������ٶ�
        void setSpeed(float speed) { _speed = speed; }
        float getSpeed() const { return _speed; }
        
        // ����/��ȡ�������ظ�������-1��ʾ���޴Σ�
        void setNumRepeats(int nreps) { _nreps = (nreps<0?-1:nreps); _nrepsRemain = _nreps; }
        int getNumRepeats() const { return _nreps; }

		// ����/��ȡ�������ٶȺ��ظ�������Ĭ��ֵ-1��ʾ���޴Σ�
        void setDuration(float speed, int nreps = -1);
        inline void getDuration(float& speed, int& nreps) const
        {
            speed = _speed;
            nreps = _nreps;
        }

     

        // ����/��ȡ�����Ĳ���ģʽ
        void setMode(SequenceMode mode);
        inline SequenceMode getMode() const { return _mode; }

		// ����/��ȡ�Ƿ�ͬ���������ͬ����Ĭ��ֵ����frames will not be sync'd to frameTime��������Ȼ
        void setSync(bool sync) { _sync = sync; }
        bool getSync() const { return _sync; }

        // ����/��ȡֹͣ���Ƿ���������ӽڵ�
        void setClearOnStop(bool clearOnStop) { _clearOnStop = clearOnStop; }
        bool getClearOnStop() const { return _clearOnStop; }

    protected :

        virtual ~Sequence() {}// IE���ܴ���

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

        SequenceMode _mode; // ��ǰ�����Ĳ���ģʽ

        bool _sync ;  // �Ƿ�ͬ��

        bool _clearOnStop ; // ֹͣʱ���Ƿ�����ӽڵ�

};
  
}

#endif
