//*******************************************************************
// FileName��IVBF_3DAnalysisToolFillCut.h
// Function��3D�������ߣ����ڷ�����
// Author: xahg w00024
// Date:     2016-01-14
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_FILLCUT_H
#define __IVBF_3DANALYSIS_TOOL_FILLCUT_H


#include <VBF_3DCom/VBF_3DAnalysis/IVBF_3DAnalysisTool.h>

class SFillCutData;

class IVBF_3DAnalysisToolFillCut: public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolFillCut() {}

    // ����/��ȡ�������Ķ������ʽ
//    virtual void                      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
//    virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;
    /**
      * @note �û����û�׼��ĸ߶�
    */
    virtual void SetReferenceHeight(double dHei) = 0;

    /**
      * @note �������ڷ��ļ������
    */
    virtual void Calculate() = 0;
};

///���ڷ�������
struct SFillCutData
{
    SFillCutData()
    {
        dFillArea = 0.0;
        dCutArea = 0.0;
        dFillVolume = 0.0;
        dCutVolune = 0.0;
        vecMaxHeiPoint = osg::Vec3d(0, 0, -100000.0);
        vecMinHeiPoint = osg::Vec3d(0, 0, 1000000.0);
        dReferenHei = 0.0;
    }

    double dFillArea;
    double dCutArea;
    double dFillVolume;
    double dCutVolune;
    osg::Vec3d vecMaxHeiPoint;
    osg::Vec3d vecMinHeiPoint;
    double dReferenHei;
};

#endif // __IVBF_3DANALYSIS_TOOL_FILLCUT_H
