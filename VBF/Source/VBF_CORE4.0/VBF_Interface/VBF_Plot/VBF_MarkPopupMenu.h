//*******************************************************************
// FileName��VBF_MarkPopupMenu.h
// Function��ʵ��ģ�͵ĵ���ʽ�˵�
// Author:   ��Ө
// Date:     2015-01-30
//*******************************************************************

#ifndef __VBF_MARK_POPUP_MENU_H__
#define __VBF_MARK_POPUP_MENU_H__


// �Ҽ�����ʽ�˵������ʽ����ʾ��ͬ���͵Ĳ˵���������ʹ�ã�
#define IDM_ITEM_STYLE_COMMON						1  // ��ͨ��ʽ����������
#define IDM_ITEM_STYLE_POPUP						2  // ����ʽ������ + С�����Σ�ָʾ�е���ʽ�Ӳ˵���
#define IDM_ITEM_STYLE_SEPARATOR					3  // �ָ���
#define IDM_ITEM_STYLE_CHECK						4  // ��ѡ�� + ���֣�ͨ���Թ���ѡ��
#define IDM_ITEM_STYLE_RADIO_BEGIN					5  // ��ѡ�����ʼ����ѡ�� + ���֣�
#define IDM_ITEM_STYLE_RADIO						6  // ��ѡ��ĳ�Ա����ѡ�� + ���֣�
#define IDM_ITEM_STYLE_RADIO_END					7  // ��ѡ��Ľ�������ѡ�� + ���֣�



// �Ҽ�����ʽ�˵����ID�ţ���Ӧ��ͬ�Ĳ���
#define IDM_MARK_OPERATE_BASE						80000

#define IDM_MARK_OPERATE_DEPTHTEST					(IDM_MARK_OPERATE_BASE+1) // ��Ȳ���
#define IDM_MARK_OPERATE_DEPTHWRITE					(IDM_MARK_OPERATE_BASE+2) // ���д��

#define IDM_MARK_OPERATE_FILLMODE_SOLID				(IDM_MARK_OPERATE_BASE+3) // ���ģʽ�����
#define IDM_MARK_OPERATE_FILLMODE_WIREFRAME			(IDM_MARK_OPERATE_BASE+4) // ���ģʽ������
#define IDM_MARK_OPERATE_FILLMODE_POINT				(IDM_MARK_OPERATE_BASE+5) // ���ģʽ����
#define IDM_MARK_OPERATE_FILLMODE_SOLIDWIREFRAME	(IDM_MARK_OPERATE_BASE+6) // ���ģʽ�����+������

#define IDM_MARK_OPERATE_ASSIGNIFF					(IDM_MARK_OPERATE_BASE+10) // ָ���������Ԥ����10�����ͣ�

#define IDM_MARK_OPERATE_TAILFLAME_SHOW				(IDM_MARK_OPERATE_BASE+20) // β���Ƿ�ɼ�
#define IDM_MARK_OPERATE_TRAIL_SHOW					(IDM_MARK_OPERATE_BASE+21) // �켣���Ƿ�ɼ�
#define IDM_MARK_OPERATE_LABEL_SHOW					(IDM_MARK_OPERATE_BASE+22) // ��ע�Ƿ�ɼ�
#define IDM_MARK_OPERATE_LABEL_DETAIL				(IDM_MARK_OPERATE_BASE+23) // ��ϸ��ע�Ƿ�ɼ�
#define IDM_MARK_OPERATE_HINTLINE_SHOW				(IDM_MARK_OPERATE_BASE+24) // �߶����Ƿ�ɼ�
#define IDM_MARK_OPERATE_IFF_SHOW					(IDM_MARK_OPERATE_BASE+25) // ��������Ƿ�ɼ�
#define IDM_MARK_OPERATE_INTERSECT_SHOW				(IDM_MARK_OPERATE_BASE+26) // ����潻���Ƿ�ɼ�
#define IDM_MARK_OPERATE_TRAILSMOKE_SHOW			(IDM_MARK_OPERATE_BASE+27) // ģ�͵�β���Ƿ�ɼ�
#define IDM_MARK_OPERATE_COORDSYS_SHOW              (IDM_MARK_OPERATE_BASE+28) // ��״ģ�͵ľֲ�����ϵ�Ƿ�ɼ�

#define IDM_MARK_OPERATE_ASSIGNTASK					(IDM_MARK_OPERATE_BASE+30) // ������ս����
#define IDM_MARK_OPERATE_TASK_SHOW					(IDM_MARK_OPERATE_BASE+31) // ��ʾ��ս����
#define IDM_MARK_OPERATE_ASSIGNWAEPON				(IDM_MARK_OPERATE_BASE+32) // ��������

