//*******************************************************************
// FileName��IVBF_3DBuildingManager.h
// Function�����潨�������ӿ�
// Author:   ��Ө
// Date:     2012-04-10
//*******************************************************************

#ifndef __IVBF_3DBUILDING_MANAGER_H__
#define __IVBF_3DBUILDING_MANAGER_H__

#include <vector>
#include <VBF_Base/VBF_Referenced.h>

namespace osg
{
	class Group;
	class UserDataContainer;
}

// ����������ID��
const char VBF_COMPONENT_3DBUILDINGMANAGER[]	= "Component: 3DBuildingManager";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DBUILDINGMANAGER[]	= "��ά���潨�������";	


// �����ﱻѡ�е���Ϣ
const char VBF_MESSAGE_3DBUIDING_SELECTED[]		= "Message: 3DBuilding Selected";	
const char VBF_MESSAGE_3DBUIDING_UNSELECTED[]	= "Message: 3DBuilding UnSelected";


// ���幤��ID��
const char VBF_TOOL_3DBUILDING_SELECT[]			= "Tool: Select One Building";			// ѡ������
const char VBF_TOOL_3DBUILDING_EDIT[]			= "Tool: Edit One Building";			// �༭������
const char VBF_TOOL_3DBUILDING_ADD[]			= "Tool: Add One Building";				// ��ӽ�����

// ��������ID��
const char VBF_COMMAND_3DBUILDING_ADD[]			= "Command: 3DBuilding AddMesh";		// ��ӽ�����
const char VBF_COMMAND_3DBUILDING_UPDATE[]		= "Command: 3DBuilding UpdateMesh";		// �޸Ľ�����
const char VBF_COMMAND_3DBUILDING_DELETE[]		= "Command: 3DBuilding DeleteMesh";		// ɾ��������
const char VBF_COMMAND_3DBUILDING_TOGGLE[]		= "Command: 3DBuilding Toggle";			// ��/�ؽ�����

const char VBF_COMMAND_BUILDING_HIGHLIGHT_BOX[]	= "Command: Building Highlight Box";//ʹ�ð�Χ�н��и�����ʾ
const char VBF_COMMAND_BUILDING_HIGHLIGHT_MODULATE[]	= "Command: Building Highlight Modulate";//ʹ�û�ɫ���и�����ʾ


// ����ģ�����ͣ���������xml�����ļ�������
const char VBF_MODELTYPE_TILE[]					= "Tile";		// �ؿ�
const char VBF_MODELTYPE_BUILDING[]				= "Building";	// ������
const char VBF_MODELTYPE_TREE[]					= "Tree";		// ��ľ


//---------------------------------------------------------------------------
// ����ṹ�壺VBF_MODELRESOURCEINFO
// �ṹ��������ģ�͵��ز���Ϣ����ive�ļ�����Ϣ
//---------------------------------------------------------------------------
typedef struct _tagVBFModelResourceInfo
{
	_tagVBFModelResourceInfo() : strID(""), strFileName("*.ive") 
	{
		fDistIn = 2000.0f;
	}

	_tagVBFModelResourceInfo(const std::string& id, const std::string& type, const std::string& fn) : 
		strID(id), strType(type), strFileName(fn) 
	{
		fDistIn = 2000.0f;
	}

	_tagVBFModelResourceInfo& operator=(const _tagVBFModelResourceInfo& src)
	{
		// ��ֹsrc=src�����Ĳ���
		if( this==&src )  return *this;	

		this->strID       = src.strID;
		this->strType	  = src.strType;
		this->strFileName = src.strFileName;
		this->fDistIn     = src.fDistIn;

		return *this;
	}
	
	std::string		strID;			// �زĵ�ȫ��ΨһID��
	std::string		strType;		// �زĵ�ģ�����ͣ�Building/Tree/Tile��
	std::string		strFileName;	// �زĶ�Ӧ��ive�ļ��ľ���·��
	float			fDistIn;		// �ز�ʵ��������ֵľ��� (��λ����)

} VBF_MODELRESOURCEINFO;


class IVBF_3DBuildingManager:public CVBF_Referenced
{
public:	
	virtual ~IVBF_3DBuildingManager() {}

	// ����/��ȡ�����������xml�����ļ���������·������������ȱʡ�ļ����ظ�
	// ȱʡΪ\\Lib\\SysSet\\3DMap\\VBF_3DBuildingConfig\\VBF_3DBuilding.xml
	// �����·����û�и��ļ�������false
	virtual bool        SetConfigFileName(const char* szFn)=0;
	virtual const char* GetConfigFileName()=0;

	// ����/��ȡ����ģ�͵Ŀɼ���
	virtual void SetVisible(bool bVisible)=0;
	virtual bool IsVisible()=0;	
	
