#pragma once
#include "IC_EngineDisplay.h"
#include "IC_2DMapDoc.h"

/*
 * @brief 二维显示引擎，负责二维场景的显示
 */
class C_EngineDisplay2D: public IC_EngineDisplay
{
public:
	C_EngineDisplay2D(void);
	~C_EngineDisplay2D(void);

	/*
	 * @brief 获取2D显示文档接口，标图文档负责管理显示的图层
	 * @return IC_2DMapDoc* 二维显示文档接口指针
	 */
	IC_2DMapDoc* get2DMapDoc() {return m_p2DMapDoc;}

	/*
	 * @breif 根据对象创建显示符号
	 * @param pObject 对象指针
	 */
	virtual void createSymbolFromObject(CVBF_STObject* pObject);

	/*
	 * @breif 根据对象移除显示符号
	 * @param pObject 对象指针
	 */
	virtual void removeSymbolOfObject(CVBF_STObject* pObject);

	/*
	 * @breif 根据对象关系创建显示符号
	 * @param pRelation 对象关系指针
	 */
	virtual void createSymbolFromRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @breif 根据对象关系移除显示符号
	 * @param pRelation 对象关系指针
	 */
	virtual void removeSymbolFromRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @breif 获得显示引擎的类型
	 * @param sting 显示引擎的类型
	 */
	virtual string type();

	/*
	 * @breif 清空所有显示符号
	 */
	virtual void clear();

private:
	IC_2DMapDoc* m_p2DMapDoc;
};

