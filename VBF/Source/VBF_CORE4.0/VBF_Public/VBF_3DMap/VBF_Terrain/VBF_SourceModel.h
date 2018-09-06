#ifndef OSGEARTH_MODEL_SOURCE_H
#define OSGEARTH_MODEL_SOURCE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/NodeUtils.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SGDB/Options>

using namespace osgEarth;

class CVBF_Map;

  
// ģ������Դ������ѡ��
class OSGEARTH_EXPORT CVBF_OptionsDriverSourceModel : public CVBF_OptionsDriver
{
public:
    CVBF_OptionsDriverSourceModel( const CVBF_Options& options =CVBF_Options() );

    virtual ~CVBF_OptionsDriverSourceModel();
    CVBF_OptionsDriverSourceModel& operator = ( const CVBF_OptionsDriverSourceModel& rhs );

public: // ����

	// ���ݿɼ�����С�����Χ
    const CVBF_Optional<float>& minRange() const { return _minRange; }
		  CVBF_Optional<float>& minRange() { return _minRange; }

	// ���ݿɼ�����������Χ
    const CVBF_Optional<float>& maxRange() const { return _maxRange; }
		  CVBF_Optional<float>& maxRange() { return _maxRange; }

	// ��Ⱦ̨˳��
    const CVBF_Optional<int>& renderOrder() const { return _renderOrder; }
		  CVBF_Optional<int>& renderOrder() { return _renderOrder; }

 	// ��Ⱦʱ�Ƿ����Ȼ���
    const CVBF_Optional<bool>& depthTestEnabled() const { return _depthTestEnabled; }
		  CVBF_Optional<bool>& depthTestEnabled() { return _depthTestEnabled; }

public:
    virtual CVBF_Config getConfig() const;

protected:
    virtual void mergeConfig( const CVBF_Config& conf );
        
private:
    void fromConfig( const CVBF_Config& conf );

    CVBF_Optional<float> _minRange, _maxRange;	// �ɼ���Χ
    CVBF_Optional<int>	_renderOrder;			// ��Ⱦ̨˳��
    CVBF_Optional<bool> _depthTestEnabled;		// ��Ⱦʱ�Ƿ����Ȼ���
    CVBF_Optional<bool> _overlay;				
};


// һ�����ɽڵ�Ĳ������
class OSGEARTH_EXPORT CVBFO_SourceModel : public osg::CVBF_Object, public osgEarth::Revisioned
{
public:
    CVBFO_SourceModel( const CVBF_OptionsDriverSourceModel& options =CVBF_OptionsDriverSourceModel() );

    virtual ~CVBFO_SourceModel();

	// �����ڵ����ڣ�������ʵ���������createNodeImplementation��
    osg::IVBF_SGNode* createNode( const CVBF_Map* map, const osgDB::Options* dbOptions, ProgressCallback* progress );


	// ���麯���������������д����ڵ�
    virtual osg::IVBF_SGNode* createNodeImplementation( const CVBF_Map* map,const osgDB::Options* dbOptions, ProgressCallback* progress ) =0;

	// ���/�Ƴ�һ���������
    void addPostProcessor( NodeOperation* cb );
    void removePostProcessor( NodeOperation* cb );

	// ��ȡ����������б�
    const NodeOperationVector& postProcessors() const;


public: // META_Object specialization
    // these are neseccary to we can load CVBFO_SourceModel implementations as plugins
    virtual osg::CVBF_Object* cloneType() const;
    virtual osg::CVBF_Object* clone(const osg::CopyOp&) const ;
    virtual bool isSameKindAs(const osg::CVBF_Object* obj) const;
    virtual const char* className() const ;
    virtual const char* libraryName() const;

public:
	// ��ʼ��
    virtual void initialize( const osgDB::Options* dbOptions );

    /** Get the options used to create this model source */
    const CVBF_OptionsDriverSourceModel& getOptions() const;

protected:

	// �����ص���ʵ����should call this whenever it adds a new node.
    void firePostProcessors( osg::IVBF_SGNode* node );

private:
    const CVBF_OptionsDriverSourceModel _options;
    CVBF_Optional<double> _minRange;
    CVBF_Optional<double> _maxRange;
    CVBF_Optional<int>    _renderOrder;

    NodeOperationVector  _postProcessors;
    mutable CVBF_Mutex  _postProcessorsMutex;

    friend class CVBF_Map;
    friend class MapEngine;
    friend class ModelSourceFactory;
};

//--------------------------------------------------------------------

class OSGEARTH_EXPORT ModelSourceDriver : public osgDB::ReaderWriter
{
protected:
    const CVBF_OptionsDriverSourceModel& getModelSourceOptions( const osgDB::ReaderWriter::Options* rwOpt ) const;
    virtual const char* className() const;
};

//--------------------------------------------------------------------

// ����CVBFO_SourceTile��ʵ������������װ�䵽һ�����ݷ��ʡ����ߡ�
class OSGEARTH_EXPORT ModelSourceFactory
{   
public:
    static CVBFO_SourceModel* create( const CVBF_OptionsDriverSourceModel& options );
};


#endif // OSGEARTH_MODEL_SOURCE_H
