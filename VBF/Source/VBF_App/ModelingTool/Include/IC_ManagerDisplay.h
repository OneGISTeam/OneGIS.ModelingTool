#ifndef IC_MANAGERDISPLAY_H
#define IC_MANAGERDISPLAY_H

#include <QObject>
#include <vector>
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"
#include "IC_EngineDisplay.h"

using namespace std;

class IC_EngineDisplay;
/*
 * @brief 显示管理器，主要用于显示引擎及显示场景的管理
 */
class IC_ManagerDisplay: public QObject{
public:
	virtual ~IC_ManagerDisplay() {};

	/*
	 * @brief 注册显示引擎
	 * @param pEngineDisplay 显示引擎接口
	 */
	virtual void registers(IC_EngineDisplay* pEngineDisplay) = 0;

	/*
	 * @brief 注销显示引擎
	 * @param pEngineDisplay 显示引擎接口
	 */
	virtual void unregisters(IC_EngineDisplay* pEngineDisplay) = 0;

	/*
	 * @brief 获得显示引擎的数量
	 * @return int 显示引擎的数量
	 */
	virtual int count() = 0;

	/*
	 * @brief 按照索引号获取显示引擎指针
	 * @return IC_EngineDisplay* 显示引擎指针
	 */
	virtual IC_EngineDisplay* at(int index) = 0;

	/*
	 * @brief 通过类型获得显示引擎，该接口要确保type唯一方可使用
	 * @param type 显示引擎类型
	 * @return IC_EngineDisplay* 显示引擎指针
	 */
	virtual IC_EngineDisplay* getByType(const string& type) = 0;

	/*
	 * @brief 通过显示引擎，更新显示场景
	 * @param currentObjects   现势对象指针集合
	 *        selectedObjects  选中对象指针集合
	 */
	virtual void update(vector<CVBF_STObject*> currentObjects, vector<CVBF_STObject*> selectedObjects) = 0;

	/*
	 * @brief 通过显示引擎，更新显示场景
	 * @param currentObjects   现势对象关系指针集合
	 *        selectedObjects  选中对象关系指针集合
	 */
	virtual void update(vector<CVBF_STObjectRelation*> currentRelations, vector<CVBF_STObjectRelation*> selectedRelations) = 0;

protected:
	IC_ManagerDisplay() {};
	vector<IC_EngineDisplay*> m_vect_engines;
};

#endif