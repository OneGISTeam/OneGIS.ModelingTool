#ifndef _VBF_GLOBAL_DATA_PERVIEW_H_
#define _VBF_GLOBAL_DATA_PERVIEW_H_

#include <VBF_Macros.h>
#include <VBF_OS.h>

#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_3DMap/VBF_Terrain/IVBF_Map.h>

// 获取全局性（为了性能，只计算一次）的与视点相关的信息
class IVBF_GlobalDataPerView : public CVBF_Referenced
{
public:
    virtual ~IVBF_GlobalDataPerView(){}

    virtual void Update(IVBF_View* pIView)=0;

    // 获取显示分辨率的向量(米/像素)，用法为：float fPixelSize = ptWorld * GetPixelSizeVector()
    virtual const osg::Vec4& GetPixelSizeVector()=0;
    virtual double GetResolution()=0;
    virtual double GetScale(unsigned int DPI = 96)=0;

    virtual const osg::Vec3d& GetEyePtInWorld()=0;
    virtual const osg::Vec3d& GetEyePtGeo()=0;

    virtual const osg::Vec3d& GetLookatPtInWorld()=0;
    virtual const osg::Vec3d& GetLookatPtGeo()=0;

    virtual double GetEyeHeight()=0;
    virtual double GetViewDist()=0;

    virtual double GetAngleH()=0;// 获取水平视角 (即方位角，单位：角度)
    virtual double GetAngleV()=0;// 获取垂直视角 (单位：角度，水平为0，向上为-90，向下为90)
};


VBF_MAPAUX_EXPORT IVBF_GlobalDataPerView* VBF_Get3DGlobalData(IVBF_View* pIView);
VBF_MAPAUX_EXPORT void VBF_SetActiveMapNode(IVBF_View* pIView,osg::IVBF_SGNode* pINodeMap);
VBF_MAPAUX_EXPORT osg::IVBF_SGNode* VBF_GetActiveMapNode(IVBF_View* pIView);
VBF_MAPAUX_EXPORT IVBF_Map* VBF_GetActiveMap(IVBF_View* pIView);


#endif

