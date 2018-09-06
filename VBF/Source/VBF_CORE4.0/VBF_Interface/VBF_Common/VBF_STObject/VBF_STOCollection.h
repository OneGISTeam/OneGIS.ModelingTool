//*******************************************************************
// FileName��  VBF_STOCollection.h
// Function��  ������ʱ�ն����м��ϵĶ���
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

	// ��ռ���
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
	// ���øü�����xml�ļ��еĽڵ��ʶ
	void SetTag(const std::string& sTag) { m_sTag = sTag; } 

	// �򼯺������һ������
	void Add(T* pType) { if(pType!=NULL) m_vType.push_back(pType); }

	// ��ȡ�����е�n������
	T* GetAt(int nIndex)		{ return (nIndex>=0 && nIndex<m_vType.size())? m_vType[nIndex] : NULL; }
	T* operator[](int nIndex)	{ return GetAt(nIndex); }

	// ��ȡ�����ж���ĸ���
	int Size() { return m_vType.size(); }
    void Reserve(int size) { m_vType.reserve(size); }

	// �����������ж���д�뵽ָ�����ڵ�
    virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false)
    {
        if(m_vType.size()==0) return;

        if(m_sTag.empty())
        {
            // ֱ��д�����ڵ���
            for(int i=0; i<m_vType.size(); i++)
            {
                m_vType[i]->WriteToXML(pElemParent, bSimpleFormat);
            }
        }
        else
        {
            // д��sTag�ڵ㣺<sTag>  </sTag>
            TiXmlElement* pElemTypes = new TiXmlElement( m_sTag );
            pElemParent->LinkEndChild( pElemTypes );

            for(int i=0; i<m_vType.size(); i++)
            {
                m_vType[i]->WriteToXML(pElemTypes, bSimpleFormat);
            }
        }
    }

	// ��ָ�����ڵ��ȡ���ж��󣬲���ӵ�������
    virtual void ReadFromXML(TiXmlElement* pElemParent, bool& bSimpleFormat)
    {
		if(NULL==pElemParent) return;

        // �ü���û�м��ϵ�xml��ʶ
		if(m_sTag.empty())
		{
			TiXmlElement* pElemType = pElemParent->FirstChildElement( T::GetTag() );
			while(pElemType)
			{
				T* pType = new T;
				pType->ReadFromXML(pElemType, bSimpleFormat);

                T* pMember = FindSameType(pType);
                if(pMember) // ͬһ�����Ѿ�����
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
		else  // �ü�����xml��ʶ
		{
			TiXmlElement* pElemTypes = pElemParent->FirstChildElement(m_sTag);
			if(NULL==pElemTypes) return;

			TiXmlElement* pElemType = pElemTypes->FirstChildElement( T::GetTag() );
			while(pElemType)
			{
                T* pType = new T;
				pType->ReadFromXML(pElemType, bSimpleFormat);

                T* pMember = FindSameType(pType);
                if(pMember) // ͬһ�����Ѿ�����
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

    T* FindSameType(T* pT) // ������ģ��ͬ��ģ�������ͬ����ͬID
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
                Add((T*)pT->Clone()); // �µģ�����
            }
            else
            {
                // �ɵģ���������
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
