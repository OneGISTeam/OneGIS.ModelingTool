#ifndef OSGEARTH_GEODATA_H
#define OSGEARTH_GEODATA_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/Bounds.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_Shape.h>

class IVBF_TerrainHeightProvider;

namespace osgEarth
{
    class CVBF_GeoExtent;

	// 地理坐标参考3D点，具体值与SRS相关
    class OSGEARTH_EXPORT GeoPoint
    {
    public:
        GeoPoint( const CVBF_SpatialReference* srs, double x, double y, double z, const AltitudeMode& mode );
        GeoPoint( const CVBF_SpatialReference* srs, double x, double y );// Z为0（相对高度），在地形表面上
        GeoPoint( const CVBF_SpatialReference* srs, const osg::Vec3d& xyz, const AltitudeMode& mode );
        GeoPoint( const CVBF_SpatialReference* srs, const GeoPoint& rhs );// 把已存在的点转换坐标参考

        GeoPoint();//无效的点
        GeoPoint(const GeoPoint& rhs);// 拷贝构造
        GeoPoint( const CVBF_Config& conf, const CVBF_SpatialReference* srs =0L );// 串行化构造

        virtual ~GeoPoint() { }

		// 设置SRS和坐标
        void set( const CVBF_SpatialReference* srs, const osg::Vec3d& xyz, const AltitudeMode& mode );
        void set( const CVBF_SpatialReference* srs, double x, double y, double z, const AltitudeMode& mode );

		// 获取各个量
        double& x() { return _p.x(); }
        double  x() const { return _p.x(); }

        double& y() { return _p.y(); }
        double  y() const { return _p.y(); }

        double& z() { return _p.z(); }
        double  z() const { return _p.z(); }

        double& alt() { return _p.z(); }
        double  alt() const { return _p.z(); }

        osg::Vec3d& vec3d() { return _p; }
        const osg::Vec3d& vec3d() const { return _p; }

        const CVBF_SpatialReference* getSRS() const { return _srs.get(); }

        AltitudeMode& altitudeMode() { return _altMode; }
        const AltitudeMode& altitudeMode() const { return _altMode; }

		// 转换到另一种SRS的点
        GeoPoint transform(const CVBF_SpatialReference* outSRS) const;
        bool transform(const CVBF_SpatialReference* outSRS, GeoPoint& output) const;


		// 转换Z坐标（与地点相关）
        bool transformZ(const AltitudeMode& altMode, const IVBF_TerrainHeightProvider* t );

        // 转换Z坐标（与地点相关），并返回转换后的Z值
        bool transformZ(const AltitudeMode& altMode, const IVBF_TerrainHeightProvider* t, double& out_z) const;

		// 转换Z坐标为绝对高度
        bool makeAbsolute(const IVBF_TerrainHeightProvider* t) { return transformZ(ALTMODE_ABSOLUTE, t); }

		// 转换Z坐标为相对高度
        bool makeRelative(const IVBF_TerrainHeightProvider* t) { return transformZ(ALTMODE_RELATIVE, t); }

		// 转换为地理坐标（lat/long）（与地点相关）
        bool makeGeographic();

   		// 输出该点对应的世界坐标，如果点是ALTMODE_RELATIVE，则返回false，因为无法解决Z坐标，可以使用下面的函数从地形获取高程
        bool toWorld( osg::Vec3d& out_world ) const;
        bool toWorld( osg::Vec3d& out_world, const IVBF_TerrainHeightProvider* terrain ) const;

		// 从世界坐标转化到地理点
        bool fromWorld(const CVBF_SpatialReference* srs, const osg::Vec3d& world);

		// 局部到世界的变化矩阵
        bool createLocalToWorld( osg::Matrixd& out_local2world ) const;

        /**
         * Outputs a matrix that will transform absolute world coordiantes so they are
         * localized into a local tangent place around this geopoint.
         */
        bool createWorldToLocal( osg::Matrixd& out_world2local ) const;


