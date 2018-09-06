#ifndef IVBF_SG_NODE_GEOMETRY_BILLBOARD_H
#define IVBF_SG_NODE_GEOMETRY_BILLBOARD_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>


namespace osg {

class IVBF_SGNodeGeometryBillboard : public IVBF_SGNodeGeometry
{
public:
	enum Mode 
	{
		POINT_ROT_EYE,		// �����ӵ�
		POINT_ROT_WORLD,	// ������ƽ�棿
		AXIAL_ROT			// ������ƣ�������ת���������ӵ�
	};


	IVBF_SGNodeGeometryBillboard(){}
	IVBF_SGNodeGeometryBillboard(const IVBF_SGNodeGeometryBillboard& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGeometry(cs,copyop) {}
	explicit IVBF_SGNodeGeometryBillboard(bool threadSafeRefUnref):IVBF_SGNodeGeometry(threadSafeRefUnref){}
  
	// ����/��ȡ�����Ƶ�ģʽ
    virtual void setMode(Mode mode)=0;
    virtual Mode getMode() const=0;
 
	// ����/��ȡ��ת�ᣬ����mode==AXIAL_ROTʱ������
    virtual void setAxis(const Vec3& axis)=0;
    virtual const Vec3& getAxis() const =0;

    // ����/��ȡ���ߣ�This normal defines child Drawables' front face direction when unrotated.
    virtual void setNormal(const Vec3& normal)=0;
    virtual const Vec3& getNormal() const =0;


	// ������Drawable��λ��
    virtual void setPosition(unsigned int i,const Vec3& pos)=0;
    virtual const Vec3& getPosition(unsigned int i) const =0;

    // ��ת��λ���б�
    typedef std::vector<Vec3> PositionList;
        
    /** Set/get the list of pivot point positions. */
    virtual void setPositionList(PositionList& pl) =0;
    virtual PositionList& getPositionList() =0;
    virtual const PositionList& getPositionList() const =0;


	virtual bool addDrawable( Drawable *gset )=0;
	virtual bool addDrawable(Drawable *gset,const Vec3& pos)=0;


    virtual bool computeMatrix(Matrix& modelview, const Vec3& eye_local, const Vec3& pos_local) const=0;

};

OSG_EXPORT IVBF_SGNodeGeometryBillboard* VBF_CreateSGNodeGeometryBillboard() ;
OSG_EXPORT IVBF_SGNodeGeometryBillboard* VBF_CreateSGNodeGeometryBillboard(const IVBF_SGNodeGeometryBillboard& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
