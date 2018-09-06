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

	// 地物数据的元数据和概要信息
    class OSGEARTHFEATURES_EXPORT FeatureProfile : public ::CVBF_Referenced
    {
    public:        
        FeatureProfile( const CVBF_GeoExtent& extent );
        virtual ~FeatureProfile() { }

  		// 获取地物的空间范围
        const CVBF_GeoExtent& getExtent() const { return m_Extent; }

		// 获取地物的空间参考系统
        const CVBF_SpatialReference* getSRS() const { return m_Extent.getSRS(); }

		// 获取/设置是否分块（瓦片）
        bool getTiled() const;
        void setTiled(bool tiled);

		// 设置/获取最小的LOD
        int getFirstLevel() const;
        void setFirstLevel(int firstLevel );

		// 设置/获取最大的LOD
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

        bool        set;// 是否设置该值，false意味着值无效
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

	// 带引用计数的FeatureID
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

	// 矢量地物数据
    class OSGEARTHFEATURES_EXPORT Feature : public osg::CVBF_Object
    {
    public: 
        Feature( Geometry* geom, const CVBF_SpatialReference* srs, const Style& style =Style(), FeatureID fid =0L );
        Feature( const Feature& rhs, const osg::CopyOp& copyop =osg::CopyOp::DEEP_COPY_ALL );

        virtual ~Feature() { }

        META_Object( VBF_Features, Feature );

    public:

		// 唯一ID（对提一个提供者来说）
        FeatureID getFID() const;

		// 地物的几何数据
        void setGeometry( Symbology::Geometry* geom );
        Symbology::Geometry* getGeometry() { dirty(); return m_ipGeom.get(); }
        const Symbology::Geometry* getGeometry() const { return m_ipGeom.get(); }

		// 空间参考系统
        const CVBF_SpatialReference* getSRS() const { return m_ipSrs.get(); }
        void setSRS( const CVBF_SpatialReference* srs );

		// 在给定的空间参考系统中计算包围盒
        bool getWorldBound( const CVBF_SpatialReference* srs, osg::BoundingSphered& out_bound ) const;

        // 获取包含该地物的一个多面体（世界坐标系，投影坐标或ECEF坐标），可用于概略判断与地形的相交
        bool getWorldBoundingPolytope( const CVBF_SpatialReference* srs, osg::Polytope& out_polytope ) const;

        const AttributeTable& getAttrs() const { return m_AttrTable; }

		// 设置属性值
        void set( const std::string& name, const std::string& value );
        void set( const std::string& name, double value );
        void set( const std::string& name, int value );
        void set( const std::string& name, bool value );

  		// 设置属性为NULL
        void setNull( const std::string& name );
        void setNull( const std::string& name, AttributeType type );

        bool hasAttr( const std::string& name ) const;

        std::string getString( const std::string& name ) const;
        double getDouble( const std::string& name, double defaultValue =0.0 ) const;
        int getInt( const std::string& name, int defaultValue =0 ) const;
        bool getBool( const std::string& name, bool defaultValue =false ) const;

		// 属性是否设置
        bool isSet( const std::string& name ) const;

        // 嵌入的风格（仅属于该地物的）
        CVBF_Optional<Style>& style() { return m_optStyle; }
        const CVBF_Optional<Style>& style() const { return m_optStyle; }

		// 地理坐标差值方法
        CVBF_Optional<GeoInterpolation>& geoInterp() { dirty(); return _geoInterp; }
        const CVBF_Optional<GeoInterpolation>& geoInterp() const { return _geoInterp; }

		// 用属性值填充表达式的变量，并重新运算
		double eval( NumericExpression& expr, FilterContext const* context=0L ) const;
        const std::string& eval( StringExpression& expr, FilterContext const* context=0L ) const;

    public:
		// 获取该地物的GeoJSON表达式，GeoJSON 是基于JavaScript对象表示法(JSON)的一种新的数据格式，
		// 用来对大量的地理特征进行编码，支持的地理特征有点、线、多边形、多多边形和地理信息集合。
        std::string getGeoJSON();

 		// 把一个地物的列表转换为GeoJSON表达式
        static std::string featuresToGeoJSON( FeatureList& features);

    public:

		// 把该对象变换到给定的空间参考系统
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
