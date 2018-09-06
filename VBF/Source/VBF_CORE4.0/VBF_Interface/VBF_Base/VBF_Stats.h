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

// 获取和每一帧相关的各种信息，绘制效率、场景图信息、线程等
class VBF_BASE_EXPORT CVBF_Stats : public ::CVBF_Referenced
{
public:
	CVBF_Stats(const std::string& name);
	CVBF_Stats(const std::string& name, unsigned int numberOfFrames);

	// 统计的名称
	void setName(const std::string& name) { m_sName = name; }
	const std::string& getName() const { return m_sName; }

	// 统计的帧数
	void allocate(unsigned int numberOfFrames); //改为SetNumberOfFrames

	// 获取最老的和最新的帧号
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


	// 根据帧号获取在数据中的索引位置
	int getIndex(unsigned int frameNumber) const
	{
		// 检测是否在统计的帧号范围内
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
