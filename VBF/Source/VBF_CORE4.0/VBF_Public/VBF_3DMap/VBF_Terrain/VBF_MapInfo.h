#ifndef OSGEARTH_MAP_INFO_H
#define OSGEARTH_MAP_INFO_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>

class CVBF_Map;


// ������ͼ����ռ��Ҫ������һЩ������Ϣ�ı����
class OSGEARTH_EXPORT CVBF_MapInfo
{
public:
    CVBF_MapInfo(const CVBF_Map* map);
    CVBF_MapInfo(const CVBF_MapInfo& rhs);
    
    virtual ~CVBF_MapInfo() {}
        
    const CVBF_Profile* getProfile()      const { return m_ipProfile.get(); }
    const CVBF_SpatialReference* getSRS() const { return m_ipProfile->getSRS(); }

    bool isGeocentric() const { return m_bIsGeocentric; }
    bool isCube()       const { return m_bIsCube; }
    bool isPlateCarre() const { return m_ipProfile->getSRS()->isPlateCarre(); }

    bool isProjectedSRS()  const { return !isGeographicSRS(); }
    bool isGeographicSRS() const { return m_ipProfile->getSRS()->isGeographic(); }

    ElevationInterpolation getElevationInterpolation() const { return m_enumEelevationInterpolationType;}

private:
    ref_ptr<const CVBF_Profile> m_ipProfile;	// 
    bool						m_bIsGeocentric;	// �Ƿ����ģ��
	bool						m_bIsCube;			// �Ƿ�������
    ElevationInterpolation		m_enumEelevationInterpolationType;	// �̲߳�ֵ���ͣ�������
};


#endif // OSGEARTH_MAP_CALLBACK_H
