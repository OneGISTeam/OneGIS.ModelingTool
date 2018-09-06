// ����GPL��������ռ�ʵ��λ��

#ifndef __VBF_DE405_H__
#define __VBF_DE405_H__


#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/VBF_Matrix.h>

// J2000 ����ϵ�����������������ϵת��������ϵ���壬X ��ָ������Z��Ϊ�������淨�����ַ���
VBF_MATH_EXPORT osg::Matrixd VBF_J2000toEarthMoon(double Mjd);

#endif
