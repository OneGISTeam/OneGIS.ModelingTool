#ifndef OSGEARTH_MASK_SOURCE_H
#define OSGEARTH_MASK_SOURCE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SGDB/Options>

class CVBF_Map;


// 掩码源的配置选项
class OSGEARTH_EXPORT CVBF_OptionsDriverSourceMask : public CVBF_OptionsDriver
{
public:
    CVBF_OptionsDriverSourceMask( const CVBF_Options& options =CVBF_Options() ) :
            CVBF_OptionsDriver( options ) { fromConfig(m_conf); }

    virtual ~CVBF_OptionsDriverSourceMask() { }

public:
    virtual CVBF_Config getConfig() const;

protected:
    virtual void mergeConfig( const CVBF_Config& conf );
        
private:
    void fromConfig( const CVBF_Config& conf );
};

// 掩码源，生成掩码几何体的插件
class OSGEARTH_EXPORT CVBFO_SourceMask : public osg::CVBF_Object, public Revisioned
{
public:        
    CVBFO_SourceMask( const CVBF_OptionsDriverSourceMask& options =CVBF_OptionsDriverSourceMask() );

    virtual ~CVBFO_SourceMask() { }

	// 在子类中实现该方法，创建边界几何体
    virtual osg::Vec3dArray* createBoundary( const CVBF_SpatialReference* srs, ProgressCallback* progress =0L ) =0;

public:
    virtual void initialize( const osgDB::Options* dbOptions, const CVBF_Map* map ) { }

    const CVBF_OptionsDriverSourceMask& getOptions() const { return _options; }
public: 

    // META_Object specialization:
    virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
    virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
    virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const CVBFO_SourceMask*>(obj)!=NULL; }
    virtual const char* className() const { return "CVBFO_SourceMask"; }
    virtual const char* libraryName() const { return "osgEarth"; }

private:
    const CVBF_OptionsDriverSourceMask _options;

    friend class CVBF_Map;
    friend class MaskSourceFactory;
};

//--------------------------------------------------------------------

class OSGEARTH_EXPORT MaskSourceDriver : public osgDB::ReaderWriter
{
protected:
    const CVBF_OptionsDriverSourceMask& getMaskSourceOptions( const osgDB::ReaderWriter::Options* rwOpt ) const;
    virtual const char* className() const;
};

//--------------------------------------------------------------------

class OSGEARTH_EXPORT MaskSourceFactory
{   
public:
    static CVBFO_SourceMask* create( const CVBF_OptionsDriverSourceMask& options );
};


#endif // OSGEARTH_MASK_SOURCE_H
