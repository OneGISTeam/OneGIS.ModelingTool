//*******************************************************************
// FileName：  VBF_STOCollection.h
// Function：  多粒度时空对象中集合的定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_STO_COLLECTION_H__
#define __VBF_STO_COLLECTION_H__

#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>
#include <vector>
#include <VBF_Macros.h>

template<class T>
class CVBF_STOVector
{
public:
    CVBF_STOVector() 
	{
		m_sTag = "";
	}

    virtual ~CVBF_STOVector()
    {
        Clear(true);
    }

	// 清空集合
    void Clear(bool bFreeMemory=true)
	{
        if(bFreeMemory)
        {
            for(int i=0; i<m_vType.size(); i++)
            {
                SAFE_DELETE(m_vType[i]);
            }
        }
        m_vType.clear();
	}
    bool Remove(T* pType)
    {
        for(int i=0;i<m_vType.size();i++)
        {
            if(pType==m_vType[i])
            {
                m_vType.erase(m_vType.begin()+i);
                return true;
            }
        }
        return false;
    }
    void Remove(int idx)
    {
        if(idx<0 || idx>=m_vType.size()) return;
        m_vType.erase(m_vType.begin()+idx);
    }
	// 设置该集合在xml文件中的节点标识
	void SetTag(const std::string& sTag) { m_sTag = sTag; } 

	// 向集合中添加一个对象
	void Add(T* pType) { if(pType!=NULL) m_vType.push_back(pType); }

	// 获取集合中第n个对象
	T* GetAt(int nIndex)		{ return (nIndex>=0 && nIndex<m_vType.size())? m_vType[nIndex] : NULL; }
	T* operator[](int nIndex)	{ return GetAt(nIndex); }

	// 获取集合中对象的个数
	int Size() { return m_vType.size(); }
    void Reserve(int size) { m_vType.reserve(size); }

	// 将集合中所有对象写入到指定父节点
    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false)
    {
        if(m_vType.size()==0) return;

        if(m_sTag.empty())
        {
            // 直接写到父节点上
            for(int i=0; i<m_vType.size(); i++)
            {
                m_vType[i]->WriteToXML(pElemParent, bSimpleFormat);
            }
        }
        else
        {
            // 写入sTag节点：<sTag>  </sTag>
            TiXmlElement* pElemTypes = new TiXmlElement( m_sTag );
            pElemParent->LinkEndChild( pElemTypes );

            for(int i=0; i<m_vType.size(); i++)
            {
                m_vType[i]->WriteToXML(pElemTypes, bSimpleFormat);
            }
        }
    }

	// 从指定父节点读取所有对象，并添加到集合中
    virtual void ReadFromXML(TiXmlElement* pElemParent, bool& bSimpleFormat)
    {
		if(NULL==pElemParent) return;

        // 该集合没有集合的xml标识
		if(m_sTag.empty())
		{
			TiXmlElement* pElemType = pElemParent->FirstChildElement( T::GetTag() );
			while(pElemType)
			{
				T* pType = new T;
				pType->ReadFromXML(pElemType, bSimpleFormat);

                T* pMember = FindSameType(pType);
                if(pMember) // 同一对象已经存在
                {
                    pMember->ReadFromXML(pElemType, bSimpleFormat);
                    SAFE_DELETE(pType);
                }
                else
                {
                    Add(pType);
                }

				pElemType = pElemType->NextSiblingElement( T::GetTag() );
			}
		}
		else  // 该集合有xml标识
		{
			TiXmlElement* pElemTypes = pElemParent->FirstChildElement(m_sTag);
			if(NULL==pElemTypes) return;

			TiXmlElement* pElemType = pElemTypes->FirstChildElement( T::GetTag() );
			while(pElemType)
			{
                T* pType = new T;
				pType->ReadFromXML(pElemType, bSimpleFormat);

                T* pMember = FindSameType(pType);
                if(pMember) // 同一对象已经存在
                {
                    pMember->ReadFromXML(pElemType, bSimpleFormat);
                    SAFE_DELETE(pType);
                }
                else
                {
                    Add(pType);
                }


				pElemType = pElemType->NextSiblingElement( T::GetTag() );
			}
		}
	}

    T* FindSameType(T* pT) // 查找与模板同类的，可能是同名、同ID
    {
        for(int i=0; i<m_vType.size(); i++)
        {
            if(m_vType[i]->IsSameType(pT))return m_vType[i];
        }
        return NULL;
    }
    virtual void Clone(CVBF_STOVector<T>& vTemplate)
    {
        m_vType.clear();
        m_vType.reserve(vTemplate.Size());
        for(int i=0;i<vTemplate.Size();i++)
        {
            T* pT = vTemplate.GetAt(i);
            Add((T*)pT->Clone());
        }

    }
    virtual void FilledByTemplate(CVBF_STOVector<T>& vTemplate)
    {
        for(int i=0;i<vTemplate.Size();i++)
        {
            T* pT = vTemplate.GetAt(i);
            if(pT==NULL) continue;

            T* pMember = FindSameType(pT);
            if(pMember==NULL)
            {
                Add((T*)pT->Clone()); // 新的，加入
            }
            else
            {
                // 旧的，补充或更新
                pMember->FilledByTemplate(pT);
            }
        }
    }

    T* Find(const std::string& strName)
    {
        for(int i=0;i<Size();i++)
        {
            T* pT = GetAt(i);
            if(pT->GetName()==strName) return pT;
        }
        return NULL;
    }
    T* FindByID(const std::string& strID)
    {
        for(int i=0;i<Size();i++)
        {
            T* pT = GetAt(i);
            if(pT->GetID()==strID) return pT;
        }
        return NULL;
    }
    void Delete(const std::string& strName)
    {
        for(int i=0;i<Size();i++)
        {
            T* pT = GetAt(i);
            if(pT->GetName()==strName)
            {
                Remove(i);
                SAFE_DELETE(pT);
                return;
            }
        }
    }
    T* FindByType(const std::string& strType)
    {
        for(int i=0;i<Size();i++)
        {
            T* pT = GetAt(i);
            if(pT->GetType()==strType) return pT;
        }
        return NULL;
    }
protected:
    std::string			m_sTag;
    std::vector<T*>		m_vType;
};
#endif
