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

	// ��������ο�3D�㣬����ֵ��SRS���
    class OSGEARTH_EXPORT GeoPoint
    {
    public:
        GeoPoint( const CVBF_SpatialReference* srs, double x, double y, double z, const AltitudeMode& mode );
        GeoPoint( const CVBF_SpatialReference* srs, double x, double y );// ZΪ0����Ը߶ȣ����ڵ��α�����
        GeoPoint( const CVBF_SpatialReference* srs, const osg::Vec3d& xyz, const AltitudeMode& mode );
        GeoPoint( const CVBF_SpatialReference* srs, const GeoPoint& rhs );// ���Ѵ��ڵĵ�ת������ο�

        GeoPoint();//��Ч�ĵ�
        GeoPoint(const GeoPoint& rhs);// ��������
        GeoPoint( const CVBF_Config& conf, const CVBF_SpatialReference* srs =0L );// ���л�����

        virtual ~GeoPoint() { }

		// ����SRS������
        void set( const CVBF_SpatialReference* srs, const osg::Vec3d& xyz, const AltitudeMode& mode );
        void set( const CVBF_SpatialReference* srs, double x, double y, double z, const AltitudeMode& mode );

		// ��ȡ������
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

		// ת������һ��SRS�ĵ�
        GeoPoint transform(const CVBF_SpatialReference* outSRS) const;
        bool transform(const CVBF_SpatialReference* outSRS, GeoPoint& output) const;


		// ת��Z���꣨��ص���أ�
        bool transformZ(const AltitudeMode& altMode, const IVBF_TerrainHeightProvider* t );

        // ת��Z���꣨��ص���أ���������ת�����Zֵ
        bool transformZ(const AltitudeMode& altMode, const IVBF_TerrainHeightProvider* t, double& out_z) const;

		// ת��Z����Ϊ���Ը߶�
        bool makeAbsolute(const IVBF_TerrainHeightProvider* t) { return transformZ(ALTMODE_ABSOLUTE, t); }

		// ת��Z����Ϊ��Ը߶�
        bool makeRelative(const IVBF_TerrainHeightProvider* t) { return transformZ(ALTMODE_RELATIVE, t); }

		// ת��Ϊ�������꣨lat/long������ص���أ�
        bool makeGeographic();

   		// ����õ��Ӧ���������꣬�������ALTMODE_RELATIVE���򷵻�false����Ϊ�޷����Z���꣬����ʹ������ĺ����ӵ��λ�ȡ�߳�
        bool toWorld( osg::Vec3d& out_world ) const;
        bool toWorld( osg::Vec3d& out_world, const IVBF_TerrainHeightProvider* terrain ) const;

		// ����������ת���������
        bool fromWorld(const CVBF_SpatialReference* srs, const osg::Vec3d& world);

		// �ֲ�������ı仯����
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


	// ��GeoPoint�Ͱ뾶���ɵ�Բ
	class OSGEARTH_EXPORT GeoCircle
	{
	public:
		GeoCircle();
		GeoCircle(const GeoCircle& rhs);
		GeoCircle( const GeoPoint& center, double radius );

		virtual ~GeoCircle() { }

		// ��ȡ/����Բ�����ĵ�
		const GeoPoint& getCenter() const { return _center; }
		void setCenter( const GeoPoint& value ) { _center = value; }

		// ��ȡ/����Բ�İ뾶��ʹ�õ�ͼ�ĳ��ȵ�λ���Ե���SRS���ף�
		double getRadius() const { return _radius; }
		void setRadius( double value ) { _radius = value; }

		// ���ĵ������ο�ϵͳ
		const CVBF_SpatialReference* getSRS() const { return _center.getSRS(); }

		bool operator == ( const GeoCircle& rhs ) const;
		bool operator != ( const GeoCircle& rhs ) const { return !operator==(rhs); }

		// �Ƿ���Ч
		bool isValid() const { return _center.isValid() && _radius > 0.0; }

		// ת������һ������ο�ϵͳ
		GeoCircle transform( const CVBF_SpatialReference* srs ) const;
		bool transform( const CVBF_SpatialReference* srs, GeoCircle& out_circle ) const;

		// �ཻ�ж�
		bool intersects( const GeoCircle& rhs ) const;

	public:
		static GeoCircle INVALID;

	protected:
		GeoPoint _center;
		double   _radius;
	};


	 // һ�������ĵ���ռ䷶Χ��A bounding box that is aligned with a spatial reference's coordinate system.
    class OSGEARTH_EXPORT CVBF_GeoExtent
    {
	public:
		CVBF_GeoExtent(); 
		CVBF_GeoExtent( const CVBF_SpatialReference* srs, double west, double south, double east, double north );

        CVBF_GeoExtent( const CVBF_SpatialReference* srs );// ��Ч�ģ���ͨ��expandToInclude����
        CVBF_GeoExtent( const CVBF_GeoExtent& rhs );
        CVBF_GeoExtent( const CVBF_SpatialReference* srs, const Bounds& bounds );

        virtual ~CVBF_GeoExtent() { }

        bool operator == ( const CVBF_GeoExtent& rhs ) const;
        bool operator != ( const CVBF_GeoExtent& rhs ) const;

 		// ��ȡ�ռ�ο�ϵͳ
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

		// ��ȡ���ĵ�
        bool getCentroid( double& out_x, double& out_y ) const;
        osg::Vec3d getCentroid() const { osg::Vec3d r; getCentroid(r.x(), r.y()); return r; }

		// �Ƿ��Խ180�Ⱦ���
        bool crossesAntimeridian() const;

		// ��ȡ��Χ
        void getBounds(double &xmin, double &ymin, double &xmax, double &ymax) const;

 		// ���������һ��ʵ�ʵġ����Ϊ������Ч��Χ�򷵻�true
        bool isValid() const;
        bool defined() const { return isValid(); }
        bool isInvalid() const { return !isValid(); }

		// �����180���ߣ���180���߷ָ�Ϊ������Χ��������true�����򷵻�false
        bool splitAcrossAntimeridian( CVBF_GeoExtent& first, CVBF_GeoExtent& second ) const;

		// ת������һ������ο�ϵͳ��ע�⣺Ŀ��SRS���ܲ��ʺ�ת�������磬��һ������ȫ���WGS84��Χת����ī����ͶӰ��
		// ����CVBF_Profile:clampAndTransformExtent()�滻
        CVBF_GeoExtent transform( const CVBF_SpatialReference* to_srs ) const;
        bool transform( const CVBF_SpatialReference* to_srs, CVBF_GeoExtent& output ) const;

		// �Ƿ�����㣨x��y�����������ο�Ϊsrs�����ߺͱ�����һ�£�srsΪNULLʱ��
        bool contains(double x, double y, const CVBF_SpatialReference* srs =0L) const;
        bool contains(const osg::Vec3d& xy, const CVBF_SpatialReference* srs =0L) const { return contains(xy.x(),xy.y(),srs); }
        bool contains( const GeoPoint& rhs ) const;
        bool contains( const CVBF_GeoExtent& rhs ) const;
        bool contains( const Bounds& rhs ) const;

		// �Ƿ�����һ������Χ�ཻ��checkSRSΪfalae��ʾ�����ǿռ�ο�ϵͳ������Ϊ�����ο�ϵͳһ�£�
        bool intersects( const CVBF_GeoExtent& rhs, bool checkSRS =true ) const;

		// ��ȡ��Χ
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

		// ��չ�÷�Χʹ�������һ����Χ
        bool expandToInclude( const CVBF_GeoExtent& rhs );
        
		// ����һ������Χ�󽻣�ʹ����ͬ��SRS��
        CVBF_GeoExtent intersectionSameSRS( const CVBF_GeoExtent& rhs ) const; 

		// ת�����ַ����������ռ�ο�ϵͳ��
        std::string VBF_toString() const;

		// ����
        void scale(double x_scale, double y_scale);

		// ��չ
        void expand( double x, double y );

		// ��ȡ���
        double area() const;

		// ��׼�����ȵ�ֵ
        void normalize();

		// ������ľ���ֵ������Ϊ�õ���Χ�ڵ�ֵ
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

	// ���е���ο���ͼ��
    class OSGEARTH_EXPORT GeoImage
    {
    public:
        GeoImage();
        GeoImage( osg::Image* image, const CVBF_GeoExtent& extent );
        virtual ~GeoImage() { }

        static GeoImage INVALID;

    public:
		// �Ƿ���Ч
        bool valid() const;

		// ��ȡͼ������
        osg::Image* getImage() const;

		// ��ȡͼ��ĵ���ռ䷶Χ
        const CVBF_GeoExtent& getExtent() const;

		// ��ȡͼ�������ο�ϵͳ
        const CVBF_SpatialReference* getSRS() const;

		// ��ͼ��ü���һ���µĵ���ռ䷶Χ
		// @param exact��true��ʾ������ķ�Χ��ȷ�ü�����Ҫ�ز��������۽ϴ�false��ʾ�򵥵Ĳü�����Χ�������Ĵ󣬵��ٶȿ�
		// @param width, height������ü����ͼ��ĳߴ�
		GeoImage crop( const CVBF_GeoExtent& extent, bool exact = false, unsigned int width = 0, 
			unsigned int height = 0, bool useBilinearInterpolation = true) const;

		// ��ͼ��任��һ���µ�����ο�ϵͳ
		// @param to_extent��ת�����ü��ķ�Χ�����ȵ���reproject()�ٵ���crop()�ٶȿ�
		//@param width, height�����ͼ��ĳߴ磬Ĭ������»��Զ�����óߴ�

		GeoImage reproject( const CVBF_SpatialReference* to_srs, const CVBF_GeoExtent* to_extent = 0,
			             unsigned int width = 0, unsigned int height = 0, bool useBilinearInterpolation = true) const;

 		// ��ͼ����������һ�����ص�͸���߽�
        GeoImage addTransparentBorder( bool leftBorder=true, bool rightBorder=true, bool bottomBorder=true, bool topBorder=true);

		// ȡ��ͼ���ڲ��������ü�����
        osg::Image* takeImage();

		// ��ȡÿ�����صĳ���
		double getUnitsPerPixel() const;

    private:
        ref_ptr<osg::Image> _image;
        CVBF_GeoExtent _extent;
    };

    typedef std::vector<GeoImage> GeoImageVector;


	// ����������ο��ĸ߳�ͼ
    class OSGEARTH_EXPORT GeoHeightField
    {
    public:
        GeoHeightField();
        GeoHeightField( osg::HeightField* heightField, const CVBF_GeoExtent&  extent );

        virtual ~GeoHeightField() { }

        static GeoHeightField INVALID;

        bool valid() const; // �Ƿ���Ч

        /**
         * ��ȡ������ĸ߳�ֵ
         * @param srs�������Ŀռ�ο�ϵ�����ΪNULL��ʾ��GeoHeightField�Ŀռ�ο�ϵһ��        
         * @param interp���̲߳�ֵ����
         
         * @param srsWithOutputVerticalDatum
         *      Transform the output elevation value according to the vertical datum 
         *      associated with this SRS. If the SRS is NULL, assume a geodetic vertical datum
         *      relative to this object's reference ellipsoid.
          */
        bool getElevation( const CVBF_SpatialReference* inputSRS, double x, double y, ElevationInterpolation interp,
							const CVBF_SpatialReference* srsWithOutputVerticalDatum, float& out_elevation ) const;
        
		// ��ȡ��ͼ��һ���֣�
        GeoHeightField createSubSample( const CVBF_GeoExtent& destEx, ElevationInterpolation interpolation) const;

        const CVBF_GeoExtent& getExtent() const; // ��ȡ�߳�ͼ�ĵ���ռ䷶Χ

  
		// ��ȡ���/��С�߳�
        float getMinHeight() const { return _minHeight; }
        float getMaxHeight() const { return _maxHeight; }

		// ��ȡ�߳�ͼ
        const osg::HeightField* getHeightField() const;
        osg::HeightField* getHeightField();

		// ȡ���߳�ͼ���ڲ��������ü�����
        osg::HeightField* takeHeightField();

		// ��ȡ������
        double getXInterval() const;
        double getYInterval() const;

		// ͨ���ֱ�������߳�ͼ
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
