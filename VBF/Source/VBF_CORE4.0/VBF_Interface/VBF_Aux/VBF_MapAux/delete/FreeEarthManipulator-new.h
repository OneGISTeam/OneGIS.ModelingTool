/**************************************************************************************************
* @file FreeEarthManipulator.h
* @note FreeEarth地球操作器
* @author 
* @data 2017-2-14
**************************************************************************************************/
#ifndef FREE_UTILS_EARTHMANIPULATOR
#define FREE_UTILS_EARTHMANIPULATOR

#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>
#include <VBF_Engine/VBF_SceneGraph/CullSettings>

#include <VBF_3DMap/VBF_Driver/engine_mp/MP_TileNode.h>
#include <VBF_3DMap/VBF_Driver/engine_mp/MP_PagedLODNode.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformAuto.h>
#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Terrain.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h>

#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

#include <VBF_Aux/VBF_MapAux/IntersectUtil.h>
#include <VBF_Aux/VBF_MapAux/RenderContext.h>

namespace FeKit
{
	class FreeEarthManipulator;

	struct CameraUpdateCallback : public osg::NodeCallback
	{
		CameraUpdateCallback(FreeEarthManipulator* m);
		virtual void operator()(IVBF_SGNode* node, osg::NodeVisitor* nv);
		observer_ptr<FreeEarthManipulator> m_pEarthManipulator;
	};

	struct FreeEarthManipTerrainCallback : public IVBF_TerrainCallback
	{
		FreeEarthManipTerrainCallback(FreeEarthManipulator* manip) : m_pEarthManipulator(manip) { }

		void onTileAdded( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, CVBF_TerrainCallbackContext& context );
        
		FreeEarthManipulator* m_pEarthManipulator;
	};

	//h00017
	class VBF_MAPAUX_EXPORT EarthOldManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
    {
    public:

        /** Bindable manipulator actions. */
        enum ActionType {
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
            ACTION_ZOOM_OUT,
            ACTION_EARTH_DRAG
        };

        /** Vector of action types */
        typedef std::vector<ActionType> ActionTypeVector;

        /** Bindable event types. */
        enum EventType {
            EVENT_MOUSE_DOUBLE_CLICK = osgGA::GUIEventAdapter::DOUBLECLICK,
            EVENT_MOUSE_DRAG         = osgGA::GUIEventAdapter::DRAG,
            EVENT_KEY_DOWN           = osgGA::GUIEventAdapter::KEYDOWN,
            EVENT_SCROLL             = osgGA::GUIEventAdapter::SCROLL,
            EVENT_MOUSE_CLICK        = osgGA::GUIEventAdapter::USER << 1,
            EVENT_MULTI_DRAG         = osgGA::GUIEventAdapter::USER << 2,   // drag with 2 fingers
            EVENT_MULTI_PINCH        = osgGA::GUIEventAdapter::USER << 3,   // pinch with 2 fingers
            EVENT_MULTI_TWIST        = osgGA::GUIEventAdapter::USER << 4    // drag 2 fingers in different directions
        };

        /** Bindable mouse buttons. */
        enum MouseEvent {
            MOUSE_LEFT_BUTTON   = osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON,
            MOUSE_MIDDLE_BUTTON = osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON,
            MOUSE_RIGHT_BUTTON  = osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON
        };

        /** Action options. Certain options are only meaningful to certain Actions.
            See the bind* documentation for information. */
        enum ActionOptionType {            
            OPTION_SCALE_X,             // Sensitivity multiplier for horizontal input movements
            OPTION_SCALE_Y,             // Sensitivity multiplier for vertical input movements
            OPTION_CONTINUOUS,          // Whether to act as long as the button or key is depressed
            OPTION_SINGLE_AXIS,         // If true, only operate on one axis at a time (the one with the larger value)
            OPTION_GOTO_RANGE_FACTOR,   // for ACTION_GOTO, multiply the Range by this factor (to zoom in/out)
            OPTION_DURATION             // Time it takes to complete the action (in seconds)
        };

        /** Tethering options **/
        enum TetherMode
        {
            TETHER_CENTER,              // The camera will follow the center of the node.
            TETHER_CENTER_AND_ROTATION, // The camera will follow the node and all rotations made by the node
            TETHER_CENTER_AND_HEADING   // The camera will follow the node and only follow heading rotation
        };

        /** Camera projection matrix type **/
        enum CameraProjection
        {
            PROJ_PERSPECTIVE,
            PROJ_ORTHOGRAPHIC
        };

        struct ActionOption {
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
            union {
                bool _bool_value;
                int _int_value;
                double _dbl_value;
            };
        };

        struct ActionOptions : public std::vector<ActionOption> {
            void add( int option, bool value ) { push_back( ActionOption(option,value) ); }
            void add( int option, int value )  { push_back( ActionOption(option,value) ); }
            void add( int option, double value) { push_back( ActionOption(option,value) ); }
        };

    protected:
        struct InputSpec 
        {
            InputSpec( int event_type, int input_mask, int modkey_mask )
                : _event_type(event_type), _input_mask(input_mask), _modkey_mask( modkey_mask ) { }
            InputSpec( const InputSpec& rhs )
                : _event_type(rhs._event_type), _input_mask(rhs._input_mask), _modkey_mask(rhs._modkey_mask) { }

