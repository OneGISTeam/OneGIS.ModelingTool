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
        OSG_WARN<<"����: osg::clone(const T*, const std::string&, const osg::CopyOp) ����ն����޷�����."<<std::endl;
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
            OSG_WARN<<"����: osg::cloneType(const T*) ����ն����޷�����."<<std::endl;
    return 0;
    }

    ref_ptr<osg::CVBF_Object> obj = t->cloneType();
    T* ptr = dynamic_cast<T*>(obj.get());
    if (ptr==NULL)
    {
            OSG_WARN<<"����: osg::cloneType(const T*) ����������������T, �޷�����."<<std::endl;
            return 0;
    }

    obj.release();
    return ptr;
}


/** ������ࣨ����֧��IO��Clone�����ü��� ����
    Based on GOF Composite, Prototype and Template Method patterns.
*/


/** META_Object �궨���˱�׼��clone��isSameKindAs��className�ȷ���������Object������ʵ�ִ��麯����*/

#define META_Object(library,name) \
        virtual osg::CVBF_Object* cloneType() const { return new name (); } \
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* libraryName() const { return #library; }\
        virtual const char* className() const { return #name; }



class OSG_EXPORT CVBF_Object : public ::CVBF_Referenced
{
public:

	// 1���빹�캯���йص�����
    CVBF_Object();
    CVBF_Object(bool threadSafeRefUnref);
	CVBF_Object(const CVBF_Object&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

	// 2���������Ϣ�йص�����
	virtual CVBF_Object* cloneType() const = 0;
	virtual CVBF_Object* clone(const CopyOp&) const = 0;// ��¡һ�������뱾����������ͬ����CopyOp������
    virtual bool isSameKindAs(const CVBF_Object*) const;
	virtual const char* libraryName() const = 0;// �������ڵĿ������
	virtual const char* className() const = 0;  // �����������

	// 2.1���̰߳�ȫ��

	/** �����Ƿ�ʹ��mutexȷ��ref()��unref()���̰߳�ȫ�ԡ�*/
	virtual void setThreadSafeRefUnref(bool threadSafe);

	// 2.2�����ͱ�ʶ
	/** Ϊ���ܹ����١���ȷ���ܷ�����ж�Object�����ͣ�����DWORD��32λ����ÿһ��Object���ͽ��б��롣
	��Ҫ�����Ż�����ṹ����Visitor��CopyOp��asXXX��*/


public:
    /*
	DWORD GetTypeID() { return m_dwTypeID; }// ��ȡ���ͱ�ʶ

	bool IsType(DWORD dwTypeID) // �ö����Ƿ���ָ��������
	{
		return (m_dwTypeID == (m_dwTypeID & dwTypeID ));
	}

	bool IsType(DWORD dwTypeID) const // �ö����Ƿ���ָ��������
	{
        return (m_dwTypeID == (m_dwTypeID & dwTypeID ));
	}

	template<class TYPE>
	TYPE* AsType(DWORD dwTypeID)		// ת��Ϊָ��������(��ʽ����ת��)
	{
		if(IsType(dwTypeID)) return (TYPE*)this;
		return NULL;
	}

	template<class TYPE>
	const TYPE* AsType(DWORD dwTypeID)	const	// ת��Ϊָ��������(��ʽ����ת��)
	{
		if(IsType(dwTypeID)) return (TYPE*)this;
		return NULL;
	}
    */


	// 3������������йص�����

	/** ����/��ȡ��������֣�ʹ��C++ style string��*/
    virtual void setName( const std::string& sName ); //
    virtual const std::string& getName() const;

	/** ���ö�������֣�ʹ��C style string.*/
    virtual void setName( const char* szName );


	// 4�����������ͣ���̬/��̬���йص�����
	//    Ϊ������û��Ϊ�̵߳İ�ȫ�����ڴ�������ˣ�Ϊ�˱�֤�Գ������޸Ĳ���ɸѡ�ͻ��Ʒ����̳߳�ͻ��
	//    �ɽ���ɸѡ���ƹ����п����޸ĵĶ�������ΪDYNAMIC��ϵͳ��֤DYNAMIC��ɸѡ���Ʋ���Update��Event�ı����������̳߳�ͻ
	enum DataVariance
	{
		DYNAMIC,    // �ڶ����������������ֵ�ᷢ���仯
		STATIC,     // �ڶ��������������������ֵ����
		UNSPECIFIED // ��δ���趨
	};

	/** ����/��ȡ��������ݱ仯�������ݱ仯���ͣ�*/
    virtual void setDataVariance(DataVariance dv);
    virtual DataVariance getDataVariance() const;

	/** ��Optimizer���ã� �Կ���ΪDYNAMIC�Ķ�������DYNAMIC��������.*/
    virtual void computeDataVariance();


	// 5�����û������йص�����

	/** ����/��ȡ����������UserDataContainer*/
	void setUserDataContainer(osg::UserDataContainer* udc);
    osg::UserDataContainer* getUserDataContainer();
    const osg::UserDataContainer* getUserDataContainer() const;

	/** ��ݷ�ʽ����UserDataContainer, ��������ڴ���������DefaultUserDataContainer��*/
	osg::UserDataContainer* getOrCreateUserDataContainer();

	/** �����û�����, ���ݱ�����Referenced�������������Զ��ڴ洦��������ݲ���Referenced�����࣬����һ��������� */
	virtual void setUserData(CVBF_Referenced* obj);

	/** ��ȡ�û����ݡ�*/
	virtual CVBF_Referenced* getUserData();
	virtual const CVBF_Referenced* getUserData() const;


	/** ��ݵķ�����UserObjectת����osg::TemplateValueObject<TYPE>�����TYPE���͵�value������Ϊ�������û�������뵽�û������б���
	* ע�⣺TYPE����Ҫ��Object������class Vec2f��Vec3f��Vec4f��Vec2d��Vec3d��Vec4d��Quat��Plane��Matrixf��Matrixd;*/
	template<typename TYPE>
	bool getUserValue(const std::string& name, TYPE& value) const;

	template<typename TYPE>
	void setUserValue(const std::string& name, const TYPE& value);

	// 6����GLObject�йص�����

    // �ı�ÿ��������GLObject buffers Ϊָ����С��
    virtual void resizeGLObjectBuffers(unsigned int /*maxSize*/);
	
    // ���State��0, �ͷ��ض�GC��OpenGL���󣬷����ͷ�����GC��OpenGL���� //!!!ע�⣺State��Ҫ�Ż�������Ϊunsigned int contextID*/
    virtual void releaseGLObjects(osg::State* = 0) const;

protected:
	/** �������͵���������ʹ�ö����ܱ�ֱ��ɾ������ֻ��ͨ�����ü���,��ֹObject���ڱ�����ʱɾ����*/
	~CVBF_Object();

protected:

        DataVariance                m_eDataVariance;		// ���ݱ仯����
        osg::UserDataContainer*     m_pUserDataContainer;	// �û�����
        DWORD                       m_dwTypeID;                 // ���ͱ�ʶ
        std::string                 m_sName;			// ����

private:
    CVBF_Object& operator = (const CVBF_Object&); //�������κο�������
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
