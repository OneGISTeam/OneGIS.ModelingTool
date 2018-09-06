#ifndef C_MANAGERSTOBJECTRELATION_H
#define C_MANAGERSTOBJECTRELATION_H

#include "IC_ManagerSTObjectRelation.h"

class C_ManagerSTObjectRelation: public IC_ManagerSTObjectRelation{
public:
	C_ManagerSTObjectRelation();
	virtual ~C_ManagerSTObjectRelation();

	/*
	 * @brief 向管理器中添加多粒度时空对象关联关系
	 * @param pObject 多粒度时空对象关联关系指针
	 */
	virtual void addRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @brief 向管理器中批量添加多粒度时空对象关联关系
	 * @param pObject 多粒度时空对象关联关系指针集合
	 */
	virtual void addRelations(vector<CVBF_STObjectRelation*> pRelations);

	/*
	 * @brief 移除多粒度时空对象关联关系
	 * @param pRelation 多粒度时空对象关联关系指针
	 */
	virtual void removeRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @brief 批量移除多粒度时空对象关联关系
	 * @param pRelations 多粒度时空对象关联关系指针集合
	 */
	virtual void removeRelations(vector<CVBF_STObjectRelation*> pRelations);

	/*
	 * @brief 根据关系标志OID，获取多粒度时空对象关联关系指针
	 * @param pObject 多粒度时空对象关联关系指针
	 */
	virtual CVBF_STObjectRelation* findRelation(string ROID);

	/*
	 * @brief 根据过滤条件获取多粒度时空对象关联关系
	 * @param pFilter 对象关系过滤条件
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<CVBF_STObjectRelation*> 多粒度时空对象关联关系指针容器
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(IC_FilterSTObjectRelation* pFilter, bool bTimeRegarded = true);

	/*
	 * @brief 根据过滤条件获取多粒度时空对象关联关系
	 * @param filters 对象关系过滤条件集合
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<CVBF_STObjectRelation*> 多粒度时空对象关联关系指针容器
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(ObjectRelationFilters filters,bool bTimeRegarded = true); 

	virtual bool load(const string& szFilePath, vector<CVBF_STObject*> loadedObjects);

	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> savedObjects);
};

#endif