            bool operator == ( const InputSpec& rhs ) const {
                return _event_type == rhs._event_type && 
                       _input_mask == rhs._input_mask && 
                       ((_modkey_mask|osgGA::GUIEventAdapter::MODKEY_NUM_LOCK) == (rhs._modkey_mask|osgGA::GUIEventAdapter::MODKEY_NUM_LOCK));
            }

            inline bool operator < (const InputSpec& rhs) const {
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

        enum Direction {
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
            ActionType _type;
            Direction _dir;
            ActionOptions _options;
            bool getBoolOption( int option, bool defaultValue ) const;
            int getIntOption( int option, int defaultValue ) const;
            double getDoubleOption( int option, double defaultValue ) const;
        private:
            void init();
        };

        void dumpActionInfo( const Action& action, osg::NotifySeverity level ) const;
        
        static Action NullAction;

    public:

        class Settings : public CVBF_Referenced, public Revisioned
        {
        public:
            // construct with default settings
            Settings();

            // copy ctor
            Settings( const Settings& rhs );

            /** dtor */
            virtual ~Settings() { }

            /**
             * Assigns behavior to the action of dragging the mouse while depressing one or
             * more mouse buttons and modifier keys.
             *
             * @param action
             *      The EarthManipulator::ActionType value to which to bind this mouse
             *      input specification.
             *
             * @param button_mask
             *      Mask of osgGA::GUIEventAdapter::MouseButtonMask values
             *
             * @param modkey_mask (default = 0L)
             *      A mask of osgGA::GUIEventAdapter::ModKeyMask values defining a modifier key 
             *      combination to associate with the action.
             *
             * @param options
             *      Action options. Valid options are:
             *      OPTION_CONTINUOUS, OPTION_SCALE_X, OPTION_SCALE_Y
             */             
            void bindMouse(
                ActionType action, int button_mask,
                int modkey_mask = 0L,
                const ActionOptions& options =ActionOptions() );

            /**
             * Assigns a bevahior to the action of clicking one or more mouse buttons.
             *
             * @param action
             *      The EarthManipulator::ActionType value to which to bind this mouse click
             *      input specification.
             *
             * @param button_mask
             *      Mask of osgGA::GUIEventAdapter::MouseButtonMask values
             *
             * @param modkey_mask (default = 0L)
             *      A mask of osgGA::GUIEventAdapter::ModKeyMask values defining a modifier key 
             *      combination to associate with the action.
             *
             * @param options
             *      Action options. Valid options are:
             *      OPTION_GOTO_RANGE_FACTOR, OPTION_DURATION
             */
            void bindMouseClick(
                ActionType action, int button_mask,
                int modkey_mask =0L,
                const ActionOptions& options =ActionOptions() );

            /**
             * Assigns a bevahior to the action of double-clicking one or more mouse buttons.
             *
             * @param action
             *      The EarthManipulator::ActionType value to which to bind this double-click
             *      input specification.
             *
             * @param button_mask
             *      Mask of osgGA::GUIEventAdapter::MouseButtonMask values
             *
             * @param modkey_mask (default = 0L)
             *      A mask of osgGA::GUIEventAdapter::ModKeyMask values defining a modifier key 
             *      combination to associate with the action.
             *
             * @param options
             *      Action options. Valid options are:
             *      OPTION_GOTO_RANGE_FACTOR, OPTION_DURATION
             */
            void bindMouseDoubleClick(
                ActionType action, int button_mask,
                int modkey_mask =0L,
                const ActionOptions& options =ActionOptions() );

            /**
             * Assigns a bevahior to the action of depressing a key.
             *
             * @param action
             *      The EarthManipulator::ActionType value to which to bind this key
             *      input specification.
             *
             * @param key
             *      A osgGA::GUIEventAdapter::KeySymbol value
             *
             * @param modkey_mask (default = 0L)
             *      A mask of osgGA::GUIEventAdapter::ModKeyMask values defining a modifier key 
             *      combination to associate with the action.
             *
             * @param options
             *      Action options. Valid options are:
             *      OPTION_CONTINUOUS
             */
            void bindKey(
                ActionType action, int key,
                int modkey_mask =0L,
                const ActionOptions& options =ActionOptions() );
            
            /**
             * Assigns a bevahior to operation of the mouse's scroll wheel.
             *
             * @param action
             *      The EarthManipulator::ActionType value to which to bind this scroll
             *      input specification.
             *
             * @param scrolling_motion
             *      A osgGA::GUIEventAdapter::ScrollingMotion value
             *
             * @param modkey_mask (default = 0L)
             *      A mask of osgGA::GUIEventAdapter::ModKeyMask values defining a modifier key 
             *      combination to associate with the action.
             *
             * @param options
             *      Action options. Valid options are:
             *      OPTION_SCALE_Y
             */
            void bindScroll(
                ActionType action, int scrolling_motion,
                int modkey_mask =0L,
                const ActionOptions& options =ActionOptions() );


            void bindPinch(
                ActionType action, const ActionOptions& =ActionOptions() );
                
            void bindTwist(
                ActionType action, const ActionOptions& =ActionOptions() );

   
            void bindMultiDrag(
                ActionType action, const ActionOptions& =ActionOptions() );

            /**
             * Sets an overall mouse sensitivity factor.
             *
             * @param value
             *      A scale factor to apply to mouse readings.
             *      1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive.
             */
            void setMouseSensitivity( double value ) { _mouse_sens = value; }

            /**
             * Gets the overall mouse sensitivity scale factor. Default = 1.0.
             */
            double getMouseSensitivity() const { return _mouse_sens; }

            /**
             * Sets the keyboard action sensitivity factor. This applies to navigation actions
             * that are bound to keyboard events. For example, you may bind the LEFT arrow to
             * the ACTION_PAN_LEFT action; this factor adjusts how much panning will occur during
             * each frame that the key is depressed.
             *
             * @param value
             *      A scale factor to apply to keyboard-controller navigation.
             *      1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive.
             */
            void setKeyboardSensitivity( double value ) { _keyboard_sens = value; }

            /**
             * Gets the keyboard action sensitivity scale factor. Default = 1.0.
             */
            double getKeyboardSensitivity() const { return _keyboard_sens; }

            /**
             * Sets the scroll-wheel sensitivity factor. This applies to navigation actions
             * that are bound to scrolling events. For example, you may bind the scroll wheel to
             * the ACTION_ZOOM_IN action; this factor adjusts how much zooming will occur each time 
             * you click the scroll wheel.
             *
             * @param value
             *      A scale factor to apply to scroll-wheel-controlled navigation.
             *      1.0 = default; < 1.0 = less sensitive; > 1.0 = more sensitive.
             */
            void setScrollSensitivity( double value ) { _scroll_sens = value; }

            /**
             * Gets the scroll wheel sensetivity scale factor. Default = 1.0.
             */
            double getScrollSensitivity() const { return _scroll_sens; }

            /** 
             * When set to true, prevents simultaneous control of pitch and azimuth. 
             *
             * Usually you can alter pitch and azimuth at the same time. When this flag
             * is set, you can only control one at a time - if you start slewing the azimuth of the camera,
             * the pitch stays locked until you stop moving and then start slewing the pitch.
             *
             * Default = false.
             */
            void setSingleAxisRotation( bool value ) { _single_axis_rotation = value; }

            /** 
             * Gets whether simultaneous control over pitch and azimuth is disabled.
             * Default = false.
             */
            bool getSingleAxisRotation() const { return _single_axis_rotation; }

            /**
             * Sets whether to lock in a camera heading when performing panning operations (i.e.,
             * changing the focal point).
             */
            void setLockAzimuthWhilePanning( bool value ) { _lock_azim_while_panning = value; }

            /**
             * Gets true if the manipulator should lock in a camera heading when performing panning
             * operations (i.e. changing the focal point.)
             */
            bool getLockAzimuthWhilePanning() const { return _lock_azim_while_panning; }

            /**
             * Sets the minimum and maximum allowable local camera pitch, in degrees.
             *
             * By "local" we mean relative to the tangent plane passing through the focal point on
             * the surface of the terrain.
             *
             * Defaults are: Min = -90, Max = -10.
             */
            void setMinMaxPitch( double min_pitch, double max_pitch );

            /** Gets the minimum allowable local pitch, in degrees. */
            double getMinPitch() const { return _min_pitch; }

            /** Gets the maximum allowable local pitch, in degrees. */
            double getMaxPitch() const { return _max_pitch; }        

            /** Gets the max x offset in world coordates */
            double getMaxXOffset() const { return _max_x_offset; }

            /** Gets the max y offset in world coordates */
            double getMaxYOffset() const { return _max_y_offset; }

            /** Gets the minimum distance from the focal point in world coordinates */
            double getMinDistance() const {return _min_distance; }
            
            /** Gets the maximum distance from the focal point in world coordinates */
            double getMaxDistance() const {return _max_distance; }

            /** Sets the min and max distance from the focal point in world coordiantes */
            void setMinMaxDistance( double min_distance, double max_distance);

            /**
            * Sets the maximum allowable offsets for the x and y camera offsets in world coordinates
            */
            void setMaxOffset(double max_x_offset, double max_y_offset);

            /**
            * Gets the TetherMode
            */
            TetherMode getTetherMode() const { return _tether_mode; }

            /**
            * Sets the TetherMode
            */
            void setTetherMode( TetherMode tether_mode ) { _tether_mode = tether_mode; }

            /** Access to the list of Actions that will automatically break a tether */
            ActionTypeVector& getBreakTetherActions() { return _breakTetherActions; }
            const ActionTypeVector& getBreakTetherActions() const { return _breakTetherActions; }

            /** Whether a setViewpoint transition whould "arc" */
            void setArcViewpointTransitions( bool value );
            bool getArcViewpointTransitions() const { return _arc_viewpoints; }

            /** Activates auto-duration for transitioned viewpoints. */
            void setAutoViewpointDurationEnabled( bool value );
            bool getAutoViewpointDurationEnabled() const { return _auto_vp_duration; }

            void setAutoViewpointDurationLimits( double minSeconds, double maxSeconds );
            void getAutoViewpointDurationLimits( double& out_minSeconds, double& out_maxSeconds ) const {
                out_minSeconds = _min_vp_duration_s;
                out_maxSeconds = _max_vp_duration_s;
            }

            /** The camera projection matrix type */
            void setCameraProjection( const CameraProjection& value );
            const CameraProjection& getCameraProjection() const { return _camProjType; }

            /** Frustum offset (in pixels) */
            void setCameraFrustumOffsets( const osg::Vec2s& offsets );
            const osg::Vec2s& getCameraFrustumOffsets() const { return _camFrustOffsets; }            

            /** Whether or not to disable collision avoidance when new data pages in */
            bool getDisableCollisionAvoidance() const { return _disableCollisionAvoidance; }
            void setDisableCollisionAvoidance( bool disableCollisionAvoidance ) { _disableCollisionAvoidance = disableCollisionAvoidance; }

            void setThrowingEnabled(bool throwingEnabled) { _throwingEnabled = throwingEnabled; }
            bool getThrowingEnabled () const { return _throwingEnabled; }
            
            void setThrowDecayRate(double throwDecayRate) { _throwDecayRate = osg::clampBetween(throwDecayRate, 0.0, 1.0); }
            double getThrowDecayRate () const { return _throwDecayRate; }

        private:

            friend class EarthManipulator;

            typedef std::pair<InputSpec,Action> ActionBinding;
            typedef std::map<InputSpec,Action> ActionBindings;

            void expandSpec( const InputSpec& input, InputSpecs& output ) const;
            void bind( const InputSpec& spec, const Action& action );

		public:
            // Gets the action bound to the provided input specification, or NullAction if there is
            // to matching binding.
            const Action& getAction( int event_type, int input_mask, int modkey_mask ) const;

        private:

            ActionBindings _bindings;
            bool _single_axis_rotation;
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
            ActionTypeVector _breakTetherActions;
            bool _arc_viewpoints;
            bool _auto_vp_duration;
            double _min_vp_duration_s, _max_vp_duration_s;

            CameraProjection _camProjType;
            osg::Vec2s _camFrustOffsets;	

            bool _disableCollisionAvoidance;

            bool _throwingEnabled;
            double _throwDecayRate;
        };

    public:
        EarthOldManipulator();
        EarthOldManipulator( const EarthOldManipulator& rhs );

        /**
         * Applies a new settings object to the manipulator, which takes effect immediately.
         */
        void applySettings( Settings* settings );

        /**
         * Gets a handle on the current manipulator settings object.
         */
        Settings* getSettings() const;

        /**
         * Gets the current camera position.
         */
        CVBF_Viewpoint getViewpoint() const;

        /**
         * Sets the camera position, optionally moving it there over time.
         */
        virtual void setViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0 );
        
