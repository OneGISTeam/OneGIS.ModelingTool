//*******************************************************************
// FileName��IVBF_MarkAttrTrailLine.h
// Function��ģ�����Խӿڣ�ģ�͵��˶��켣�������Σ�
// Author:   ��Ө
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_LINE_H__
#define __IVBF_MARK_ATTR_TRAIL_LINE_H__


#include <VBF_Plot/Common/IVBF_MarkAttrTrail.h>
#include <Types/VBF_3DStyles.h>


//=======================================================================
// ����ӿڣ�IVBF_MarkAttrTrailLine
// �ӿ��������켣�ߣ���������Ч�����ٶȽϿ죩
//=======================================================================
class IVBF_MarkAttrTrailLine: public IVBF_MarkAttrTrail
{
public:
	virtual ~IVBF_MarkAttrTrailLine() {}

	// ����/��ȡ�켣���Ƿ񽥱䣨Ĭ��ֵΪfalse����������ή��ϵͳ�����ٶȣ�
	virtual void EnableFade(bool bEnable)=0;
	virtual bool IsFadeEnabled()=0;

	// ����/��ȡ�켣�ߵ���ʽ
	virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};



#endif 
