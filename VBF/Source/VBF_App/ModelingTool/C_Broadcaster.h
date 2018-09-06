#ifndef C_Broadcaster_H
#define C_Broadcaster_H

#include <QObject>
#include "vector"
#include "map"
using namespace std;
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

/*
 * @brief ϵͳ�㲥�����ڴ����źţ�������Ӧ
 */
class C_Broadcaster : public QObject
{
	Q_OBJECT

public:
	C_Broadcaster(QObject *parent = 0);
	~C_Broadcaster();
	/*
	 * @brief ������������ӣ����롢�������������ɣ�ʱ��������Ӧ�ź�
	 * @param pObjects ������ʱ�ն���ָ������
	 */
	void emit_addSTObjects(vector<CVBF_STObject*> pObjects);

	/*
	 * @brief �������������ӣ����롢�������������ɣ�ʱ��������Ӧ�ź�
	 * @param pObject ������ʱ�ն���ָ��
	 */
	void emit_addSTObject(CVBF_STObject* pObject);

	/*
	 * @brief ���������ɾ����ͨ��������ͼ������ͼ��ɾ����ʱ��������Ӧ�ź�
	 * @param vecStr ������ʱ�ն���ȫ��Ψһ��ʶ���ַ���������
	 */
	void emit_removeSTObjects(vector<string> vecStr);

	/*
	 * @brief ����������ɾ����ͨ��������ͼ������ͼ��ɾ����ʱ��������Ӧ�ź�
	 * @param str ������ʱ�ն���ȫ��Ψһ��ʶ���ַ�����
	 */
	void emit_removeSTObject(string str);

	/*
	 * @brief ���������༭ʱ��������Ӧ�ź�
	 * @param pObjects ������ʱ�ն���ָ������
	 */
	void emit_editSTObjects(vector<CVBF_STObject*> pObjects);

	/*
	 * @brief ����������༭ʱ��������Ӧ�ź�
	 * @param pObject ������ʱ�ն���ָ��
	 */
	void emit_editSTObject(CVBF_STObject* pObject);

	/*
	 * @brief ���ö������ɼ���ʱ��������Ӧ�ź�
	 * @param mapVis map�������ͣ���Ϊ����ȫ��Ψһ��ʶ���ַ�������ֵΪbool�ͣ��ɼ���Ϊtrue
	 */
	void emit_setSTObjectsVisibility(map<string,bool> mapVis);

	/*
	 * @brief ���õ�������ɼ���ʱ��������Ӧ�ź�
	 * @param str ������ʱ�ն���ȫ��Ψһ��ʶ���ַ�����
	 *        bVisible true ����Ϊ�ɼ�	false ����Ϊ���ɼ�
	 */
	void emit_setSTObjectVisibility(string str, bool bVisible);

	/*
	 * @brief �������ѡ��ʱ��������Ӧ�ź�
	 * @param vecStr ������ʱ�ն���ȫ��Ψһ��ʶ���ַ���������
	 */
	void emit_selectSTObjects(vector<string> vecStr);

	/*
	 * @brief ��������ѡ��ʱ��������Ӧ�ź�
	 * @param str ������ʱ�ն���ȫ��Ψһ��ʶ���ַ�����
	 */
	void emit_selectSTObject(string str);

	/*
	 * @brief ���������ɺ󣬴�����Ӧ�ź�
	 * @param pObjects ������ʱ�ն���ָ������
	 */
	void emit_filterSTObjects(vector<CVBF_STObject*> pObjects);

	/*
	 * @brief ���ö�����ʽʱ��������Ӧ�ź�
	 */
	void emit_setSTObjectStyle();

	/*
	 * @brief �����ϵ���Ӻ󣬴�����Ӧ�ź�
	 * @param pRelations ��ϵָ������
	 */
	void emit_addRelations(vector<CVBF_STObjectRelation*> pRelations);

	/*
	 * @brief ������ϵ���Ӻ󣬴�����Ӧ�ź�
	 * @param pRelation ��ϵָ��
	 */
	void emit_addRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @brief ɾ�������ϵʱ��������Ӧ�ź�
	 * @param vecStr ��ϵȫ��Ψһ��ʶ���ַ���������
	 */
	void emit_removeRelations(vector<string> vecStr);

