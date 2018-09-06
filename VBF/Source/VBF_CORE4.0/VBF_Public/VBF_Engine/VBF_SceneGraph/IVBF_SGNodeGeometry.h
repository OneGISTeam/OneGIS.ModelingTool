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

    /** 移除Drawable。如果被移除了返回true，否则返回false。*/
    virtual bool removeDrawable( Drawable *drawable )=0;

    /** 移除指定位置的Drawable。如果至少有一个被移除了返回true，否则返回false。*/
    virtual bool removeDrawables(unsigned int i,unsigned int numDrawablesToRemove=1)=0;

    /** 用一个Drawable替换另一个Drawable。 等同于setDrawable(getDrawableIndex(origDraw),newDraw)  */
    virtual bool replaceDrawable( Drawable *origDraw, Drawable *newDraw )=0;

    /** 在指定的位置上设置Drawable。减少原来的Drawable的引用计数，增加新的drawable的引用计数、设置包围球dirty标志
        * 如果i超界或原来的Drawable没找到，则返回 false并不添加新的Drawable 。
        * 如果新的Drawable为空，则返回false并不移除原来的Drawable。
    */
    virtual bool setDrawable( unsigned int i, Drawable* drawable )=0;

    /** 获取Drawable的个数 */
    virtual unsigned int getNumDrawables() const =0;

	/** 获取指定位置的Drawable（注意：i不能超界） */
	virtual Drawable* getDrawable( unsigned int i ) =0;
	virtual const Drawable* getDrawable( unsigned int i ) const =0;

    /** 是否包含指定的Drawable。*/
    virtual bool containsDrawable(const Drawable* gset) const=0;
       
    /** 获取给定drawable在列表中的索引号。找到返回0 到getNumDrawables()-1之间的值，否则返回getNumDrawables。*/
    virtual unsigned int getDrawableIndex( const Drawable* drawable ) const =0;
       
    /** 获取Drawable列表 */
    virtual const DrawableList& getDrawableList() const =0;

	// 5、编译Drawable
    virtual void compileDrawables(RenderInfo& renderInfo)=0;

	// 6、计算包围盒
	virtual const BoundingBox& getBoundingBox() const=0;

};

OSG_EXPORT IVBF_SGNodeGeometry* VBF_CreateSGNodeGeometry() ;
OSG_EXPORT IVBF_SGNodeGeometry* VBF_CreateSGNodeGeometry(const IVBF_SGNodeGeometry& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
