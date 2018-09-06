//*******************************************************************
// FileName��IVBF_MarkModelGraphics.h
// Function�������Զ���ͼ�εľ���ʵ��ģ�ͣ�������Mesh��Raster��
// Author:   ��Ө
// Date:     2013-11-11
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_GRAPHICS_H__
#define __IVBF_MARK_MODEL_GRAPHICS_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>


class IVBF_GraphicsObserver;

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelGraphics
// �ӿ������������Զ���ͼ�εľ���ʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelGraphics : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelGraphics() {}

public:

	// ����/��ȡͼ�ε����
	virtual void SetAppearance(IVBF_GraphicsAppearance* pAppearance)=0;
	virtual IVBF_GraphicsAppearance* GetAppearance()=0;  // �ú����ض��ɹ�

	// ���/�Ƴ�ͼ�εĹ۲���
	virtual void AddObserver(IVBF_GraphicsObserver* pIObserver)=0;
	virtual void RemoveObserver(IVBF_GraphicsObserver* pIObserver)=0;

	// ��ȡ/����ͼ�εĹ۲���
	virtual int GetNumObservers()=0;
	virtual IVBF_GraphicsObserver* GetObserver(int nIndex)=0;
};


// ����۲��߿��Խ��յ��ĸ�����Ϣ
const char VBF_GRAPHICS_MESSAGE_MODEL_CHANGED[]			= "Message: Graphics Model Changed";		// ͼ�ε�ģ�͸ı���
const char VBF_GRAPHICS_MESSAGE_STATESET_CHANGED[]		= "Message: Graphics StateSet Changed";		// ͼ�ε���Ⱦ״̬�ı���
const char VBF_GRAPHICS_MESSAGE_APPEARANCE_CHANGED[]	= "Message: Graphics Appearance Changed";	// ͼ�ε���۸ı���


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_GraphicsObserver
// �ӿ���������״�۲��ߣ��Ա���Ӧ��״�仯��Ϣ
//--------------------------------------------------------------------
class IVBF_GraphicsObserver : public CVBF_Referenced
{
public:
	virtual ~IVBF_GraphicsObserver() {}

public:

	// ��Ӧ������Ϣ����Ϣ�����ݲμ�����Ķ��壨��VBF_GRAPHICS_MESSAGE_MODEL_CHANGED��
	virtual void OnGraphicsMessage(IVBF_MarkModelGraphics* pISender, const char* szMessage)=0;
};


#endif 
