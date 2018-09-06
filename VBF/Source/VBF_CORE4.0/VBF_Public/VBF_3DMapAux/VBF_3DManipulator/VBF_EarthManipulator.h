// earth��������ʵ���ࡣ
#ifndef __VBF_EARTH_MANIPULATOR_H__
#define __VBF_EARTH_MANIPULATOR_H__

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>
#include "VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h"

#include <VBF_3DMapAux/VBF_3DManipulator/VBF_3DManipulator_Global.h>


#include <VBF_Base/VBF_Timer.h>
#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerSimple.h>

#include <map>
#include <list>
#include <utility>

//��¼·����
using namespace osgEarth::Util;
using namespace osgEarth;

// �������������
class VBF_3DMANIPULATORSHARED_EXPORT VBF_EarthManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
public:
	// �����������������ͣ������������¼���
	enum ActionType
	{
		ACTION_NULL,
		ACTION_HOME,
		ACTION_GOTO,
		ACTION_PAN,
		ACTION_PAN_LEFT,
		ACTION_PAN_RIGHT,
		ACTION_PAN_UP,
		ACTION_PAN_DOWN,
		ACTION_ROTATE,
		ACTION_ROTATE_LEFT,
		ACTION_ROTATE_RIGHT,
		ACTION_ROTATE_UP,
		ACTION_ROTATE_DOWN,
		ACTION_ZOOM,
		ACTION_ZOOM_IN,
		ACTION_ZOOM_OUT
	};

	// �¼������ͣ����붯����
	enum EventType
	{
		EVENT_MOUSE_CLICK        = osgGA::GUIEventAdapter::USER << 1,
		EVENT_MOUSE_DOUBLE_CLICK = osgGA::GUIEventAdapter::DOUBLECLICK,
		EVENT_MOUSE_DRAG         = osgGA::GUIEventAdapter::DRAG,
		EVENT_KEY_DOWN           = osgGA::GUIEventAdapter::KEYDOWN,
		EVENT_SCROLL             = osgGA::GUIEventAdapter::SCROLL
	};

	// ����
	enum MouseEvent
	{
		MOUSE_LEFT_BUTTON   = osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON,
		MOUSE_MIDDLE_BUTTON = osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON,
		MOUSE_RIGHT_BUTTON  = osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON
	};

	// Action��ѡ��
	enum ActionOptionType
	{
		OPTION_SCALE_X,             // ˮƽ�����ķŴ���
		OPTION_SCALE_Y,             // ��ֱ�����ķŴ���
		OPTION_CONTINUOUS,          // ���������̧��ʱ����ִ�ж���
		OPTION_SINGLE_AXIS,         // �Ƿ�һ�ν�����һ���� (ֵ�����)
		OPTION_GOTO_RANGE_FACTOR,   // for ACTION_GOTO, multiply the Range by this factor (to zoom in/out)
		OPTION_DURATION             // ��ɶ�����ʱ��(��)
	};

	/** Tethering options **/
	enum TetherMode
	{
		TETHER_CENTER,              // The camera will follow the center of the node.
		TETHER_CENTER_AND_ROTATION, // The camera will follow the node and all rotations made by the node
		TETHER_CENTER_AND_HEADING   // The camera will follow the node and only follow heading rotation
	};

	struct  ActionOption
	{
		ActionOption() { }
		ActionOption( int option, bool value ) : _option(option), _bool_value(value) { }
		ActionOption( int option, int value ) : _option(option), _int_value(value) { }
		ActionOption( int option, double value ) : _option(option), _dbl_value(value) { }

		int option() const { return _option; }
		bool boolValue() const { return _bool_value; }
		int intValue() const { return _int_value; }
		double doubleValue() const { return _dbl_value; }

	private:
		int _option;
		union
		{
			bool   _bool_value;
			int    _int_value;
			double _dbl_value;
		};
	};

	struct  ActionOptions : public std::vector<ActionOption>
	{
		void add( int option, bool value ) { push_back( ActionOption(option,value) ); }
		void add( int option, int value )  { push_back( ActionOption(option,value) ); }
		void add( int option, double value) { push_back( ActionOption(option,value) ); }
	};

