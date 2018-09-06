#ifndef OSG_GEOMETRY
#define OSG_GEOMETRY 1

#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <Types/Vec2>
#include <Types/Vec3>
#include <Types/Vec4>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/PrimitiveSet>

namespace osg {


class OSG_EXPORT Geometry : public Drawable
{
    public:
        Geometry();
        Geometry(const Geometry& geometry,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
            
        virtual CVBF_Object* cloneType() const { return new Geometry(); }
        virtual CVBF_Object* clone(const CopyOp& copyop) const { return new Geometry(*this,copyop); }        
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const Geometry*>(obj)!=NULL; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "Geometry"; }

        virtual Geometry* asGeometry() { return this; }
        virtual const Geometry* asGeometry() const { return this; }

        bool empty() const;

        enum AttributeBinding
        {
            BIND_OFF=0,				// 不启用绑定
            BIND_OVERALL,			// 绑定全部顶点
            BIND_PER_PRIMITIVE_SET,	// 单个绘图基元（图元）绑定
            BIND_PER_PRIMITIVE,		// 单个独立的图元绑定
            BIND_PER_VERTEX			// 单个顶点绑定
        };
               
        struct OSG_EXPORT ArrayData
        {
            ArrayData():
                binding(BIND_OFF),
                normalize(GL_FALSE) {}// IE可能错误
                
            ArrayData(const ArrayData& data,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

            ArrayData(Array* a, AttributeBinding b, GLboolean n = GL_FALSE):
                array(a),
                indices(0),
                binding(b),
                normalize(n) {}// IE可能错误

            ArrayData(Array* a, IndexArray* i, AttributeBinding b, GLboolean n = GL_FALSE):
                array(a),
                indices(i),
                binding(b),
                normalize(n) {}// IE可能错误

            ArrayData& operator = (const ArrayData& rhs)
            {
                array = rhs.array;
                indices = rhs.indices;
                binding = rhs.binding;
                normalize = rhs.normalize;
                return *this;
            }
            
            inline bool empty() const { return !array.valid(); } 

            ref_ptr<Array>          array;
            ref_ptr<IndexArray>     indices;
            AttributeBinding        binding;
            GLboolean               normalize;
        };
        
        struct OSG_EXPORT Vec3ArrayData
        {
            Vec3ArrayData():
                binding(BIND_OFF),
                normalize(GL_FALSE) {}// IE可能错误
                
            Vec3ArrayData(const Vec3ArrayData& data,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

            Vec3ArrayData(Vec3Array* a, AttributeBinding b, GLboolean n = GL_FALSE):
                array(a),
                indices(0),
                binding(b),
                normalize(n) {}// IE可能错误

            Vec3ArrayData(Vec3Array* a, IndexArray* i, AttributeBinding b, GLboolean n = GL_FALSE):
                array(a),
                indices(i),
                binding(b),
                normalize(n) {}// IE可能错误

            Vec3ArrayData& operator = (const Vec3ArrayData& rhs)
            {
                array = rhs.array;
                indices = rhs.indices;
                binding = rhs.binding;
                normalize = rhs.normalize;
                return *this;
            }

            inline bool empty() const { return !array.valid(); } 

            ref_ptr<Vec3Array>      array;
            ref_ptr<IndexArray>     indices;
            AttributeBinding        binding;
            GLboolean               normalize;
        };

        /** Static ArrayData which is returned from getTexCoordData(i) const and getVertexAttribData(i) const 
          * when i is out of range.
        */
        static const ArrayData s_InvalidArrayData;
        
        typedef std::vector< ArrayData >  ArrayDataList;
               

		// 获取/设置顶点数组
        void setVertexArray(Array* array);
        Array* getVertexArray() { return _vertexData.array.get(); }
        const Array* getVertexArray() const  { return _vertexData.array.get(); }

		// 设置/获取顶点数组数据
        void setVertexData(const ArrayData& arrayData);
        ArrayData& getVertexData() { return _vertexData; }
        const ArrayData& getVertexData() const { return _vertexData; }
        
		// 设置法线绑定模式
        void setNormalBinding(AttributeBinding ab);
        AttributeBinding getNormalBinding() const { return _normalData.binding; }

		// 设置/获取法线数组
        void setNormalArray(Array* array);
        Array* getNormalArray() { return _normalData.array.get(); }
        const Array* getNormalArray() const { return _normalData.array.get(); }

		// 设置/获取法线数组数据
        void setNormalData(const ArrayData& arrayData);
        ArrayData& getNormalData() { return _normalData; }
        const ArrayData& getNormalData() const { return _normalData; }

		// 设置/获取颜色绑定模式
        void setColorBinding(AttributeBinding ab);
        AttributeBinding getColorBinding() const { return _colorData.binding; }

