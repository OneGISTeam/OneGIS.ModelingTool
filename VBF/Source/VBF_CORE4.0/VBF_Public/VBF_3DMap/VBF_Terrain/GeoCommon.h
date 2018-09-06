#ifndef VBF_EARTH_GEODATA_H
#define VBF_EARTH_GEODATA_H 1

namespace osgEarth
{
	#define NO_DATA_VALUE -FLT_MAX

	// ��������������ֵ������
    enum GeoInterpolation
    {
        GEOINTERP_GREAT_CIRCLE,	// ��Բ��
        GEOINTERP_RHUMB_LINE    // �ȽǺ���
    };

    // �̲߳�ֵ������ͨ����ͬλ�õĶ�����ֵ��
    enum ElevationInterpolation
    {
        INTERP_AVERAGE,		// ��ֵ
        INTERP_NEAREST,		// �����ֵ
        INTERP_BILINEAR,	// ˫����
        INTERP_TRIANGULATE	// ���ǲ�ֵ
    };

	// �̲߳������ԣ�ͨ��ͬһλ�õĶ����ֵͬ��ֵ��
    enum ElevationSamplePolicy
    {
        SAMPLE_FIRST_VALID,	// ��һ����Чֵ
        SAMPLE_HIGHEST,		// ���߳�
        SAMPLE_LOWEST,		// ��С�߳�
        SAMPLE_AVERAGE		// ƽ���߳�
    };


	// �߶�ģʽ����ν���Z�����ֵ��
    enum AltitudeMode
    {
        ALTMODE_ABSOLUTE,  // Z ֵ�Ǿ��Ը߶ȣ���MSL/HAE���㣩
        ALTMODE_RELATIVE   // Z ֵ����Ը߶ȣ��ӵر����㣩
    };
}

#endif // VBF_EARTH_GEODATA_H
