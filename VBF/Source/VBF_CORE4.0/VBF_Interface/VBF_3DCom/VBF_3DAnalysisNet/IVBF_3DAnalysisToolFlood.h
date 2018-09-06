//*******************************************************************
// FileName��IVBF_3DAnalysisToolFlood.h
// Function��3D�������ߣ���û����
// Author: xahg w00024
// Date:     2016-01-14
//*******************************************************************

#ifndef __IVBF_3DANALYSIS_TOOL_FLOOD_H_
#define __IVBF_3DANALYSIS_TOOL_FLOOD_H_


#include <VBF_3DCom/VBF_3DAnalysisNet/IVBF_3DAnalysisTool.h>
#include <VBF_3DCom/VBF_3DAnalysisNet/IVBF_3DAnalysis.h>


class IVBF_3DAnalysisToolFlood: public IVBF_3DAnalysisTool
{
public:
    virtual ~IVBF_3DAnalysisToolFlood() {}

    // ����/��ȡ�������Ķ������ʽ
//    virtual void                      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
//    virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;
    /**
    *@note: ��ʼ��̬����
    */
    virtual void StartDynamicCalculate() = 0;

    /**
    *@note: ��ʼ��̬����
    */
    virtual void PauseDynamicCalculate() = 0;

    /**
    *@note: ����ˮ�͵�״̬���ص�ˮ��֮ǰ��Ч��
    */
    virtual void ResetFloodState() = 0;

    /**
    *@note: ����ÿ��ˮ��������߶�
    */
    virtual void SetDeltaHeight(double dHei) = 0;

    /**
    *@note: �����Ƿ���ʾ�߽�
    */
    virtual void SetBorderShow(bool bShow) = 0;

    /**
    *@note: ��ȡ�߽��Ƿ���ʾ
    */
    virtual bool IsShowBorder() = 0;
};

struct SFloodData
{
    osg::Vec3d maxHeiPoint;
    osg::Vec3d minHeiPoint;
    double dDeltaHei;
    double dTotalArea;
    double dFloodArea;
    double dCurrentFloodHei;

    SFloodData()
    {
        maxHeiPoint = osg::Vec3d(0.0, 0.0, -1000000.0);
        minHeiPoint = osg::Vec3d(0.0, 0.0, 1000000.0);
        dDeltaHei = 10.0;
        dTotalArea = 0.0;
        dFloodArea = 0.0;
        dCurrentFloodHei = 0.0;
    }

	// û�б���û������
	std::vector< ref_ptr<osg::Vec3dArray> > regionsNotFlood;
};

#endif // __IVBF_3DANALYSIS_TOOL_FLOOD_H_