        /**
         * Cancels a viewpoint transition if one is in progress
         */
        void cancelViewpointTransition() { _setting_viewpoint = false; }

        /**
         * Sets the viewpoint to activate when performing the ACTION_HOME action.
         */
        void setHomeViewpoint( const CVBF_Viewpoint& vp, double duration_s = 0.0 );

        /**
         * Locks the camera's focal point on the center of a node's bounding sphere.
         * While tethered, you can still call navigate or call setViewpoint() to move the
         * camera relative to the tether object. Pass NULL to deactivate the tether.
         *
         * @param node
         *      Node to which to tether the viewpoint.
         */
        void setTetherNode( osg::IVBF_SGNode* node );

        /**
         * Gets the node to which the camera is tethered, or NULL if tethering is
         * disabled.
         */
        osg::IVBF_SGNode* getTetherNode() const;

        /**
         * Gets the spatial reference system of the terrain map to which this
         * manipulator is currently attached.
         */
        const CVBF_SpatialReference* getSRS() const;

        /**
         * Move the focal point of the camera using deltas (normalized screen coords).
         */
        virtual void pan( double dx, double dy );

        /**
         * Rotate the camera (dx = azimuth, dy = pitch) using deltas (radians).
         */
        virtual void rotate( double dx, double dy );

