#ifndef OSG_BILLBOARD
#define OSG_BILLBOARD 1

#include <Types/VBF_Matrix.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometryImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometryBillboard.h>
namespace osg {




class OSG_EXPORT Billboard : public IVBF_SGNodeGeometryImpl<IVBF_SGNodeGeometryBillboard>
{
    public:

        
        Billboard();
        Billboard(const Billboard&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, Billboard);


        // ����/��ȡ�����Ƶ�ģʽ
        void setMode(Mode mode);
        inline Mode getMode() const { return _mode; }

  
		// ����/��ȡ��ת�ᣬ����mode==AXIAL_ROTʱ������
        void setAxis(const Vec3& axis);
        inline const Vec3& getAxis() const { return _axis; }

        // ����/��ȡ���ߣ�This normal defines child Drawables' front face direction when unrotated.
        void setNormal(const Vec3& normal);
        inline const Vec3& getNormal() const { return _normal; }


		// ������Drawable��λ��
        inline void setPosition(unsigned int i,const Vec3& pos)      { _positionList[i] = pos; }
        inline const Vec3& getPosition(unsigned int i) const         { return _positionList[i]; }

        
        /** Set/get the list of pivot point positions. */
        inline void setPositionList(PositionList& pl)       { _positionList=pl; }
        inline PositionList& getPositionList()              { return _positionList; }
        inline const PositionList& getPositionList() const  { return _positionList; }

        /** Add a Drawable with a default position of Vec3(0,0,0).
          * Call the base-class Geode::addDrawble() to add the given Drawable
          * gset as a child. If Geode::addDrawable() returns true, add the
          * default position to the pivot point position list and return true.
          * Otherwise, return false. */
        virtual bool addDrawable( Drawable *gset );

        /** Add a Drawable with a specified position.
          * Call the base-class Geode::addDrawble() to add the given Drawable
          * gset as a child. If Geode::addDrawable() returns true, add the
          * given position pos to the pivot point position list and return true.
          * Otherwise, return false. */
        virtual bool addDrawable(Drawable *gset,const Vec3& pos);

        /** Remove a Drawable and its associated position.
          * If gset is a child, remove it, decrement its reference count,
          * remove its pivot point position. and return true.
          * Otherwise, return false. */
        virtual bool removeDrawable( Drawable *gset );
                

        bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const;

        virtual BoundingSphere computeBound() const;

    protected:

        virtual ~Billboard();

        enum AxisAligned
        {
            AXIAL_ROT_X_AXIS=AXIAL_ROT+1,
            AXIAL_ROT_Y_AXIS,
            AXIAL_ROT_Z_AXIS,
            POINT_ROT_WORLD_Z_AXIS,
            CACHE_DIRTY
        };


        Mode                                _mode;
        Vec3                                _axis;
        Vec3                                _normal;
        Matrix                              _rotateNormalToZAxis;
        PositionList                        _positionList;
        
        // used internally as cache of which what _axis is aligned to help
        // decide which method of rotation to use.
        int                                 _cachedMode;
        Vec3                                _side;
        void updateCache();

};

}

#endif