        bool operator == (const GeoPoint& rhs) const;
        bool operator != (const GeoPoint& rhs) const { return !operator==(rhs); }
        bool isValid() const { return _srs.valid(); }

        CVBF_Config getConfig() const;

    public:
        static GeoPoint INVALID;

    protected:
        ref_ptr<const CVBF_SpatialReference> _srs;
        osg::Vec3d       _p;
        AltitudeMode _altMode;
    };


	// 由GeoPoint和半径构成的圆
	class OSGEARTH_EXPORT GeoCircle
	{
	public:
		GeoCircle();
		GeoCircle(const GeoCircle& rhs);
		GeoCircle( const GeoPoint& center, double radius );

		virtual ~GeoCircle() { }

		// 获取/设置圆的中心点
		const GeoPoint& getCenter() const { return _center; }
		void setCenter( const GeoPoint& value ) { _center = value; }

		// 获取/设置圆的半径，使用地图的长度单位（对地理SRS是米）
		double getRadius() const { return _radius; }
		void setRadius( double value ) { _radius = value; }

		// 中心点的坐标参考系统
		const CVBF_SpatialReference* getSRS() const { return _center.getSRS(); }

		bool operator == ( const GeoCircle& rhs ) const;
		bool operator != ( const GeoCircle& rhs ) const { return !operator==(rhs); }

		// 是否有效
		bool isValid() const { return _center.isValid() && _radius > 0.0; }

		// 转换到里一个坐标参考系统
		GeoCircle transform( const CVBF_SpatialReference* srs ) const;
		bool transform( const CVBF_SpatialReference* srs, GeoCircle& out_circle ) const;

		// 相交判断
		bool intersects( const GeoCircle& rhs ) const;

	public:
		static GeoCircle INVALID;

	protected:
		GeoPoint _center;
		double   _radius;
	};


	 // 一个轴对齐的地理空间范围，A bounding box that is aligned with a spatial reference's coordinate system.
    class OSGEARTH_EXPORT CVBF_GeoExtent
    {
	public:
		CVBF_GeoExtent(); 
		CVBF_GeoExtent( const CVBF_SpatialReference* srs, double west, double south, double east, double north );

        CVBF_GeoExtent( const CVBF_SpatialReference* srs );// 无效的，可通过expandToInclude生成
        CVBF_GeoExtent( const CVBF_GeoExtent& rhs );
        CVBF_GeoExtent( const CVBF_SpatialReference* srs, const Bounds& bounds );

        virtual ~CVBF_GeoExtent() { }

        bool operator == ( const CVBF_GeoExtent& rhs ) const;
        bool operator != ( const CVBF_GeoExtent& rhs ) const;

 		// 获取空间参考系统
        const CVBF_SpatialReference* getSRS() const { return _srs.get(); }

        double west() const { return _west; }
        double east() const { return _east; }
        double south() const { return _south; }
        double north() const { return _north; }

        double xMin() const { return west(); }
        double xMax() const { return east(); }
        double yMin() const { return south(); }
        double yMax() const { return north(); }

        double width() const;
        double height() const;

		// 获取中心点
        bool getCentroid( double& out_x, double& out_y ) const;
        osg::Vec3d getCentroid() const { osg::Vec3d r; getCentroid(r.x(), r.y()); return r; }

		// 是否跨越180度经线
        bool crossesAntimeridian() const;

		// 获取范围
        void getBounds(double &xmin, double &ymin, double &xmax, double &ymax) const;

 		// 如果定义了一个实际的、面积为正的有效范围则返回true
        bool isValid() const;
        bool defined() const { return isValid(); }
        bool isInvalid() const { return !isValid(); }

		// 如果跨180度线，按180度线分割为两个范围，并返回true，否则返回false
        bool splitAcrossAntimeridian( CVBF_GeoExtent& first, CVBF_GeoExtent& second ) const;

