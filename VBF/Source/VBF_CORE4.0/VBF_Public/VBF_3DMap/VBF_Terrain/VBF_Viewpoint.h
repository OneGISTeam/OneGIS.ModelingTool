#ifndef OSGEARTH_VIEWPOINT
#define OSGEARTH_VIEWPOINT

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>

// �ӵ�
class OSGEARTH_EXPORT CVBF_Viewpoint
{
public:

    CVBF_Viewpoint(); // ����һ�˿յģ���Ч�ģ��ӵ�

    /**
        * @����focal_point�����㣨ָ��㣩��ʹ��map��SRS�����ָ����SRC
        * @����heading_deg������ǣ�Heading��˳ʱ�뷽�򣬵�λ��)���������ڽ������ڵ���ƽ��
        * @����pitch_deg  �������ǣ�Pitch����λ�� �����������ڽ������ڵ���ƽ��
        * @����range		  ���������ָ��㣨���㣩��ֱ�߾���
        * @����srs (��ѡ) ������ָ��㣨���㣩�Ŀռ�ο�
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

	// �Ƿ�����Ч���ӵ�
    bool isValid() const;

	// ����/��ȡ�ӵ������
    void setName( const std::string& name );
    const std::string& getName() const;

	// ����/��ȡ���ָ��ĵ�
    const osg::Vec3d& getFocalPoint() const;
    void setFocalPoint( const osg::Vec3d& point );

    double x() const;
    double& x();

    double y() const;
    double& y();

    double z() const;
    double& z();

	// ����/��ȡ�����
    double getHeading() const;
    void setHeading( double heading_deg );

	// ��ȡ���ø�����
    double getPitch() const;
    void setPitch( double pitch_deg );

	// ��ȡ/�������������ľ���
    double getRange() const;
    void setRange( double range );

	// ��ȡ�����SRS����������˵Ļ���
    const CVBF_SpatialReference* getSRS() const;

	// ���ӵ�����ת��Ϊ�ַ���
    std::string VBF_toString() const;

	// Serialize this viewpoint to a config.
    CVBF_Config getConfig() const;

    void SetValid(bool bValid){ _is_valid = bValid; }

private:
    std::string m_sName;
    osg::Vec3d _focal_point;
    double m_dAngleHeading; // ��λ����
    double m_dAnglePitch;	// ��λ����
    double _range;
    ref_ptr<const CVBF_SpatialReference> _srs;
    bool _is_valid;
};



#endif // OSGEARTH_VIEWPOINT
