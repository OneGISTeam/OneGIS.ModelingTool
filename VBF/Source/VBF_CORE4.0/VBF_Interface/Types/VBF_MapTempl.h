//-------------------------------------------------------------------------
//  �ļ����� VBF_MapTempl.h
//  ������   �����Զ����Mapģ����
//  ʱ�䣺   2004-12-17
//  ���ߣ�   ��Ө 
//-------------------------------------------------------------------------

#ifndef __VBF_MAP_TEMPL_H__
#define __VBF_MAP_TEMPL_H__

#include <VBF_Macros.h>
#include <VBF_STL.h>
#include <assert.h>


// �رձ�����ʾ��ģ�������������255���ַ�
#pragma warning(disable : 4786)


//------------------------------------------------------------------------
// ����ģ���ࣺCVBF_MapStringToPtrQueue
// ģ����˵��������ͬʱ�������CMapStringToPtr��CQueue(�Ƚ��ȳ�)�Ĺ���
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
	vector<string>   m_aKey;  //����������ģ��CQueue�ġ��Ƚ��ȳ���	             
};	

// ����������ɾ������ָ��
template <class VALUETYPE>
inline CVBF_MapStringToPtrQueue<VALUETYPE>::~CVBF_MapStringToPtrQueue() 
{
	RemoveAll();
}

// ��������ն���
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

// ����һ���ɾ����һ��������
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::Add(string key, VALUETYPE& value)
{
	if( m_nSize <= 0 ) return;

	VALUETYPE rValue; 
	if( Lookup( key, (VALUETYPE&)rValue ) ) return;

	// ����Ŀ���������涨��Ŀʱ��ɾ����һ����������Ŀ
	// ��������CQueue�ġ��Ƚ��ȳ����ص�
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

// ����һ������ص�һ��������(��ɾ����ָ��)
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

// ɾ��һ�����ɾ�������Ӧ��ָ��
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::RemoveKey(string key)
{
	map<string, VALUETYPE>::iterator pIter = find(key);
	if(pIter!=end()) erase(pIter);
}

// ɾ��һ���ɾ�������Ӧ��ָ��
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

// ɾ��һ������ظ����Ӧ��ָ��
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

// ����������һ��
template <class VALUETYPE>
inline void CVBF_MapStringToPtrQueue<VALUETYPE>::SetAt(string key, VALUETYPE newValue)
{
	assert(false);  // ��ֹ�ⲿ���øú���
}



#endif