private:
	struct InputSpec 
	{
		InputSpec( int nType, int nInputMask, int nModkeyMask )
			: _event_type(nType), _input_mask(nInputMask), _modkey_mask( nModkeyMask ) { }
		InputSpec( const InputSpec& rhs )
			: _event_type(rhs._event_type), _input_mask(rhs._input_mask), _modkey_mask(rhs._modkey_mask) { }

		bool operator == ( const InputSpec& rhs ) const
		{
			return _event_type == rhs._event_type && _input_mask == rhs._input_mask &&
				((_modkey_mask|osgGA::GUIEventAdapter::MODKEY_NUM_LOCK) == (rhs._modkey_mask|osgGA::GUIEventAdapter::MODKEY_NUM_LOCK));
		}

		inline bool operator < (const InputSpec& rhs) const
		{
			if ( _event_type < rhs._event_type) return true;
			else if ( _event_type > rhs._event_type ) return false;
			else if ( _input_mask < rhs._input_mask ) return true;
			else if ( _input_mask > rhs._input_mask ) return false;
			else return ( _modkey_mask < rhs._modkey_mask );
		}

		int _event_type;
		int _input_mask;
		int _modkey_mask;
	};
	typedef std::list<InputSpec> InputSpecs;

	enum Direction
	{
		DIR_NA,
		DIR_LEFT,
		DIR_RIGHT,
		DIR_UP,
		DIR_DOWN
	};

	struct Action
	{
		Action( ActionType type =ACTION_NULL );
		Action( ActionType type, const ActionOptions& options );
		Action( const Action& rhs );

		bool    getBoolOption( int option, bool defaultValue ) const;
		int     getIntOption( int option, int defaultValue ) const;
		double  getDoubleOption( int option, double defaultValue ) const;

		ActionType  _type;
		Direction   _dir;
		ActionOptions _options;

	private:
		void init();
	};

	void dumpActionInfo( const Action& action, osg::NotifySeverity level ) const;

	static Action NullAction;

