//-------------------------------------------------------------------------
//  文件名： VBF_MapTempl.h
//  描述：   各种自定义的Map模板类
//  时间：   2004-12-17
//  作者：   杜莹 
//-------------------------------------------------------------------------

#ifndef __VBF_MAP_TEMPL_H__
#define __VBF_MAP_TEMPL_H__

#include <VBF_Macros.h>
#include <VBF_STL.h>
#include <assert.h>


// 关闭编译提示：模板类的类名超过255个字符
#pragma warning(disable : 4786)


//------------------------------------------------------------------------
// 定义模板类：CVBF_MapStringToPtrQueue
// 模板类说明：用于同时完成类似CMapStringToPtr和CQueue(先进先出)的工作
//------------------------------------------------------------------------
template <class VALUETYPE>
class CVBF_MapStringToPtrQueue : public map<string, VALUETYPE>
{	
public:
	CVBF_MapStringToPtrQueue(int nSize=1997) { SetSize(nSize); }
	virtual ~CVBF_MapStringToPtrQueue();

	void SetSize(int nSize) 
	{ 
		m_nSize = nSize; 
	//	InitHashTable(m_nSize);
		m_aKey.reserve(m_nSize);
	}

	void  Add(string key, VALUETYPE& value);
	void  Add(string key, VALUETYPE& value, VALUETYPE& valueDel);
	
	void  RemoveKey0(string key);
	void  RemoveKey0(string key, VALUETYPE& valueDel);
	void  SetAt(string key, VALUETYPE newValue);
	void  RemoveAll();
	bool  Lookup(string key, VALUETYPE& value);

protected:
	void  RemoveKey(string key);

protected:
	int              m_nSize; 
	vector<string>   m_aKey;  //该数组用来模拟CQueue的“先进先出”	             
};	

// 析构函数，删除所有指针
template <class VALUETYPE>
inline CVBF_MapStringToPtrQueue<VALUETYPE>::~CVBF_MapStringToPtrQueue() 
{
	RemoveAll();
}

// 描述：清空队列
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::RemoveAll()
{
	m_aKey.clear();
	
	for(map<string, VALUETYPE>::iterator pIter=begin(); pIter!=end(); pIter++)
	{
		string strKey = pIter->first;
		VALUETYPE pObj = pIter->second;
		SAFE_DELETE(pObj);	
	}
	clear();
}

// 增加一项，并删除第一个多余项
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::Add(string key, VALUETYPE& value)
{
	if( m_nSize <= 0 ) return;

	VALUETYPE rValue; 
	if( Lookup( key, (VALUETYPE&)rValue ) ) return;

	// 当项目个数超过规定数目时，删除第一个进来的项目
	// 这类似于CQueue的“先进先出”特点
	if( (int)m_aKey.size() >= m_nSize )
	{
		VALUETYPE valueDel = NULL;
		Lookup(m_aKey[0], (VALUETYPE&)valueDel);
		SAFE_DELETE(valueDel);

		map<string, VALUETYPE>::iterator pIter = find(m_aKey[0]);
		if(pIter!=end())
		{
			erase(pIter);
			m_aKey.erase( m_aKey.begin() );
		}
	}

	m_aKey.push_back( key );
	map<string, VALUETYPE>::insert( map<string, VALUETYPE>::value_type(key, value) );
}

// 增加一项，并返回第一个多余项(不删除其指针)
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::Add(string key, VALUETYPE& value, VALUETYPE& valueDel)
{
	valueDel = NULL;
	if( m_nSize <= 0 ) return;

	VALUETYPE rValue; 
	if( Lookup( key, (void*&)rValue ) ) return;

	if( (int)m_aKey.size() >= m_nSize )
	{
		Lookup( m_aKey[0], (void*&)valueDel );

		map<string, VALUETYPE>::iterator pIter = find(m_aKey[0]);
		if(pIter!=end())
		{
			erase(pIter);
			m_aKey.erase( m_aKey.begin() );
		}
	}

	m_aKey.Add(key);
	map<string, VALUETYPE>::insert( map<string, VALUETYPE>::value_type(key, value) );
}

// 删除一项，但不删除该项对应的指针
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::RemoveKey(string key)
{
	map<string, VALUETYPE>::iterator pIter = find(key);
	if(pIter!=end()) erase(pIter);
}

// 删除一项，并删除该项对应的指针
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::RemoveKey0(string key)
{
	if( m_nSize <= 0 ) return;

	VALUETYPE rValue; 
	if( !Lookup( key, (void*&)rValue ) ) return;
	
	SAFE_DELETE(rValue);
	RemoveKey(key);
	
	for(vector<string>::iterator pIter=m_aKey.begin(); pIter!=m_aKey.end(); pIter++)
	{
		if( strcmp(*pIter, key)==0 )
		{
			m_aKey.erase(pIter);
			break;
		}
	}
}

// 删除一项，并返回该项对应的指针
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::RemoveKey0(string key, VALUETYPE& valueDel)
{
	if( m_nSize <= 0 ) return;
	if( !Lookup(key, (void*&)valueDel) ) return;
	
	RemoveKey(key);

	for(vector<string>::iterator pIter=m_aKey.begin(); pIter!=m_aKey.end(); pIter++)
	{
		if( strcmp(*pIter, key)==0 )
		{
			m_aKey.erase(pIter);
			break;
		}
	}
}

template <class VALUETYPE>
inline bool CVBF_MapStringToPtrQueue<VALUETYPE>::Lookup(string key, VALUETYPE& value)
{
	map<string, VALUETYPE>::iterator pIter = find(key);
	if(pIter==end()) return false;

	value = pIter->second;
	return true;
}

// 描述：设置一项
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::SetAt(string key, VALUETYPE newValue)
{
	assert(false);  // 禁止外部调用该函数
}



#endif