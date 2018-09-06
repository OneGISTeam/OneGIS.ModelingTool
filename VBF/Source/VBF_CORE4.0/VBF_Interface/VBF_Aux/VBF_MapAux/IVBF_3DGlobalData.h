#ifndef _VBF_GLOBAL_DATA_PERVIEW_H_
#define _VBF_GLOBAL_DATA_PERVIEW_H_

#include <VBF_Macros.h>
#include <VBF_OS.h>

#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_3DMap/VBF_Terrain/IVBF_Map.h>

// ��ȡȫ���ԣ�Ϊ�����ܣ�ֻ����һ�Σ������ӵ���ص���Ϣ
class IVBF_GlobalDataPerView : public CVBF_Referenced
{
public:
    virtual ~IVBF_GlobalDataPerView(){}

    virtual void Update(IVBF_View* pIView)=0;

    // ��ȡ��ʾ�ֱ��ʵ�����(��/����)���÷�Ϊ��float fPixelSize = ptWorld * GetPixelSizeVector()
    virtual const osg::Vec4& GetPixelSizeVector()=0;
    virtual double GetResolution()=0;
    virtual double GetScale(unsigned int DPI = 96)=0;

    virtual const osg::Vec3d& GetEyePtInWorld()=0;
    virtual const osg::Vec3d& GetEyePtGeo()=0;

    virtual const osg::Vec3d& GetLookatPtInWorld()=0;
    virtual const osg::Vec3d& GetLookatPtGeo()=0;

    virtual double GetEyeHeight()=0;
    virtual double GetViewDist()=0;

    virtual double GetAngleH()=0;// ��ȡˮƽ�ӽ� (����λ�ǣ���λ���Ƕ�)
    virtual double GetAngleV()=0;// ��ȡ��ֱ�ӽ� (��λ���Ƕȣ�ˮƽΪ0������Ϊ-90������Ϊ90)
};


VBF_MAPAUX_EXPORT IVBF_GlobalDataPerView* VBF_Get3DGlobalData(IVBF_View* pIView);
VBF_MAPAUX_EXPORT void VBF_SetActiveMapNode(IVBF_View* pIView,osg::IVBF_SGNode* pINodeMap);
VBF_MAPAUX_EXPORT osg::IVBF_SGNode* VBF_GetActiveMapNode(IVBF_View* pIView);
VBF_MAPAUX_EXPORT IVBF_Map* VBF_GetActiveMap(IVBF_View* pIView);


#endif

