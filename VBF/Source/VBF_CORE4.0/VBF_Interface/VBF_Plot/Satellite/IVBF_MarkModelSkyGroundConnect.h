//*******************************************************************
// FileName：IVBF_MarkModelSkyGroundConnect.h
// Function：实体模型：卫星与地面之间的通联
// Author:   杜莹
// Date:     2016-06-27
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SKY_GROUND_CONNECT_H__
#define __IVBF_MARK_MODEL_SKY_GROUND_CONNECT_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Satellite/VBF_3DPlotDataTypes_Satellite.h>
#include <Types/VBF_3DStyles.h>
#include <string>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelSkyGroundConnect
// 接口描述：卫星与地面之间的通联
//--------------------------------------------------------------------
class IVBF_MarkModelSkyGroundConnect : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelSkyGroundConnect() {}

    // 设置/获取起始和终止点的世界坐标
    virtual void SetWorldPos(const osg::Vec3d& vPosFrom, const osg::Vec3d& vPosTo)=0;
    virtual void GetWorldPos(osg::Vec3d& vPosFrom, osg::Vec3d& vPosTo)=0;

    // 设置/获取起始和终止半径（要求fRadiusFrom<fRadiusTo）
    virtual void SetRadius(float fRadiusFrom, float fRadiusTo)=0;
    virtual void GetRadius(float& fRadiusFrom, float& fRadiusTo)=0;

    // 设置/获取起始和终止透明度（要求fAlphaFrom<fAlphaTo）
    virtual void SetAlpha(float fAlphaFrom, float fAlphaTo)=0;
    virtual void GetAlpha(float& fAlphaFrom, float& fAlphaTo)=0;

    // 设置/获取颜色
    virtual void             SetColor(const osg::Vec4& color)=0;
    virtual const osg::Vec4& GetColor()=0;

    // 设置/获取每间隔几帧颜色变化一次（默认值为2帧）
    virtual void SetColorChangeFrames(int nFrames)=0;
    virtual int  GetColorChangeFrames()=0;
};


#endif
