#ifndef IC_MANAGERSTOBJECTRELATION_H 
#define IC_MANAGERSTOBJECTRELATION_H

#include <vector>
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"
#include "IC_FilterSTObjectRelation.h"
#include "IC_AccessFileRelation.h"

using namespace std;

/*
 * @brief 多粒度时空对象管理器接口，用于对象的统一管理及操作
 */
class IC_ManagerSTObjectRelation{

public:
	virtual ~IC_ManagerSTObjectRelation() {};

	/*
	 * @brief 向管理器中添加多粒度时空对象关联关系
	 * @param pObject 多粒度时空对象关联关系指针
	 */
	virtual void addRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @brief 向管理器中批量添加多粒度时空对象关联关系
	 * @param pObject 多粒度时空对象关联关系指针集合
	 */
	virtual void addRelations(vector<CVBF_STObjectRelation*> pRelations) = 0;

	/*
	 * @brief 移除多粒度时空对象关联关系
	 * @param pRelation 多粒度时空对象关联关系指针
	 */
	virtual void removeRelation(CVBF_STObjectRelation* pRelation) = 0;

	/*
	 * @brief 批量移除多粒度时空对象关联关系
	 * @param pRelations 多粒度时空对象关联关系指针集合
	 */
	virtual void removeRelations(vector<CVBF_STObjectRelation*> pRelations) = 0;

	/*
	 * @brief 根据关系标志OID，获取多粒度时空对象关联关系指针
	 * @param pObject 多粒度时空对象关联关系指针
	 */
	virtual CVBF_STObjectRelation* findRelation(string ROID) = 0;

	/*
	 * @brief 根据过滤条件获取多粒度时空对象关联关系
	 * @param pFilter 对象关系过滤条件
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<CVBF_STObjectRelation*> 多粒度时空对象关联关系指针容器
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(IC_FilterSTObjectRelation* pFilter, bool bTimeRegarded = true) = 0;

	/*
	 * @brief 根据过滤条件获取多粒度时空对象关联关系
	 * @param filters 对象关系过滤条件集合
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<CVBF_STObjectRelation*> 多粒度时空对象关联关系指针容器
	 */
	virtual vector<CVBF_STObjectRelation*> findRelations(ObjectRelationFilters filters, bool bTimeRegarded = true) = 0; 

	/*
	 * @brief 获取多粒度时空对象关联关系集合
	 * @return vector<CVBF_STObjectRelation*> 关联关系集合
	 */
	virtual vector<CVBF_STObjectRelation*> getRelations() {return m_vect_relations;};

	virtual bool load(const string& szFilePath, vector<CVBF_STObject*> loadedObjects) = 0;

	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> savedObjects) = 0;

protected:
	IC_ManagerSTObjectRelation() {};

	//对象关联关系集合
	vector<CVBF_STObjectRelation*> m_vect_relations;

	IC_AccessFileRelation* m_pAccessFileRelation;
};


#endif