#ifndef OSG_SWITCH
#define OSG_SWITCH 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>

namespace osg {

// 开关节点：可以渲染或跳过指定的子节点。该节点的作用在于能够根据当前渲染的负荷有选择地
//          渲染子场景以实现渲染性能的均衡，或者在场景之间有选择的切换
//          可以设置子节点在不同时刻不同的状态，如信号灯
class IVBF_SGNodeGroupSwitch : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupSwitch(){}
	IVBF_SGNodeGroupSwitch(const IVBF_SGNodeGroupSwitch& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupSwitch(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

	// 设置/获取新加子节点的默认值
    virtual void setNewChildDefaultValue(bool value)=0; 
    virtual bool getNewChildDefaultValue() const=0; 

	// 添加子节点，并设置它的值
    virtual bool addChild( IVBF_SGNode *child )=0; 
    virtual bool addChild( IVBF_SGNode *child, bool value )=0; 

	// 插入子节点，并设置它的值
    virtual bool insertChild( unsigned int index, IVBF_SGNode *child )=0; 
    virtual bool insertChild( unsigned int index, IVBF_SGNode *child, bool value )=0; 
	
	// 移除子节点
    virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove)=0; 

	// 设置/获取索引为pos的子节点的值
    virtual void setValue(unsigned int pos,bool value)=0; 
    virtual bool getValue(unsigned int pos) const=0; 

	// 设置/获取子节点
    virtual void setChildValue(const IVBF_SGNode* child,bool value)=0;   
    virtual bool getChildValue(const IVBF_SGNode* child) const=0;

    // 设置所有的子节点（不）显示，并设置新的子节点的默认值为（不）显示
	virtual bool setAllChildrenOff()=0;
    virtual bool setAllChildrenOn()=0;
        
	// 设置单个节点显示，其他子节点都不显示
    virtual bool setSingleChildOn(unsigned int pos)=0;
   
    typedef std::vector<bool>   ValueList;
        
	// 设置/获取值的列表
    virtual void setValueList(const ValueList& values)=0;
    virtual const ValueList& getValueList() const=0;

};

class OSG_EXPORT Switch : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupSwitch>
{
    public :
        Switch();
        Switch(const Switch&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        virtual IVBF_SGNodeGroupSwitch* asSwitch() { return this; }
        virtual const IVBF_SGNodeGroupSwitch* asSwitch() const { return this; }

 //     META_Node(osg, Switch);
		virtual CVBF_Object* cloneType() const { return new Switch(); }
        virtual CVBF_Object* clone(const CopyOp& copyop) const { return new Switch(*this,copyop); }
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const IVBF_SGNodeGroupSwitch*>(obj)!=NULL; }
        virtual const char* className() const { return "Switch"; }

        virtual void traverse(NodeVisitor& nv);
        
		// 设置/获取新加子节点的默认值
        void setNewChildDefaultValue(bool value) { _newChildDefaultValue = value; }      
        bool getNewChildDefaultValue() const { return _newChildDefaultValue; }

		// 添加子节点，并设置它的值
        virtual bool addChild( IVBF_SGNode *child );
        virtual bool addChild( IVBF_SGNode *child, bool value );

		// 插入子节点，并设置它的值
        virtual bool insertChild( unsigned int index, IVBF_SGNode *child );
        virtual bool insertChild( unsigned int index, IVBF_SGNode *child, bool value );

		// 移除子节点
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);

		// 设置/获取索引为pos的子节点的值
        void setValue(unsigned int pos,bool value);
        bool getValue(unsigned int pos) const;

		// 设置/获取子节点
        void setChildValue(const IVBF_SGNode* child,bool value);      
        bool getChildValue(const IVBF_SGNode* child) const;

        // 设置所有的子节点（不）显示，并设置新的子节点的默认值为（不）显示
        bool setAllChildrenOff();
        bool setAllChildrenOn();
        
        // 设置单个节点显示，其他子节点都不显示
        bool setSingleChildOn(unsigned int pos);
        
		// 设置/获取值的列表
        void setValueList(const ValueList& values) { _values=values; }
        const ValueList& getValueList() const { return _values; }

        virtual BoundingSphere computeBound() const;

    protected : 
        virtual ~Switch() {}// IE可能错误

        bool        _newChildDefaultValue;
        ValueList   _values;
};

}

#endif