        /**
         * Zoom the camera using deltas (dy only)
         */
        virtual void zoom( double dx, double dy );

        /**
         * Drag the earth using deltas
         */
        virtual void drag( double dx, double dy, IVBF_View* view);
        
        /**
         * Converts screen coordinates (relative to the view's viewpoint) to world
         * coordinates. Note, this method will use the mask set by setTraversalMask().
         *
         * @param x, y
         *      Viewport coordinates
         * @param view
         *      View for which to calculate world coordinates
         * @param out_coords
         *      Output world coordinates (only valid if the method returns true)
         */
        virtual bool screenToWorld(float x, float y, IVBF_View* view, osg::Vec3d& out_coords ) const;	


        /**
         * Gets the distance from the focal point in world coordiantes
         */
        double getDistance() const { return _distance; }

        /**
         * Sets the distance from the focal point in world coordinates.
         *
         * The incoming distance value will be clamped within the valid range specified by the settings.
         */
        void   setDistance( double distance);

        /**
         * Gets the rotation of the manipulator.  Note:  This rotation is in addition to the rotation needed to center the view on the focal point.
         */
        const osg::Quat& getRotation() { return _rotation; }

        /**
         * Sets the rotation of the manipulator.  Note:  This rotation is in addition to the rotation needed to center the view on the focal point.
         */
        void  setRotation( const osg::Quat& rotation) { _rotation = rotation; }

