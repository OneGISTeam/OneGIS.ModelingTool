#ifndef OSG_SWITCH
#define OSG_SWITCH 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>

namespace osg {

// ���ؽڵ㣺������Ⱦ������ָ�����ӽڵ㡣�ýڵ�����������ܹ����ݵ�ǰ��Ⱦ�ĸ�����ѡ���
//          ��Ⱦ�ӳ�����ʵ����Ⱦ���ܵľ��⣬�����ڳ���֮����ѡ����л�
//          ���������ӽڵ��ڲ�ͬʱ�̲�ͬ��״̬�����źŵ�
class IVBF_SGNodeGroupSwitch : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupSwitch(){}
	IVBF_SGNodeGroupSwitch(const IVBF_SGNodeGroupSwitch& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupSwitch(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

	// ����/��ȡ�¼��ӽڵ��Ĭ��ֵ
    virtual void setNewChildDefaultValue(bool value)=0; 
    virtual bool getNewChildDefaultValue() const=0; 

	// ����ӽڵ㣬����������ֵ
    virtual bool addChild( IVBF_SGNode *child )=0; 
    virtual bool addChild( IVBF_SGNode *child, bool value )=0; 

	// �����ӽڵ㣬����������ֵ
    virtual bool insertChild( unsigned int index, IVBF_SGNode *child )=0; 
    virtual bool insertChild( unsigned int index, IVBF_SGNode *child, bool value )=0; 
	
	// �Ƴ��ӽڵ�
    virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove)=0; 

	// ����/��ȡ����Ϊpos���ӽڵ��ֵ
    virtual void setValue(unsigned int pos,bool value)=0; 
    virtual bool getValue(unsigned int pos) const=0; 

	// ����/��ȡ�ӽڵ�
    virtual void setChildValue(const IVBF_SGNode* child,bool value)=0;   
    virtual bool getChildValue(const IVBF_SGNode* child) const=0;

    // �������е��ӽڵ㣨������ʾ���������µ��ӽڵ��Ĭ��ֵΪ��������ʾ
	virtual bool setAllChildrenOff()=0;
    virtual bool setAllChildrenOn()=0;
        
	// ���õ����ڵ���ʾ�������ӽڵ㶼����ʾ
    virtual bool setSingleChildOn(unsigned int pos)=0;
   
    typedef std::vector<bool>   ValueList;
        
	// ����/��ȡֵ���б�
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
        
		// ����/��ȡ�¼��ӽڵ��Ĭ��ֵ
        void setNewChildDefaultValue(bool value) { _newChildDefaultValue = value; }      
        bool getNewChildDefaultValue() const { return _newChildDefaultValue; }

		// ����ӽڵ㣬����������ֵ
        virtual bool addChild( IVBF_SGNode *child );
        virtual bool addChild( IVBF_SGNode *child, bool value );

		// �����ӽڵ㣬����������ֵ
        virtual bool insertChild( unsigned int index, IVBF_SGNode *child );
        virtual bool insertChild( unsigned int index, IVBF_SGNode *child, bool value );

		// �Ƴ��ӽڵ�
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);

		// ����/��ȡ����Ϊpos���ӽڵ��ֵ
        void setValue(unsigned int pos,bool value);
        bool getValue(unsigned int pos) const;

		// ����/��ȡ�ӽڵ�
        void setChildValue(const IVBF_SGNode* child,bool value);      
        bool getChildValue(const IVBF_SGNode* child) const;

        // �������е��ӽڵ㣨������ʾ���������µ��ӽڵ��Ĭ��ֵΪ��������ʾ
        bool setAllChildrenOff();
        bool setAllChildrenOn();
        
        // ���õ����ڵ���ʾ�������ӽڵ㶼����ʾ
        bool setSingleChildOn(unsigned int pos);
        
		// ����/��ȡֵ���б�
        void setValueList(const ValueList& values) { _values=values; }
        const ValueList& getValueList() const { return _values; }

        virtual BoundingSphere computeBound() const;

    protected : 
        virtual ~Switch() {}// IE���ܴ���

        bool        _newChildDefaultValue;
        ValueList   _values;
};

}

#endif
