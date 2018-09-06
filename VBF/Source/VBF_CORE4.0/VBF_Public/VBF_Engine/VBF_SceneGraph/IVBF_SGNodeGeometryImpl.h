#ifndef IVBF_SG_NODE_GEOMETRY_IMPL_H
#define IVBF_SG_NODE_GEOMETRY_IMPL_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osg {



/** 场景图的叶节点，包含若干个"renderable things"。叶节点的目的是管理Drawable对象。*/
template<class T>
class IVBF_SGNodeGeometryImpl : public IVBF_SGNodeImpl<T>
{
    typedef IVBF_SGNodeImpl<T> _Base;

public:

  		
		// 1、与构造函数有关的内容

        IVBF_SGNodeGeometryImpl();

        /** 拷贝构造函数, 通过CopyOp控制动态数据的shallow vs deep拷贝。*/
        IVBF_SGNodeGeometryImpl(const IVBF_SGNodeGeometryImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
		
		// 2、与基本信息有关的内容

 //       META_Node(osg, Geode);
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const T*>(obj)!=NULL; }
        virtual const char* className() const { return "IVBF_SGNodeGeometryImpl"; }

 	
		
		// 3、类型转化，!!!去掉，在使用时改为dynamic_cast<XXX*>(this)形式，降低性能（降低多少？）但代码结构清晰
     
		virtual IVBF_SGNodeGeometry* asGeode() { return this; }
        virtual const IVBF_SGNodeGeometry* asGeode() const { return this; }
        

		// 4、与Drawable管理相关的内容

		/** 添加drawable。如果drawable非空并未被该叶节点包含则增加该子节点的引用计数、把它加入到drawable
		  * 列表、设置包围球dirty标志并返回true，否则返回false。
		*/
		virtual bool addDrawable( Drawable *drawable );

        /** 移除Drawable。如果被移除了返回true，否则返回false。*/
        virtual bool removeDrawable( Drawable *drawable );

        /** 移除指定位置的Drawable。如果至少有一个被移除了返回true，否则返回false。*/
        virtual bool removeDrawables(unsigned int i,unsigned int numDrawablesToRemove=1);

        /** 用一个Drawable替换另一个Drawable。 等同于setDrawable(getDrawableIndex(origDraw),newDraw)  */
        virtual bool replaceDrawable( Drawable *origDraw, Drawable *newDraw );

        /** 在指定的位置上设置Drawable。减少原来的Drawable的引用计数，增加新的drawable的引用计数、设置包围球dirty标志
          * 如果i超界或原来的Drawable没找到，则返回 false并不添加新的Drawable 。
          * 如果新的Drawable为空，则返回false并不移除原来的Drawable。
        */
        virtual bool setDrawable( unsigned int i, Drawable* drawable );

        /** 获取Drawable的个数 */
        virtual unsigned int getNumDrawables() const { return _drawables.size(); }

		/** 获取指定位置的Drawable（注意：i不能超界） */
		virtual Drawable* getDrawable( unsigned int i ) { return _drawables[i].get(); }
		virtual const Drawable* getDrawable( unsigned int i ) const { return _drawables[i].get(); }

        /** 是否包含指定的Drawable。*/
        virtual bool containsDrawable(const Drawable* gset) const
        {
            for (IVBF_SGNodeGeometry::DrawableList::const_iterator itr=_drawables.begin(); itr!=_drawables.end(); ++itr)
            {
                if (itr->get()==gset) return true;
            }
            return false;
        }

        /** 获取给定drawable在列表中的索引号。找到返回0 到getNumDrawables()-1之间的值，否则返回getNumDrawables。*/
        virtual unsigned int getDrawableIndex( const Drawable* drawable ) const
        {
            for (unsigned int drawableNum=0;drawableNum<_drawables.size();++drawableNum)
            {
                if (_drawables[drawableNum]==drawable) return drawableNum;
            }
            return _drawables.size(); // 没找到
        }

        /** 获取Drawable列表 */
        const IVBF_SGNodeGeometry::DrawableList& getDrawableList() const { return _drawables; }




		// 5、编译Drawable

        /** 为每个drawable编译OpenGL显示列表。*/
        void compileDrawables(RenderInfo& renderInfo);



		// 6、计算包围盒

        /** Return the Geode's bounding box, which is the union of all the
          * bounding boxes of the geode's drawables.*/
        virtual const BoundingBox& getBoundingBox() const
        {
            if(!_Base::_boundingSphereComputed) _Base::getBound();
            return _bbox;
        }




		// 7、重载父类中的方法

		/** 计算包围球 */
        virtual BoundingSphere computeBound() const;

        /** 设置是否使用mutex确保ref()和unref()的线程安全性。*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        /** 改变每个上下文GLObject buffers 为指定大小。 */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** 释放OpenGL对象。*/
        virtual void releaseGLObjects(osg::State* = 0) const;


    protected:

        virtual ~IVBF_SGNodeGeometryImpl();


        mutable osg::BoundingBox        _bbox;
        IVBF_SGNodeGeometry::DrawableList                    _drawables;

};

#define square(x)   ((x)*(x))

}
#include "VBFO_SGNodeGeometry.inl"
#endif
