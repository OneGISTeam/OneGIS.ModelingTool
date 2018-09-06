#ifndef OSGEARTH_MASK_LAYER_H
#define OSGEARTH_MASK_LAYER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Layer.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceMask.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>

class CVBF_Map;

// 掩码图层的配置项
class OSGEARTH_EXPORT MaskLayerOptions : public CVBF_Options
{
public:        
    MaskLayerOptions( const CVBF_Options& options =CVBF_Options() );
    MaskLayerOptions( const std::string& name, const CVBF_OptionsDriverSourceMask& driverOptions =CVBF_OptionsDriverSourceMask() );

    virtual ~MaskLayerOptions();

	// 图层名
    CVBF_Optional<std::string>& name() { return m_sName; }
    const CVBF_Optional<std::string>& name() const { return m_sName; }

	// 数据源驱动器的选项
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

// 掩饰图层是一个特殊的图层。用于盖掉地形的一部分（相当于插图）
class OSGEARTH_EXPORT CVBF_LayerMask : public CVBF_Layer
{
public:
	// 根据配置选项构建掩饰图层
    CVBF_LayerMask( const MaskLayerOptions& options =MaskLayerOptions() );

	// 根据数据驱动器选项构建掩饰图层
    CVBF_LayerMask( const std::string& name, const CVBF_OptionsDriverSourceMask& options );
        
	// 根据掩饰数据源构建掩饰图层
    CVBF_LayerMask(const MaskLayerOptions& options, CVBFO_SourceMask* source );

    virtual ~CVBF_LayerMask() { }

	// 获取掩饰图层数据源
    CVBFO_SourceMask* getMaskSource() const { return _maskSource.get(); }

    virtual int getUID() const { return 0; }
    virtual bool getEnabled() const { return true; }
    virtual void setVisible( bool value ){}
    virtual bool getVisible() const { return true; }

public:
	// 获取名字
    const std::string& getName() const { return *_runtimeOptions.name(); }

	// 获取被掩饰掉区域的几何边界多边形
    osg::Vec3dArray* getOrCreateBoundary( float heightScale = 1.0, const CVBF_SpatialReference* srs = NULL, ProgressCallback* progress =0L );

public:

	// 初始化
    void initialize( const osgDB::Options* dbOptions, const CVBF_Map* map );

private:
    MaskLayerOptions				_initOptions;	// 初始化选项
    MaskLayerOptions				_runtimeOptions;// 运行时选项
    ref_ptr<CVBFO_SourceMask>		_maskSource;	// 数据源
    Revision						_maskSourceRev;	// 数据源版本
    ref_ptr<osg::Vec3dArray>		_boundary;		// 边界
    ref_ptr<osgDB::Options>			_dbOptions;		// 数据库选项

    void copyOptions();
};

typedef std::vector< ref_ptr<CVBF_LayerMask> > CVBF_LayersMask;


#endif // OSGEARTH_MASK_LAYER_H

