//*******************************************************************
// FileName��IVBF_MarkAttrTrail.h
// Function��ģ�����Խӿڣ�ģ�͵��˶��켣��������/�����Σ�
// Author:   ��Ө
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_H__
#define __IVBF_MARK_ATTR_TRAIL_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


// ���幤��ID��
const char VBF_TOOL_MARKATTR_QUERY_TRAILPOINT[]	 = "Tool: Query Mark Attr of Trail Point";		// ���Բ�ѯ���켣����Ϣ



//--------------------------------------------------------------------
// ����ö�٣�EVBF_TRAIL_STYLE
// �ӿ�����������켣�Ļ��Ʒ�ʽ������������ö��ֵ�ĵ���
//--------------------------------------------------------------------
enum EVBF_TRAIL_STYLE
{
    VBF_TRAIL_STYLE_POINT		= 0x01,		// ֻ���ƹ켣��
    VBF_TRAIL_STYLE_LINE		= 0x02,		// ֻ���ƹ켣��
    VBF_TRAIL_STYLE_COMPOSITE	= (VBF_TRAIL_STYLE_POINT | VBF_TRAIL_STYLE_LINE)	// ͬʱ���ƹ켣��͹켣��
};


class IVBF_MarkAttrTrail : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrTrail() {}

    // ����/��ȡ�켣�Ļ��Ʒ�ʽ
    virtual void             SetRenderStyle(EVBF_TRAIL_STYLE nStyle)=0;
    virtual EVBF_TRAIL_STYLE GetRenderStyle()=0;

    // ����/��ȡ�켣�����ʽ
    virtual void                  SetPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetPointStyle()=0;

    // ����/��ȡ�켣������Ҫ�����ĵ�������Щ���¼���ڴ��У���һ��ȫ����ʾ��
    // ע�⣺�õ�������С��SetNumPointsVisible()���������õĵ���
    virtual void SetNumPointsRetained(int num)=0;
    virtual int  GetNumPointsRetained()=0;

    // ����/��ȡ�켣���в�����Ƶĵ���
    virtual void SetNumPointsVisible(int num)=0;
    virtual int  GetNumPointsVisible()=0;

    // ����/��ȡ�켣���ѯ��Ϣ�ı������ǿɼ���Ĭ��ֵΪtrue��
    virtual void SetQueryFrameVisible(bool bVisible)=0;
    virtual bool IsQueryFrameVisible()=0;

    // ����/��ȡ�켣���ѯ��Ϣ�ı�������ʽ
    virtual void                      SetQueryFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetQueryFrameStyle()=0;

    // ����/��ȡ�켣���ѯ��Ϣ���ı���ʽ
    virtual void                 SetQueryTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetQueryTextStyle()=0;

    // �ж��Ƿ����ָ�������λ�ã��������жϹ켣�㣬���жϹ켣��/�켣����
    // ������������ظù켣��������������Ϣ
    virtual bool Contains(float x, float y, osg::Vec3d& ptWorld, std::string& strInfo)=0;

	// ��չ켣
	// ������bClearImmediately -- �Ƿ�����ɾ����ֻ����Update()�����в�����ò���Ϊtrue������ᵼ�»����̳߳���
	virtual void Clear(bool bClearImmediately=false)=0;
};


#endif 
