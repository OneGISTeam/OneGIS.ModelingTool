//*******************************************************************
// FileName：  VBF_STObjectRelation.h
// Function：  多粒度时空对象的关系定义
// Author:     
// Date:       2017-10-21
//*******************************************************************

#ifndef __VBF_ST_OBJECT_RELATION_H__
#define __VBF_ST_OBJECT_RELATION_H__

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_STObject/VBF_STOParameter.h>
#include <VBF_Common/VBF_XML/tinyxml.h>
#include <string>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Common/VBF_STObject/VBF_LifeTime.h>

#include <VBF_Common/VBF_STObject/VBF_STOCollection.h>

#include "VBF_Common/VBF_STObject/VBF_STObject.h"

typedef CVBF_STOVector<CVBF_STObjectParameter> CVBF_STONodeParameters;
typedef CVBF_STOVector<CVBF_STObjectParameter> CVBF_STOEdgeParameters;
typedef CVBF_STOVector<CVBF_STObjectParameter> CVBF_STORingParameters;


// 对象关系的类模板
class VBF_STOBJECT_EXPORT CVBF_ObjectRelationClass
{
public:
	CVBF_ObjectRelationClass();
    CVBF_ObjectRelationClass(const std::string& sName,const std::string& sID);

	const std::string& GetName() { return m_sName; }
    const std::string& GetID()	 { return m_sID; }
    
    CVBF_STONodeParameters& NodeParameters() { return m_NodeParameters; }
    CVBF_STOEdgeParameters& EdgeParameters() { return m_EdgeParameters; }
    CVBF_STORingParameters& RingParameters() { return m_RingParameters; }

	void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemRelationClass, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "ObjectRelationClass"; }

private:
    std::string					m_sName;    // 名称
    std::string					m_sID;      // ID
    CVBF_STONodeParameters		m_NodeParameters;
    CVBF_STOEdgeParameters		m_EdgeParameters;
    CVBF_STORingParameters		m_RingParameters;
};


// 节点
class VBF_STOBJECT_EXPORT CVBF_STONode
{
public:
    CVBF_STONode();
    CVBF_STONode(const std::string& sID);

    void SetID(const std::string& sID)	{ m_sID = sID; }
	const std::string& GetID()			{ return m_sID; }

	void SetRefObject(CVBF_STObject* pObject) {m_pRefObject = pObject;};
	CVBF_STObject* GetRefObject() {return m_pRefObject;};

    CVBF_STOParameterValues& ParameterValues()	{ return m_ParameterValues; }

	virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemNode, bool& bSimpleFormat);

    bool IsSameType(CVBF_STONode* pNode);
    CVBF_STONode* Clone();
    void FilledByTemplate(CVBF_STONode* pNode);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Node"; }

    std::string GetParameterValue(const std::string& strName);
    void SetParameterValue(const std::string& strName,const std::string& strValue);

private:
    std::string					m_sID;      // ID
    CVBF_STOParameterValues		m_ParameterValues;
	CVBF_STObject* m_pRefObject;
};


// 改名为带参数的Vector
template<class T>
class CVBF_STORelationElementVector : public CVBF_STOVector<T>
{
public:
    CVBF_STORelationElementVector():CVBF_STOVector<T>()
    {
        m_pParameters = NULL;
    }
    void SetParameters(CVBF_STOVector<CVBF_STObjectParameter>& Parameters )
    {
        m_pParameters = &Parameters;
    }
protected:
    CVBF_STOVector<CVBF_STObjectParameter>* m_pParameters;
};



typedef CVBF_STORelationElementVector<CVBF_STONode> CVBF_STONodes;



// 半边，单向边
class VBF_STOBJECT_EXPORT CVBF_STOHalfEdge
{
public:
    CVBF_STOHalfEdge();
    
    void SetNode1ID(const std::string& sNode1ID)	{ m_sNode1ID = sNode1ID; }
    void SetNode2ID(const std::string& sNode2ID)	{ m_sNode2ID = sNode2ID; }
	void SetLifeTime(CVBF_LifeTime* pLifeTime)		{ m_ipLifeTime = pLifeTime; }
	
    const std::string& GetNode1ID()		{ return m_sNode1ID; }
    const std::string& GetNode2ID()		{ return m_sNode2ID; }
	CVBF_LifeTime*     GetLifeTime()	{ return m_ipLifeTime.get(); }

	CVBF_STOParameterValues& ParameterValues()	{ return m_ParameterValues; }

	virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemHalfEdge, bool& bSimpleFormat);

    bool IsSameType(CVBF_STOHalfEdge* pEdge);
    CVBF_STOHalfEdge* Clone();
    void FilledByTemplate(CVBF_STOHalfEdge* pHalfEdge);


	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "HalfEdge"; }
    std::string GetParameterValue(const std::string& strName);
    void SetParameterValue(const std::string& strName,const std::string& strValue);

protected:
    std::string					m_sNode1ID;   
    std::string					m_sNode2ID;
    ref_ptr<CVBF_LifeTime>		m_ipLifeTime;
    CVBF_STOParameterValues		m_ParameterValues;
    std::string					m_sTag;
};
//typedef CVBF_STORelationElementVector<CVBF_STOHalfEdge> CVBF_STOHalfEdgeVector;
class CVBF_STOHalfEdgeVector:public CVBF_STORelationElementVector<CVBF_STOHalfEdge>
{
public:
    CVBF_STOHalfEdge* FindByID(const std::string& strNode1ID,const std::string& strNode2ID)
    {
        for(int i=0;i<Size();i++)
        {
            CVBF_STOHalfEdge* pHalfEdge = GetAt(i);
            if(pHalfEdge->GetNode1ID()==strNode1ID && pHalfEdge->GetNode2ID()==strNode2ID) return pHalfEdge;
        }
        return NULL;
    }
};