#define IDM_MARK_OPERATE_POWERMAP_SHOW				(IDM_MARK_OPERATE_BASE+50) // ����ͼ�Ƿ�ɼ�
#define IDM_MARK_OPERATE_POWERMAP_SOLID				(IDM_MARK_OPERATE_BASE+51) // ����ͼ���ģʽ
#define IDM_MARK_OPERATE_POWERMAP_WIREFRAME			(IDM_MARK_OPERATE_BASE+52) // ����ģʽ
#define IDM_MARK_OPERATE_POWERMAP_POINT				(IDM_MARK_OPERATE_BASE+53) // ����ͼ��ģʽ
#define IDM_MARK_OPERATE_POWERMAP_SOLIDWIREFRAME	(IDM_MARK_OPERATE_BASE+54) // ����ͼ���+������ģʽ
#define IDM_MARK_OPERATE_POWERMAP_COLOR				(IDM_MARK_OPERATE_BASE+55) // ����ͼ��ɫ����

#define IDM_MARK_OPERATE_AIRLINE_NEW				(IDM_MARK_OPERATE_BASE+70) // �½�����
#define IDM_MARK_OPERATE_AIRLINE_ASSIGN				(IDM_MARK_OPERATE_BASE+71) // ָ������
#define IDM_MARK_OPERATE_AIRLINE_SHOW_PRIMARY		(IDM_MARK_OPERATE_BASE+72) // ��ʾԭʼ����
#define IDM_MARK_OPERATE_AIRLINE_SHOW_SMOOTH		(IDM_MARK_OPERATE_BASE+73) // ��ʾ�⻬��ĺ���
#define IDM_MARK_OPERATE_AIRLINE_SHOW_PIPELINE		(IDM_MARK_OPERATE_BASE+74) // ��ʾ���չ���
#define IDM_MARK_OPERATE_AIRLINE_SHOW_HINTLINE		(IDM_MARK_OPERATE_BASE+75) // ��ʾ���߸߶�ָʾ��
#define IDM_MARK_OPERATE_AIRLINES_OUTPUT_COOR		(IDM_MARK_OPERATE_BASE+76) // �����������

// ����ģ�͵Ĳ˵�
#define IDM_MARK_OPERATE_SATELLITE_INFO				(IDM_MARK_OPERATE_BASE+80) // ��ʾ������Ϣ
#define IDM_MARK_OPERATE_SATELLITE_ORBIT			(IDM_MARK_OPERATE_BASE+81) // ��ʾ���ǹ��
#define IDM_MARK_OPERATE_SATELLITE_SPECIALPOINTS	(IDM_MARK_OPERATE_BASE+82) // ��ʾ����ϵ�����㣨����ص㡢Զ�ص㣩
#define IDM_MARK_OPERATE_SATELLITE_VERTLINE			(IDM_MARK_OPERATE_BASE+83) // ��ʾ���ǵĴ���
#define IDM_MARK_OPERATE_SATELLITE_SPHEREATTITUDE	(IDM_MARK_OPERATE_BASE+84) // ��ʾ���ǵ���̬��
#define IDM_MARK_OPERATE_SATELLITE_GROUNDTRACK		(IDM_MARK_OPERATE_BASE+85) // ��ʾ���µ�켣
#define IDM_MARK_OPERATE_SATELLITE_SENSOR			(IDM_MARK_OPERATE_BASE+86) // ��ʾ���ǵĴ�����


//---------------------------------------------------------------------
// �����ࣺCVBF_PopupMenuItem
// ���������Ҽ�����ʽ�˵��е�����
//---------------------------------------------------------------------
class CVBF_PopupMenuItem
{
public:
	unsigned int 	nStyle;		// �˵������ʽ���μ�IDM_ITEM_STYLE_COMMON�ȵĶ���
	std::string		strLabel;	// �˵�������ֱ�ǩ
	unsigned int 	nID;		// �˵����Ӧ�Ĳ������μ�IDM_MARK_OPERATE_BASE�ȵĶ���
	bool			bCheck;		// �Ƿ�ѡ����������IDM_ITEM_STYLE_CHECK��IDM_ITEM_STYLE_RADIO������ʽ��

	CVBF_PopupMenuItem()
	{
		nStyle		= IDM_ITEM_STYLE_COMMON;
		strLabel	= "";
		nID			= 0;
		bCheck		= false;
	}

	CVBF_PopupMenuItem(unsigned int nStyle0)
	{
		nStyle		= nStyle0;
		strLabel	= "";
		nID			= 0;
		bCheck		= false;
	}

	CVBF_PopupMenuItem(unsigned int nStyle0, const std::string& sLabel0)
	{
		nStyle		= nStyle0;
		strLabel	= sLabel0;
		nID			= 0;
		bCheck		= false;
	}

	CVBF_PopupMenuItem(unsigned int nStyle0, const std::string& sLabel0, unsigned int nID0, bool bCheck0)
	{
		nStyle		= nStyle0;
		strLabel	= sLabel0;
		nID			= nID0;
		bCheck		= bCheck0;
	}

	CVBF_PopupMenuItem& operator=(const CVBF_PopupMenuItem& src)
	{
		if(this==&src) return *this;

		nStyle		= src.nStyle;
		strLabel	= src.strLabel;
		nID			= src.nID;
		bCheck		= src.bCheck;

		return *this;
	}

	bool operator==(const CVBF_PopupMenuItem& src)
	{
		return (nStyle==src.nStyle && strLabel==src.strLabel && nID==src.nID && bCheck==src.bCheck);
	}
};


#endif 
