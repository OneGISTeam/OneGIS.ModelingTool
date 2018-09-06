#ifndef OSGGA_GUIACTIONADAPTER
#define OSGGA_GUIACTIONADAPTER 1 

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Engine/VBF_SceneGraph/VBF_CameraSlave.h>

/**
	����ӿڣ�������UIϵͳ��������
	�¼����������������¼����д�����ϣ����GUI����һЩ�������磬�϶�ģ�Ͳ�ͻȻ�ɿ���ʹģ�͵ĳ�����ת���ƶ���
	��ʱ���¼�������ϣ������һ����ʱ�����ظ����ò�ͣ��ˢ�������λ�úͷ���
*/
class IVBF_GUIActionAdapter
{
public:
	virtual ~IVBF_GUIActionAdapter() {}

	virtual osg::IVBF_ViewBrief* asView() { return 0; }// �ṩһ�ֻ�ȡ��֮������View�Ļ��ơ�

	virtual void requestRedraw() = 0; // �����ػ�һ��
	virtual void requestContinuousUpdate(bool needed=true) = 0; // �����θ��£�����ʱ���ϻ��ƣ�
	virtual void requestWarpPointer(float x,float y) = 0;       // ������λ������

};

#endif

