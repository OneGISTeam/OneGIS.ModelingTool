//***************************************************************************************
// FileName： VBF_3DMotionControl.h
// Function： 运动模拟中运动控制
// Author:    w00024
// Date:      2016-05-28
//***************************************************************************************

#ifndef __IVBF_3D_MOTION_CONTROL_H_
#define __IVBF_3D_MOTION_CONTROL_H_

#include <Types/Vec3d>
#include <Types/Vec4d>
#include <string>
#include <vector>

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/AnimationPath.h>

namespace FeMotion
{
    struct CModelProperty
    {
        std::string strName;
        std::string strIcon;
        std::string strDescription;
    };
}

class IVBF_3DMotionControl : public CVBF_Referenced
{
public:
    virtual ~IVBF_3DMotionControl() {}

public:
    /**
    * @brief 获取组装的模型
    */
    virtual void GetModelInfo(std::vector<FeMotion::CModelProperty> &vecModelInfo) = 0;

    /**
    * @brief 对当前航线添加鼠标绘制操作
    */
    virtual bool ActivateEventHandler(bool flag = true) = 0;

    virtual bool IsActivateEventHandler() = 0;

    /**
    * @brief 设置水平竖直编辑模式
    */
    virtual void SetHorizontalDragMode(bool flag) = 0;

    /**
    * @brief 获取水平是否可编辑
    */
    virtual bool IsHorizontalDragMode() = 0;

    /**
    * @brief 设置是否关键点是否可编辑
    */
    virtual void SetEditPickEnabled(bool bEdit) = 0;

    /**
    * @brief 获取是否可编辑
    */
    virtual bool IsEditPickEnabled() = 0;

    /**
    * @note 显示编辑节点
    */
    virtual void SetEditPointsVisible(bool bEdit) = 0;

    /**
    * @note 去除编辑节点
    */
    virtual bool IsEditPointsVisible() = 0;

    /**
    * @note 显示运动路径
    */
    virtual void SetMotionPathVisible(bool bEdit) = 0;

    /**
    * @note 运动路径是否显示
    */
    virtual bool IsMotionPathVisible() = 0;

    /**
    * @brief 获取拾取点
    */
    virtual osg::Vec3d GetPickPoint() = 0;

    /**
    * @brief 修改拾取点
    */
    virtual bool ChangedPickPoint(const osg::Vec3d& point) = 0;

    /**
    * @brief 插入拾取点之前
    */
    virtual bool InsertFrontPickPoint(const osg::Vec3d& point)= 0;

    /**
    * @brief 删除拾取点
    */
    virtual bool DeletePickPoint() = 0;

    /**
    * @brief 插值处理
    */
    virtual void InterpolationHandle(osg::Vec4d interParas) = 0;

    /**
    * @brief 取消插值
    */
    virtual void UnInterpolationHandle() = 0;

    /**
    * @brief 是否已经插值
    */
    virtual bool IsInterpolationHandle() = 0;

    /**
    * @brief 设置运动速度
    */
    virtual void SetMotionSpeed(double speed) = 0;

    virtual double GetMotionSpeed() = 0;

    /**
    * @brief 设置运动名称
    */
    virtual void SetMotionNodeName(const std::string& strName) = 0;

    /**
    * @brief 运动重置
    */
    virtual void Reset() = 0;

    /**
    * @brief 开始运动
    */
    virtual bool Start() = 0;

    /**
    * @brief 暂停/继续
    */
    virtual void SetPause(bool flag) = 0;

    /**
    * @brief 是否暂停
    */
    virtual bool IsPause() = 0;


    /**
    * @brief 保存当前路径到文件strFile
    */
    virtual bool SavePath(const std::string &strFile) = 0;

    /**
    * @brief 加载文件strFile到新的路径
    */
    virtual bool LoadPath(const std::string &strFile) = 0;

    virtual void Locate() = 0;

	virtual bool SaveAsAnimPath(osg::AnimationPath *pAnimPath) = 0;
};

#endif