	// ˵�������÷���������ģ�͵Ŀɼ���
	// ������udc -- ��ѯ�������������ɲ�����
	// UserDataContainer���÷������ڣ�
	// ref_ptr<osg::DefaultUserDataContainer> udc = new osg::DefaultUserDataContainer;
	// udc->addUserObject( new osg::TemplateValueObject<float>("ModelType", "Building")  );	
	// Ŀǰ֧�ֵ��������Ͱ�����string/bool/char/unsigned char/short/unsigned short/int/unsigned int
	virtual void SetModelVisible(osg::UserDataContainer* udc, bool bVisible)=0;

	// ����/��ȡģ�ͱ�ǩ�ı��Ŀɼ���
	virtual void SetLabelTextVisible(bool bVisible)=0;
	virtual void SetLabelTextVisible(osg::UserDataContainer* udc, bool bVisible)=0;
	virtual bool IsLabelTextVisible()=0;

	// ����/��ȡģ�ͱ�ǩͼ��Ŀɼ���
	virtual void SetLabelImageVisible(bool bVisible)=0;
	virtual bool IsLabelImageVisible()=0;

	// ����/��ȡģ�ͱ�ѡ��ʱ�ı���Ϣ�Ƿ�ɼ� (Ĭ��Ϊ�ɼ�)
	virtual void SetSelectedInfoVisible(bool bVisible)=0;
	virtual bool IsSelectedInfoVisible()=0;

	// ����/��ȡģ�ͱ�ѡ��ʱ��ý����Ϣ�Ƿ�ɼ�
	virtual void SetSelectedMediaVisible(bool bVisible)=0;
	virtual bool IsSelectedMediaVisible()=0;

	// ����/��ȡ���ĸ��ȼ�ѭ�������ѡģ�͵Ķ�ý����Ϣ����ֵ��osg::KeySymbol���� (Ĭ��Ϊ��Up/Down��)
	// ������bNextΪtrue��ʾ�����һ����false��ʾ�����һ��
	virtual void SetKeyToBrowseMedia(bool bNext, int nKey)=0;
	virtual int  GetKeyToBrowseMedia(bool bNext)=0;

	// ˵������������ѡ�񲢸�����ʾģ�� �ò�����xml�����ļ��趨
	// ���أ����ѡ��ָ��������ģ�ͣ�����true�����򣬷���false
	virtual bool SelectModel(osg::UserDataContainer* udc)=0;
	
	// ȡ��ѡ��״̬
	virtual void ClearSelected()=0;

	// ��ȡ��ѡ�н�����ĸ���
	virtual int GetNumSelected()=0;

	// ��ȡ��n����ѡ�еĽ���������ڱ�������˳���޹�
	virtual osg::IVBF_SGNodeGroup* GetSelected(int nIndex)=0;

	// ���ø�����ʾʱ�Ƿ�ʹ�ð�Χ����ʽ��Ĭ��Ϊʹ�ð�Χ��
	// ������bBox      -- �Ƿ�ʹ�ð�Χ����ʽ
	//       nTimes    -- ��˸�Ĵ���
	//       nInterval -- ��˸�ļ��֡��
	virtual void SetHighlightStyleOfBox(bool bBox)=0;

	// ���ø�����ʾ����ɫ��ֵ��Ϊ[0, 1]��Ĭ��Ϊ[1,0,0,1]
	virtual void SetHighlightColor(float r, float g, float b, float a)=0;

	// ���ø�����ʾ���ٶ�
	// ������nTimes    -- ��˸�Ĵ�����Ĭ��Ϊֻ��˸3��
	//       nInterval -- ��˸�ļ��֡����Ĭ��Ϊ���20֡
	// ������bAlways   -- �Ƿ��Ƿ�һֱ��˸
	virtual void SetHighlightSpeed(int nTimes, int nInterval, bool bAlways)=0;

	// ˵��������ѯ������ģ�ͽ��з���ѡ�񣬲���ѡ��������͸��������ʾ
	// ������udc -- ��ѯ�������������ɲ�����
	// ���أ��������ѡ��ָ��������ģ�ͣ�����true�����򣬷���false
	virtual bool SelectModelInverse(osg::UserDataContainer* udc)=0;

	// ȡ������ѡ����
	virtual void ClearSelectedInverse()=0;

	// ���÷���ѡ�񵽵Ľ������͸����ɫ
	virtual void SetTransparentColorAmbient(float r, float g, float b, float a)=0;  // Ĭ��Ϊ(0.2, 0.2, 0.2, 1.0)
	virtual void SetTransparentColorDiffuse(float r, float g, float b, float a)=0;	// Ĭ��Ϊ(1.0, 1.0, 0.97, 0.3)

	// ������ʾ/ȡ������������ģ��
	virtual void HighlightModel(osg::UserDataContainer* udc, float r, float g, float b, float a, bool bModulate=true)=0;
	virtual void UnHighlightModel(osg::UserDataContainer* udc)=0;

	// �л�����ģ�͵�ָ��״̬
	virtual void SwitchAllModels(const char* szSwitchKey, const char* szSwitchValue)=0;
};

#endif 
