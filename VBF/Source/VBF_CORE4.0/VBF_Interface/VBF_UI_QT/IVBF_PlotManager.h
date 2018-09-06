/**************************************************************************************************
* @file IVBF_PlotManager.h
* @note ͼ�����ӿ�
* @author w00040
* @data 2017-9-21
**************************************************************************************************/
#ifndef IVBF_PLOT_MANAGER_H
#define IVBF_PLOT_MANAGER_H

#include <VBF_Base/VBF_Referenced.h>

#include <string>
#include <QWidget>

// ����ͼ�����ģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_PLOTMANAGER[]	= "ͼ�����ӿ�";

/**
  * @class IVBF_PlotManager
  * @brief ͼ�������ӿ�
  * @note ʵ��ͼ�����ӿ�
  * @author w00040
*/
class IVBF_PlotManager : public CVBF_Referenced
{
public:
	/**  
	  * @brief ���캯��
	*/
	IVBF_PlotManager(){};

	/**  
	  * @brief ��������
	*/
	virtual ~IVBF_PlotManager(){};

	/**  
	  * @brief ʵ����ͼ��������
	*/
	virtual void InitWidgetPlotManager(QWidget *parent) = 0;

	/**  
	  * @brief ��ȡͼ�������
	*/
	virtual void* GetWidgetPlotManager() = 0;

	/**  
	  * @brief ����ͼ�������λ��
	*/
	virtual void SetPlotManagePosition(int x, int y, int w, int h) = 0;
};

#endif