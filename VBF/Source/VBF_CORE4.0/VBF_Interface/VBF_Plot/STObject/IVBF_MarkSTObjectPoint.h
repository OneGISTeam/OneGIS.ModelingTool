//*******************************************************************
// FileName��IVBF_MarkSTObjectPoint.h
// Function����״ʱ�ն���ģ�ͽӿ�
// Author:
// Date:     2017-12-26
//*******************************************************************

#ifndef __IVBF_MARK_STOBJECT_POINT_H__
#define __IVBF_MARK_STOBJECT_POINT_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/STObject/VBF_3DPlotDataTypes_STObject.h>

// ������ϢID��
const char VBF_MESSAGE_STOBJECT_SELECTED[] = "Message: STObject Selected";


class CVBF_STObject;
//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkSTObjectPoint
// �ӿ���������״ʱ�ն���
//--------------------------------------------------------------------
class IVBF_MarkSTObjectPoint : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkSTObjectPoint() {}
    virtual void Init(CVBF_STObject* pSTObject)=0;
    virtual CVBF_STObject* GetSTObject()=0;
    virtual void SetDataPath(const std::string& strDataPath)=0;
    virtual void EnableShowAttr(bool bEnable)=0;
};


#endif 
