/**************************************************************************************************
* @file CoordConverter.h
* @note ����ת������
* @author 
* @data 2015-7-8
**************************************************************************************************/
#ifndef COORDINATE_CONVERTER_H
#define COORDINATE_CONVERTER_H

#include <Types/Vec3d>
#include <Types/VBF_Matrix.h>
#include <VBF_Base/observer_ptr>

#include <VBF_Aux/VBF_MapAux/RenderContext.h>

#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>

#include <VBF_Common/VBF_Math/VBF_CoordConverter.h>

namespace FeUtil
{
	    /**
        *@note: ת�����ؾ�γ����Ϊ��������ϵ������������û��ȱ�ʾ
        */
        //VBF_MAPAUX_EXPORT bool RadianLLH2XYZ(CRenderContext* pContext, const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

        /**
        *@note: ת�����ؾ�γ����Ϊ��������ϵ������������ýǶȱ�ʾ
        */
        //VBF_MAPAUX_EXPORT bool DegreeLLH2XYZ(CRenderContext* pContext, const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

        /**
        *@note: ת����������ϵΪ���ؾ�γ���꣬����������û��ȱ�ʾ
        */
       // VBF_MAPAUX_EXPORT bool XYZ2RadianLLH(CRenderContext* pContext, const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

        /**
        *@note: ת����������ϵΪ���ؾ�γ���꣬����������ýǶȱ�ʾ
        */
       // VBF_MAPAUX_EXPORT bool XYZ2DegreeLLH(CRenderContext* pContext, const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

        /**
        *@note: ת����Ļ����Ϊ���ؾ�γ���꣬����������ýǶȱ�ʾ
        */
        VBF_MAPAUX_EXPORT bool ScreenXY2DegreeLLH(CRenderContext* pContext, float fX, float fY, osg::Vec3d& vecLLH);
        VBF_MAPAUX_EXPORT bool ScreenXY2DegreeLLH(CRenderContext* pContext, float fX, float fY, double& dLon, double& dLat, double& dHei);
		
        /**
        *@note: ת����Ļ����ϵΪ���ؾ�γ���꣬����������û��ȱ�ʾ
        */
        VBF_MAPAUX_EXPORT bool ScreenXY2RadiaLLH(CRenderContext* pContext, float fX, float fY, osg::Vec3d& vecLLH);
        VBF_MAPAUX_EXPORT bool ScreenXY2RadiaLLH(CRenderContext* pContext, float fX, float fY, double& dLon, double& dLat, double& dHei);

        /**
        *@note: ת�����ؾ�γ����ΪMatrix������������û��ȱ�ʾ
        */
        //VBF_MAPAUX_EXPORT bool RadiaLLH2Matrix(CRenderContext* pContext, const osg::Vec3d& vecLLH,osg::Matrix& matrix );

        /**
        *@note: ת�����ؾ�γ����ΪMatrix������������ýǶȱ�ʾ
        */
         //       VBF_MAPAUX_EXPORT bool DegreeLLH2Matrix(CRenderContext* pContext, const osg::Vec3d& vecLLH,osg::Matrix& matrix );

		/**
        *@note: ת��XYZ����ΪMatrix������������ýǶȱ�ʾ
        */
        //        VBF_MAPAUX_EXPORT bool XYZ2Matrix(CRenderContext* pContext, const osg::Vec3d& vecXYZ,osg::Matrix& matrix );

		/**
        *@note: �ɾ�γ�����ʵ�ʸ߶�,��γ���û��ȼ���
        */
                VBF_MAPAUX_EXPORT bool DegreeLL2LLH(CRenderContext* pContext, osg::Vec3d& vecLLA);
		
		/**
        *@note: �ɾ�γ�����ʵ�ʸ߶�,��γ���û��ȼ���
        */
                VBF_MAPAUX_EXPORT bool RadiaLL2LLH(CRenderContext* pContext, osg::Vec3d& vecLLA);

		/**
        *@note: �ֲ���������ת����Ļ����
        */
                VBF_MAPAUX_EXPORT bool ConvertLocalWorldCoordToScreen(CRenderContext* pContext, const osg::Vec3d& pos, osg::Vec2d& screenPos);

		/**
		*@note: ���GeoDistance���룬��õ��������µ��������,����ľ�γ�Ȳ��û���
		*/
                VBF_MAPAUX_EXPORT double GetGeoDistance(CRenderContext* pContext, double dSLon, double dSLat, double dELon, double dELat);
}


#endif //COORDINATE_CONVERTER_H