	/*
	 * @brief ɾ��������ϵʱ��������Ӧ�ź�
	 * @param str ��ϵȫ��Ψһ��ʶ���ַ�����
	 */
	void emit_removeRelation(string str);

	/*
	 * @brief ���ö����ϵ�ɼ���ʱ��������Ӧ�ź�
	 * @param mapVis map�������ͣ���Ϊ��ϵȫ��Ψһ��ʶ���ַ�������ֵΪbool�ͣ��ɼ���Ϊtrue
	 */
	void emit_setRelationsVisibility(map<string,bool> mapVis);

	/*
	 * @brief ���õ�����ϵ�ɼ���ʱ��������Ӧ�ź�
	 * @param str ��ϵȫ��Ψһ��ʶ���ַ�����
	 *        bVisible true ����Ϊ�ɼ�	false ����Ϊ���ɼ�
	 */
	void emit_setRelationVisibility(string str, bool bVisible);

	/*
	 * @brief �����ϵ��ѡ�к󣬴�����Ӧ�ź�
	 * @param vecStr ��ϵȫ��Ψһ��ʶ���ַ���������
	 */
	void emit_selectRelations(vector<string> vecStr);

	/*
	 * @brief ������ϵ��ѡ�к󣬴�����Ӧ�ź�
	 * @param str ��ϵȫ��Ψһ��ʶ���ַ�����
	 */
	void emit_selectRelation(string str);

	/*
	 * @brief ���ù�ϵ��ʽʱ��������Ӧ�ź�
	 */
	void emit_setRelationStyle();

signals:

	/*
	 * @brief ��������źţ������źŶ��󣺶�����ͼ������ͼ��ͼ����ͼ��������ȹ�������2D/3D���ڡ�ʱ����
	 */
	void signal_STObjectAdded(vector<CVBF_STObject*>);

	/*
	 * @brief ����ɾ���źţ������źŶ��󣺶�����ͼ������ͼ����ϵ��ͼ��ͼ����ͼ��������ȹ�������2D/3D���ڡ�ʱ����
	 */
	void signal_STObjectRemoved(vector<string>);

	/*
	 * @brief ����༭�źţ������źŶ���2D/3D���ڡ�ʱ����
	 */
	void signal_STObjectEdited(vector<CVBF_STObject*>);

	/*
	 * @brief ����ɼ��Ըı��źţ������źŶ��󣺶�����ͼ������ͼ��ͼ����ͼ��2D/3D���ڣ��漰��ϵ��ʾ����
	 */
	void signal_STObjectVisibilityChanged(map<string,bool>);

	/*
	 * @brief ����ѡ���źţ������źŶ���ʱ���ᡢ������ͼ������ͼ��ͼ����ͼ��2D/3D����
	 */
	void signal_STObjectSelected(vector<string>);

	/*
	 * @brief ��������źţ������źŶ���ʱ���ᡢ������ͼ������ͼ��ͼ����ͼ��2D/3D����
	 */
	void signal_STObjectFiltered(vector<CVBF_STObject*>);

	/*
	 * @brief ������ʽ�ı��źţ������źŶ���2D/3D����
	 */
	void signal_STObjectStyleChanged();

	/*
	 * @brief ��ϵ�����źţ������źŶ��󣺹�ϵ��ͼ��2D/3D����
	 */
	void signal_RelationAdded(vector<CVBF_STObjectRelation*>);

	/*
	 * @brief ��ϵɾ���źţ������źŶ��󣺹�ϵ��ͼ��2D/3D����
	 */
	void signal_RelationRemoved(vector<string>);

	/*
	 * @brief ��ϵ�ɼ��Ըı��źţ������źŶ���2D/3D����
	 */
	void signal_RelationVisibilityChanged(map<string,bool>);

	/*
	 * @brief ��ϵѡ���źţ������źŶ���2D/3D����
	 */
	void signal_RelationSelected(vector<string>);

	/*
	 * @brief ��ϵ��ʽ�ı��źţ������źŶ���2D/3D����
	 */
	void signal_RelationStyleChanged();
};

#endif // C_Broadcaster_H