        /**
         * Gets the traversal node mask used to find root CVBFO_SGNodeMap and CoordinateSystemNodes. Default is 0x1.
         */
        osg::IVBF_SGNode::NodeMask getFindNodeTraversalMask( ) { return _findNodeTraversalMask; }

        /**
         * Sets the traversal node mask used to find root CVBFO_SGNodeMap and CoordinateSystemNode. Default is 0x1. 
         * Use this method if you change CVBFO_SGNodeMap or CoordinateSystemNode mask and want manipulator to work with them correctly.  
         */
        void  setFindNodeTraversalMask( const osg::IVBF_SGNode::NodeMask & nodeMask ) { _findNodeTraversalMask = nodeMask; }

    public: // osgGA::MatrixManipulator

        virtual const char* className() const { return "EarthOldManipulator"; }
        
        /** set the position of the matrix manipulator using a 4x4 Matrix.*/
        virtual void setByMatrix(const osg::Matrixd& matrix);

        /** set the position of the matrix manipulator using a 4x4 Matrix.*/
        virtual void setByInverseMatrix(const osg::Matrixd& matrix) { setByMatrix(osg::Matrixd::inverse(matrix)); }

        /** get the position of the manipulator as 4x4 Matrix.*/
        virtual osg::Matrixd getMatrix() const;

        /** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
        virtual osg::Matrixd getInverseMatrix() const;

        // Gets the stereo convergance mode.
        virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return osgUtil::SceneView::USE_FUSION_DISTANCE_VALUE; }

        // Gets the stereo convergance distance.
        virtual float getFusionDistanceValue() const { return _distance; }

        // Attach a node to the manipulator.
        virtual void setNode(osg::IVBF_SGNode*);

        // Gets the node to which this manipulator is attached.
        virtual osg::IVBF_SGNode* getNode();

        // Move the camera to the default position.
        virtual void home(double /*unused*/);
        virtual void home(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& us);
        
        // Start/restart the manipulator.
        virtual void init(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& us);

        // handle events, return true if handled, false otherwise.
        virtual bool handle(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& us);

        // Get the keyboard and mouse usage of this manipulator.
        virtual void getUsage(ApplicationUsage& usage) const;

        virtual void computeHomePosition();

		double getScrollDuration(){return _scrollDuration;}
		void setScrollDuration(double duration){_scrollDuration = duration;}

    protected:

        virtual ~EarthOldManipulator();
        
        bool intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection) const;

        // resets the mouse event stack and pushes the provided event.
        void resetMouse( IVBF_GUIActionAdapter& aa, bool flushEventStack=true);

        // Reset the internal event stack.
        void flushMouseEventStack();

        // Add the current mouse osgGA::GUIEvent to internal stack.
        void addMouseEvent(const osgGA::GUIEventAdapter& ea);

        // sets the camera position by doing a "look at" calculation. This is only used for
        // the "home" function at the moment -- look into depcrecation -GW
        virtual void setByLookAt(const osg::Vec3d& eye, const osg::Vec3d& lv, const osg::Vec3d& up);

        // checks to see whether the mouse is "moving".
        bool isMouseMoving();

        // This sets the camera's roll based on your location on the globe.
        void recalculateRoll();

		virtual void mousePushEvent(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa, const Action& action){}

		virtual void mouseThrowingEvent(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa){}

