#ifndef OSGEARTH_GEOID_H
#define OSGEARTH_GEOID_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoCommon.h>
#include <VBF_3DMap/VBF_Terrain/Bounds.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_Shape.h>


namespace osgEarth
{
	// ˮ׼��
    class OSGEARTH_EXPORT Geoid : public ::CVBF_Referenced
    {
    public:
        Geoid();
        virtual ~Geoid() { }

        // ����/��ȡ����
        void setName( const std::string& value );
        const std::string& getName() const { return m_sName; }

		// ����/��ȡ�߶ȳ��������Ǿ�γ�����񣨴�����"��"��ʾ��ԭ��ͼ�������߶�ֵΪ����ڲο��������
        void setHeightField( osg::HeightField* hf );
        const osg::HeightField* getHeightField() const { return _hf.get(); }

		// ��ȡ�����㣨�������꣩�ĸ߳�ƫ��
        float getHeight( double lat_deg, double lon_deg, const ElevationInterpolation& interp =INTERP_BILINEAR) const;

        const CVBF_Units& getUnits() const { return _units; } // �߳�ֵ�ĵ�λ
        void setUnits( const CVBF_Units& value );

        bool isValid() const { return _valid; } // �Ƿ���Ч

        bool isEquivalentTo( const Geoid& rhs ) const; // �ж�����Geoid�Ƿ����

    private:
        std::string    m_sName;
        CVBF_Units     _units;
        bool           _valid;
        Bounds         _bounds;

        ref_ptr<osg::HeightField> _hf;

        void validate();
    };
}

#endif
