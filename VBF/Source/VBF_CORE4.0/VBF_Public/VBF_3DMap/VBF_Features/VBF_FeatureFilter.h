#ifndef OSGEARTHFEATURES_FILTER_H
#define OSGEARTHFEATURES_FILTER_H 1


#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FilterContext.h>
#include <Types/VBF_Matrixd.h>
#include <list>


namespace osgEarth { namespace Features
{
    using namespace osgEarth;

	// ����������
    class Filter : public ::CVBF_Referenced
    {
    };

	// feature����������
    class OSGEARTHFEATURES_EXPORT FeatureFilter : public Filter
    {
    public:
        virtual FilterContext push( FeatureList& input, FilterContext& context ) =0;
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }
        virtual ~FeatureFilter() { }
    };


    typedef std::list< ref_ptr<FeatureFilter> > FeatureFilterList;



	// �������ã�CVBF_Config������FeatureFilter���๤����Factory��
    class OSGEARTHFEATURES_EXPORT FeatureFilterFactory : public ::CVBF_Referenced
    {
    public:
        virtual FeatureFilter* create( const CVBF_Config& conf ) = 0;
    };    

    typedef std::list< ref_ptr< FeatureFilterFactory > > FeatureFilterFactoryList;




	// FeatureFilter���ע����
    class OSGEARTHFEATURES_EXPORT FeatureFilterRegistry : public ::CVBF_Referenced
    {         
    public:
		// ��ʵ������
        static FeatureFilterRegistry* instance();

		// ���һ���µ�FeatureFilterFactory
        void add( FeatureFilterFactory* factory );

		// ʹ��ע��Ĳ��������һ��FeatureFilter
        FeatureFilter* create( const CVBF_Config& conf );

    protected:
        FeatureFilterRegistry();
        FeatureFilterFactoryList _factories;
    };




    template<class T>
    struct SimpleFeatureFilterFactory : public FeatureFilterFactory
    {
        SimpleFeatureFilterFactory(const std::string& key):_key(key){}

        virtual FeatureFilter* create(const CVBF_Config& conf)
        {
            if (conf.key() == _key) return new T(conf);            
            return 0;
        }

        std::string _key;
    };

    template<class T>
    struct RegisterFeatureFilterProxy
    {
        RegisterFeatureFilterProxy( T* factory) { FeatureFilterRegistry::instance()->add( factory ); }
        RegisterFeatureFilterProxy() { FeatureFilterRegistry::instance()->add( new T ); }
    };

#define OSGEARTH_REGISTER_FEATUREFILTER( CLASSNAME )\
    static osgEarth::Features::RegisterFeatureFilterProxy<CLASSNAME> s_osgEarthRegisterFeatureFilterProxy_##CLASSNAME;

#define OSGEARTH_REGISTER_SIMPLE_FEATUREFILTER( KEY, CLASSNAME)\
    static osgEarth::Features::RegisterFeatureFilterProxy< osgEarth::Features::SimpleFeatureFilterFactory<CLASSNAME> > s_osgEarthRegisterFeatureFilterProxy_##CLASSNAME##KEY(new osgEarth::Features::SimpleFeatureFilterFactory<CLASSNAME>(#KEY));


    template<typename T>
    class TemplateFeatureFilter : public Filter, public T
    {
    public:
        FilterContext push( FeatureList& input, FilterContext& context ) 
		{
            for( FeatureList::iterator i = input.begin(); i != input.end(); ++i ) 
			{
                T::operator()( i->get(), context );
            }
            return context;
        }
    };


	//  Base class for a filter that converts features into an osg Node.
    class OSGEARTHFEATURES_EXPORT FeaturesToNodeFilter : public Filter
    {
    public:
        virtual osg::IVBF_SGNode* push( Features::FeatureList& input, FilterContext& context ) =0;

    public:
        const osg::Matrixd& local2world() const { return _local2world; }
        const osg::Matrixd& world2local() const { return _world2local; }
        
        virtual ~FeaturesToNodeFilter() { }
        
    protected:

        // computes the matricies required to localizer/delocalize double-precision coords
        void computeLocalizers( const FilterContext& context );

        /** Parents the node with a localizer group if necessary */
        osg::IVBF_SGNode*  delocalize( osg::IVBF_SGNode* node ) const;
        osg::IVBF_SGNodeGroup* delocalizeAsGroup( osg::IVBF_SGNode* node ) const;
        osg::IVBF_SGNodeGroup* createDelocalizeGroup() const;

        void transformAndLocalize( const std::vector<osg::Vec3d>& input,
				const CVBF_SpatialReference*  inputSRS, osg::Vec3Array* output,
				const CVBF_SpatialReference* outputSRS, const osg::Matrixd& world2local, bool toECEF );

        void transformAndLocalize( const std::vector<osg::Vec3d>& input,
				const CVBF_SpatialReference* inputSRS, osg::Vec3Array* out_verts, osg::Vec3Array* out_normals,
				const CVBF_SpatialReference* outputSRS, const osg::Matrixd& world2local, bool toECEF );

        void transformAndLocalize( const osg::Vec3d& input, const CVBF_SpatialReference* inputSRS,
				osg::Vec3d& output, const CVBF_SpatialReference* outputSRS,
				const osg::Matrixd&  world2local, bool toECEF );

        osg::Matrixd _world2local, _local2world;   // for coordinate localization
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FILTER_H
