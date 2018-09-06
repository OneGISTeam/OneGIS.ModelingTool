#ifndef OSGEARTH_MASK_LAYER_H
#define OSGEARTH_MASK_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Layer.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceMask.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>

class CVBF_Map;

// ����ͼ���������
class OSGEARTH_EXPORT MaskLayerOptions : public CVBF_Options
{
public:        
    MaskLayerOptions( const CVBF_Options& options =CVBF_Options() );
    MaskLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceMask& driverOptions =CVBF_OptionsDriverSourceMask() );

    virtual ~MaskLayerOptions();

	// ͼ����
    CVBF_Optional<std::string>& name() { return m_sName; }
    const CVBF_Optional<std::string>& name() const { return m_sName; }

	// ����Դ��������ѡ��
    CVBF_Optional<CVBF_OptionsDriverSourceMask>& driver() { return _driver; }
    const CVBF_Optional<CVBF_OptionsDriverSourceMask>& driver() const { return _driver; }

public:
    virtual CVBF_Config getConfig() const;
    virtual void mergeConfig( const CVBF_Config& conf );

private:
    void fromConfig( const CVBF_Config& conf );
    void setDefaults();

    CVBF_Optional<std::string> m_sName;
    CVBF_Optional<CVBF_OptionsDriverSourceMask> _driver;
};

// ����ͼ����һ�������ͼ�㡣���ڸǵ����ε�һ���֣��൱�ڲ�ͼ��
class OSGEARTH_EXPORT CVBF_LayerMask : public CVBF_Layer
{
public:
	// ��������ѡ�������ͼ��
    CVBF_LayerMask( const MaskLayerOptions& options =MaskLayerOptions() );

	// ��������������ѡ�������ͼ��
    CVBF_LayerMask( const std::string& name, const CVBF_OptionsDriverSourceMask& options );
        
	// ������������Դ��������ͼ��
    CVBF_LayerMask(const MaskLayerOptions& options, CVBFO_SourceMask* source );

    virtual ~CVBF_LayerMask() { }

	// ��ȡ����ͼ������Դ
    CVBFO_SourceMask* getMaskSource() const { return _maskSource.get(); }

    virtual int getUID() const { return 0; }
    virtual bool getEnabled() const { return true; }
    virtual void setVisible( bool value ){}
    virtual bool getVisible() const { return true; }

public:
	// ��ȡ����
    const std::string& getName() const { return *_runtimeOptions.name(); }

	// ��ȡ�����ε�����ļ��α߽�����
    osg::Vec3dArray* getOrCreateBoundary( float heightScale = 1.0, const CVBF_SpatialReference* srs = NULL, ProgressCallback* progress =0L );

public:

	// ��ʼ��
    void initialize( const osgDB::Options* dbOptions, const CVBF_Map* map );

private:
    MaskLayerOptions				_initOptions;	// ��ʼ��ѡ��
    MaskLayerOptions				_runtimeOptions;// ����ʱѡ��
    ref_ptr<CVBFO_SourceMask>		_maskSource;	// ����Դ
    Revision						_maskSourceRev;	// ����Դ�汾
    ref_ptr<osg::Vec3dArray>		_boundary;		// �߽�
    ref_ptr<osgDB::Options>			_dbOptions;		// ���ݿ�ѡ��

    void copyOptions();
};

typedef std::vector< ref_ptr<CVBF_LayerMask> > CVBF_LayersMask;


#endif // OSGEARTH_MASK_LAYER_H

