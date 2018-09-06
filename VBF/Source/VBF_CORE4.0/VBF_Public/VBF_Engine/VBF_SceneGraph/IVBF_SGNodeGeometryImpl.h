#ifndef IVBF_SG_NODE_GEOMETRY_IMPL_H
#define IVBF_SG_NODE_GEOMETRY_IMPL_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

namespace osg {



/** ����ͼ��Ҷ�ڵ㣬�������ɸ�"renderable things"��Ҷ�ڵ��Ŀ���ǹ���Drawable����*/
template<class T>
class IVBF_SGNodeGeometryImpl : public IVBF_SGNodeImpl<T>
{
    typedef IVBF_SGNodeImpl<T> _Base;

public:

  		
		// 1���빹�캯���йص�����

        IVBF_SGNodeGeometryImpl();

        /** �������캯��, ͨ��CopyOp���ƶ�̬���ݵ�shallow vs deep������*/
        IVBF_SGNodeGeometryImpl(const IVBF_SGNodeGeometryImpl&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
		
		// 2���������Ϣ�йص�����

 //       META_Node(osg, Geode);
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const T*>(obj)!=NULL; }
        virtual const char* className() const { return "IVBF_SGNodeGeometryImpl"; }

 	
		
		// 3������ת����!!!ȥ������ʹ��ʱ��Ϊdynamic_cast<XXX*>(this)��ʽ���������ܣ����Ͷ��٣���������ṹ����
     
		virtual IVBF_SGNodeGeometry* asGeode() { return this; }
        virtual const IVBF_SGNodeGeometry* asGeode() const { return this; }
        

		// 4����Drawable������ص�����

		/** ���drawable�����drawable�ǿղ�δ����Ҷ�ڵ���������Ӹ��ӽڵ�����ü������������뵽drawable
		  * �б����ð�Χ��dirty��־������true�����򷵻�false��
		*/
		virtual bool addDrawable( Drawable *drawable );

        /** �Ƴ�Drawable��������Ƴ��˷���true�����򷵻�false��*/
        virtual bool removeDrawable( Drawable *drawable );

        /** �Ƴ�ָ��λ�õ�Drawable�����������һ�����Ƴ��˷���true�����򷵻�false��*/
        virtual bool removeDrawables(unsigned int i,unsigned int numDrawablesToRemove=1);

        /** ��һ��Drawable�滻��һ��Drawable�� ��ͬ��setDrawable(getDrawableIndex(origDraw),newDraw)  */
        virtual bool replaceDrawable( Drawable *origDraw, Drawable *newDraw );

        /** ��ָ����λ��������Drawable������ԭ����Drawable�����ü����������µ�drawable�����ü��������ð�Χ��dirty��־
          * ���i�����ԭ����Drawableû�ҵ����򷵻� false��������µ�Drawable ��
          * ����µ�DrawableΪ�գ��򷵻�false�����Ƴ�ԭ����Drawable��
        */
        virtual bool setDrawable( unsigned int i, Drawable* drawable );

        /** ��ȡDrawable�ĸ��� */
        virtual unsigned int getNumDrawables() const { return _drawables.size(); }

		/** ��ȡָ��λ�õ�Drawable��ע�⣺i���ܳ��磩 */
		virtual Drawable* getDrawable( unsigned int i ) { return _drawables[i].get(); }
		virtual const Drawable* getDrawable( unsigned int i ) const { return _drawables[i].get(); }

        /** �Ƿ����ָ����Drawable��*/
        virtual bool containsDrawable(const Drawable* gset) const
        {
            for (IVBF_SGNodeGeometry::DrawableList::const_iterator itr=_drawables.begin(); itr!=_drawables.end(); ++itr)
            {
                if (itr->get()==gset) return true;
            }
            return false;
        }

        /** ��ȡ����drawable���б��е������š��ҵ�����0 ��getNumDrawables()-1֮���ֵ�����򷵻�getNumDrawables��*/
        virtual unsigned int getDrawableIndex( const Drawable* drawable ) const
        {
            for (unsigned int drawableNum=0;drawableNum<_drawables.size();++drawableNum)
            {
                if (_drawables[drawableNum]==drawable) return drawableNum;
            }
            return _drawables.size(); // û�ҵ�
        }

        /** ��ȡDrawable�б� */
        const IVBF_SGNodeGeometry::DrawableList& getDrawableList() const { return _drawables; }




		// 5������Drawable

        /** Ϊÿ��drawable����OpenGL��ʾ�б�*/
        void compileDrawables(RenderInfo& renderInfo);



		// 6�������Χ��

        /** Return the Geode's bounding box, which is the union of all the
          * bounding boxes of the geode's drawables.*/
        virtual const BoundingBox& getBoundingBox() const
        {
            if(!_Base::_boundingSphereComputed) _Base::getBound();
            return _bbox;
        }




		// 7�����ظ����еķ���

		/** �����Χ�� */
        virtual BoundingSphere computeBound() const;

        /** �����Ƿ�ʹ��mutexȷ��ref()��unref()���̰߳�ȫ�ԡ�*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

        /** �ı�ÿ��������GLObject buffers Ϊָ����С�� */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** �ͷ�OpenGL����*/
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
