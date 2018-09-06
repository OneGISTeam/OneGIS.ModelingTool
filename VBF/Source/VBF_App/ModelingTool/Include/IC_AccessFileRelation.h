#ifndef IC_ACCESSFILERELATION_H
#define IC_ACCESSFILERELATION_H

#include <vector>
#include "VBF_Common/VBF_STObject/VBF_STObjectRelation.h"

/*
 * @brief 关联关系文件访问接口，该接口的调用一般是在IC_AccessFileObject调用完成之后
 */
class IC_AccessFileRelation{

public:
	virtual ~IC_AccessFileRelation() {};

	/*
	 * @brief 导出多粒度时空对象关联关系
	 * @param szFilePath 关联关系文件路径
	 *        saveObjects 已导出的多粒度时空对象指针集合
	 *        relations  关联关系指针集合
	 * @return bool 导出结果，true为成功，false为不成功
	 */
	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> saveObjects, vector<CVBF_STObjectRelation*> relations) = 0;

	/*
	 * @brief 加载多粒度时空对象关联关系
	 * @param szFilePath 关联关系文件路径
	 *        loadedObjects 已加载的多粒度时空对象指针集合
	 * @return vector<CVBF_STObjectRelation*> 加载成功的多粒度时空对象关联关系集合
	 */
	virtual vector<CVBF_STObjectRelation*> load(const string& szFilePath, vector<CVBF_STObject*> loadedObjects) = 0;

protected:
	IC_AccessFileRelation() {};

};

#endif