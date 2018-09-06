#ifndef IC_ENGINEDISPLAY_H
#define IC_ENGINEDISPLAY_H
#include <string>
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

using namespace std;

/*
 * @brief 显示引擎接口，用于控制场景中对象的显示
 */
class IC_EngineDisplay{

public:
	virtual ~IC_EngineDisplay() {};
	
	/*
	 * @breif 根据对象创建显示符号
	 * @param pObject 对象指针
	 */
	virtual void createSymbolFromObject(CVBF_STObject* pObject) = 0;

	/*
	 * @breif 根据对象移除显示符号
	 * @param pObject 对象指针
	 */
	virtual void removeSymbolOfObject(CVBF_STObject* pObject) = 0;

	/*
	 * @breif 根据对象关系创建显示符号
	 * @param pRelation 对象关系指针
	 */
	virtual void createSymbolFromRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @breif 根据对象关系移除显示符号
	 * @param pRelation 对象关系指针
	 */
	virtual void removeSymbolFromRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @breif 获得显示引擎的类型
	 * @param sting 显示引擎的类型
	 */
	virtual string type() = 0;

	/*
	 * @breif 清空所有显示符号
	 */
	virtual void clear() = 0;
	
protected:
	IC_EngineDisplay() {};
};

#endif