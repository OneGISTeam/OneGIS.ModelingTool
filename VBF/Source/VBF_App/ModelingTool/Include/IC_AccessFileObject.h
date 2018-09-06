#ifndef IC_ACCESSFILEOBJECT_H
#define IC_ACCESSFILEOBJECT_H

#include "VBF_Common/VBF_STObject/VBF_STObject.h"
#include <vector>

using namespace std;

class IC_AccessFileObject{
public:
	virtual ~IC_AccessFileObject() {};

	/*
	 * @brief 对象文档加载接口，用于读取符合交换格式标准的对象文件
	 * @param szFilePath 文件路径
	 * @return vector<CVBF_STObject*> 多粒度时空对象指针集合
	 */
	virtual vector<CVBF_STObject*> load(const string& szFilePath) = 0;

	/*
	 * @brief 对象文档保存接口，用于将内存中的数据导出成符合交换格式标准的对象文件
	 * @param szFilePath 文件路径
	 * @return bool 保存结果，true为成功导出所有对象
	 *                        false为没有成功导出所有对象
	 */
	virtual bool save(const string& szFilePath, vector<CVBF_STObject*> objects) = 0;

protected:
	IC_AccessFileObject() {};
};

#endif