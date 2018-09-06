#ifndef IC_FILTER_H
#define IC_FILTER_H

#include <vector>

using namespace std;

template <typename T>
class IC_Filter{

public:
	virtual ~IC_Filter() {};

	/*
	 * @brief ���õ�ǰʱ�䣬��ʱ��Ϊϵͳ����ʱ��
	 * @param currentTime JD��ʽ��ϵͳ����ʱ��
	 */
	void setCurrentTime(double currentTime) {m_dCurrentTime = currentTime;};

	/*
	 * @brief ��ȡ��ǰʱ�䣬��ʱ��Ϊϵͳ����ʱ��
	 * @return double JD��ʽ��ϵͳ����ʱ��
	 */
	double getCurrentTime() {return m_dCurrentTime;};

	/*
	 * @brief ��ȡ�����������ƣ�Ҳ��Ψһ��־
	 * @return string ����������
	 */
	virtual string filterName() = 0; 
	
	/*
	 * @brief �Թ�����ϵ���Ͻ��й���
	 * @param source ��Ҫ���й��˵���ģ�弯��
	 *        bTimeRegarded true  ����ʱ����ʱ�����⣬Ĭ��ֵ
	 *                      false ����ʱ������ʱ������
	 * @return vector<T*> ���˽������
	 */
	virtual vector<T*> filter(vector<T*> source, bool bTimeRegarded = true) = 0;

protected:
	IC_Filter() {};

	double m_dCurrentTime;
};

#endif