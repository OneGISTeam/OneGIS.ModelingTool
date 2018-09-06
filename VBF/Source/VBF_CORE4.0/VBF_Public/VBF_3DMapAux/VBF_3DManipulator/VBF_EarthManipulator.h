// earth的漫游器实现类。
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

//记录路径的
using namespace osgEarth::Util;
using namespace osgEarth;

// 地形浏览操作器
class VBF_3DMANIPULATORSHARED_EXPORT VBF_EarthManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
public:
	// 操作（动作）的类型，将与鼠标键盘事件绑定
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

	// 事件的类型，将与动作绑定
	enum EventType
	{
		EVENT_MOUSE_CLICK        = osgGA::GUIEventAdapter::USER << 1,
		EVENT_MOUSE_DOUBLE_CLICK = osgGA::GUIEventAdapter::DOUBLECLICK,
		EVENT_MOUSE_DRAG         = osgGA::GUIEventAdapter::DRAG,
		EVENT_KEY_DOWN           = osgGA::GUIEventAdapter::KEYDOWN,
		EVENT_SCROLL             = osgGA::GUIEventAdapter::SCROLL
	};

	// 鼠标键
	enum MouseEvent
	{
		MOUSE_LEFT_BUTTON   = osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON,
		MOUSE_MIDDLE_BUTTON = osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON,
		MOUSE_RIGHT_BUTTON  = osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON
	};

	// Action的选项
	enum ActionOptionType
	{
		OPTION_SCALE_X,             // 水平动作的放大倍数
		OPTION_SCALE_Y,             // 垂直动作的放大倍数
		OPTION_CONTINUOUS,          // 鼠标键或键盘抬起时继续执行动作
		OPTION_SINGLE_AXIS,         // 是否一次仅操作一个轴 (值大的轴)
		OPTION_GOTO_RANGE_FACTOR,   // for ACTION_GOTO, multiply the Range by this factor (to zoom in/out)
		OPTION_DURATION             // 完成动作的时间(秒)
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
	// 可以创建多个"Settings"对象，已设置不同的操作方式。运行时调用applySettings()确定选用的操作方式
	class VBF_3DMANIPULATORSHARED_EXPORT Settings : public ::CVBF_Referenced
	{
	public:
		Settings();
		Settings( const Settings& rhs );

		// button_mask为osgGA::GUIEventAdapter::MouseButtonMask
		// modkey_mask为osgGA::GUIEventAdapter::ModKeyMask

		// 把鼠标事件与Action绑定.options为OPTION_CONTINUOUS, OPTION_SCALE_X, OPTION_SCALE_Y
		void bindMouse(ActionType action, int button_mask,int modkey_mask = 0L, const ActionOptions& options =ActionOptions() );

		// 把鼠标单击事件与Action绑定。options为OPTION_GOTO_RANGE_FACTOR, OPTION_DURATION
		void bindMouseClick( ActionType action, int button_mask, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// 把鼠标双击事件与Action绑定。options为OPTION_GOTO_RANGE_FACTOR, OPTION_DURATION
		void bindMouseDoubleClick( ActionType action, int button_mask, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// 把键盘事件与Action绑定。options为OPTION_CONTINUOUS
		void bindKey(ActionType action, int key, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// 把鼠标滚轮事件与Action绑定。options为OPTION_SCALE_Y
		void bindScroll( ActionType action, int scrolling_motion, int modkey_mask =0L, const ActionOptions& options =ActionOptions() );

		// 设置/获取鼠标的敏感度1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive
		void setMouseSensitivity( double value ) { _mouse_sens = value; }
		double getMouseSensitivity() const { return _mouse_sens; }

		// 设置/获取键盘的敏感度（如每按下一次LEFT键，场景移动的距离）1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive
		void setKeyboardSensitivity( double value ) { _keyboard_sens = value; }
		double getKeyboardSensitivity() const { return _keyboard_sens; }

		// 设置/获取滚轮的敏感度（如放大的比例）1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive.
		void setScrollSensitivity( double value ) { _scroll_sens = value; }
		double getScrollSensitivity() const { return _scroll_sens; }

		// 设置/获取单轴旋转，为true时仅能控制azimuth，false时可控制pitch和azimuth。默认为false
		void setSingleAxisRotation( bool value ) { _single_axis_rotation = value; }
		bool getSingleAxisRotation() const { return _single_axis_rotation; }

		// 设置/获取是否可以甩动漫游
		void setThrowingEnabled( bool value ) { _throwing = value; }
		bool getThrowingEnabled() const { return _throwing; }

		// 设置/获取漫游时是否固定方位角
		void setLockAzimuthWhilePanning( bool value ) { _lock_azim_while_panning = value; }
		bool getLockAzimuthWhilePanning() const { return _lock_azim_while_panning; }


		// 设置/获取最大/最小俯仰角，单位度
		void setMinMaxPitch( double min_pitch, double max_pitch );
		double getMinPitch() const { return _min_pitch; }
		double getMaxPitch() const { return _max_pitch; }        

		// 设置/获取获取最大偏移量（世界坐标）
		void setMaxOffset(double max_x_offset, double max_y_offset);
		double getMaxXOffset() const { return _max_x_offset; }
		double getMaxYOffset() const { return _max_y_offset; }

		// 设置/获取最大最小视线距离（世界坐标）
		void setMinMaxDistance( double min_distance, double max_distance);
		double getMinDistance() const {return _min_distance; }
		double getMaxDistance() const {return _max_distance; }

		//
		TetherMode getTetherMode() const { return _tether_mode; }
		void setTetherMode( TetherMode tether_mode ) { _tether_mode = tether_mode; }

		/** Whether a setViewpoint transition whould "arc" */
		void setArcViewpointTransitions( bool value );
		bool getArcViewpointTransitions() const { return _arc_viewpoints; }

		// 设置/获取视点变换时是否平滑移动（否则直接跳转）
		void setAutoViewpointDurationEnabled( bool value );
		bool getAutoViewpointDurationEnabled() const { return _auto_vp_duration; }

		// 设置/获取视点变换时平滑移动的最大最小时间
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

		// 获取键绑定的动作,如果没有返回 NullAction
		const Action& getAction( int event_type, int input_mask, int modkey_mask ) const;

		// 把合成的输入（功能键组合）转换为简单的输入
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

	// 更改/获取该操作器的设置，立即生效
	void applySettings( Settings* settings );
	Settings* getSettings() const;

	// 获取当前相机位置
	CVBF_Viewpoint getViewpoint() const;

	// 设置相机位置。duration_s：变换到新位置所用的时间
	virtual void setViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0 );

	// 取消正在进行的视点变换
	void cancelViewpointTransition() { m_SettingViewPoint.Cancel(); }

	// 设置默认视点
	void setHomeViewpoint( const CVBF_Viewpoint& vp, double duration_s = 0.0 );

	// 把相机的焦点锁定在node的包围球，传入NULL解除锁定
	// 当锁定时，仍然可以调用navigate和setViewpoint()，此时相机相对于锁定的节点
	void setTetherNode( osg::IVBF_SGNode* node );
	osg::IVBF_SGNode* getTetherNode() const { return m_opNodeTether.get(); }

	// 获取地形的空间参考系统
	const CVBF_SpatialReference* getSRS() const;

	// 平移相机，增量，屏幕坐标
	virtual void pan( double dx, double dy );

	// 旋转相机（dx = azimuth, dy = pitch），增量旋转，单位弧度
	virtual void rotate( double dx, double dy );

	// 缩放：相机拉远/拉近，仅用dy
	virtual void zoom( double dx, double dy );

	// 屏幕坐标变换到世界坐标，会用到setTraversalMask设置的mask
	bool screenToWorld(float x, float y, osg::IVBF_ViewBrief* view, osg::Vec3d& out_coords ) const;

	// 设置/获取视线距离
	double getDistance() const { return m_dDistance; }
	void   setDistance( double distance);


	// 设置/获取旋转量Note:  This rotation is in addition to the rotation needed to center the view on the focal point.
	const osg::Quat& getRotation() { return _rotation; }
	void  setRotation( const osg::Quat& rotation) { _rotation = rotation; }



public: // osgGA::MatrixManipulator

	virtual const char* className() const { return "VBF_EarthManipulator"; }

	// 通过矩阵/逆矩阵设置该操作器
	virtual void setByMatrix(const osg::Matrixd& matrix);
	virtual void setByInverseMatrix(const osg::Matrixd& matrix) { setByMatrix(osg::Matrixd::inverse(matrix)); }
	virtual osg::Matrixd getMatrix() const;       
	virtual osg::Matrixd getInverseMatrix() const;// 典型的用法是作为模型视图矩阵（model view）

	// 获取空间融合距离模式和值，用于立体
	virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return osgUtil::SceneView::USE_FUSION_DISTANCE_VALUE; }
	virtual float getFusionDistanceValue() const { return m_dDistance; }

	// 设置/获取操作器关联的节点
	virtual void setNode(osg::IVBF_SGNode*);
	virtual osg::IVBF_SGNode* getNode();

	// 把相机移到默认的位置
	virtual void home(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

	// 启动/重启该操作器.
	virtual void init(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

	// 处理事件, 如果已经处理返回 true,否则返回 false.
	virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

	// 获取该操作器中鼠标和键盘的用法.
	virtual void GetUsage(ApplicationUsage& usage) const;

	virtual void computeHomePosition();

	// 获取水平/垂直视角
	double GetAngleH()  { return osg::RadiansToDegrees( _local_azim ); }
	double GetAngleV()  { return osg::RadiansToDegrees(_local_pitch); }


protected:

	virtual ~VBF_EarthManipulator();

	bool intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection) const;


	// resets the mouse event stack and pushes the provided event.
	void resetMouse( ::IVBF_GUIActionAdapter& );

    void flushMouseEventStack();// 重设最近的两次鼠标事件
    void addMouseEvent(const GUIEventAdapter& ea);// 添加最近的鼠标事件（只保留2个）


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

	// 当前进行的操作任务
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

	void updateSetViewpoint(); // 设置视点过程中，更新视点

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


	// 坐标系统相关内容，为了坐标转换
	observer_ptr<osg::CVBF_SGNodeGroupCoordSys> _csn; // 坐标系统节点
	osg::CVBF_SGNodePath  _csnPath;         // 坐标系统节点路径
	osg::ObserverNodePath _csnObserverPath; // 坐标系统节点路径观察者：跟踪CVBF_SGNodePath的变化，当节点被删除时自动使之失效

	ref_ptr<const CVBF_SpatialReference> m_ipSRS;
	bool _is_geocentric;
	bool _srs_lookup_failed;

	observer_ptr<osg::IVBF_SGNode> m_opNodeTether;


	double       m_dTimeNow;// 当前时间，秒
	double       m_dTimeDelta; // 一帧经过的时间，秒（本帧与上一帧之差）
	double       m_dTimeFactor;  // 该因子调整帧速率相对于60fps的变化


	osg::Vec3d    _center; // 焦点的世界坐标

	osg::Quat     _rotation; // 相机旋转(heading and pitch)in the earth-local frame.
	osg::Quat     _centerRotation;// 使相机旋转到朝向地面上的焦点. 等价于用经纬度旋转
	double        m_dDistance;


	double             _offset_x;
	double             _offset_y;
	osg::Vec3d         _previousUp;
	ref_ptr<Task>      _task;
	double                  _local_pitch;
	double                  _local_azim;

	bool      _thrown;

	bool      m_bContinuous; // 当鼠标/键盘抬起时继续执行动作
	double    m_dDeltaX_Continuous;
	double    m_dDeltaY_Continuous;

	// 未定的视点仅用于设置帧循环开始前的视点
	bool                    _has_pending_viewpoint;
	CVBF_Viewpoint          _pending_viewpoint;
	double                  _pending_viewpoint_duration_s;

	class CVBF_SettingViewPoint // 用于设置新视点（视点变换）
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


		// 视点变化时的参数
		bool           m_bSetting; // 正在设置新视点的过程中
		CVBF_Viewpoint m_vpStart;  // 起始的视点
		double         m_dDeltaHeading, m_dDeltaPitch, m_dDeltaRange; // 每帧的变化量
		osg::Vec3d     m_vDeltaFocalPoint; // FocalPoint的每帧变化量

		double m_dArcHeight; // 弧形视点变换的高度
		double  m_dTimeSet; // 设置视点时的时间（单位秒）

		double  m_dDuration; // 延迟时间，单位秒
		double  m_dAccel; // 上升阶段加速系数
		double  m_dAccel2;// 下降阶段加速系数
	};

	CVBF_SettingViewPoint m_SettingViewPoint;

	unsigned           _frame_count;

	ref_ptr<Settings> _settings;		

	CVBF_Optional<CVBF_Viewpoint> m_optHome; // Home点
	double m_dHomeDuration; // 移到Home点需要持续的时间

	Action m_ActionLast;

	// 为了支持在更新遍历（traversal）之后更新相机(e.g., for tethering)
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

	// 根据视点高度计算缩放比（视点越低，缩放比越小，杜莹添加：2017-03-06）
	float CalRangeFactorFromEyeHeight(double dEyeHeight, const Action& action);
};

#endif