		virtual void mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa){}

		//virtual void checkClampProjectionMatrixCallback() {};

    protected:

        enum TaskType
        {
            TASK_NONE,
            TASK_PAN,
            TASK_ROTATE,
            TASK_ZOOM
        };

        struct Task : public CVBF_Referenced
        {
            Task() : _type(TASK_NONE) { }
            void set( TaskType type, double dx, double dy, double duration, double now ) {
                _type = type; _dx = dx; _dy = dy; _duration_s = duration; _time_last_service = now;
            }
            TaskType _type;
            double   _dx, _dy;
            double   _duration_s;
            double   _time_last_service;
        };

        // "ticks" the resident Task, which allows for multi-frame animation of navigation
        // movements.
        virtual bool serviceTask(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa);

        //void recalculateLocalPitchAndAzimuth();
        virtual void getLocalEulerAngles( double* out_azim, double* out_pitch =0L ) const;


        virtual void recalculateCenter( const osg::CoordinateFrame& frame, osg::IVBF_SGNode* tile = NULL);

        osg::Matrixd getRotation(const osg::Vec3d& center) const;
        osg::Quat makeCenterRotation(const osg::Vec3d& center) const
        {
            return getRotation(center).getRotate().inverse();
        }

        void updateTether();

        virtual void updateSetViewpoint();

        void updateHandCam( const CVBF_Timer& now );

        bool isMouseClick( const osgGA::GUIEventAdapter* mouse_up_event ) const;
        
        void applyOptionsToDeltas( const Action& action, double& dx, double& dy );

        virtual void configureDefaultSettings();

        void reinitialize();

        bool established();

        // sets the new center (focal) point and recalculates it's L2W matrix.
        void setCenter( const osg::Vec3d& center );

        // creates a "local-to-world" transform relative to the input point.
        bool createLocalCoordFrame( const osg::Vec3d& worldPos, osg::CoordinateFrame& out_frame ) const;

        // returns an ActionType that would be initiated by the OSG UI event
        ActionType getActionTypeForEvent( const osgGA::GUIEventAdapter& ea ) const;

    public:
            
        void recalculateCenter(osg::IVBF_SGNode* tile = NULL) { recalculateCenter(_centerLocalToWorld, tile); }

        const GeoPoint& centerMap() const { return _centerMap; }

    protected:
        typedef osgGA::GUIEventAdapter::TouchData::TouchPoint TouchPoint;
        typedef std::vector<TouchPoint> MultiTouchPoint; // one per ID (finger/touchpoint)
        typedef std::deque<MultiTouchPoint> MultiTouchPointQueue;
        MultiTouchPointQueue _touchPointQueue;
        //struct TouchEvent {
        //    EventType _eventType;     // derived touch/other event
        //    float     _deltaDistance; // change in distance between 2 touches
        //    float     _dx[2], _dy[2]; // movement of primary and secondary touch points
        //    float     _dot;
        //};
        struct TouchEvent {
            TouchEvent() : _mbmask(0) { }
            EventType _eventType;
            unsigned  _mbmask;
            float     _dx, _dy;
        };
        typedef std::vector<TouchEvent> TouchEvents;
        void addTouchEvents( const osgGA::GUIEventAdapter& ea );
        bool parseTouchEvents( TouchEvents& ev );

        // Applies an action using the raw input parameters.
        bool handleAction( const Action& action, double dx, double dy, double duration );

        virtual bool handleMouseAction( const Action& action, IVBF_View* view );
        virtual bool handleMouseClickAction( const Action& action );
        virtual bool handleKeyboardAction( const Action& action, double duration_s = DBL_MAX );
        virtual bool handleScrollAction( const Action& action, double duration_s = DBL_MAX );
        virtual bool handlePointAction( const Action& type, float mx, float my, IVBF_View* view );
        virtual void handleContinuousAction( const Action& action, IVBF_View* view );
        virtual void handleMovementAction( const ActionType& type, double dx, double dy, IVBF_View* view );
        //virtual bool handleMultiTouchAction( const Action& action, const TouchEvent& te, IVBF_View* view );
		//virtual bool handleMouseMoveEvent(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa){ return false; }
		
		// start HGT: 实现osgEarth 定位功能添加 w00024
		virtual bool isSettingViewpoint() { return false; }
		virtual double setViewpointFrame(double time_s) { return 0.0; }
		CVBF_Optional<Duration>      _setVPStartTime;            // Time of call to setViewpoint
		// end
		
    protected:

        // makeshift "stack" of the last 2 incoming events.
        ref_ptr<const osgGA::GUIEventAdapter> _ga_t1;
        ref_ptr<const osgGA::GUIEventAdapter> _ga_t0;

        ref_ptr<const osgGA::GUIEventAdapter> _mouse_down_event;

        observer_ptr<osg::IVBF_SGNode> _node;
        observer_ptr<osg::CVBF_SGNodeGroupCoordSys> _csn;
#ifdef USE_OBSERVER_NODE_PATH
        osg::ObserverNodePath _csnObserverPath;