		// 
        void setColorArray(Array* array);
        Array* getColorArray() { return _colorData.array.get(); }
        const Array* getColorArray() const { return _colorData.array.get(); }

        void setColorData(const ArrayData& arrayData);
        ArrayData& getColorData() { return _colorData; }
        const ArrayData& getColorData() const { return _colorData; }

		// 设置第二颜色绑定模式
        void setSecondaryColorBinding(AttributeBinding ab);
        AttributeBinding getSecondaryColorBinding() const { return _secondaryColorData.binding; }

        void setSecondaryColorArray(Array* array);
        Array* getSecondaryColorArray() { return _secondaryColorData.array.get(); }
        const Array* getSecondaryColorArray() const { return _secondaryColorData.array.get(); }

        void setSecondaryColorData(const ArrayData& arrayData);
        ArrayData& getSecondaryColorData() { return _secondaryColorData; }
        const ArrayData& getSecondaryColorData() const { return _secondaryColorData; }

		// 设置雾坐标绑定模式
        void setFogCoordBinding(AttributeBinding ab);
        AttributeBinding getFogCoordBinding() const { return _fogCoordData.binding; }

        void setFogCoordArray(Array* array);
        Array* getFogCoordArray() { return _fogCoordData.array.get(); }
        const Array* getFogCoordArray() const { return _fogCoordData.array.get(); }

        void setFogCoordData(const ArrayData& arrayData);
        ArrayData& getFogCoordData() { return _fogCoordData; }
        const ArrayData& getFogCoordData() const { return _fogCoordData; }
        

        void setTexCoordArray(unsigned int unit,Array*);
        Array* getTexCoordArray(unsigned int unit);
        const Array* getTexCoordArray(unsigned int unit) const;

        void setTexCoordData(unsigned int index,const ArrayData& arrayData);
        ArrayData& getTexCoordData(unsigned int index);
        const ArrayData& getTexCoordData(unsigned int index) const;

        unsigned int getNumTexCoordArrays() const {  return static_cast<unsigned int>(_texCoordList.size()); }
        ArrayDataList& getTexCoordArrayList() { return _texCoordList; }
        const ArrayDataList& getTexCoordArrayList() const { return _texCoordList; }



        void setVertexAttribArray(unsigned int index,Array* array);
        Array *getVertexAttribArray(unsigned int index);
        const Array *getVertexAttribArray(unsigned int index) const;

        void setVertexAttribBinding(unsigned int index,AttributeBinding ab);
        AttributeBinding getVertexAttribBinding(unsigned int index) const;

        void setVertexAttribNormalize(unsigned int index,GLboolean norm);
        GLboolean getVertexAttribNormalize(unsigned int index) const;

        void setVertexAttribData(unsigned int index,const ArrayData& arrayData);
        ArrayData& getVertexAttribData(unsigned int index);
        const ArrayData& getVertexAttribData(unsigned int index) const;

        unsigned int getNumVertexAttribArrays() const { return static_cast<unsigned int>(_vertexAttribList.size()); }
        ArrayDataList& getVertexAttribArrayList() { return _vertexAttribList; }
        const ArrayDataList& getVertexAttribArrayList() const { return _vertexAttribList; }



        typedef std::vector< ref_ptr<PrimitiveSet> > PrimitiveSetList;

        void setPrimitiveSetList(const PrimitiveSetList& primitives);
        
        PrimitiveSetList& getPrimitiveSetList() { return _primitives; }
        const PrimitiveSetList& getPrimitiveSetList() const { return _primitives; }

        unsigned int getNumPrimitiveSets() const { return static_cast<unsigned int>(_primitives.size()); }
        PrimitiveSet* getPrimitiveSet(unsigned int pos) { return _primitives[pos].get(); }
        const PrimitiveSet* getPrimitiveSet(unsigned int pos) const { return _primitives[pos].get(); }
        
        /** Add a primitive set to the geometry. */
        bool addPrimitiveSet(PrimitiveSet* primitiveset);
        
        /** Set a primitive set to the specified position in geometry's primitive set list. */
        bool setPrimitiveSet(unsigned int i,PrimitiveSet* primitiveset);
        
        /** Insert a primitive set to the specified position in geometry's primitive set list. */
        bool insertPrimitiveSet(unsigned int i,PrimitiveSet* primitiveset);
        
        /** Remove primitive set(s) from the specified position in geometry's primitive set list. */
        bool removePrimitiveSet(unsigned int i,unsigned int numElementsToRemove=1);

        /** Get the index number of a primitive set, return a value between
          * 0 and getNumPrimitiveSet()-1 if found, if not found then return getNumPrimitiveSet().
          * When checking for a valid find value use if ((value=geometry->getPrimitiveSetIndex(primitive))!=geometry.getNumPrimitiveSet())
        */
        unsigned int getPrimitiveSetIndex(const PrimitiveSet* primitiveset) const;


