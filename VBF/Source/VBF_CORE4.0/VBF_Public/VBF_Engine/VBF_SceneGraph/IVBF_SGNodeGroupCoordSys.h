#ifndef IVBF_SG_NODE_GROUP_COORD_SYS_H
#define IVBF_SG_NODE_GROUP_COORD_SYS_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

namespace osg {

const double WGS_84_RADIUS_EQUATOR = 6378137.0;
const double WGS_84_RADIUS_POLAR = 6356752.3142;

// EllipsoidModel封装了用于天体建模的椭球体，如太阳、行星、月亮等，默认是地球。所有的距离单位为米，角度单位为弧度 
class EllipsoidModel : public CVBF_Object
{
    public:

        // WGS_84是描述地球椭球的常用的坐标系
        EllipsoidModel(double radiusEquator = WGS_84_RADIUS_EQUATOR, double radiusPolar = WGS_84_RADIUS_POLAR):
                         _radiusEquator(radiusEquator),
                         _radiusPolar(radiusPolar) 
		{ 
			computeCoefficients(); 
		}

        EllipsoidModel(const EllipsoidModel& et,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            CVBF_Object(et,copyop),
            _radiusEquator(et._radiusEquator),
            _radiusPolar(et._radiusPolar) { computeCoefficients(); }

        META_Object(osg,EllipsoidModel);

        void setRadiusEquator(double radius) { _radiusEquator = radius; computeCoefficients(); }
        double getRadiusEquator() const { return _radiusEquator; }

        void setRadiusPolar(double radius) { _radiusPolar = radius; computeCoefficients(); }
        double getRadiusPolar() const { return _radiusPolar; }

        virtual void convertLatLongHeightToXYZ(double B, double L, double height,
                                              double& X, double& Y, double& Z) const;

        virtual void convertXYZToLatLongHeight(double X, double Y, double Z,
                                              double& B, double& L, double& height) const;

        virtual void computeLocalToWorldTransformFromLatLongHeight(double B, double L, double height, osg::Matrixd& localToWorld) const;

        virtual void computeLocalToWorldTransformFromXYZ(double X, double Y, double Z, osg::Matrixd& localToWorld) const;

        virtual void computeCoordinateFrame(double B, double L, osg::Matrixd& localToWorld) const;

        virtual osg::Vec3d computeLocalUpVector(double X, double Y, double Z) const;

        // 判断该椭球模型是不是WGS84椭球
        virtual bool isWGS84() const {return(_radiusEquator == WGS_84_RADIUS_EQUATOR && _radiusPolar == WGS_84_RADIUS_POLAR);}

        // 比较两个椭球模型是否相等，仅比较关键的变量
        friend bool operator == ( const EllipsoidModel & e1, const EllipsoidModel& e2) {return(e1._radiusEquator == e2._radiusEquator && e1._radiusPolar == e2._radiusPolar);}


        virtual osg::Vec3d ConvertLatLongHeightToXYZ(const osg::Vec3d& vGeo) const;

    protected:

        void computeCoefficients()
        {
            double flattening = (_radiusEquator-_radiusPolar)/_radiusEquator;
            _eccentricitySquared = 2*flattening - flattening*flattening;
        }

        double _radiusEquator;
        double _radiusPolar;
        double _eccentricitySquared;

};

// 坐标系统节点：使子节点关联一个坐标系统，通常的坐标系统有WKT、PROJ4、USGS。
class IVBF_SGNodeGroupCoordSys : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupCoordSys(){}
	IVBF_SGNodeGroupCoordSys(const IVBF_SGNodeGroupCoordSys& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupCoordSys(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

	/** Set the coordinate system format string. Typical values would be WKT, PROJ4, USGS etc.*/
	virtual void setFormat(const std::string& format)=0;
	virtual const std::string& getFormat() const=0;

	/** Set the CoordinateSystem reference string, should be stored in a form consistent with the Format.*/
	virtual void setCoordinateSystem(const std::string& cs)=0;
	virtual const std::string& getCoordinateSystem() const =0;


	/** Set EllipsoidModel to describe the model used to map lat, long and height into geocentric XYZ and back. */
	virtual void setEllipsoidModel(EllipsoidModel* ellipsode) =0;
	virtual EllipsoidModel* getEllipsoidModel() =0;
	virtual const EllipsoidModel* getEllipsoidModel() const =0;

};


OSG_EXPORT IVBF_SGNodeGroupCoordSys* VBF_CreateSGNodeGroupCoordSys() ;
OSG_EXPORT IVBF_SGNodeGroupCoordSys* VBF_CreateSGNodeGroupCoordSys(const IVBF_SGNodeGroupCoordSys& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// implement inline methods.
//
inline void EllipsoidModel::convertLatLongHeightToXYZ(double B, double L, double height,
                                      double& X, double& Y, double& Z) const
{
    // for details on maths see http://www.colorado.edu/geography/gcraft/notes/datum/gif/llhxyz.gif
    double sinB = sin(B);
    double cosB = cos(B);
    double N = _radiusEquator / sqrt( 1.0 - _eccentricitySquared*sinB*sinB);

    double dNHcosB = (N+height)*cosB;
    X = dNHcosB*cos(L);
    Y = dNHcosB*sin(L);
    Z = (N*(1-_eccentricitySquared)+height)*sinB;
}

inline osg::Vec3d EllipsoidModel::ConvertLatLongHeightToXYZ(const osg::Vec3d& vGeo) const
{
    double sinB = sin(vGeo.y());
    double cosB = cos(vGeo.y());
    double N = _radiusEquator / sqrt( 1.0 - _eccentricitySquared*sinB*sinB);

    double dNHcosB = (N+vGeo.z())*cosB;
    double X = dNHcosB*cos(vGeo.x());
    double Y = dNHcosB*sin(vGeo.x());
    double Z = (N*(1-_eccentricitySquared)+vGeo.z())*sinB;
    return osg::Vec3d(X,Y,Z);
}
inline void EllipsoidModel::convertXYZToLatLongHeight(double X, double Y, double Z,
                                      double& B, double& L, double& height) const
{
    // http://www.colorado.edu/geography/gcraft/notes/datum/gif/xyzllh.gif
    double p = sqrt(X*X + Y*Y);
    double theta = atan2(Z*_radiusEquator , (p*_radiusPolar));
    double eDashSquared = (_radiusEquator*_radiusEquator - _radiusPolar*_radiusPolar)/
                          (_radiusPolar*_radiusPolar);

    double sin_theta = sin(theta);
    double cos_theta = cos(theta);

    B = atan( (Z + eDashSquared*_radiusPolar*sin_theta*sin_theta*sin_theta) /
                     (p - _eccentricitySquared*_radiusEquator*cos_theta*cos_theta*cos_theta) );
    L = atan2(Y,X);

    double sinB = sin(B);
    double N = _radiusEquator / sqrt( 1.0 - _eccentricitySquared*sinB*sinB);

    height = p/cos(B) - N;
}

inline void EllipsoidModel::computeLocalToWorldTransformFromLatLongHeight(double B, double L, double height, osg::Matrixd& localToWorld) const
{
    double X, Y, Z;
    convertLatLongHeightToXYZ(B,L,height,X,Y,Z);

    localToWorld.makeTranslate(X,Y,Z);
    computeCoordinateFrame(B, L, localToWorld);
}

inline void EllipsoidModel::computeLocalToWorldTransformFromXYZ(double X, double Y, double Z, osg::Matrixd& localToWorld) const
{
    double  B, L, height;
    convertXYZToLatLongHeight(X,Y,Z,B,L,height);

    localToWorld.makeTranslate(X,Y,Z);
    computeCoordinateFrame(B, L, localToWorld);
}

inline void EllipsoidModel::computeCoordinateFrame(double B, double L, osg::Matrixd& localToWorld) const
{
    osg::Vec3d up( cos(L)*cos(B), sin(L)*cos(B), sin(B));// Compute up vector
    osg::Vec3d east (-sin(L), cos(L), 0);// Compute east vector
    osg::Vec3d north = up ^ east;// Compute north vector = outer product up x east

    // set matrix
    localToWorld(0,0) = east[0];
    localToWorld(0,1) = east[1];
    localToWorld(0,2) = east[2];

    localToWorld(1,0) = north[0];
    localToWorld(1,1) = north[1];
    localToWorld(1,2) = north[2];

    localToWorld(2,0) = up[0];
    localToWorld(2,1) = up[1];
    localToWorld(2,2) = up[2];
}

inline osg::Vec3d EllipsoidModel::computeLocalUpVector(double X, double Y, double Z) const
{
    // Note B is angle between normal to ellipsoid surface and XY-plane
    double  B;
    double  L;
    double  altitude;
    convertXYZToLatLongHeight(X,Y,Z,B,L,altitude);

    // Compute up vector
    return osg::Vec3d(  cos(L) * cos(B),sin(L) * cos(B),sin(B));
}

}
#endif