#endif
        CVBF_SGNodePath _csnPath;

        ref_ptr<const CVBF_SpatialReference> _cached_srs;
        bool _is_geocentric;
        bool _srs_lookup_failed;

        observer_ptr<osg::IVBF_SGNode> _tether_node;
        CVBF_Viewpoint                    _pre_tether_vp;

        double                  _time_s_last_frame;
        double                  _time_s_now;
        CVBF_Timer            _now;
        double                  _delta_t;
        double                  _t_factor;
        bool                    _thrown;
        double                  _throw_dx;
        double                  _throw_dy;
        double                  _dx;
        double                  _dy;

		double                  _scrollDuration;
		double                  _continuousPow;

        // The world coordinate of the CVBF_Viewpoint focal point.
        osg::Vec3d              _center;
        GeoPoint                _centerMap;

        // local2world matrix for the center point.
        osg::CoordinateFrame    _centerLocalToWorld;

        // The rotation (heading and pitch) of the camera in the
        // earth-local frame.
        osg::Quat               _rotation;

        // The rotation that makes the camera look down on the focal
        // point on the earth. This is equivalent to a rotation by
        // latitude, longitude.
        osg::Quat               _centerRotation;
        double                  _distance;
        double                  _offset_x;
        double                  _offset_y;
        osg::Vec3d              _previousUp;
        ref_ptr<Task>      _task;
        CVBF_Timer            _time_last_frame;
        //double                  _local_pitch;
        //double                  _local_azim;

        bool                    _continuous;
        double                  _continuous_dx;
        double                  _continuous_dy;
        double                  _last_continuous_action_time;

        double                  _single_axis_x;
        double                  _single_axis_y;

        // the "pending" viewpoint is only used to enable setting the
        // viewpoint before the frame loop starts
        bool                    _has_pending_viewpoint;
        CVBF_Viewpoint               _pending_viewpoint;
        double                  _pending_viewpoint_duration_s;

        bool                    _setting_viewpoint;
        CVBF_Viewpoint               _start_viewpoint;
        double                  _delta_heading, _delta_pitch, _delta_range, _arc_height;
        osg::Vec3d              _delta_focal_point;
        double                  _time_s_set_viewpoint;
        double                  _set_viewpoint_duration_s;
        double                  _set_viewpoint_accel;
        double                  _set_viewpoint_accel_2;

        unsigned                _frame_count;

        ref_ptr<Settings> _settings;		

        CVBF_Optional<CVBF_Viewpoint> _homeViewpoint;
        double _homeViewpointDuration;

        Action _last_action;
        
        EventType _last_event;
        double    _time_s_last_event;
        
		observer_ptr<CVBFO_SGNodeMap>   _mapNode;

        // to support updating the camera after the update traversal (e.g., for tethering)
        observer_ptr<osg::IVBF_Camera> _viewCamera;
        double _vfov;
        double _tanHalfVFOV;
        CVBF_Optional<osg::CullSettings::ComputeNearFarMode> _savedCNFMode;
        Revision _viewCameraSettingsMonitor;
        
        struct CameraPostUpdateCallback : public osg::NodeCallback {
            CameraPostUpdateCallback(EarthOldManipulator* m) : _m(m) { }
            virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv) { _m->postUpdate(); traverse(node,nv); }
            EarthOldManipulator* _m;
        };
        void postUpdate();
        friend struct CameraUpdateCallback;

        observer_ptr<CameraPostUpdateCallback> _cameraUpdateCB;

        void updateCamera( osg::IVBF_Camera* eventCamera );
        // Support snappy transition when the pointer leaves and
        // returns to earth during a drag
        osg::Vec3d               _lastPointOnEarth;


        ref_ptr< IVBF_TerrainCallback > _terrainCallback;

        // Traversal mask used in established and dtor methods to find CVBFO_SGNodeMap and CoordinateSystemNode
        osg::IVBF_SGNode::NodeMask  _findNodeTraversalMask;
    };
	//h00017

	class VBF_MAPAUX_EXPORT FreeEarthManipulator : public EarthOldManipulator
	{	
		friend struct EarthProjMatCallback;
		friend struct CameraUpdateCallback;
		friend struct FreeEarthManipTerrainCallback;

	public:
		FreeEarthManipulator(FeUtil::CRenderContext* pContext,const std::string& strCenterIcon);
		virtual ~FreeEarthManipulator();

		virtual const char* className() const { return "FreeEarthManipulator"; }

	private:
		bool m_bGoogleModeEnable;     // 判断是否是google 模式
		/** pushEvent 使用 */
		osg::Vec3d m_v3dLastCenter;	  // 记录中心点
		osg::Quat  m_qLastQuat;		  // 记录四元素
	
		/** Pan 使用 */
		bool m_bLastPanIntersected;
		osg::Vec3d m_v3dLastPanIntersect;
		bool m_bPanRelease;
		bool m_bEnableThrowing;
		ref_ptr<osg::IVBF_Camera> m_rpCameraCopy;

		bool m_bIsRotateChecked;
		bool m_bLastPanSkyIntersected;
		bool m_bLastZoomIntersected;
		bool m_bLastRotateIntersected;

		osg::Vec3d m_v3dLastZoomIntersect;
		osg::Vec3d m_v3dLastRotateIntersect;
		mutable bool m_bLastIntersectWithTerrain;
		ref_ptr<Settings> m_settings;
		unsigned int m_uRotateSensitivity;

		osg::Vec3d m_v3dOldCenter;
		osg::Quat m_qOldCenterRotation;
		osg::Quat m_qOldRotation;
		double m_dOldDistance;

		bool m_bCurIntersectWithEarth;
		osg::Vec3d m_v3dCurIntersectWithEarth;
		osg::Vec3d m_v3dLastPanAxis;
		double m_dLastPanAngle;
		double m_dMaxZoomDis;
		double m_dLastZoomDis;	
		ref_ptr<FreeEarthManipTerrainCallback> m_rpTerrainCallback;
		bool m_bIsRotating;
		bool m_bIsZooming;

		ref_ptr<osg::AutoTransform> m_billboardMT;
		ref_ptr<osg::IVBF_SGNodeGeometryBillboard> m_billboard;
		double m_billboardScale;

		observer_ptr<FeUtil::CRenderContext>   m_opRenderContext;
	 	
		// 单个函数中使用
		float m_fLastX,m_fLastY;      
		double m_dScrollDuration;
		double m_dSkyPlaneDis;


		osg::Vec3d m_oldCenter;
		osg::Quat m_oldCenterRotation;
		osg::Quat m_oldRotation;
		double m_oldDistance;
	protected:
		virtual bool  handlePointAction (const Action &type, float mx, float my, IVBF_View *view) ;
		virtual void  handleMovementAction (const ActionType &type, double dx, double dy, IVBF_View *view) ;			

		virtual bool  serviceTask(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa);

		virtual void  updateSetViewpoint();

		virtual void  mousePushEvent(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa, const Action& action);
		virtual void  mouseThrowingEvent(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa);
		virtual void  mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa);

		void  configureDefaultSettings();

		virtual void recalculateCenter( const osg::CoordinateFrame& frame, osg::IVBF_SGNode* tile = NULL);

		// 放大缩小
		void zoom( double dx, double dy, const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa);
		void zoomToPoint(double dx, double dy);

		// 拖动
		void panPush(float x, float y);
		void panAngleAixs(osg::Vec3d lp, osg::Vec3d cp,bool checkPan = false);
		void panThrown(double rate);

		double getCurAltFromTerrain(){return m_curAltFromTerrain;}
		void setCurAltFromTerrain(double alt){m_curAltFromTerrain = alt;}

		// 天空
		bool getIntersectPointFromSky(float x,float y,osg::IVBF_Camera* cam,osg::Vec3d& outPoint);
		// onTileAdded调用
		bool rayToWorld(osg::Vec3d start,osg::Vec3d end,osg::Vec3d& outPoint,osg::Vec3d& hitNormal);

		bool checkCollision(osg::Vec3d& start, osg::Vec3d& end, osg::Vec3d& safePoint, osg::Vec3d& upPoint,double checkDis = 5.0);	
		bool getUpPoint(osg::Vec3d& center,osg::Vec3d& upCenter);

		void storeParameter();
		void restoreParameter();

		// 设置视点调用 setViewpoint
		void setGoogleModeViewPoint(CVBF_Viewpoint& v);
		bool getOldModeViewPoint(CVBF_Viewpoint& v); // handlePointAction 调用
		osg::Matrixd getOldMatrix();
		//handlePointAction 调用 
		void updateEarthIntersectPoint(double radius);
		void rotate( double dx, double dy ,const osg::Vec3d& center);
		
		void resetCenter();
		void getTileNode(osg::IVBF_SGNodeGroup* pGroup,double west,double east,double north,double south);
		
		bool getIntersectPointWithTerrain(double radius,osg::Vec3d positon,osg::IVBF_SGNodeGroup* tileGroup,osg::Vec3d& safePoint);
		bool getIntersectPointWithTerrain(double radius,osg::Vec3d positon,osg::Drawable* pDrawable,osg::Vec3d& safePoint);

		// 标牌
		osg::Drawable* createSquare(const osg::Vec3d& corner,const osg::Vec3d& width,const osg::Vec3d& height, osg::Image* image=NULL);
		void updateBillboard(osg::Vec3d corner);

		// 海洋
		//bool screenToOcean(float x, float y, osg::Vec3d& out_coords ) const;	

		// start HGT: 实现osgEarth 定位功能添加 w00024
		virtual bool isSettingViewpoint() { 
			return _setVP0.isSet() && _setVP1.isSet()/* && !_setVP1->nodeIsSet();*/; }
		virtual double setViewpointFrame(double time_s);
		CVBF_Optional<CVBF_Viewpoint>     _setVP0;                    // Starting viewpoint
		CVBF_Optional<CVBF_Viewpoint>     _setVP1;                    // Final viewpoint
		Duration                _setVPDuration;             // Transition time for setViewpoint
		double                  _setVPAccel, _setVPAccel2;  // Acceleration factors for setViewpoint
		double                  _setVPArcHeight;            // Altitude arcing height for setViewpoint

		osg::Quat               _tetherRotationVP0;         // saves _tetherRotation at the start of a transition
		osg::Quat               _tetherRotationVP1;         // target _tetherRotation if not tethered
		// end
		double m_curAltFromTerrain;
	public:
		virtual void setViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0,bool testFlag = false );
		virtual void setByMatrix(const osg::Matrixd& matrix);
		virtual void setByLookAt(const osg::Vec3d& eye, const osg::Vec3d& lv, const osg::Vec3d& up);
		virtual void pan( double dx, double dy );
		virtual void zoom( double dx, double dy );
		virtual void rotate( double dx, double dy );

		// 导航条调用
		void rotateWithCamCenter( double dx, double dy );
		void panThroughCtrl(double dx, double dy);
		void getPanAxis(osg::Vec3d& up,osg::Vec3d& north,osg::Vec3d& right);

		FeUtil::CRenderContext* GetRenderContext(){return m_opRenderContext.get();}

		// 鸟瞰图定位调用
		void flyToViewpoint(const CVBF_Viewpoint& vp, double dTime = 2.0);

	protected:
		virtual bool  screenToWorldHitTerrian(float x, float y, IVBF_View* view, ref_ptr<osg::IVBF_Camera>& out_cam, osg::Vec3d& out_coords,bool& hitTerrain) const;
		virtual bool  screenToWorld(float x, float y, IVBF_View* view, osg::Vec3d& out_coords ,bool& hitTerrain) const;	
		bool screenToWorldWithIntersector(float x, float y, IVBF_View* theView,ref_ptr<osg::IVBF_Camera>& out_cam,  osg::Vec3d& out_coords) const;
		bool screenToRay(float x, float y, ref_ptr<osg::IVBF_Camera>& cam, osg::Vec3d& start,osg::Vec3d& end) const;
		bool screenToMaskNodeIntersector(float x, float y, IVBF_View* theView, osg::Vec3d& out_coords) const;
	};
}

#endif // FREE_UTILS_EARTHMANIPULATOR
