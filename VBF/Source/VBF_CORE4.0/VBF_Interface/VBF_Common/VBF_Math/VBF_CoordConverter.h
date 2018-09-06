#ifndef _VBF_COORD_CONVERTER_H_
#define _VBF_COORD_CONVERTER_H_

#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/Vec3d>
#include <Types/VBF_Matrix.h>


/**
*@note: ����������ĳ�����뾶����������ת���ļ���
*/
VBF_MATH_EXPORT void ResetEllipRadius(double radiusEquator, double radiusPolar);

/**
*@note: ת�����ؾ�γ����Ϊ��������ϵ������������û��ȱ�ʾ
*/
VBF_MATH_EXPORT void RadianLLH2XYZ(const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

/**
*@note: ת�����ؾ�γ����Ϊ��������ϵ������������ýǶȱ�ʾ
*/
VBF_MATH_EXPORT void DegreeLLH2XYZ(const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

/**
*@note: ת����������ϵΪ���ؾ�γ���꣬����������û��ȱ�ʾ
*/
VBF_MATH_EXPORT void XYZ2RadianLLH(const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

/**
*@note: ת����������ϵΪ���ؾ�γ���꣬����������ýǶȱ�ʾ
*/
VBF_MATH_EXPORT void XYZ2DegreeLLH(const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

/**
*@note: ת�����ؾ�γ����ΪMatrix������������û��ȱ�ʾ
*/
VBF_MATH_EXPORT void RadiaLLH2Matrix(const osg::Vec3d& vecLLH,osg::Matrix& matrix );

/**
*@note: ת�����ؾ�γ����ΪMatrix������������ýǶȱ�ʾ
*/
VBF_MATH_EXPORT void DegreeLLH2Matrix(const osg::Vec3d& vecLLH,osg::Matrix& matrix );

/**
*@note: �ɾ�γ�����ʵ�ʸ߶�,��γ���û��ȼ���
*/
VBF_MATH_EXPORT void DegreeLL2LLH(osg::Vec3d& vecLLA);
		
/**
*@note: �ɾ�γ�����ʵ�ʸ߶�,��γ���û��ȼ���
*/
//VBF_MATH_EXPORT void RadiaLL2LLH(osg::Vec3d& vecLLA);

/**
*@note: �ֲ���������ת����Ļ����
*/
//VBF_MATH_EXPORT void ConvertLocalWorldCoordToScreen(const osg::Vec3d& pos, osg::Vec2d& screenPos);

/**
*@note: ���GeoDistance���룬��õ��������µ��������,����ľ�γ�Ȳ��û���
*/
//VBF_MATH_EXPORT double GetGeoDistance(double dSLon, double dSLat, double dELon, double dELat);

#endif