		// 已废弃，设置/获取顶点索引数组，强迫OpenGL以较慢的方式执行，保留仅是为了向后兼容
        void setVertexIndices(IndexArray* array);
        IndexArray* getVertexIndices() { return _vertexData.indices.get(); }
        const IndexArray* getVertexIndices() const  { return _vertexData.indices.get(); }
     
        // 已废弃，设置/获取法线索引数组，强迫OpenGL以较慢的方式执行，保留仅是为了向后兼容
        void setNormalIndices(IndexArray* array);
        IndexArray* getNormalIndices() { return _normalData.indices.get(); }
        const IndexArray* getNormalIndices() const { return _normalData.indices.get(); }

		// 已废弃，设置/获取颜色索引数组，强迫OpenGL以较慢的方式执行，保留仅是为了向后兼容
        void setColorIndices(IndexArray* array);
        IndexArray* getColorIndices() { return _colorData.indices.get(); }
        const IndexArray* getColorIndices() const { return _colorData.indices.get(); }

		// 已废弃，设置/获取第二颜色索引数组，强迫OpenGL以较慢的方式执行，保留仅是为了向后兼容
        void setSecondaryColorIndices(IndexArray* array);
        IndexArray* getSecondaryColorIndices() { return _secondaryColorData.indices.get(); }
        const IndexArray* getSecondaryColorIndices() const { return _secondaryColorData.indices.get(); }

		// 已废弃，设置/获取雾坐标索引数组，强迫OpenGL以较慢的方式执行，保留仅是为了向后兼容
        void setFogCoordIndices(IndexArray* array);
        IndexArray* getFogCoordIndices() { return _fogCoordData.indices.get(); }
        const IndexArray* getFogCoordIndices() const { return _fogCoordData.indices.get(); }

		// 已废弃，设置/获取纹理坐标索引数组，强迫OpenGL以较慢的方式执行，保留仅是为了向后兼容
        void setTexCoordIndices(unsigned int unit,IndexArray*);
        IndexArray* getTexCoordIndices(unsigned int unit);
        const IndexArray* getTexCoordIndices(unsigned int unit) const;

		// 已废弃，设置/获取顶点属性数组，强迫OpenGL以较慢的方式执行，保留仅是为了向后兼容
        void setVertexAttribIndices(unsigned int index,IndexArray* array);
        IndexArray* getVertexAttribIndices(unsigned int index);
        const IndexArray* getVertexAttribIndices(unsigned int index) const;




        /** When set to true, ignore the setUseDisplayList() settings, and hints to the drawImplementation 
            method to use OpenGL vertex buffer objects for rendering.*/
        virtual void setUseVertexBufferObjects(bool flag);

        /** Force a recompile on next draw() of any OpenGL display list associated with this geoset.*/
        virtual void dirtyDisplayList();


        /** Resize any per context GLObject buffers to specified size. */
        virtual void resizeGLObjectBuffers(unsigned int maxSize);

        /** If State is non-zero, this function releases OpenGL objects for
          * the specified graphics context. Otherwise, releases OpenGL objects
          * for all graphics contexts. */
        virtual void releaseGLObjects(State* state=0) const;

        typedef std::vector<osg::Array*>  ArrayList;
        bool getArrayList(ArrayList& arrayList) const;

        typedef std::vector<osg::DrawElements*>  DrawElementsList;
        bool getDrawElementsList(DrawElementsList& drawElementsList) const;

        osg::VertexBufferObject* getOrCreateVertexBufferObject();

        osg::ElementBufferObject* getOrCreateElementBufferObject();


        /** Set whether fast paths should be used when supported. */
        void setFastPathHint(bool on) {  _fastPathHint = on; }

        /** Get whether fast paths should be used when supported. */
        bool getFastPathHint() const { return _fastPathHint; }


        /** Return true if OpenGL fast paths will be used with drawing this Geometry.
          * Fast paths directly use vertex arrays, and glDrawArrays/glDrawElements so have low CPU overhead.
          * With Slow paths the osg::Geometry::drawImplementation has to dynamically assemble OpenGL
          * compatible vertex arrays from the osg::Geometry arrays data and then dispatch these to OpenGL,
          * so have higher CPU overhead than the Fast paths.
          * Use of per primitive bindings or per vertex indexed arrays will drop the rendering path off the fast path.
        */
        inline bool areFastPathsUsed() const
        {
            if (_internalOptimizedGeometry.valid())
                return _internalOptimizedGeometry->areFastPathsUsed();
            else
                return _fastPath && _fastPathHint;
        }

        bool computeFastPathsUsed();

        bool verifyBindings() const;

        void computeCorrectBindingsAndArraySizes();

        /** check whether the arrays, indices, bindings and primitives all match correctly, return false is .*/
        bool verifyArrays(std::ostream& out) const;

