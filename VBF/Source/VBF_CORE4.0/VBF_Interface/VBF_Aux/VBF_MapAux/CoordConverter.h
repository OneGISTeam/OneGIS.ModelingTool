/**************************************************************************************************
* @file CoordConverter.h
* @note 坐标转换工具
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
        *@note: 转换本地经纬坐标为世界坐标系，本地坐标采用弧度表示
        */
        //VBF_MAPAUX_EXPORT bool RadianLLH2XYZ(CRenderContext* pContext, const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

        /**
        *@note: 转换本地经纬坐标为世界坐标系，本地坐标采用角度表示
        */
        //VBF_MAPAUX_EXPORT bool DegreeLLH2XYZ(CRenderContext* pContext, const osg::Vec3d& vecLLH, osg::Vec3d& vecXYZ);

        /**
        *@note: 转换世界坐标系为本地经纬坐标，本地坐标采用弧度表示
        */
       // VBF_MAPAUX_EXPORT bool XYZ2RadianLLH(CRenderContext* pContext, const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

        /**
        *@note: 转换世界坐标系为本地经纬坐标，本地坐标采用角度表示
        */
       // VBF_MAPAUX_EXPORT bool XYZ2DegreeLLH(CRenderContext* pContext, const osg::Vec3d& vecXYZ, osg::Vec3d& vecLLH);

        /**
        *@note: 转换屏幕坐标为本地经纬坐标，本地坐标采用角度表示
        */
        VBF_MAPAUX_EXPORT bool ScreenXY2DegreeLLH(CRenderContext* pContext, float fX, float fY, osg::Vec3d& vecLLH);
        VBF_MAPAUX_EXPORT bool ScreenXY2DegreeLLH(CRenderContext* pContext, float fX, float fY, double& dLon, double& dLat, double& dHei);
		
        /**
        *@note: 转换屏幕坐标系为本地经纬坐标，本地坐标采用弧度表示
        */
        VBF_MAPAUX_EXPORT bool ScreenXY2RadiaLLH(CRenderContext* pContext, float fX, float fY, osg::Vec3d& vecLLH);
        VBF_MAPAUX_EXPORT bool ScreenXY2RadiaLLH(CRenderContext* pContext, float fX, float fY, double& dLon, double& dLat, double& dHei);

        /**
        *@note: 转换本地经纬坐标为Matrix，本地坐标采用弧度表示
        */
        //VBF_MAPAUX_EXPORT bool RadiaLLH2Matrix(CRenderContext* pContext, const osg::Vec3d& vecLLH,osg::Matrix& matrix );

        /**
        *@note: 转换本地经纬坐标为Matrix，本地坐标采用角度表示
        */
         //       VBF_MAPAUX_EXPORT bool DegreeLLH2Matrix(CRenderContext* pContext, const osg::Vec3d& vecLLH,osg::Matrix& matrix );

		/**
        *@note: 转换XYZ坐标为Matrix，本地坐标采用角度表示
        */
        //        VBF_MAPAUX_EXPORT bool XYZ2Matrix(CRenderContext* pContext, const osg::Vec3d& vecXYZ,osg::Matrix& matrix );

		/**
        *@note: 由经纬度求得实际高度,经纬采用弧度计算
        */
                VBF_MAPAUX_EXPORT bool DegreeLL2LLH(CRenderContext* pContext, osg::Vec3d& vecLLA);
		
		/**
        *@note: 由经纬度求得实际高度,经纬采用弧度计算
        */
                VBF_MAPAUX_EXPORT bool RadiaLL2LLH(CRenderContext* pContext, osg::Vec3d& vecLLA);

		/**
        *@note: 局部世界坐标转成屏幕坐标
        */
                VBF_MAPAUX_EXPORT bool ConvertLocalWorldCoordToScreen(CRenderContext* pContext, const osg::Vec3d& pos, osg::Vec2d& screenPos);

		/**
		*@note: 获得GeoDistance距离，获得地球坐标下的两点距离,输入的经纬度采用弧度
		*/
                VBF_MAPAUX_EXPORT double GetGeoDistance(CRenderContext* pContext, double dSLon, double dSLat, double dELon, double dELat);
}


#endif //COORDINATE_CONVERTER_H
