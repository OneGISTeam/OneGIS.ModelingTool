#ifndef IVBF_SG_NODE_GEOMETRY_H
#define IVBF_SG_NODE_GEOMETRY_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>

namespace osg {



class IVBF_SGNodeGeometry : public IVBF_SGNode
{
public:
	typedef std::vector< ref_ptr<Drawable> > DrawableList;
public:
	IVBF_SGNodeGeometry(){}
	IVBF_SGNodeGeometry(const IVBF_SGNodeGeometry& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNode(cs,copyop) {}

	explicit IVBF_SGNodeGeometry(bool threadSafeRefUnref):IVBF_SGNode(threadSafeRefUnref){}
	
	
	virtual bool addDrawable( Drawable *drawable )=0;

    /** �Ƴ�Drawable��������Ƴ��˷���true�����򷵻�false��*/
    virtual bool removeDrawable( Drawable *drawable )=0;

    /** �Ƴ�ָ��λ�õ�Drawable�����������һ�����Ƴ��˷���true�����򷵻�false��*/
    virtual bool removeDrawables(unsigned int i,unsigned int numDrawablesToRemove=1)=0;

    /** ��һ��Drawable�滻��һ��Drawable�� ��ͬ��setDrawable(getDrawableIndex(origDraw),newDraw)  */
    virtual bool replaceDrawable( Drawable *origDraw, Drawable *newDraw )=0;

    /** ��ָ����λ��������Drawable������ԭ����Drawable�����ü����������µ�drawable�����ü��������ð�Χ��dirty��־
        * ���i�����ԭ����Drawableû�ҵ����򷵻� false��������µ�Drawable ��
        * ����µ�DrawableΪ�գ��򷵻�false�����Ƴ�ԭ����Drawable��
    */
    virtual bool setDrawable( unsigned int i, Drawable* drawable )=0;

    /** ��ȡDrawable�ĸ��� */
    virtual unsigned int getNumDrawables() const =0;

	/** ��ȡָ��λ�õ�Drawable��ע�⣺i���ܳ��磩 */
	virtual Drawable* getDrawable( unsigned int i ) =0;
	virtual const Drawable* getDrawable( unsigned int i ) const =0;

    /** �Ƿ����ָ����Drawable��*/
    virtual bool containsDrawable(const Drawable* gset) const=0;
       
    /** ��ȡ����drawable���б��е������š��ҵ�����0 ��getNumDrawables()-1֮���ֵ�����򷵻�getNumDrawables��*/
    virtual unsigned int getDrawableIndex( const Drawable* drawable ) const =0;
       
    /** ��ȡDrawable�б� */
    virtual const DrawableList& getDrawableList() const =0;

	// 5������Drawable
    virtual void compileDrawables(RenderInfo& renderInfo)=0;

	// 6�������Χ��
	virtual const BoundingBox& getBoundingBox() const=0;

};

OSG_EXPORT IVBF_SGNodeGeometry* VBF_CreateSGNodeGeometry() ;
OSG_EXPORT IVBF_SGNodeGeometry* VBF_CreateSGNodeGeometry(const IVBF_SGNodeGeometry& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