// 边，双向边
class VBF_STOBJECT_EXPORT CVBF_STOEdge : public CVBF_STOHalfEdge
{
public:
    CVBF_STOEdge();

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Edge"; }
};
typedef CVBF_STORelationElementVector<CVBF_STOEdge> CVBF_STOEdgeVector;


// 多边，从一点出发的多个半边
class VBF_STOBJECT_EXPORT CVBF_STOMultiEdge
{
public:
    CVBF_STOMultiEdge();
   
	void SetNode1ID(const std::string& sNode1ID)	{ m_sNode1ID = sNode1ID; }
    void SetLifeTime(CVBF_LifeTime* pLifeTime)		{ m_ipLifeTime = pLifeTime; }

	const std::string& GetNode1ID()			{ return m_sNode1ID; }
	CVBF_LifeTime*     GetLifeTime()		{ return m_ipLifeTime.get(); }

    CVBF_STOHalfEdgeVector& HalfEdges()		{ return m_HalfEdges;}

	virtual void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	virtual void ReadFromXML(TiXmlElement* pElemMultiEdge, bool& bSimpleFormat);

    bool IsSameType(CVBF_STOMultiEdge* pEdge);
    CVBF_STOMultiEdge* Clone();
    void FilledByTemplate(CVBF_STOMultiEdge* pMultiEdge);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "MultiEdge"; }

private:
    std::string					m_sNode1ID;      // ID
    ref_ptr<CVBF_LifeTime>		m_ipLifeTime;
    CVBF_STOHalfEdgeVector		m_HalfEdges;
};
typedef CVBF_STORelationElementVector<CVBF_STOMultiEdge> CVBF_STOMultiEdgeVector;

class VBF_STOBJECT_EXPORT CVBF_STORing
{
public:
    CVBF_STORing();
    CVBF_STORing(const std::string& sID);

    const std::string& GetID() { return m_sID; }
    void SetLifeTime(CVBF_LifeTime* pLifeTime)	{ m_ipLifeTime = pLifeTime; }
	CVBF_LifeTime* GetLifeTime()				{ return m_ipLifeTime.get(); }

    CVBF_STOParameterValues& ParameterValues()	{ return m_ParameterValues; }

	void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemRing, bool& bSimpleFormat);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "Ring"; }


    bool IsSameType(CVBF_STORing* pRing);
    CVBF_STORing* Clone();
    void FilledByTemplate(CVBF_STORing* pRing);


private:
    std::string		m_sID;      // ID
    ref_ptr<CVBF_LifeTime>		m_ipLifeTime;
    CVBF_STOParameterValues		m_ParameterValues;

};
typedef CVBF_STORelationElementVector<CVBF_STORing> CVBF_STORings;


class VBF_STOBJECT_EXPORT CVBF_STOEdges
{
public:
    CVBF_STOEdges();
    
    CVBF_STOHalfEdgeVector&  HalfEdges()	{ return m_HalfEdges;}
    CVBF_STOEdgeVector&		 Edges()		{ return m_Edges;}
    CVBF_STOMultiEdgeVector& MultiEdges()	{ return m_MultiEdges;}

	void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemParent, bool& bSimpleFormat);

    void SetParameters(CVBF_STOVector<CVBF_STObjectParameter>& Parameters );

private:
    CVBF_STOHalfEdgeVector		m_HalfEdges;
    CVBF_STOEdgeVector			m_Edges;
    CVBF_STOMultiEdgeVector		m_MultiEdges;
};


// 对象关系
class VBF_STOBJECT_EXPORT CVBF_STObjectRelation
{
public:
    CVBF_STObjectRelation();
    void SetRelationClass(CVBF_ObjectRelationClass* pRelationClass);
   
    CVBF_STONodes& Nodes()	{ return m_Nodes; }
	CVBF_STONode* FindNode(const CVBF_STObject* pObject);

    CVBF_STOEdges& Edges()	{ return m_Edges; }
	CVBF_STOEdges& FindEdge( CVBF_STONode* pNode);

    CVBF_STORings& Rings()	{ return m_Rings; }

    void SetName(const std::string& sName)			{ m_sName = sName; }
    void SetID(const std::string& sID)				{ m_sID = sID; }
    void SetClassID(const std::string& sClassID)	{ m_sClassID = sClassID; }
    void SetLifeTime(CVBF_LifeTime* pLifeTime)		{ m_ipLifeTime = pLifeTime; }

	const std::string& GetName()		{ return m_sName; }
    const std::string& GetID()			{ return m_sID; }
    const std::string& GetClassID()		{ return m_sClassID; }
    CVBF_LifeTime*     GetLifeTime()	{ return m_ipLifeTime.get(); }

	void WriteToXML(TiXmlElement* pElemParent, bool bSimpleFormat=false);
	void ReadFromXML(TiXmlElement* pElemRelation, bool& bSimpleFormat);

    bool IsSameType(CVBF_STObjectRelation* pRelation);
    CVBF_STObjectRelation* Clone();
    void FilledByTemplate(CVBF_STObjectRelation* pRelation);

	// 静态函数：获取该类的xml标识
	static std::string GetTag() { return "ObjectRelation"; }

private:
	std::string		m_sName;    // 名称
    std::string		m_sClassID; // 类别
    std::string		m_sID;      // ID

    CVBF_STONodes	m_Nodes;	// 节点集合
    CVBF_STOEdges	m_Edges;	// 边集合
    CVBF_STORings	m_Rings;	// 环集合

    ref_ptr<CVBF_LifeTime> m_ipLifeTime; // 生命期

};

typedef CVBF_STOVector<CVBF_STObjectRelation> CVBF_STObjectRelations;

#endif
