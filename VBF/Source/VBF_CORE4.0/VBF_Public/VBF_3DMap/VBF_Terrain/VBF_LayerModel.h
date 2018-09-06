#ifndef OSGEARTH_MODEL_LAYER_H
#define OSGEARTH_MODEL_LAYER_H 1

#include <vector>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SGDB/Options>

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Layer.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceModel.h>
#include <VBF_3DMap/VBF_Terrain/ShaderUtils.h>


//!!! 此部分应该是与Node无关的，应该把Node优化掉

class CVBF_Map;

// 模型图层的配置选项
class OSGEARTH_EXPORT ModelLayerOptions : public CVBF_Options
{
public:
	// 根据配置项构建模型图层选项
    ModelLayerOptions( const CVBF_Options& options =CVBF_Options() );
	// 根据数据源驱动器配置项构建模型图层选项
    ModelLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceModel& driverOptions =CVBF_OptionsDriverSourceModel() );
    ModelLayerOptions( const ModelLayerOptions& rhs );

    virtual ~ModelLayerOptions();

    ModelLayerOptions& operator = ( const ModelLayerOptions& rhs );

	// 获取图层名字
    CVBF_Optional<std::string>& name()			   { return m_sName; }
    const CVBF_Optional<std::string>& name() const { return m_sName; }

	// 获取数据源驱动器配置项
    CVBF_Optional<CVBF_OptionsDriverSourceModel>& driver() { return _driver; }
    const CVBF_Optional<CVBF_OptionsDriverSourceModel>& driver() const { return _driver; }

	// 模型节点是否启用OpenGL光照
    CVBF_Optional<bool>& lightingEnabled() { return _lighting; }
    const CVBF_Optional<bool>& lightingEnabled() const { return _lighting; }

	// 该图层是否可用（active）
    CVBF_Optional<bool>& enabled() { return _enabled; }
    const CVBF_Optional<bool>& enabled() const { return _enabled; }

	// 该图层是否可见
    CVBF_Optional<bool>& visible() { return _visible; }
    const CVBF_Optional<bool>& visible() const { return _visible; }

	// 是否作为一个投影的覆盖层（projected overlay）覆盖地形，默认是false。（是正常几何体，还是地形覆盖层）
    CVBF_Optional<bool>& overlay() { return _overlay; }
    const CVBF_Optional<bool>& overlay() const { return _overlay; }

public:
    virtual CVBF_Config getConfig() const;
    virtual void mergeConfig( const CVBF_Config& conf );

private:
    void fromConfig( const CVBF_Config& conf );
    void setDefaults();

    CVBF_Optional<std::string>        m_sName;
    CVBF_Optional<bool>               _overlay;
    CVBF_Optional<CVBF_OptionsDriverSourceModel> _driver;
    CVBF_Optional<bool>               _enabled;
    CVBF_Optional<bool>               _visible;
    CVBF_Optional<bool>               _lighting;
};

// 模型图层的回调函数：接收model layer属性变化通知的回调
struct ModelLayerCallback : public ::CVBF_Referenced
{
    virtual void onVisibleChanged( class CVBF_LayerModel* layer ) { }
    virtual void onOverlayChanged( class CVBF_LayerModel* layer ) { }
    virtual ~ModelLayerCallback() { }
};

typedef void (ModelLayerCallback::*ModelLayerCallbackMethodPtr)(CVBF_LayerModel* layer);

typedef std::list< ref_ptr<ModelLayerCallback> > ModelLayerCallbackList;

// 模型图层
class OSGEARTH_EXPORT CVBF_LayerModel : public CVBF_Layer
{
public:
    CVBF_LayerModel();
	// 根据模型图层的配置选项创建模型图层
    CVBF_LayerModel( const ModelLayerOptions& options );

	// 根据数据源驱动器配置项创建模型图层
    CVBF_LayerModel( const std::string& name, const CVBF_OptionsDriverSourceModel& options );
        
    // 根据模型图层的配置选项和数据源创建模型图层
    CVBF_LayerModel(const ModelLayerOptions& options, CVBFO_SourceModel* pSource );

	// 根据图层名和一个已经存在的节点创建模型图层//!!!可以去掉？？？
    CVBF_LayerModel(const std::string& name, osg::IVBF_SGNode* pINode);

    virtual ~CVBF_LayerModel();

public:
	// 获取图层的名称
    const std::string& getName() const { return *_runtimeOptions.name(); }

	// 获取图层的初始配置选项
    const ModelLayerOptions& getModelLayerOptions() const { return _initOptions; }

	// 获取模型数据源
    CVBFO_SourceModel* getModelSource() const { return m_ipModelSource.get(); }

public:
	// 初始化，由Map调用
    void initialize( const osgDB::Options* options );

	// 创建描述该图层的场景图节点
    osg::IVBF_SGNode* createSceneGraph( const CVBF_Map* map, const osgDB::Options* dbOptions, ProgressCallback* progress );

public: // properties

	// 获取/设置是否渲染该图层
    bool getVisible() const;
    void setVisible(bool value);

	// 是否启用该图层
    bool getEnabled() const;

	// 该图层是作为正常几何体，还是作为地形覆盖层绘制
    bool getOverlay() const;
    void setOverlay( bool overlay );

	// 图层的根节点是否启用光照
    void setLightingEnabled( bool value );
    bool isLightingEnabled() const;

public:

	// 添加/移除一个回调函数，该回调函数向外部通知图层属性变化
    void addCallback( ModelLayerCallback* cb );
    void removeCallback( ModelLayerCallback* cb );

private:
    ref_ptr<CVBFO_SourceModel>    m_ipModelSource;

    const ModelLayerOptions            _initOptions;
    ModelLayerOptions					_runtimeOptions;

    Revision							_modelSourceRev;
    ModelLayerCallbackList				_callbacks;
    UpdateLightingUniformsHelper		_updateLightingUniformsHelper;

    typedef std::set< observer_ptr<osg::IVBF_SGNode> > NodeObserverSet;
    NodeObserverSet _nodeSet;

    virtual void fireCallback( ModelLayerCallbackMethodPtr method );

    void copyOptions();
};

typedef std::vector< ref_ptr<CVBF_LayerModel> > CVBF_LayersModel;


#endif // OSGEARTH_MODEL_LAYER_H
