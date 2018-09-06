#ifndef __IVBF_3DMAP_H__
#define __IVBF_3DMAP_H__


#include <VBF_MainCtrl/IVBF_PropertySet.h>
#include <VBF_3DMap/VBF_EarthUtil/VBF_ColorFilterRGB.h>
#include <VBF_3DMap/VBF_EarthUtil/VBF_ColorFilterHSL.h>
#include <VBF_3DMap/VBF_Terrain/IVBF_Map.h>


// ����������ID��
const char VBF_COMPONENT_3DMAP[]	= "Component: 3DMap";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DMAP[]	= "��ά��ͼ";

// ��������ID��
const char VBF_COMMAND_SHOWDIALOG_FILTERRGB[]       = "Command: Show Dialog FilterRGB";     // ��ʾ��ͼ��ɫ�Ի���RGBģʽ
const char VBF_COMMAND_SHOWDIALOG_FILTERHSL[]       = "Command: Show Dialog FilterHSL";     // ��ʾ��ͼ��ɫ�Ի���HSLģʽ
const char VBF_COMMAND_SHOWDIALOG_LAYERCONTROL[]    = "Command: Show Dialog LayerControl";  // ��ʾ��ͼͼ����ƶԻ���
const char VBF_COMMAND_SHOWDIALOG_NATUREOPTIONS[]   = "Command: Show Dialog NatureOptions"; // ��ʾ��Ȼ����ѡ��Ի���
const char VBF_COMMAND_SHOWDIALOG_TIMER[]   = "Command: Show Dialog Set Time"; // ��ʾ����ʱ��Ի���
const char VBF_COMMAND_SHOWDIALOG_MAP_ADDIMAGELAYER[]    = "Command: Show Dialog Map AddImageLayer";  // ��ʾ���Ӱ��ͼ��Ի���


//-------------------------------------------------------------------
// ����ӿڣ�IVBF_3DMap
// �ӿ���������ά��ͼ����Ľӿ�
//-------------------------------------------------------------------
class IVBF_3DMap
{
public:	
	virtual ~IVBF_3DMap() {}
};

#endif 