public:
	// ���Դ������"Settings"���������ò�ͬ�Ĳ�����ʽ������ʱ����applySettings()ȷ��ѡ�õĲ�����ʽ
	class VBF_3DMANIPULATORSHARED_EXPORT Settings : public ::CVBF_Referenced
	{
	public:
		Settings();
		Settings( const Settings& rhs );

		// button_maskΪosgGA::GUIEventAdapter::MouseButtonMask
		// modkey_maskΪosgGA::GUIEventAdapter::ModKeyMask

		// ������¼���Action��.optionsΪOPTION_CONTINUOUS, OPTION_SCALE_X, OPTION_SCALE_Y
		void bindMouse(ActionType action, int button_mask,int modkey_mask = 0L, const ActionOptions& options =ActionOptions() );

		// ����굥���¼���Action�󶨡�optionsΪOPTION_GOTO_RANGE_FACTOR, OPTION_DURATION
		void bindMouseClick( ActionType action, int button_mask, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// �����˫���¼���Action�󶨡�optionsΪOPTION_GOTO_RANGE_FACTOR, OPTION_DURATION
		void bindMouseDoubleClick( ActionType action, int button_mask, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// �Ѽ����¼���Action�󶨡�optionsΪOPTION_CONTINUOUS
		void bindKey(ActionType action, int key, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// ���������¼���Action�󶨡�optionsΪOPTION_SCALE_Y
		void bindScroll( ActionType action, int scrolling_motion, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// ����/��ȡ�������ж�1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive
		void setMouseSensitivity( double value ) { _mouse_sens = value; }
		double getMouseSensitivity() const { return _mouse_sens; }

		// ����/��ȡ���̵����жȣ���ÿ����һ��LEFT���������ƶ��ľ��룩1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive
		void setKeyboardSensitivity( double value ) { _keyboard_sens = value; }
		double getKeyboardSensitivity() const { return _keyboard_sens; }

		// ����/��ȡ���ֵ����жȣ���Ŵ�ı�����1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive.
		void setScrollSensitivity( double value ) { _scroll_sens = value; }
		double getScrollSensitivity() const { return _scroll_sens; }

		// ����/��ȡ������ת��Ϊtrueʱ���ܿ���azimuth��falseʱ�ɿ���pitch��azimuth��Ĭ��Ϊfalse
		void setSingleAxisRotation( bool value ) { _single_axis_rotation = value; }
		bool getSingleAxisRotation() const { return _single_axis_rotation; }

		// ����/��ȡ�Ƿ����˦������
		void setThrowingEnabled( bool value ) { _throwing = value; }
		bool getThrowingEnabled() const { return _throwing; }

		// ����/��ȡ����ʱ�Ƿ�̶���λ��
		void setLockAzimuthWhilePanning( bool value ) { _lock_azim_while_panning = value; }
		bool getLockAzimuthWhilePanning() const { return _lock_azim_while_panning; }


		// ����/��ȡ���/��С�����ǣ���λ��
		void setMinMaxPitch( double min_pitch, double max_pitch );
		double getMinPitch() const { return _min_pitch; }
		double getMaxPitch() const { return _max_pitch; }        

		// ����/��ȡ��ȡ���ƫ�������������꣩
		void setMaxOffset(double max_x_offset, double max_y_offset);
		double getMaxXOffset() const { return _max_x_offset; }
		double getMaxYOffset() const { return _max_y_offset; }

		// ����/��ȡ�����С���߾��루�������꣩
		void setMinMaxDistance( double min_distance, double max_distance);
		double getMinDistance() const {return _min_distance; }
		double getMaxDistance() const {return _max_distance; }

		//
		TetherMode getTetherMode() const { return _tether_mode; }
		void setTetherMode( TetherMode tether_mode ) { _tether_mode = tether_mode; }

		/** Whether a setViewpoint transition whould "arc" */
		void setArcViewpointTransitions( bool value );
		bool getArcViewpointTransitions() const { return _arc_viewpoints; }

		// ����/��ȡ�ӵ�任ʱ�Ƿ�ƽ���ƶ�������ֱ����ת��
		void setAutoViewpointDurationEnabled( bool value );
		bool getAutoViewpointDurationEnabled() const { return _auto_vp_duration; }

		// ����/��ȡ�ӵ�任ʱƽ���ƶ��������Сʱ��
		void setAutoViewpointDurationLimits( double minSeconds, double maxSeconds );
		void getAutoViewpointDurationLimits( double& out_minSeconds, double& out_maxSeconds ) const
		{
			out_minSeconds = _min_vp_duration_s;
			out_maxSeconds = _max_vp_duration_s;
		}
	private:

		friend class VBF_EarthManipulator;

		typedef std::pair<InputSpec,Action> ActionBinding;
		typedef std::map<InputSpec,Action> ActionBindings;

		// ��ȡ���󶨵Ķ���,���û�з��� NullAction
		const Action& getAction( int event_type, int input_mask, int modkey_mask ) const;

		// �Ѻϳɵ����루���ܼ���ϣ�ת��Ϊ�򵥵�����
		void expandSpec( const InputSpec& input, InputSpecs& output ) const;
		void bind( const InputSpec& spec, const Action& action );

	private:
		ActionBindings _bindings;
		bool _single_axis_rotation;
		bool _throwing;
		bool _lock_azim_while_panning;
		double _mouse_sens;
		double _keyboard_sens;
		double _scroll_sens;
		double _min_pitch;
		double _max_pitch;

		double _max_x_offset;
		double _max_y_offset;

		double _min_distance;
		double _max_distance;

		TetherMode _tether_mode;
		bool _arc_viewpoints;
		bool _auto_vp_duration;
		double _min_vp_duration_s, _max_vp_duration_s;
	};

public:
	VBF_EarthManipulator();

	// ����/��ȡ�ò����������ã�������Ч
	void applySettings( Settings* settings );
	Settings* getSettings() const;

	// ��ȡ��ǰ���λ��
	CVBF_Viewpoint getViewpoint() const;

	// �������λ�á�duration_s���任����λ�����õ�ʱ��
	virtual void setViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0 );

	// ȡ�����ڽ��е��ӵ�任
	void cancelViewpointTransition() { m_SettingViewPoint.Cancel(); }

	// ����Ĭ���ӵ�
	void setHomeViewpoint( const CVBF_Viewpoint& vp, double duration_s = 0.0 );

	// ������Ľ���������node�İ�Χ�򣬴���NULL�������
	// ������ʱ����Ȼ���Ե���navigate��setViewpoint()����ʱ�������������Ľڵ�
	void setTetherNode( osg::IVBF_SGNode* node );
	osg::IVBF_SGNode* getTetherNode() const { return m_opNodeTether.get(); }

	// ��ȡ���εĿռ�ο�ϵͳ
	const CVBF_SpatialReference* getSRS() const;

	// ƽ���������������Ļ����
	virtual void pan( double dx, double dy );

	// ��ת�����dx = azimuth, dy = pitch����������ת����λ����
	virtual void rotate( double dx, double dy );

	// ���ţ������Զ/����������dy
	virtual void zoom( double dx, double dy );

	// ��Ļ����任���������꣬���õ�setTraversalMask���õ�mask
	bool screenToWorld(float x, float y, osg::IVBF_ViewBrief* view, osg::Vec3d& out_coords ) const;

	// ����/��ȡ���߾���
	double getDistance() const { return m_dDistance; }
	void   setDistance( double distance);


	// ����/��ȡ��ת��Note:  This rotation is in addition to the rotation needed to center the view on the focal point.
	const osg::Quat& getRotation() { return _rotation; }
	void  setRotation( const osg::Quat& rotation) { _rotation = rotation; }



public: // osgGA::MatrixManipulator

	virtual const char* className() const { return "VBF_EarthManipulator"; }

	// ͨ������/��������øò�����
	virtual void setByMatrix(const osg::Matrixd& matrix);
	virtual void setByInverseMatrix(const osg::Matrixd& matrix) { setByMatrix(osg::Matrixd::inverse(matrix)); }
	virtual osg::Matrixd getMatrix() const;       
	virtual osg::Matrixd getInverseMatrix() const;// ���͵��÷�����Ϊģ����ͼ����model view��

	// ��ȡ�ռ��ںϾ���ģʽ��ֵ����������
	virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return osgUtil::SceneView::USE_FUSION_DISTANCE_VALUE; }
	virtual float getFusionDistanceValue() const { return m_dDistance; }

	// ����/��ȡ�����������Ľڵ�
	virtual void setNode(osg::IVBF_SGNode*);
	virtual osg::IVBF_SGNode* getNode();

	// ������Ƶ�Ĭ�ϵ�λ��
	virtual void home(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

	// ����/�����ò�����.
	virtual void init(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

	// �����¼�, ����Ѿ������� true,���򷵻� false.
	virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

	// ��ȡ�ò����������ͼ��̵��÷�.
	virtual void GetUsage(ApplicationUsage& usage) const;

	virtual void computeHomePosition();

	// ��ȡˮƽ/��ֱ�ӽ�
	double GetAngleH()  { return osg::RadiansToDegrees( _local_azim ); }
	double GetAngleV()  { return osg::RadiansToDegrees(_local_pitch); }


protected:

	virtual ~VBF_EarthManipulator();

	bool intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection) const;


	// resets the mouse event stack and pushes the provided event.
	void resetMouse( ::IVBF_GUIActionAdapter& );

    void flushMouseEventStack();// �����������������¼�
    void addMouseEvent(const GUIEventAdapter& ea);// ������������¼���ֻ����2����


	// sets the camera position by doing a "look at" calculation. This is only used for
	// the "home" function at the moment -- look into depcrecation -GW
	void setByLookAt(const osg::Vec3d& eye, const osg::Vec3d& lv, const osg::Vec3d& up);

	// Applies an action using the raw input parameters.
	bool handleAction( const Action& action, double dx, double dy, double duration );

	bool handleMouseAction( const Action& action, osg::IVBF_ViewBrief* view );
	bool handleMouseClickAction( const Action& action );
	bool handleKeyboardAction( const Action& action, double duration_s = DBL_MAX );
	bool handleScrollAction( const Action& action, double duration_s = DBL_MAX );        
	bool handlePointAction( const Action& type, float mx, float my, osg::IVBF_ViewBrief* view );
	void handleContinuousAction( const Action& action, osg::IVBF_ViewBrief* view );
	void handleMovementAction( const ActionType& type, double dx, double dy,
		osg::IVBF_ViewBrief* view );

	// checks to see whether the mouse is "moving".
	bool isMouseMoving();

	// This sets the camera's roll based on your location on the globe.
	void recalculateRoll();

private:

	enum TaskType
	{
		TASK_NONE,
		TASK_PAN,
		TASK_ROTATE,
		TASK_ZOOM
	};

	// ��ǰ���еĲ�������
	struct Task : public ::CVBF_Referenced
	{
		Task() : _type(TASK_NONE) { }

		void set( TaskType type, double dx, double dy, double duration =DBL_MAX )
		{
			_type = type; _dx = dx; _dy = dy; _duration_s = duration;
		}
		TaskType _type;
		double   _dx, _dy;
		double   _duration_s;
	};

	// "ticks" the resident Task, which allows for multi-frame animation of navigation movements.
	bool serviceTask();

	void recalculateLocalPitchAndAzimuth();
	double getAzimuth() const;

	void recalculateCenter( const osg::CoordinateFrame& frame );

	osg::Matrixd getRotation(const osg::Vec3d& center) const;
	osg::Quat makeCenterRotation(const osg::Vec3d& center) const
	{
		return getRotation(center).getRotate().inverse();
	}

	void updateTether();

	void updateSetViewpoint(); // �����ӵ�����У������ӵ�

	void updateHandCam( const CVBF_Timer_t& now );

	bool isMouseClick( const osgGA::GUIEventAdapter* mouse_up_event ) const;

	void applyOptionsToDeltas( const Action& action, double& dx, double& dy );

	void configureDefaultSettings();

	void reinitialize();

	bool established();

	osg::CoordinateFrame getMyCoordinateFrame( const osg::Vec3d& position ) const;

protected:
	// makeshift "stack" of the last 2 incoming events.
	ref_ptr<const osgGA::GUIEventAdapter> m_ipEventAdapter1;
	ref_ptr<const osgGA::GUIEventAdapter> m_ipEventAdapter0;
	ref_ptr<const osgGA::GUIEventAdapter> _mouse_down_event;

	observer_ptr<osg::IVBF_SGNode> _node;


	// ����ϵͳ������ݣ�Ϊ������ת��
	observer_ptr<osg::CVBF_SGNodeGroupCoordSys> _csn; // ����ϵͳ�ڵ�
	osg::CVBF_SGNodePath  _csnPath;         // ����ϵͳ�ڵ�·��
	osg::ObserverNodePath _csnObserverPath; // ����ϵͳ�ڵ�·���۲��ߣ�����CVBF_SGNodePath�ı仯�����ڵ㱻ɾ��ʱ�Զ�ʹ֮ʧЧ

	ref_ptr<const CVBF_SpatialReference> m_ipSRS;
	bool _is_geocentric;
	bool _srs_lookup_failed;

	observer_ptr<osg::IVBF_SGNode> m_opNodeTether;


	double       m_dTimeNow;// ��ǰʱ�䣬��
	double       m_dTimeDelta; // һ֡������ʱ�䣬�루��֡����һ֮֡�
	double       m_dTimeFactor;  // �����ӵ���֡���������60fps�ı仯


	osg::Vec3d    _center; // �������������

	osg::Quat     _rotation; // �����ת(heading and pitch)in the earth-local frame.
	osg::Quat     _centerRotation;// ʹ�����ת����������ϵĽ���. �ȼ����þ�γ����ת
	double        m_dDistance;


	double             _offset_x;
	double             _offset_y;
	osg::Vec3d         _previousUp;
	ref_ptr<Task>      _task;
	double                  _local_pitch;
	double                  _local_azim;

	bool      _thrown;

	bool      m_bContinuous; // �����/����̧��ʱ����ִ�ж���
	double    m_dDeltaX_Continuous;
	double    m_dDeltaY_Continuous;

	// δ�����ӵ����������֡ѭ����ʼǰ���ӵ�
	bool                    _has_pending_viewpoint;
	CVBF_Viewpoint          _pending_viewpoint;
	double                  _pending_viewpoint_duration_s;

	class CVBF_SettingViewPoint // �����������ӵ㣨�ӵ�任��
	{
	public:
		CVBF_SettingViewPoint()
		{
			m_bSetting = false;
			m_dArcHeight = 0.0;
		}
		bool IsSetting() { return m_bSetting; }
		void Cancel() { m_bSetting = false; }
		void Set(const CVBF_Viewpoint& vpStart,const CVBF_Viewpoint& vpEnd, double duration_s,
			const CVBF_SpatialReference* pSRS,bool bGeocentric,ref_ptr<Settings>& ipSettings );
		CVBF_Viewpoint GetNewViewPoint(double dTime);


		// �ӵ�仯ʱ�Ĳ���
		bool           m_bSetting; // �����������ӵ�Ĺ�����
		CVBF_Viewpoint m_vpStart;  // ��ʼ���ӵ�
		double         m_dDeltaHeading, m_dDeltaPitch, m_dDeltaRange; // ÿ֡�ı仯��
		osg::Vec3d     m_vDeltaFocalPoint; // FocalPoint��ÿ֡�仯��

		double m_dArcHeight; // �����ӵ�任�ĸ߶�
		double  m_dTimeSet; // �����ӵ�ʱ��ʱ�䣨��λ�룩

		double  m_dDuration; // �ӳ�ʱ�䣬��λ��
		double  m_dAccel; // �����׶μ���ϵ��
		double  m_dAccel2;// �½��׶μ���ϵ��
	};

	CVBF_SettingViewPoint m_SettingViewPoint;

	unsigned           _frame_count;

	ref_ptr<Settings> _settings;		

	CVBF_Optional<CVBF_Viewpoint> m_optHome; // Home��
	double m_dHomeDuration; // �Ƶ�Home����Ҫ������ʱ��

	Action m_ActionLast;

	// Ϊ��֧���ڸ��±�����traversal��֮��������(e.g., for tethering)
	observer_ptr<osg::IVBF_Camera> _viewCamera;

	struct CameraPostUpdateCallback : public osg::NodeCallback
	{
		CameraPostUpdateCallback(VBF_EarthManipulator* m) : _m(m) { }
		virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv) { _m->postUpdate(); traverse(node,nv); }
		VBF_EarthManipulator* _m;
	};

	void postUpdate();
	friend struct CameraUpdateCallback;

	observer_ptr<CameraPostUpdateCallback> _cameraUpdateCB;

	void updateCamera( osg::IVBF_Camera* eventCamera );

	// �����ӵ�߶ȼ������űȣ��ӵ�Խ�ͣ����ű�ԽС����Ө��ӣ�2017-03-06��
	float CalRangeFactorFromEyeHeight(double dEyeHeight, const Action& action);
};

#endif
