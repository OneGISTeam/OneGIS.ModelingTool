#ifndef OSGEARTHFEATURES_FEATURE_H
#define OSGEARTHFEATURES_FEATURE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/FilterContext.h>


#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/VBFO_Shape.h>
#include <map>
#include <list>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    class FilterContext;

	// �������ݵ�Ԫ���ݺ͸�Ҫ��Ϣ
    class OSGEARTHFEATURES_EXPORT FeatureProfile : public ::CVBF_Referenced
    {
    public:        
        FeatureProfile( const CVBF_GeoExtent& extent );
        virtual ~FeatureProfile() { }

  		// ��ȡ����Ŀռ䷶Χ
        const CVBF_GeoExtent& getExtent() const { return m_Extent; }

		// ��ȡ����Ŀռ�ο�ϵͳ
        const CVBF_SpatialReference* getSRS() const { return m_Extent.getSRS(); }

		// ��ȡ/�����Ƿ�ֿ飨��Ƭ��
        bool getTiled() const;
        void setTiled(bool tiled);

		// ����/��ȡ��С��LOD
        int getFirstLevel() const;
        void setFirstLevel(int firstLevel );

		// ����/��ȡ����LOD
        int getMaxLevel() const;
        void setMaxLevel(int maxLevel);

        const CVBF_Profile* getProfile() const;
        void setProfile( const CVBF_Profile* profile );

    protected:
        ref_ptr< const CVBF_Profile > m_ipProfile;
        CVBF_GeoExtent m_Extent;
        bool m_bTiled;
        int m_nLevelFirst;
        int m_LevelMax;
    };

    struct AttributeValueUnion
    {
        std::string stringValue;
        double      doubleValue;
        int         intValue;
        bool        boolValue;

        bool        set;// �Ƿ����ø�ֵ��false��ζ��ֵ��Ч
    };

    enum AttributeType
    {
        ATTRTYPE_UNSPECIFIED,
        ATTRTYPE_STRING,
        ATTRTYPE_INT,
        ATTRTYPE_DOUBLE,
        ATTRTYPE_BOOL
    };

    struct OSGEARTHFEATURES_EXPORT AttributeValue : public std::pair<AttributeType,AttributeValueUnion>
    {    
        std::string getString() const;
        double  getDouble( double defaultValue =0.0 ) const;
        int     getInt( int defaultValue =0 ) const;
        bool    getBool( bool defaultValue =false ) const;
    };

    typedef std::map<std::string, AttributeValue> AttributeTable;


    typedef unsigned long FeatureID;

	// �����ü�����FeatureID
    class RefFeatureID : public ::CVBF_Referenced
    {
    public:
        RefFeatureID( FeatureID fid ) : _fid(fid) { }
        virtual ~RefFeatureID() { }

        operator FeatureID () const { return _fid; }
    protected:
        FeatureID _fid;
    };


    typedef std::map< std::string, AttributeType > FeatureSchema;

    class Feature;

    typedef std::list< ref_ptr<Feature> > FeatureList;

	// ʸ����������
    class OSGEARTHFEATURES_EXPORT Feature : public osg::CVBF_Object
    {
    public: 
        Feature( Geometry* geom, const CVBF_SpatialReference* srs, const Style& style =Style(), FeatureID fid =0L );
        Feature( const Feature& rhs, const osg::CopyOp& copyop =osg::CopyOp::DEEP_COPY_ALL );

        virtual ~Feature() { }

        META_Object( VBF_Features, Feature );

    public:

		// ΨһID������һ���ṩ����˵��
        FeatureID getFID() const;

		// ����ļ�������
        void setGeometry( Symbology::Geometry* geom );
        Symbology::Geometry* getGeometry() { dirty(); return m_ipGeom.get(); }
        const Symbology::Geometry* getGeometry() const { return m_ipGeom.get(); }

		// �ռ�ο�ϵͳ
        const CVBF_SpatialReference* getSRS() const { return m_ipSrs.get(); }
        void setSRS( const CVBF_SpatialReference* srs );

		// �ڸ����Ŀռ�ο�ϵͳ�м����Χ��
        bool getWorldBound( const CVBF_SpatialReference* srs, osg::BoundingSphered& out_bound ) const;

        // ��ȡ�����õ����һ�������壨��������ϵ��ͶӰ�����ECEF���꣩�������ڸ����ж�����ε��ཻ
        bool getWorldBoundingPolytope( const CVBF_SpatialReference* srs, osg::Polytope& out_polytope ) const;

        const AttributeTable& getAttrs() const { return m_AttrTable; }

		// ��������ֵ
        void set( const std::string& name, const std::string& value );
        void set( const std::string& name, double value );
        void set( const std::string& name, int value );
        void set( const std::string& name, bool value );

  		// ��������ΪNULL
        void setNull( const std::string& name );
        void setNull( const std::string& name, AttributeType type );

        bool hasAttr( const std::string& name ) const;

        std::string getString( const std::string& name ) const;
        double getDouble( const std::string& name, double defaultValue =0.0 ) const;
        int getInt( const std::string& name, int defaultValue =0 ) const;
        bool getBool( const std::string& name, bool defaultValue =false ) const;

		// �����Ƿ�����
        bool isSet( const std::string& name ) const;

        // Ƕ��ķ�񣨽����ڸõ���ģ�
        CVBF_Optional<Style>& style() { return m_optStyle; }
        const CVBF_Optional<Style>& style() const { return m_optStyle; }

		// ���������ֵ����
        CVBF_Optional<GeoInterpolation>& geoInterp() { dirty(); return _geoInterp; }
        const CVBF_Optional<GeoInterpolation>& geoInterp() const { return _geoInterp; }

		// ������ֵ�����ʽ�ı���������������
		double eval( NumericExpression& expr, FilterContext const* context=0L ) const;
        const std::string& eval( StringExpression& expr, FilterContext const* context=0L ) const;

    public:
		// ��ȡ�õ����GeoJSON���ʽ��GeoJSON �ǻ���JavaScript�����ʾ��(JSON)��һ���µ����ݸ�ʽ��
		// �����Դ����ĵ����������б��룬֧�ֵĵ��������е㡢�ߡ�����Ρ������κ͵�����Ϣ���ϡ�
        std::string getGeoJSON();

 		// ��һ��������б�ת��ΪGeoJSON���ʽ
        static std::string featuresToGeoJSON( FeatureList& features);

    public:

		// �Ѹö���任�������Ŀռ�ο�ϵͳ
        void transform( const CVBF_SpatialReference* srs );

    protected:
        Feature( FeatureID fid =0L );

        FeatureID                            m_nID;
        ref_ptr<Symbology::Geometry>         m_ipGeom;
        ref_ptr<const CVBF_SpatialReference> m_ipSrs;
        AttributeTable                       m_AttrTable;
        CVBF_Optional<Style>                 m_optStyle;
        CVBF_Optional<GeoInterpolation>      _geoInterp;
        CVBF_GeoExtent                       _cachedExtent;

        void dirty();
    };



} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_H
