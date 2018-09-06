#ifndef VBF_DELETEHANDLER_H
#define VBF_DELETEHANDLER_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <VBF_Base/VBF_Referenced.h>

#include <list>

/** 延迟删除处理器。更改默认的删除行为，以实现自定义的删除策略。可以对多线程时意外删除对象进行保护。
  * 注意：DeleteHandler自身不能用引用计数，否则it would be responsible for deleting itself!
  * 在VBF_Referenced.cpp中使用静态的auto_ptr<>管理 DeleteHandler的内存
  
  废弃对象的延迟删除技术：简单说，就是收集所有已经弃用的场景对象，并在需要的时候执行flush，将它们统一删除。
  一个对象，被使用时引用计数加1，被剔除时引用计数减1。引用计数值为0，这个对象被"弃用"，应当被立即删除，以释放相应的内存空间。
  
  C++中最通用的删除对象的方法是delete，不过由于采用多线程更新/渲染的方式，这样做可能带来会某些隐患，如：
  1、场景某个的节点负责显示某种图形，它的工作一直很正常；
  2、如采用DrawThreadPerContext或CullThreadPerCameraDrawThreadPerContext线程模型，存在"上次的渲染与下次的更新交叠"的情况.
  3、假设在更新工作中立即将这个节点删除，而上次渲染工作可能正要将这个节点中的数据送往OpenGL 图形渲染管线，那么灾难就发生了……
 
 一种解决方案是在渲染后台也使用ref_ptr来引用（ref）图形节点，然后在渲染结束取消引用（unref）。但存在渲染效率问题。渲染
  数万个几何体节点时，如果每个节点的渲染都要多执行一次ref/unref，效率的损失将是无法被忽略的。经过测算，CPU时间损失大概为6%。
  另一种解决方案是垃圾处理器，把引用计数为零的对象统一收集起来，确保它们不会再被渲染线程用到之后，再在适当的地方予以释放。
  重要参数_numFramesToRetainObjects的意义是，垃圾对象被收集之后，再经过多少帧（默认设置是2），方予以释放。

  */

class VBF_BASE_EXPORT DeleteHandler
{
public:

	typedef std::pair<unsigned int, const CVBF_Referenced*> FrameNumberObjectPair;
	typedef std::list<FrameNumberObjectPair> ObjectsToDeleteList;

	DeleteHandler(int numberOfFramesToRetainObjects=0);

	virtual ~DeleteHandler();

	/** 设置/获取对象被请求删除后保留的帧数。为了解决多线程的问题，请求删除之后，对象还可以保留若干帧。*/        
	void setNumFramesToRetainObjects(unsigned int numberOfFramesToRetainObjects) {  _numFramesToRetainObjects = numberOfFramesToRetainObjects; }
	unsigned int getNumFramesToRetainObjects() const { return _numFramesToRetainObjects; }

	/** 设置/获取当前的帧戳，以便随后的删除工作时作为依据。 */
	void setFrameNumber(unsigned int frameNumber) { _currentFrameNumber = frameNumber; }
	unsigned int getFrameNumber() const { return _currentFrameNumber; }


	// 真正的删除
	inline void doDelete(const CVBF_Referenced* object) { delete object; }


	/** Flush objects that ready to be fully deleted.*/
	virtual void flush();

	/** Flush all objects that the DeleteHandler holds.
	* Note, this should only be called if there are no threads running with non ref_ptr<> pointers, such as graphics threads.*/
	virtual void flushAll();

	/** 请求删除一个对象，删除的时机依赖具体的实现， 默认的是直接删除。 */
	virtual void requestDelete(const CVBF_Referenced* object);

protected:
    DeleteHandler(const DeleteHandler&);
    DeleteHandler operator = (const DeleteHandler&);

	unsigned int            _numFramesToRetainObjects; // 对象被保留的帧数
	unsigned int            _currentFrameNumber;       // 当前帧戳
	OpenThreads::Mutex      _mutex;                    // 
	ObjectsToDeleteList     _objectsToDelete;          // 待删除对象指针列表

};


#endif
