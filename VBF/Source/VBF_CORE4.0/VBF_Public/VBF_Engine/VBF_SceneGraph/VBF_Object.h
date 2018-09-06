#ifndef VBF_OBJECT_H
#define VBF_OBJECT_H 1

#include <VBF_Macros.h>
#include <VBF_Base/VBF_Referenced.h>

#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_Notify.h>

#include <string>
//#include <vector>

namespace osg {

class State;
class UserDataContainer;

#define _ADDQUOTES(def) #def
#define ADDQUOTES(def) _ADDQUOTES(def)


template<typename T>
T* clone(const T* t, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
{
    if (t==NULL)
    {
        OSG_WARN<<"Warning: osg::clone(const T*, osg::CopyOp&) passed null object to clone, returning NULL."<<std::endl;
        return 0;
    }

	ref_ptr<osg::CVBF_Object> obj = t->clone(copyop);
	T* ptr = dynamic_cast<T*>(obj.get());
	if (ptr==NULL)
	{
		OSG_WARN<<"Warning: osg::clone(const T*, osg::CopyOp&) cloned object not of type T, returning NULL."<<std::endl;
		return 0;
	}
	
	obj.release();
	return ptr;
}

template<typename T>
T* clone(const T* t, const std::string& name, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
{
    T* newObject = osg::clone(t, copyop);
	if(newObject==NULL)
    {
        OSG_WARN<<"警告: osg::clone(const T*, const std::string&, const osg::CopyOp) 传入空对象，无法拷贝."<<std::endl;
        return 0;
    }

    newObject->setName(name);
    return newObject; 
}

template<typename T>
T* cloneType(const T* t)
{
    if (t==NULL)
    {
            OSG_WARN<<"警告: osg::cloneType(const T*) 传入空对象，无法拷贝."<<std::endl;
    return 0;
    }

    ref_ptr<osg::CVBF_Object> obj = t->cloneType();
    T* ptr = dynamic_cast<T*>(obj.get());
    if (ptr==NULL)
    {
            OSG_WARN<<"警告: osg::cloneType(const T*) 被拷贝对象不是类型T, 无法拷贝."<<std::endl;
            return 0;
    }

    obj.release();
    return ptr;
}


/** 对象基类（对象支持IO、Clone、引用计数 ）。
    Based on GOF Composite, Prototype and Template Method patterns.
*/


/** META_Object 宏定义了标准的clone、isSameKindAs、className等方法。便于Object的子类实现纯虚函数。*/

#define META_Object(library,name) \
        virtual osg::CVBF_Object* cloneType() const { return new name (); } \
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* libraryName() const { return #library; }\
        virtual const char* className() const { return #name; }



class OSG_EXPORT CVBF_Object : public ::CVBF_Referenced
{
public:

	// 1、与构造函数有关的内容
    CVBF_Object();
    CVBF_Object(bool threadSafeRefUnref);
	CVBF_Object(const CVBF_Object&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

	// 2、与基本信息有关的内容
	virtual CVBF_Object* cloneType() const = 0;
	virtual CVBF_Object* clone(const CopyOp&) const = 0;// 克隆一个对象，与本对象数据相同（由CopyOp决定）
    virtual bool isSameKindAs(const CVBF_Object*) const;
	virtual const char* libraryName() const = 0;// 返回所在的库的名字
	virtual const char* className() const = 0;  // 返回类的名字

	// 2.1、线程安全性

	/** 设置是否使用mutex确保ref()和unref()的线程安全性。*/
	virtual void setThreadSafeRefUnref(bool threadSafe);

	// 2.2、类型标识
	/** 为了能够快速、精确并能分类的判断Object的类型，采用DWORD（32位）对每一个Object类型进行编码。
	主要用于优化代码结构，如Visitor、CopyOp、asXXX。*/


public:
    /*
	DWORD GetTypeID() { return m_dwTypeID; }// 获取类型标识

	bool IsType(DWORD dwTypeID) // 该对象是否是指定的类型
	{
		return (m_dwTypeID == (m_dwTypeID & dwTypeID ));
	}

	bool IsType(DWORD dwTypeID) const // 该对象是否是指定的类型
	{
        return (m_dwTypeID == (m_dwTypeID & dwTypeID ));
	}

	template<class TYPE>
	TYPE* AsType(DWORD dwTypeID)		// 转换为指定的类型(显式类型转换)
	{
		if(IsType(dwTypeID)) return (TYPE*)this;
		return NULL;
	}

	template<class TYPE>
	const TYPE* AsType(DWORD dwTypeID)	const	// 转换为指定的类型(显式类型转换)
	{
		if(IsType(dwTypeID)) return (TYPE*)this;
		return NULL;
	}
    */


	// 3、与对象名称有关的内容

	/** 设置/获取对象的名字，使用C++ style string。*/
    virtual void setName( const std::string& sName ); //
    virtual const std::string& getName() const;

	/** 设置对象的名字，使用C style string.*/
    virtual void setName( const char* szName );


	// 4、与数据类型（静态/动态）有关的内容
	//    为了性能没有为线程的安全增设内存锁，因此，为了保证对场景的修改不与筛选和绘制发生线程冲突，
	//    可将在筛选绘制过程中可能修改的对象设置为DYNAMIC。系统保证DYNAMIC的筛选绘制不与Update、Event的遍历处理发生线程冲突
	enum DataVariance
	{
		DYNAMIC,    // 在对象的生命期中数据值会发生变化
		STATIC,     // 在对象的整个生命期中数据值不变
		UNSPECIFIED // 还未被设定
	};

	/** 设置/获取对象的数据变化。（数据变化类型）*/
    virtual void setDataVariance(DataVariance dv);
    virtual DataVariance getDataVariance() const;

	/** 被Optimizer调用， 对可能为DYNAMIC的对象，设置DYNAMIC对象属性.*/
    virtual void computeDataVariance();


	// 5、与用户数据有关的内容

	/** 设置/获取与对象关联的UserDataContainer*/
	void setUserDataContainer(osg::UserDataContainer* udc);
    osg::UserDataContainer* getUserDataContainer();
    const osg::UserDataContainer* getUserDataContainer() const;

	/** 便捷方式返回UserDataContainer, 如果不存在创建并设置DefaultUserDataContainer。*/
	osg::UserDataContainer* getOrCreateUserDataContainer();

	/** 设置用户数据, 数据必须是Referenced的子类以允许自动内存处理。如果数据不是Referenced的子类，创建一个适配对象。 */
	virtual void setUserData(CVBF_Referenced* obj);

	/** 获取用户数据。*/
	virtual CVBF_Referenced* getUserData();
	virtual const CVBF_Referenced* getUserData() const;


	/** 便捷的方法把UserObject转化到osg::TemplateValueObject<TYPE>并获得TYPE类型的value，并作为命名的用户对象加入到用户对象列表。。
	* 注意：TYPE不需要是Object的子类class Vec2f、Vec3f、Vec4f、Vec2d、Vec3d、Vec4d、Quat、Plane、Matrixf、Matrixd;*/
	template<typename TYPE>
	bool getUserValue(const std::string& name, TYPE& value) const;

	template<typename TYPE>
	void setUserValue(const std::string& name, const TYPE& value);

	// 6、与GLObject有关的内容

    // 改变每个上下文GLObject buffers 为指定大小。
    virtual void resizeGLObjectBuffers(unsigned int /*maxSize*/);
	
    // 如果State非0, 释放特定GC的OpenGL对象，否则释放所有GC的OpenGL对象。 //!!!注意：State需要优化掉，改为unsigned int contextID*/
    virtual void releaseGLObjects(osg::State* = 0) const;

protected:
	/** 保护类型的析构函数使得对象不能被直接删除，而只能通过引用计数,防止Object还在被引用时删除。*/
	~CVBF_Object();

protected:

        DataVariance                m_eDataVariance;		// 数据变化类型
        osg::UserDataContainer*     m_pUserDataContainer;	// 用户数据
        DWORD                       m_dwTypeID;                 // 类型标识
        std::string                 m_sName;			// 名称

private:
    CVBF_Object& operator = (const CVBF_Object&); //不允许任何拷贝操作
};

}



#include <VBF_Engine/VBF_SceneGraph/UserDataContainer>

#include <VBF_Engine/VBF_SceneGraph/ValueObject>


template<typename TYPE>
bool osg::CVBF_Object::getUserValue(const std::string& name, TYPE& value) const
{
    const osg::UserDataContainer* pUDC = dynamic_cast<const osg::UserDataContainer*>(this);
    if (!pUDC) pUDC = m_pUserDataContainer;

    typedef TemplateValueObject<TYPE> UserValueObject;
    const UserValueObject* uvo = pUDC ? dynamic_cast<const UserValueObject*>(pUDC->getUserObject(name)) : 0;
    if (uvo==NULL) return false;

    value = uvo->getValue();
    return true;
}


template<typename TYPE>
void osg::CVBF_Object::setUserValue(const std::string& name, const TYPE& value)
{
    typedef TemplateValueObject<TYPE> UserValueObject;

    osg::UserDataContainer* udc = dynamic_cast<osg::UserDataContainer*>(this);
    if (!udc)
    {
        getOrCreateUserDataContainer();
        udc = m_pUserDataContainer;
    }

    unsigned int i = udc->getUserObjectIndex(name);
    if (i<udc->getNumUserObjects()) udc->setUserObject(i, new UserValueObject(name,value));
    else udc->addUserObject(new UserValueObject(name,value));
}

#endif
