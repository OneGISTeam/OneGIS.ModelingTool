//***************************************************************************************
// FileName： VBF_3DContourSet.h
// Function： 运动模拟中运动物体，运动路线
// Author:    w00024
// Date:      2016-05-28
//***************************************************************************************

#ifndef __IVBF_3D_CONTOUR_SET_H_
#define __IVBF_3D_CONTOUR_SET_H_

#include <vector>
#include <string>
#include <Types/Vec3d>

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DCONTOURMAP[]	= "晕眩图";

class IVBF_3DContourSet
{
public:
    virtual ~IVBF_3DContourSet() {}

public:
    virtual void SetVisible(bool bVisible) = 0;
    virtual void GetProjectNames(std::vector<std::string> &strOut) = 0;
    virtual void GetCurrentProjectName(std::string &strName) = 0;
    virtual void SetCurrentProject(const std::string strName) = 0;
    virtual void SetOpacity(double val) = 0;
    virtual void GetColorArray(std::vector<osg::Vec3d> &vecColor) = 0;
    virtual void SetColor(int num, const osg::Vec3d &color) = 0;
    virtual void SaveProject() = 0;
    virtual void ResetProject() = 0;
    virtual void NewProject(const std::string &strName) = 0;
    virtual void DeleteProject(std::string &outFilePath) = 0;
};

#endif
