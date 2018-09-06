#ifndef IC_FILTER_H
#define IC_FILTER_H

#include <vector>

using namespace std;

template <typename T>
class IC_Filter{

public:
	virtual ~IC_Filter() {};

	/*
	 * @brief 设置当前时间，该时间为系统仿真时间
	 * @param currentTime JD形式的系统仿真时间
	 */
	void setCurrentTime(double currentTime) {m_dCurrentTime = currentTime;};

	/*
	 * @brief 获取当前时间，该时间为系统仿真时间
	 * @return double JD形式的系统仿真时间
	 */
	double getCurrentTime() {return m_dCurrentTime;};

	/*
	 * @brief 获取过滤器的名称，也是唯一标志
	 * @return string 过滤器名称
	 */
	virtual string filterName() = 0; 
	
	/*
	 * @brief 对关联关系集合进行过滤
	 * @param source 需要进行过滤的类模板集合
	 *        bTimeRegarded true  过滤时考虑时间问题，默认值
	 *                      false 过滤时不考虑时间问题
	 * @return vector<T*> 过滤结果集合
	 */
	virtual vector<T*> filter(vector<T*> source, bool bTimeRegarded = true) = 0;

protected:
	IC_Filter() {};

	double m_dCurrentTime;
};

#endif