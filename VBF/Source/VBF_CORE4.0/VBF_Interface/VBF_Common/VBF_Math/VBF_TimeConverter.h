#ifndef _VBF_TIME_CONVERTER_H_
#define _VBF_TIME_CONVERTER_H_

#include <VBF_Common/VBF_Math/VBF_Export.h>


const double SA_S2D = 1.0 / 86400.0; // ����ת������
const double SA_M2D = 1.0 / 1440.0;  // �ѷ�ת������
const double SA_H2D = 1.0 / 24.0;    // ��Сʱת������
const double SA_M2H = 1.0 / 60.0;    // �ѷ�ת����Сʱ
const double SA_S2H = 1.0 / 3600.0;  // ����ת����Сʱ
const double SA_S2M = 1.0 / 60.0;    // ����ת������
const double SA_D2C = 1.0 / 36525.0; // ����ת��������

// ������(JD)��һ?�����ꡢ�µ�?��?�շ������Ե��Ƶ���Ԫǰ4713��1��1�ո�������ƽ?����?�������ڣ�ÿ��??���¡�
const double SA_JD2MJD = 2400000.5; // JD��MJD֮��ı任���� MJD = JD - 2400000.5




/* ��ͬʱ��ϵͳ֮���ת��
 * ����ԭ��ʱ(TAI)��1967��ĵ�13����ʶ����������ͨ���ģ�һ��Ϊ�-133ԭ�ӻ�̬��������ϸ�ܼ���ԾǨ����9,192,631,770����������ʱ�䡣
                  TAI�Ǹ���������Ķ����һ�ֹ��ʲ���ʱ�꣬�����ʵ�λ��(SI)��
                  TAI��һ��������ʱ�꣬��1958��1��1��0ʱ0��0�������ա�ʱ���֡�����㡣ԭ��ʱ���׼ȷ��Ϊÿ�������룬������ʱ��׼ȷ����ֻΪ�����롣
 * Э������ʱ(UTC)��һ������ʱ�꣬��1972��������Ϊ��ȷ��Э������ʱ������ʱ(UT1)���ᳬ��0.9�룬
                   ����Ҫʱ�����Э������ʱ�ڼ����������롣���Э������ʱ�����ԭ��ʱ(TAI)
                   ֮����������������Ĳ��λ�ڰ���Ĺ��ʵ�����ת���������(IERS)���������ʱ�������롣
   ��̫��ʱ����һ��Դ��̫������λ�õ�ʱ���׼
   ����ʱ(UT)����������ƽʱ(GMT)�����ڵ���������Բ�Σ��������ٶ������ŵ�����̫���ľ���ı�����ֱ仯��
                   �����̫��ʱǷȱ�����ԡ���̫���յĳ���ͬʱ���ܵ�������ת����Թ�������б����Ӱ�졣
                   Ϊ��Ҫ���������Ĳ������ԣ�����ѧ�Ҽ�������Բ�ι켣�뼫����б����̫��ʱ��ЧӦ��
                   ƽ̫��ʱ����ָ���޶������̫��ʱ��
                   �ڸ��������������ϵ�ƽ̫��ʱ��Ϊ����ʱ(UT0)���ֽи�������ƽʱ(GMT)��

   �������α�׼ʱ�䣨GMT������ָλ�ڸ�����������̨�ı�׼ʱ�䣬��Ϊ���������߱�������ͨ������ľ��ߡ�

 *		-MST Means Sidereal Time
 *		-GMST Mean sun time of Greenwich
 *		-GAST True sun time of Greenwich
 *		-TDT Terrestrial Dynamic Time
 *		-TDB Barycentric Dynamic Time
 * ������(JD)��һ�ֲ����ꡢ�µĳ��ڼ��շ������Ե��Ƶ���Ԫǰ4713��1��1�ո�������ƽʱ����Ϊ�������ڣ�ÿ��˳�����¡�
 * Լ��������(MJD)��MJD = JD - 2400000.5

 */


class VBF_MATH_EXPORT CVF_TimeConverter
{
public:

	static double convertTDTtoTAI(double TDT);
	static double convertTAItoTDT(double TAI);

	static double convertUTCtoTAI(double MUTC);
	static double convertTAItoUTC(double MTAI);

//	static double convertUT1toTDT(double MUT1);
//	static double convertTDTtoUT1(double MTDT);

//	static double convertUT1toUTC(double MUT1);
//	static double convertUTCtoUT1(double MUTC);

	static double convertTDTtoTDB(double MTDT);
	static double convertUT1toGMST(double MUT1);


    // MJD��Լ�������գ���JD�������գ�֮��ı任
	static double convertJDtoMJD(double JD);
	static double convertMJDtoJD(double MJD);


    // ���ݸ��������ں�ʱ�䣬ת��ΪJD�������գ�
	static double convertDTtoJD(int year, int month, int day,
			int hour, int minute, double second);

    // ���ݸ�����JD�������գ���ת��Ϊ���ں�ʱ��
	static void convertJDtoDT(double JD, int &year, int &month, int &day,
			int &hour, int &minute, double &second);

    // Convert datetime to MTDT directly
//    static double convertDTtoMTDT(int year, int month, int day, int hour, int minute, double second);
    // Convert UTC to MTDT directly
//    static double convertUTCtoMTDT(double UTC);
    static double deltaUTCtoTAI(double MUTC);
};

#endif