		// 转换到另一个坐标参考系统。注意：目标SRS可能不适合转换（例如，把一个覆盖全球的WGS84范围转换到墨卡托投影）
		// 可用CVBF_Profile:clampAndTransformExtent()替换
        CVBF_GeoExtent transform( const CVBF_SpatialReference* to_srs ) const;
        bool transform( const CVBF_SpatialReference* to_srs, CVBF_GeoExtent& output ) const;

		// 是否包含点（x，y），点的坐标参考为srs，或者和本对象一致（srs为NULL时）
        bool contains(double x, double y, const CVBF_SpatialReference* srs =0L) const;
        bool contains(const osg::Vec3d& xy, const CVBF_SpatialReference* srs =0L) const { return contains(xy.x(),xy.y(),srs); }
        bool contains( const GeoPoint& rhs ) const;
        bool contains( const CVBF_GeoExtent& rhs ) const;
        bool contains( const Bounds& rhs ) const;

		// 是否与另一个地理范围相交，checkSRS为falae表示不考虑空间参考系统（即认为两个参考系统一致）
        bool intersects( const CVBF_GeoExtent& rhs, bool checkSRS =true ) const;

		// 获取范围
        Bounds bounds() const;

        /**
         * Gets a geo circle bounding this extent.
         */
        const GeoCircle& getBoundingGeoCircle() const { return _circle; }

        /**
         * Grow this extent to include the specified point (which is assumed to be
         * in the extent's SRS.
         */
        void expandToInclude( double x, double y ); 
        void expandToInclude( const osg::Vec3d& v ) { expandToInclude(v.x(), v.y()); }
        void expandToInclude( const Bounds& bounds );

		// 扩展该范围使其包含另一个范围
        bool expandToInclude( const CVBF_GeoExtent& rhs );
        
		// 与另一个地理范围求交（使用相同的SRS）
        CVBF_GeoExtent intersectionSameSRS( const CVBF_GeoExtent& rhs ) const; 

		// 转换成字符串（不含空间参考系统）
        std::string VBF_toString() const;

		// 缩放
        void scale(double x_scale, double y_scale);

		// 扩展
        void expand( double x, double y );

		// 获取面积
        double area() const;

		// 标准化经度的值
        void normalize();

		// 把输入的经度值，规则化为该地理范围内的值
        double normalizeLongitude( double longitude ) const;

    public:
        static CVBF_GeoExtent INVALID;

    private:
        ref_ptr<const CVBF_SpatialReference> _srs;
        double _west, _east, _south, _north;
        GeoCircle _circle;

        void recomputeCircle();
    };

    /**
     * A geospatial area with tile data LOD extents
     */
    class OSGEARTH_EXPORT DataExtent : public CVBF_GeoExtent
    {
    public:
        DataExtent(const CVBF_GeoExtent& extent);
        DataExtent(const CVBF_GeoExtent& extent, unsigned minLevel );
        DataExtent(const CVBF_GeoExtent& extent, unsigned minLevel, unsigned maxLevel);
        virtual ~DataExtent() { }

        /** The minimum LOD of the extent */
        const CVBF_Optional<unsigned>& minLevel() const { return _minLevel; }

        /** The maximum LOD of the extent */
        const CVBF_Optional<unsigned>& maxLevel() const { return _maxLevel; }

    private:
        CVBF_Optional<unsigned> _minLevel;
        CVBF_Optional<unsigned> _maxLevel;
    };

    typedef std::vector< DataExtent > DataExtentList;

	// 带有地理参考的图像
    class OSGEARTH_EXPORT GeoImage
    {
    public:
        GeoImage();
        GeoImage( osg::Image* image, const CVBF_GeoExtent& extent );
        virtual ~GeoImage() { }

        static GeoImage INVALID;

    public:
		// 是否有效
        bool valid() const;

		// 获取图像数据
        osg::Image* getImage() const;

