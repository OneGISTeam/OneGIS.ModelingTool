#ifndef VBF_DELETEHANDLER_H
#define VBF_DELETEHANDLER_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <VBF_Base/VBF_Referenced.h>

#include <list>

/** �ӳ�ɾ��������������Ĭ�ϵ�ɾ����Ϊ����ʵ���Զ����ɾ�����ԡ����ԶԶ��߳�ʱ����ɾ��������б�����
  * ע�⣺DeleteHandler�����������ü���������it would be responsible for deleting itself!
  * ��VBF_Referenced.cpp��ʹ�þ�̬��auto_ptr<>���� DeleteHandler���ڴ�
  
  ����������ӳ�ɾ����������˵�������ռ������Ѿ����õĳ������󣬲�����Ҫ��ʱ��ִ��flush��������ͳһɾ����
  һ�����󣬱�ʹ��ʱ���ü�����1�����޳�ʱ���ü�����1�����ü���ֵΪ0���������"����"��Ӧ��������ɾ�������ͷ���Ӧ���ڴ�ռ䡣
  
  C++����ͨ�õ�ɾ������ķ�����delete���������ڲ��ö��̸߳���/��Ⱦ�ķ�ʽ�����������ܴ�����ĳЩ�������磺
  1������ĳ���Ľڵ㸺����ʾĳ��ͼ�Σ����Ĺ���һֱ��������
  2�������DrawThreadPerContext��CullThreadPerCameraDrawThreadPerContext�߳�ģ�ͣ�����"�ϴε���Ⱦ���´εĸ��½���"�����.
  3�������ڸ��¹���������������ڵ�ɾ�������ϴ���Ⱦ����������Ҫ������ڵ��е���������OpenGL ͼ����Ⱦ���ߣ���ô���Ѿͷ����ˡ���
 
 һ�ֽ������������Ⱦ��̨Ҳʹ��ref_ptr�����ã�ref��ͼ�νڵ㣬Ȼ������Ⱦ����ȡ�����ã�unref������������ȾЧ�����⡣��Ⱦ
  �����������ڵ�ʱ�����ÿ���ڵ����Ⱦ��Ҫ��ִ��һ��ref/unref��Ч�ʵ���ʧ�����޷������Եġ��������㣬CPUʱ����ʧ���Ϊ6%��
  ��һ�ֽ�������������������������ü���Ϊ��Ķ���ͳһ�ռ�������ȷ�����ǲ����ٱ���Ⱦ�߳��õ�֮�������ʵ��ĵط������ͷš�
  ��Ҫ����_numFramesToRetainObjects�������ǣ����������ռ�֮���پ�������֡��Ĭ��������2�����������ͷš�

  */

class VBF_BASE_EXPORT DeleteHandler
{
public:

	typedef std::pair<unsigned int, const CVBF_Referenced*> FrameNumberObjectPair;
	typedef std::list<FrameNumberObjectPair> ObjectsToDeleteList;

	DeleteHandler(int numberOfFramesToRetainObjects=0);

	virtual ~DeleteHandler();

	/** ����/��ȡ��������ɾ��������֡����Ϊ�˽�����̵߳����⣬����ɾ��֮�󣬶��󻹿��Ա�������֡��*/        
	void setNumFramesToRetainObjects(unsigned int numberOfFramesToRetainObjects) {  _numFramesToRetainObjects = numberOfFramesToRetainObjects; }
	unsigned int getNumFramesToRetainObjects() const { return _numFramesToRetainObjects; }

	/** ����/��ȡ��ǰ��֡�����Ա�����ɾ������ʱ��Ϊ���ݡ� */
	void setFrameNumber(unsigned int frameNumber) { _currentFrameNumber = frameNumber; }
	unsigned int getFrameNumber() const { return _currentFrameNumber; }


	// ������ɾ��
	inline void doDelete(const CVBF_Referenced* object) { delete object; }


	/** Flush objects that ready to be fully deleted.*/
	virtual void flush();

	/** Flush all objects that the DeleteHandler holds.
	* Note, this should only be called if there are no threads running with non ref_ptr<> pointers, such as graphics threads.*/
	virtual void flushAll();

	/** ����ɾ��һ������ɾ����ʱ�����������ʵ�֣� Ĭ�ϵ���ֱ��ɾ���� */
	virtual void requestDelete(const CVBF_Referenced* object);

protected:
    DeleteHandler(const DeleteHandler&);
    DeleteHandler operator = (const DeleteHandler&);

	unsigned int            _numFramesToRetainObjects; // ���󱻱�����֡��
	unsigned int            _currentFrameNumber;       // ��ǰ֡��
	OpenThreads::Mutex      _mutex;                    // 
	ObjectsToDeleteList     _objectsToDelete;          // ��ɾ������ָ���б�

};


#endif
