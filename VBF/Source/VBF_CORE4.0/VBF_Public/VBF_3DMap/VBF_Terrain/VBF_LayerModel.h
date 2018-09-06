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


//!!! �˲���Ӧ������Node�޹صģ�Ӧ�ð�Node�Ż���

class CVBF_Map;

// ģ��ͼ�������ѡ��
class OSGEARTH_EXPORT ModelLayerOptions : public CVBF_Options
{
public:
	// �����������ģ��ͼ��ѡ��
    ModelLayerOptions( const CVBF_Options& options =CVBF_Options() );
	// ��������Դ�������������ģ��ͼ��ѡ��
    ModelLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceModel& driverOptions =CVBF_OptionsDriverSourceModel() );
    ModelLayerOptions( const ModelLayerOptions& rhs );

    virtual ~ModelLayerOptions();

    ModelLayerOptions& operator = ( const ModelLayerOptions& rhs );

	// ��ȡͼ������
    CVBF_Optional<std::string>& name()			   { return m_sName; }
    const CVBF_Optional<std::string>& name() const { return m_sName; }

	// ��ȡ����Դ������������
    CVBF_Optional<CVBF_OptionsDriverSourceModel>& driver() { return _driver; }
    const CVBF_Optional<CVBF_OptionsDriverSourceModel>& driver() const { return _driver; }

	// ģ�ͽڵ��Ƿ�����OpenGL����
    CVBF_Optional<bool>& lightingEnabled() { return _lighting; }
    const CVBF_Optional<bool>& lightingEnabled() const { return _lighting; }

	// ��ͼ���Ƿ���ã�active��
    CVBF_Optional<bool>& enabled() { return _enabled; }
    const CVBF_Optional<bool>& enabled() const { return _enabled; }

	// ��ͼ���Ƿ�ɼ�
    CVBF_Optional<bool>& visible() { return _visible; }
    const CVBF_Optional<bool>& visible() const { return _visible; }

	// �Ƿ���Ϊһ��ͶӰ�ĸ��ǲ㣨projected overlay�����ǵ��Σ�Ĭ����false���������������壬���ǵ��θ��ǲ㣩
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

// ģ��ͼ��Ļص�����������model layer���Ա仯֪ͨ�Ļص�
struct ModelLayerCallback : public ::CVBF_Referenced
{
    virtual void onVisibleChanged( class CVBF_LayerModel* layer ) { }
    virtual void onOverlayChanged( class CVBF_LayerModel* layer ) { }
    virtual ~ModelLayerCallback() { }
};

typedef void (ModelLayerCallback::*ModelLayerCallbackMethodPtr)(CVBF_LayerModel* layer);

typedef std::list< ref_ptr<ModelLayerCallback> > ModelLayerCallbackList;

// ģ��ͼ��
class OSGEARTH_EXPORT CVBF_LayerModel : public CVBF_Layer
{
public:
    CVBF_LayerModel();
	// ����ģ��ͼ�������ѡ���ģ��ͼ��
    CVBF_LayerModel( const ModelLayerOptions& options );

	// ��������Դ�������������ģ��ͼ��
    CVBF_LayerModel( const std::string& name, const CVBF_OptionsDriverSourceModel& options );
        
    // ����ģ��ͼ�������ѡ�������Դ����ģ��ͼ��
    CVBF_LayerModel(const ModelLayerOptions& options, CVBFO_SourceModel* pSource );

	// ����ͼ������һ���Ѿ����ڵĽڵ㴴��ģ��ͼ��//!!!����ȥ��������
    CVBF_LayerModel(const std::string& name, osg::IVBF_SGNode* pINode);

    virtual ~CVBF_LayerModel();

public:
	// ��ȡͼ�������
    const std::string& getName() const { return *_runtimeOptions.name(); }

	// ��ȡͼ��ĳ�ʼ����ѡ��
    const ModelLayerOptions& getModelLayerOptions() const { return _initOptions; }

	// ��ȡģ������Դ
    CVBFO_SourceModel* getModelSource() const { return m_ipModelSource.get(); }

public:
	// ��ʼ������Map����
    void initialize( const osgDB::Options* options );

	// ����������ͼ��ĳ���ͼ�ڵ�
    osg::IVBF_SGNode* createSceneGraph( const CVBF_Map* map, const osgDB::Options* dbOptions, ProgressCallback* progress );

public: // properties

	// ��ȡ/�����Ƿ���Ⱦ��ͼ��
    bool getVisible() const;
    void setVisible(bool value);

	// �Ƿ����ø�ͼ��
    bool getEnabled() const;

	// ��ͼ������Ϊ���������壬������Ϊ���θ��ǲ����
    bool getOverlay() const;
    void setOverlay( bool overlay );

	// ͼ��ĸ��ڵ��Ƿ����ù���
    void setLightingEnabled( bool value );
    bool isLightingEnabled() const;

public:

	// ���/�Ƴ�һ���ص��������ûص��������ⲿ֪ͨͼ�����Ա仯
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
