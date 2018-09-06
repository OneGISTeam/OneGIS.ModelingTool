#ifndef __IVBF_MARK_INPUTHANDLER_H__
#define __IVBF_MARK_INPUTHANDLER_H__


#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
class IVBF_3DPlot;

class IVBF_MarkInputHandler : public osgGA::GUIEventHandler
{
public:
    virtual ~IVBF_MarkInputHandler() {}
public:
    // ��ȡ����
	virtual unsigned int GetType()=0;

    virtual unsigned int GetMarkType()=0;
    virtual std::string  GetMarkCode()=0;

    // ��Ӧ�˻�������Ϣ
    virtual bool Initilize( IVBF_3DPlot* pI3DPlot )=0;
    virtual std::string GetMarkUUID()=0;
};


#endif 
