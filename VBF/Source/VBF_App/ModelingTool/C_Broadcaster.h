#ifndef C_Broadcaster_H
#define C_Broadcaster_H

#include <QObject>
#include "vector"
#include "map"
using namespace std;
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

/*
 * @brief 系统广播，用于传递信号，触发响应
 */
class C_Broadcaster : public QObject
{
	Q_OBJECT

public:
	C_Broadcaster(QObject *parent = 0);
	~C_Broadcaster();
	/*
	 * @brief 当多个对象增加（导入、创建、批量生成）时，触发相应信号
	 * @param pObjects 多粒度时空对象指针容器
	 */
	void emit_addSTObjects(vector<CVBF_STObject*> pObjects);

	/*
	 * @brief 当单个对象增加（导入、创建、批量生成）时，触发相应信号
	 * @param pObject 多粒度时空对象指针
	 */
	void emit_addSTObject(CVBF_STObject* pObject);

	/*
	 * @brief 当多个对象删除（通过对象视图或类视图等删除）时，触发相应信号
	 * @param vecStr 多粒度时空对象全局唯一标识（字符串）容器
	 */
	void emit_removeSTObjects(vector<string> vecStr);

	/*
	 * @brief 当单个对象删除（通过对象视图或类视图等删除）时，触发相应信号
	 * @param str 多粒度时空对象全局唯一标识（字符串）
	 */
	void emit_removeSTObject(string str);

	/*
	 * @brief 当多个对象编辑时，触发相应信号
	 * @param pObjects 多粒度时空对象指针容器
	 */
	void emit_editSTObjects(vector<CVBF_STObject*> pObjects);

	/*
	 * @brief 当单个对象编辑时，触发相应信号
	 * @param pObject 多粒度时空对象指针
	 */
	void emit_editSTObject(CVBF_STObject* pObject);

	/*
	 * @brief 设置多个对象可见性时，触发相应信号
	 * @param mapVis map容器类型，键为对象全局唯一标识（字符串），值为bool型，可见即为true
	 */
	void emit_setSTObjectsVisibility(map<string,bool> mapVis);

	/*
	 * @brief 设置单个对象可见性时，触发相应信号
	 * @param str 多粒度时空对象全局唯一标识（字符串）
	 *        bVisible true 设置为可见	false 设置为不可见
	 */
	void emit_setSTObjectVisibility(string str, bool bVisible);

	/*
	 * @brief 多个对象被选中时，触发相应信号
	 * @param vecStr 多粒度时空对象全局唯一标识（字符串）容器
	 */
	void emit_selectSTObjects(vector<string> vecStr);

	/*
	 * @brief 单个对象被选中时，触发相应信号
	 * @param str 多粒度时空对象全局唯一标识（字符串）
	 */
	void emit_selectSTObject(string str);

	/*
	 * @brief 对象过滤完成后，触发相应信号
	 * @param pObjects 多粒度时空对象指针容器
	 */
	void emit_filterSTObjects(vector<CVBF_STObject*> pObjects);

	/*
	 * @brief 设置对象样式时，触发相应信号
	 */
	void emit_setSTObjectStyle();

	/*
	 * @brief 多个关系增加后，触发相应信号
	 * @param pRelations 关系指针容器
	 */
	void emit_addRelations(vector<CVBF_STObjectRelation*> pRelations);

	/*
	 * @brief 单个关系增加后，触发相应信号
	 * @param pRelation 关系指针
	 */
	void emit_addRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @brief 删除多个关系时，触发相应信号
	 * @param vecStr 关系全局唯一标识（字符串）容器
	 */
	void emit_removeRelations(vector<string> vecStr);

	/*
	 * @brief 删除单个关系时，触发相应信号
	 * @param str 关系全局唯一标识（字符串）
	 */
	void emit_removeRelation(string str);

	/*
	 * @brief 设置多个关系可见性时，触发相应信号
	 * @param mapVis map容器类型，键为关系全局唯一标识（字符串），值为bool型，可见即为true
	 */
	void emit_setRelationsVisibility(map<string,bool> mapVis);

	/*
	 * @brief 设置单个关系可见性时，触发相应信号
	 * @param str 关系全局唯一标识（字符串）
	 *        bVisible true 设置为可见	false 设置为不可见
	 */
	void emit_setRelationVisibility(string str, bool bVisible);

	/*
	 * @brief 多个关系被选中后，触发相应信号
	 * @param vecStr 关系全局唯一标识（字符串）容器
	 */
	void emit_selectRelations(vector<string> vecStr);

	/*
	 * @brief 单个关系被选中后，触发相应信号
	 * @param str 关系全局唯一标识（字符串）
	 */
	void emit_selectRelation(string str);

	/*
	 * @brief 设置关系样式时，触发相应信号
	 */
	void emit_setRelationStyle();

signals:

	/*
	 * @brief 对象添加信号；接受信号对象：对象视图、类视图、图层视图、对象调度管理器、2D/3D窗口、时间轴
	 */
	void signal_STObjectAdded(vector<CVBF_STObject*>);

	/*
	 * @brief 对象删除信号；接受信号对象：对象视图、类视图、关系视图、图层视图、对象调度管理器、2D/3D窗口、时间轴
	 */
	void signal_STObjectRemoved(vector<string>);

	/*
	 * @brief 对象编辑信号；接受信号对象：2D/3D窗口、时间轴
	 */
	void signal_STObjectEdited(vector<CVBF_STObject*>);

	/*
	 * @brief 对象可见性改变信号；接受信号对象：对象视图、类视图、图层视图、2D/3D窗口（涉及关系显示？）
	 */
	void signal_STObjectVisibilityChanged(map<string,bool>);

	/*
	 * @brief 对象选中信号；接受信号对象：时间轴、对象视图、类视图、图层视图、2D/3D窗口
	 */
	void signal_STObjectSelected(vector<string>);

	/*
	 * @brief 对象过滤信号；接受信号对象：时间轴、对象视图、类视图、图层视图、2D/3D窗口
	 */
	void signal_STObjectFiltered(vector<CVBF_STObject*>);

	/*
	 * @brief 对象样式改变信号；接受信号对象：2D/3D窗口
	 */
	void signal_STObjectStyleChanged();

	/*
	 * @brief 关系增加信号；接受信号对象：关系视图、2D/3D窗口
	 */
	void signal_RelationAdded(vector<CVBF_STObjectRelation*>);

	/*
	 * @brief 关系删除信号；接受信号对象：关系视图、2D/3D窗口
	 */
	void signal_RelationRemoved(vector<string>);

	/*
	 * @brief 关系可见性改变信号；接受信号对象：2D/3D窗口
	 */
	void signal_RelationVisibilityChanged(map<string,bool>);

	/*
	 * @brief 关系选中信号；接受信号对象：2D/3D窗口
	 */
	void signal_RelationSelected(vector<string>);

	/*
	 * @brief 关系样式改变信号；接受信号对象：2D/3D窗口
	 */
	void signal_RelationStyleChanged();
};

#endif // C_Broadcaster_H
