#ifndef IC_ENGINEDISPLAY_H
#define IC_ENGINEDISPLAY_H
#include <string>
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

using namespace std;

/*
 * @brief ��ʾ����ӿڣ����ڿ��Ƴ����ж������ʾ
 */
class IC_EngineDisplay{

public:
	virtual ~IC_EngineDisplay() {};
	
	/*
	 * @breif ���ݶ��󴴽���ʾ����
	 * @param pObject ����ָ��
	 */
	virtual void createSymbolFromObject(CVBF_STObject* pObject) = 0;

	/*
	 * @breif ���ݶ����Ƴ���ʾ����
	 * @param pObject ����ָ��
	 */
	virtual void removeSymbolOfObject(CVBF_STObject* pObject) = 0;

	/*
	 * @breif ���ݶ����ϵ������ʾ����
	 * @param pRelation �����ϵָ��
	 */
	virtual void createSymbolFromRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @breif ���ݶ����ϵ�Ƴ���ʾ����
	 * @param pRelation �����ϵָ��
	 */
	virtual void removeSymbolFromRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @breif �����ʾ���������
	 * @param sting ��ʾ���������
	 */
	virtual string type() = 0;

	/*
	 * @breif ���������ʾ����
	 */
	virtual void clear() = 0;
	
protected:
	IC_EngineDisplay() {};
};

#endif