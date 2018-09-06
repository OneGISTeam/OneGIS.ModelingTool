#ifndef OSGEARTH_DEPTH_ADJUSTMENT_H
#define OSGEARTH_DEPTH_ADJUSTMENT_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrProgram.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>

/**
深度偏移
几何体与地形重合时会导致Z-Buffer争夺现象，深度偏移通过给几何体的深度值加一个偏移减轻Z-Buffer争夺
该想法类似于polygon offsetting，但它是动态应用于所有的几何体（而不仅仅是多边形）

* Depth offsetting works by pretending the vertex is closer to the camera 
* than it actually is, and writing a depth value based on that simulated
* location. The distance we shift the vertex towards the camera is the "bias".
*
* The "range" is the distance from camera to vertex at which a given
* bias is applied. The minimum bias is applied to geometry at or below the
* minimum range; the maximum bias is applied to geometry at or above the 
* maximum range; and the bias is interpolated for ranges in between.
*
* The tessellation granularity of the geometry affects how well depth offsetting
* works at a given camera distance. As a rule of thumb, the closer the camera is
* to the geometry, the more it needs to be tessellated in order for depth
* offsetting to work properly.
*/

/**
* Depth Offsetting options.
*/
class OSGEARTH_EXPORT CVBF_DepthOffsetOptions
{
public:
    CVBF_DepthOffsetOptions(const CVBF_Config& conf =CVBF_Config());

public:
	// 是否启用深度偏移
    CVBF_Optional<bool>& enabled() { return _enabled; }
    const CVBF_Optional<bool>& enabled() const { return _enabled; }

 	// 相机可见范围最小时，深度偏差（单位米）
    CVBF_Optional<float>& minBias() { return _minBias; }
    const CVBF_Optional<float>& minBias() const { return _minBias; }

	// 相机可见范围最大时，深度偏差（单位米）
	CVBF_Optional<float>& maxBias() { return _maxBias; }
    const CVBF_Optional<float>& maxBias() const { return _maxBias; }

    /** camera range (in meters) at which to apply the minimum depth bias. */
    CVBF_Optional<float>& minRange() { return _minRange; }
    const CVBF_Optional<float>& minRange() const { return _minRange; }

    /** camera range (in meters) at which to apply the maximum depth bias. */
    CVBF_Optional<float>& maxRange() { return _maxRange; }
    const CVBF_Optional<float>& maxRange() const { return _maxRange; }

public:
    CVBF_Config getConfig() const;

private:
    CVBF_Optional<bool>		_enabled;
    CVBF_Optional<float>	_minBias;
    CVBF_Optional<float>	_maxBias;
    CVBF_Optional<float>	_minRange;
    CVBF_Optional<float>	_maxRange;
};


/**
    * Controller that affects a stateset with depth offset settings.
    * It does NOT install any shaders.
    */
class OSGEARTH_EXPORT CVBF_DepthOffsetOptionsAdapter
{
public:
    CVBF_DepthOffsetOptionsAdapter(osg::StateSet* stateSet);

    void setOptions(const CVBF_DepthOffsetOptions& options);
    const CVBF_DepthOffsetOptions& getOptions() const { return _options; }

private:
    ref_ptr<osg::StateSet> _stateSet;
    ref_ptr<osg::Uniform>  _biasUniform;
    ref_ptr<osg::Uniform>  _rangeUniform;
    CVBF_DepthOffsetOptions          _options;
};


/**
    * Utilities to manage depth testing for feature data. Handy especially
    * for terrain-conforming lines.
    */
class OSGEARTH_EXPORT CVBF_DepthOffsetUtils
{
public:
    /**
        * Creates a uniform that will configure the depth adjustment program.
        * The value of the uniform is the minimum depth offset applied to 
        * geometry under the program's stateset. If you pass in a graph, it
        * will analyze it and attempt to come up with a reasonable default
        * minimum offset.
        */
    static osg::Uniform* createMinOffsetUniform( osg::IVBF_SGNode* graphToAdjust =0L );

    /**
        * Analyses a graph, calculates a suitable minimum depth offset, and
        * returns it. Also may install support uniforms within the graph as
        * necessary to support depth offsetting.
        */
    static float recalculate( const osg::IVBF_SGNode* graph );

    /**
        * Traverses a graph and applies the necessary uniforms to statesets
        * so they'll work with depth offsetting.
        */
    static void prepareGraph( osg::IVBF_SGNode* graph );

    /**
        * Creates a complete shader program that you can use to implement vertex
        * depth adjustment. Use createUniform() to make a uniform for tweaking
        * the depth offset value.
        */
    static osg::Program* getOrCreateProgram();

    /**
        * Returns a uniform that, when used with the Program, can inform the program
        * whether the underlying drawables are osgText drawables.
        */
    static osg::Uniform* getIsTextUniform();

    /**
        * Returns a uniform that, when used with the Program, can inform the program
        * whether the underlying drawables are NOT osgText drawables.
        */
    static osg::Uniform* getIsNotTextUniform();

    /**
        * Creates the source for a depth adjustment vertex shader. Use this instead
        * of createProgram() if you want you are using the shader composition framework.
        * You can install this in any FunctionLocation.
        */
    static std::string createVertexFunction(
        const std::string& funcName ="osgearth_depth_adjustment_vertex" );

    /**
        * Creates the source for a depth adjustment fragment shader. Use this instead
        * of createProgram() if you want you are using the shader composition framework.
        * You can install this in any FunctionLocation.
        */
    static std::string createFragmentFunction(
        const std::string& funcName ="osgearth_depth_adjustment_fragment" );
};

/**
    * Group that applies the depth offset technique to its children.
    */
class OSGEARTH_EXPORT CVBFO_SGNodeDepthOffset : public osg::CVBF_SGNodeGroup
{
public:
    /**
        * Constructs a new depth offset group
        */
    CVBFO_SGNodeDepthOffset();

    /** dtor */
    virtual ~CVBFO_SGNodeDepthOffset() { }

    /**
        * Sets a minimum depth offset range (in scene units, e.g. meters)
        * This is the minimim simulated depth offset that will be applied to 
        * geometry under this group.
        */
    void setMinimumOffset( float value );

    /**
        * Sets the group to automatically calculate an "appropriate" minimum
        * depth offset based on the child geometry. Whenever the child graph
        * changes, it will attempt to recalculate the best offset to use.
        */
    void setAutoMinimumOffset();

public: // osg::Node

    virtual osg::BoundingSphere computeBound() const;

    virtual void traverse(osg::NodeVisitor& );

protected:
    bool _auto;
    bool m_bDirty;
    osg::Uniform* _minOffsetUniform;
    void update();
    void dirty();
};


#endif // OSGEARTH_DEPTH_ADJUSTMENT_H
