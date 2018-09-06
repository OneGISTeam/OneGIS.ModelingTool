#ifndef VBF_STATISTICS_H
#define VBF_STATISTICS_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <VBF_Base/VBF_Referenced.h>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>

#include <string>
#include <map>
#include <vector>
#include <ostream>

// ��ȡ��ÿһ֡��صĸ�����Ϣ������Ч�ʡ�����ͼ��Ϣ���̵߳�
class VBF_BASE_EXPORT CVBF_Stats : public ::CVBF_Referenced
{
public:
	CVBF_Stats(const std::string& name);
	CVBF_Stats(const std::string& name, unsigned int numberOfFrames);

	// ͳ�Ƶ�����
	void setName(const std::string& name) { m_sName = name; }
	const std::string& getName() const { return m_sName; }

	// ͳ�Ƶ�֡��
	void allocate(unsigned int numberOfFrames); //��ΪSetNumberOfFrames

	// ��ȡ���ϵĺ����µ�֡��
	unsigned int getEarliestFrameNumber() const { return _latestFrameNumber < static_cast<unsigned int>(_attributeMapList.size()) ? 0 : _latestFrameNumber - static_cast<unsigned int>(_attributeMapList.size()) + 1; }
	unsigned int getLatestFrameNumber() const { return _latestFrameNumber; }

	typedef std::map<std::string, double> AttributeMap;
	typedef std::vector<AttributeMap> AttributeMapList;

	bool setAttribute(unsigned int frameNumber, const std::string& attributeName, double value);

	inline bool getAttribute(unsigned int frameNumber, const std::string& attributeName, double& value) const
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
		return getAttributeNoMutex(frameNumber, attributeName, value);
	}

	bool getAveragedAttribute(const std::string& attributeName, double& value, bool averageInInverseSpace=false) const;
	bool getAveragedAttribute(unsigned int startFrameNumber, unsigned int endFrameNumber, const std::string& attributeName, double& value, bool averageInInverseSpace=false) const;

	inline AttributeMap& getAttributeMap(unsigned int frameNumber)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
		return getAttributeMapNoMutex(frameNumber);
	}

	inline const AttributeMap& getAttributeMap(unsigned int frameNumber) const
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
		return getAttributeMapNoMutex(frameNumber);
	}

	typedef std::map<std::string, bool> CollectMap;

	void collectStats(const std::string& str, bool flag) { _collectMap[str] = flag; }

	inline bool collectStats(const std::string& str) const
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);

		CollectMap::const_iterator itr = _collectMap.find(str); 
		return (itr !=  _collectMap.end()) ? itr->second : false;
	}

	void report(std::ostream& out, const char* indent=0) const;
	void report(std::ostream& out, unsigned int frameNumber, const char* indent=0) const;

protected:
    virtual ~CVBF_Stats();

	bool getAttributeNoMutex(unsigned int frameNumber, const std::string& attributeName, double& value) const;

	AttributeMap& getAttributeMapNoMutex(unsigned int frameNumber);
	const AttributeMap& getAttributeMapNoMutex(unsigned int frameNumber) const;


	// ����֡�Ż�ȡ�������е�����λ��
	int getIndex(unsigned int frameNumber) const
	{
		// ����Ƿ���ͳ�Ƶ�֡�ŷ�Χ��
		if (frameNumber > _latestFrameNumber) return -1;
		if (frameNumber < getEarliestFrameNumber()) return -1;

		if (frameNumber >= _baseFrameNumber) return frameNumber - _baseFrameNumber;
		else return static_cast<int>(_attributeMapList.size()) - (_baseFrameNumber-frameNumber);
	}

	std::string         m_sName;

	mutable OpenThreads::Mutex  _mutex;

	unsigned int        _baseFrameNumber;
	unsigned int        _latestFrameNumber;

	AttributeMapList    _attributeMapList;
	AttributeMap        _invalidAttributeMap;

	CollectMap          _collectMap;

};


#endif
