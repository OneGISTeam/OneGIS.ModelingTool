//*******************************************************************
// FileName��IVBF_MarkModelFunction.h
// Function��ʵ��ģ�ͽӿڣ���������
// Author:   ��Ө
// Date:     2017-04-01
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_FUNCTION_H__
#define __IVBF_MARK_MODEL_FUNCTION_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>
#include <Types/Vec4f>
#include <vector>
#include <VBF_Plot/Common/VBF_SurfaceFunction.h>
#include <VBF_Plot/Common/VBF_ParamSurface.h>
#include <VBF_Plot/Common/VBF_ColorFunction.h>


//--------------------------------------------------------------------
// ����ö�٣�EVBF_SURFACE_STYLE
// �ӿ��������Զ�����������ʽ������������ö��ֵ�ĵ���
//--------------------------------------------------------------------
enum EVBF_SURFACE_STYLE
{
    EVBF_SURFACE_STYLE_POINT		= 0x01,		// ֻ���Ƶ�
    EVBF_SURFACE_STYLE_LINE         = 0x02,		// ֻ������
    EVBF_SURFACE_STYLE_FILL         = 0x04,		// ֻ����ʵ��
    EVBF_SURFACE_STYLE_COMPOSITE	= (EVBF_SURFACE_STYLE_FILL | EVBF_SURFACE_STYLE_LINE)	// ͬʱ����ʵ���������
};


class IVBF_MarkModelFunction : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelFunction() {}

    // �����û��Զ�������溯������ɫ�����������ɫ����ΪNULL��ϵͳ��ʹ�ñ�׼��ɫ����
    virtual void SetFunction(CVBF_SurfaceFunction* pSurfaceFunc, CVBF_ColorFunction* pColorFunc=NULL)=0;

    // �����û��Զ���Ĳ����������ɫ�����������ɫ����ΪNULL��ϵͳ��ʹ�ñ�׼��ɫ����
    virtual void SetParamSurface(CVBF_ParamSurface* pParamSurface, CVBF_ColorFunction* pColorFunc=NULL)=0;

    // ����/��ȡ���������ʽ��Ĭ��ΪEVBF_SURFACE_STYLE_COMPOSITE��
    virtual void                SetSurfaceStyle(EVBF_SURFACE_STYLE nStyle)=0;
    virtual EVBF_SURFACE_STYLE  GetSurfaceStyle()=0;

    // ����/��ȡ�����ߵ���ʽ
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;
};

#endif 
