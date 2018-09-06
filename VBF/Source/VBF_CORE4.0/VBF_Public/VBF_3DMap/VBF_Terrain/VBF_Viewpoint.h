#ifndef OSGEARTH_VIEWPOINT
#define OSGEARTH_VIEWPOINT

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>

// 视点
class OSGEARTH_EXPORT CVBF_Viewpoint
{
public:

    CVBF_Viewpoint(); // 创建一了空的（无效的）视点

    /**
        * @参数focal_point：焦点（指向点），使用map的SRS或参数指定的SRC
        * @参数heading_deg：航向角（Heading，顺时针方向，单位度)，相机相对于焦点所在的切平面
        * @参数pitch_deg  ：俯仰角（Pitch，单位度 ），相机相对于焦点所在的切平面
        * @参数range		  ：从相机到指向点（焦点）的直线距离
        * @参数srs (可选) ：定义指向点（焦点）的空间参考
        */
    CVBF_Viewpoint( const osg::Vec3d& focal_point, double heading_deg, double pitch_deg,
					double range, const CVBF_SpatialReference* srs =NULL );

    CVBF_Viewpoint( double x_or_lon, double y_or_lat, double z,double heading_deg, double pitch_deg, 
					double range, const CVBF_SpatialReference* srs =NULL );

    CVBF_Viewpoint( const std::string& name, const osg::Vec3d& focal_point,
					double heading_deg, double pitch_deg,
					double range, const CVBF_SpatialReference* srs =NULL );

    CVBF_Viewpoint( const std::string& name, double x_or_lon, double y_or_lat, double z,
					double heading_deg, double pitch_deg,
					double range, const CVBF_SpatialReference* srs =NULL );


    CVBF_Viewpoint( const CVBF_Config& conf );
    CVBF_Viewpoint( const CVBF_Viewpoint& rhs );

    virtual ~CVBF_Viewpoint();
    CVBF_Viewpoint& operator = (const CVBF_Viewpoint& rhs);

public:

	// 是否是有效的视点
    bool isValid() const;

	// 设置/获取视点的名字
    void setName( const std::string& name );
    const std::string& getName() const;

	// 设置/获取相机指向的点
    const osg::Vec3d& getFocalPoint() const;
    void setFocalPoint( const osg::Vec3d& point );

    double x() const;
    double& x();

    double y() const;
    double& y();

    double z() const;
    double& z();

	// 设置/获取航向角
    double getHeading() const;
    void setHeading( double heading_deg );

	// 获取设置俯仰角
    double getPitch() const;
    void setPitch( double pitch_deg );

	// 获取/设置相机到焦点的距离
    double getRange() const;
    void setRange( double range );

	// 获取焦点的SRS（如果定义了的话）
    const CVBF_SpatialReference* getSRS() const;

	// 把视点数据转换为字符串
    std::string VBF_toString() const;

	// Serialize this viewpoint to a config.
    CVBF_Config getConfig() const;

    void SetValid(bool bValid){ _is_valid = bValid; }

private:
    std::string m_sName;
    osg::Vec3d _focal_point;
    double m_dAngleHeading; // 单位：度
    double m_dAnglePitch;	// 单位：度
    double _range;
    ref_ptr<const CVBF_SpatialReference> _srs;
    bool _is_valid;
};



#endif // OSGEARTH_VIEWPOINT
