#ifndef IC_MANAGERSTOBJECT_H 
#define IC_MANAGERSTOBJECT_H
#include "IC_ManagerSTObjectRelation.h"
#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include "IC_FilterSTObject.h"
#include <vector>

using namespace std;

/*
 * @brief 多粒度时空对象管理器接口，用于对象的统一管理及操作
 *        对象管理器控制关系管理器的生命周期
 */
class IC_ManagerSTObject{

public:
	virtual ~IC_ManagerSTObject() {
		if(m_pManagerRelation){
			delete m_pManagerRelation;
		}
	};

	/*
	 * @brief 获取多粒度时空对象的关系管理器
	 * @return IC_ManagerSTObjectRelation* 关系管理器指针
	 */
	IC_ManagerSTObjectRelation* objectRelationManager() {return m_pManagerRelation;};

	/*
	 * @brief 向管理器中添加多粒度时空对象
	 * @param pObject 多粒度时空对象指针
	 */
	virtual void addObject(CVBF_STObject* pObject) = 0;

	/*
	 * @brief 向管理器中批量添加多粒度时空对象
	 * @param pObjects 多粒度时空对象指针容器
	 */
	virtual void addObjects(vector<CVBF_STObject*> pObjects) = 0;

	/*
	 * @brief 移除多粒度时空对象
	 * @param pObject 多粒度时空对象指针
	 *        bFlag   true 即使该对象与其它对象有关联也进行强制删除
	 *                false 如果对象与其它对象有关联，则不要删除
	 */
	virtual void removeObject(CVBF_STObject* pObject, bool bFlag = true) = 0;

	/*
	 * @brief 批量移除多粒度时空对象
	 * @param pObject 多粒度时空对象指针容器
	 *        bFlag   true 即使该对象与其它对象有关联也进行强制删除
	 *                false 如果对象与其它对象有关联，则不要删除
	 */
	virtual void removeObjects(vector<CVBF_STObject*> pObjects, bool bFlag = true) = 0;

	/*
	 * @brief 根据对象标志OID，获取多粒度时空对象指针
	 * @param pObject 多粒度时空对象指针
	 */
	virtual CVBF_STObject* findObject(string OID) = 0;

	/*
	 * @brief 根据过滤条件获取多粒度时空对象
	 * @param filters 对象过滤条件集合
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<CVBF_STObject*> 多粒度时空对象指针容器
	 */
	virtual vector<CVBF_STObject*> findObjects(IC_FilterSTObject* pFilter, bool bTimeRegarded = true) = 0;

	/*
	 * @brief 根据过滤条件获取多粒度时空对象
	 * @param filters 对象过滤条件集合
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<CVBF_STObject*> 多粒度时空对象指针容器
	 */
	virtual vector<CVBF_STObject*> findObjects(ObjectFilters filters, bool bTimeRegarded = true) = 0;

	/*
	 * @brief 获取多粒度时空对象指针容器
	 * @return vector<CVBF_STObject*> 多粒度时空对象指针容器
	 */
	vector<CVBF_STObject*> getObjects() {return m_vect_objects;};

	/*
	 * @brief 加载多粒度时空对象（暂时默认方式是文件加载，后期可能可以从数据库直接加载）
	 * @param szFilePath    加载文件路径（含文件名）
	 *        bLoadRelation 是否加载关联关系，默认为加载
	 * @return bool 加载结果，true为成功，false为失败
	 */
	virtual bool load(const string& szFilePath, bool bLoadRelation = true) = 0;

	/*
	 * @brief 导出多粒度时空对象（暂时默认方式是文件导出，后期可能直接数据库入库）
	 * @param szFilePath    导出文件路径（含文件名）
	 *        bLoadRelation 是否导出关联关系，默认为导出
	 * @return bool 导出结果，true为成功，false为失败
	 */
	virtual bool save(const string& szFilePath, bool bSaveRelation = true) = 0;

protected:
	IC_ManagerSTObject(IC_ManagerSTObjectRelation* pManagerRelation) {m_pManagerRelation = pManagerRelation;};

protected:
	//多粒度时空对象关联关系管理器
	IC_ManagerSTObjectRelation* m_pManagerRelation;
	
	//多粒度时空对象指针集合
	vector<CVBF_STObject*> m_vect_objects;
};


#endif