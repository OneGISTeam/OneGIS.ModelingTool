#pragma once
#include "IC_ManagerDisplay.h"

class C_ManagerDisplay: public IC_ManagerDisplay
{
	Q_OBJECT
public:
	C_ManagerDisplay(void);
	~C_ManagerDisplay(void);

	/*
	 * @brief 注册显示引擎
	 * @param pEngineDisplay 显示引擎接口
	 */
	virtual void registers(IC_EngineDisplay* pEngineDisplay);

	/*
	 * @brief 注销显示引擎
	 * @param pEngineDisplay 显示引擎接口
	 */
	virtual void unregisters(IC_EngineDisplay* pEngineDisplay);

	/*
	 * @brief 获得显示引擎的数量
	 * @return int 显示引擎的数量
	 */
	virtual int count();

	/*
	 * @brief 按照索引号获取显示引擎指针
	 * @return IC_EngineDisplay* 显示引擎指针
	 */
	virtual IC_EngineDisplay* at(int index);

	/*
	 * @brief 通过类型获得显示引擎，该接口要确保type唯一方可使用
	 * @param type 显示引擎类型
	 * @return IC_EngineDisplay* 显示引擎指针
	 */
	virtual IC_EngineDisplay* getByType(const string& type);

	/*
	 * @brief 通过显示引擎，更新显示场景
	 * @param currentObjects   现势对象指针集合
	 *        selectedObjects  选中对象指针集合
	 */
	virtual void update(vector<CVBF_STObject*> currentObjects, vector<CVBF_STObject*> selectedObjects);

	/*
	 * @brief 通过显示引擎，更新显示场景
	 * @param currentObjects   现势对象关系指针集合
	 *        selectedObjects  选中对象关系指针集合
	 */
	virtual void update(vector<CVBF_STObjectRelation*> currentRelations, vector<CVBF_STObjectRelation*> selectedRelations);
};