		// 获取图像的地理空间范围
        const CVBF_GeoExtent& getExtent() const;

		// 获取图像的坐标参考系统
        const CVBF_SpatialReference* getSRS() const;

		// 把图像裁剪到一个新的地理空间范围
		// @param exact：true表示用请求的范围精确裁剪，需要重采样，代价较大；false表示简单的裁剪，范围会比请求的大，但速度快
		// @param width, height：请求裁剪后的图像的尺寸
		GeoImage crop( const CVBF_GeoExtent& extent, bool exact = false, unsigned int width = 0, 
			unsigned int height = 0, bool useBilinearInterpolation = true) const;

		// 把图像变换到一个新的坐标参考系统
		// @param to_extent：转换并裁剪的范围，比先调用reproject()再调用crop()速度快
		//@param width, height：输出图像的尺寸，默认情况下会自动计算该尺寸

		GeoImage reproject( const CVBF_SpatialReference* to_srs, const CVBF_GeoExtent* to_extent = 0,
			             unsigned int width = 0, unsigned int height = 0, bool useBilinearInterpolation = true) const;

 		// 在图像的四周添加一个像素的透明边界
        GeoImage addTransparentBorder( bool leftBorder=true, bool rightBorder=true, bool bottomBorder=true, bool topBorder=true);

		// 取出图像（内部减少引用计数）
        osg::Image* takeImage();

		// 获取每个像素的长度
		double getUnitsPerPixel() const;

    private:
        ref_ptr<osg::Image> _image;
        CVBF_GeoExtent _extent;
    };

    typedef std::vector<GeoImage> GeoImageVector;


	// 带地理坐标参考的高程图
    class OSGEARTH_EXPORT GeoHeightField
    {
    public:
        GeoHeightField();
        GeoHeightField( osg::HeightField* heightField, const CVBF_GeoExtent&  extent );

        virtual ~GeoHeightField() { }

        static GeoHeightField INVALID;

        bool valid() const; // 是否有效

        /**
         * 获取给定点的高程值
         * @param srs：输入点的空间参考系，如果为NULL表示与GeoHeightField的空间参考系一致        
         * @param interp：高程插值方法
         
         * @param srsWithOutputVerticalDatum
         *      Transform the output elevation value according to the vertical datum 
         *      associated with this SRS. If the SRS is NULL, assume a geodetic vertical datum
         *      relative to this object's reference ellipsoid.
          */
        bool getElevation( const CVBF_SpatialReference* inputSRS, double x, double y, ElevationInterpolation interp,
							const CVBF_SpatialReference* srsWithOutputVerticalDatum, float& out_elevation ) const;
        
		// 获取子图（一部分）
        GeoHeightField createSubSample( const CVBF_GeoExtent& destEx, ElevationInterpolation interpolation) const;

        const CVBF_GeoExtent& getExtent() const; // 获取高程图的地理空间范围

  
		// 获取最大/最小高程
        float getMinHeight() const { return _minHeight; }
        float getMaxHeight() const { return _maxHeight; }

		// 获取高程图
        const osg::HeightField* getHeightField() const;
        osg::HeightField* getHeightField();

		// 取出高程图（内部减少引用计数）
        osg::HeightField* takeHeightField();

		// 获取网格间隔
        double getXInterval() const;
        double getYInterval() const;

		// 通过分辨率排序高程图
        struct SortByResolutionFunctor
        {
            inline bool operator() (const GeoHeightField& lhs, const GeoHeightField& rhs) const
            {                
                return lhs.getXInterval() < rhs.getXInterval();                
            }
        };

    protected:
        ref_ptr<osg::HeightField> _heightField;
        CVBF_GeoExtent            _extent;
        float                    _minHeight, _maxHeight;
    };

	typedef std::vector<GeoHeightField> GeoHeightFieldVector;


}

#endif // OSGEARTH_GEODATA_H