        bool suitableForOptimization() const;

        void copyToAndOptimize(Geometry& target);


        bool containsSharedArrays() const;
        
        void duplicateSharedArrays();
        

        void computeInternalOptimizedGeometry();

        void removeInternalOptimizedGeometry() { _internalOptimizedGeometry = 0; }

        void setInternalOptimizedGeometry(osg::Geometry* geometry) { _internalOptimizedGeometry = geometry; }

        osg::Geometry* getInternalOptimizedGeometry() { return _internalOptimizedGeometry.get(); }

        const osg::Geometry* getInternalOptimizedGeometry() const { return _internalOptimizedGeometry.get(); }


        /** Return the estimated size of GLObjects (display lists/vertex buffer objects) that are associated with this drawable.
          * This size is used a hint for reuse of deleted display lists/vertex buffer objects. */
        virtual unsigned int getGLObjectSizeHint() const;

        /** Immediately compile this \c Drawable into an OpenGL Display List/VertexBufferObjects.
          * @note Operation is ignored if \c _useDisplayList is \c false or VertexBufferObjects are not used.
        */
        virtual void compileGLObjects(RenderInfo& renderInfo) const;

        /** Draw Geometry directly ignoring an OpenGL display list which could be attached.
          * This is the internal draw method which does the drawing itself,
          * and is the method to override when deriving from Geometry for user-drawn objects.
        */
        virtual void drawImplementation(RenderInfo& renderInfo) const;

        /** Return true, osg::Geometry does support accept(Drawable::AttributeFunctor&). */
        virtual bool supports(const Drawable::AttributeFunctor&) const { return true; }

        /** Accept an Drawable::AttributeFunctor and call its methods to tell it about the internal attributes that this Drawable has. */
        virtual void accept(Drawable::AttributeFunctor& af);

        /** Return true, osg::Geometry does support accept(Drawable::ConstAttributeFunctor&). */
        virtual bool supports(const Drawable::ConstAttributeFunctor&) const { return true; }

        /** Accept a Drawable::ConstAttributeFunctor and call its methods to tell it about the internal attributes that this Drawable has. */
        virtual void accept(Drawable::ConstAttributeFunctor& af) const;

        /** Return true, osg::Geometry does support accept(PrimitiveFunctor&). */
        virtual bool supports(const PrimitiveFunctor&) const { return true; }

        /** Accept a PrimitiveFunctor and call its methods to tell it about the internal primitives that this Drawable has. */
        virtual void accept(PrimitiveFunctor& pf) const;

        /** Return true, osg::Geometry does support accept(PrimitiveIndexFunctor&). */
        virtual bool supports(const PrimitiveIndexFunctor&) const { return true; }

        /** Accept a PrimitiveFunctor and call its methods to tell it about the internal primitives that this Drawable has. */
        virtual void accept(PrimitiveIndexFunctor& pf) const;


    protected:

        Geometry& operator = (const Geometry&) { return *this;}

        virtual ~Geometry();
       
        bool verifyBindings(const ArrayData& arrayData) const;
        bool verifyBindings(const Vec3ArrayData& arrayData) const;
        
        void computeCorrectBindingsAndArraySizes(ArrayData& arrayData,const char* arrayName);
        void computeCorrectBindingsAndArraySizes(Vec3ArrayData& arrayData,const char* arrayName);
        
        void addVertexBufferObjectIfRequired(osg::Array* array);
        void addElementBufferObjectIfRequired(osg::PrimitiveSet* primitiveSet);
        

        PrimitiveSetList                _primitives;
        ArrayData                       _vertexData;
        ArrayData                       _normalData;
        ArrayData                       _colorData;
        ArrayData                       _secondaryColorData;
        ArrayData                       _fogCoordData;
        ArrayDataList                   _texCoordList;
        ArrayDataList                   _vertexAttribList;

        mutable bool                    _fastPath;
        bool                            _fastPathHint;

        ref_ptr<Geometry>               _internalOptimizedGeometry;
};

/** Convenience function to be used for creating quad geometry with texture coords.
  * Tex coords go from left bottom (l,b) to right top (r,t).
*/
extern OSG_EXPORT Geometry* createTexturedQuadGeometry(const Vec3& corner,const Vec3& widthVec,const Vec3& heightVec, float l, float b, float r, float t);

/** Convenience function to be used for creating quad geometry with texture coords.
  * Tex coords go from bottom left (0,0) to top right (s,t).
*/
inline Geometry* createTexturedQuadGeometry(const Vec3& corner,const Vec3& widthVec,const Vec3& heightVec, float s=1.0f, float t=1.0f)
{
    return createTexturedQuadGeometry(corner,widthVec,heightVec, 0.0f, 0.0f, s, t);
}


}

#endif
