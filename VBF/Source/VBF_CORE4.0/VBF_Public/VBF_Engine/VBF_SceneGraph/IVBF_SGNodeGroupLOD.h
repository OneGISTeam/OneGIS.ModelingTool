#ifndef IVBF_SG_NODE_GROUP_LOD_H
#define IVBF_SG_NODE_GROUP_LOD_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

namespace osg {

// ϸ�ڲ�Σ�LOD���ڵ㣺���ӵ㿿������ʱ����ϸ��ϸ�ڱ�ʾ�����ӵ�Զ������ʱ�ü򻯵�ϸ������ʾ��
//                    LOD�ڵ���һ����װ���ڴ�ģ�ֻ����ѡ���Ե���Ⱦ��

class IVBF_SGNodeGroupLOD : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupLOD(){}
	IVBF_SGNodeGroupLOD(const IVBF_SGNodeGroupLOD& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupLOD(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}
	
	// �ӵ㵽�ڵ�ľ�������ӵ㵽�ڵ����ĵľ��룬�ڵ����Ŀ����ǰ�Χ������ģ�Ҳ�����������㣨��ģ������ϵ��ԭ�㣩
	enum CenterMode // �ڵ�����ģʽ
	{
		USE_BOUNDING_SPHERE_CENTER, // ��Χ������
		USER_DEFINED_CENTER			// �Զ������ģ���Ҫ����setCenter()
	};

	typedef osg::BoundingSphere::vec_type vec_type;
	typedef osg::BoundingSphere::value_type value_type;

	virtual bool addChild(IVBF_SGNode* child )=0;
    virtual bool addChild(IVBF_SGNode* child, float min, float max)=0;


	/** Set how the center of object should be determined when computing which child is active.*/
	virtual void setCenterMode(CenterMode mode)=0;
	virtual CenterMode getCenterMode() const =0;

	/** Sets the object-space point which defines the center of the osg::LOD.  
	center is affected by any transforms in the hierarchy above the osg::LOD.*/
	virtual void setCenter(const vec_type& center) =0;
	virtual const vec_type& getCenter() const=0;


	/** Set the object-space reference radius of the volume enclosed by the LOD. 
	* Used to determine the bounding sphere of the LOD in the absence of any children.*/
	virtual void setRadius(value_type radius)=0;
	virtual value_type getRadius() const =0;


    typedef std::pair<float,float>  MinMaxPair;
    typedef std::vector<MinMaxPair> RangeList;

 	// LOD��ģ�͵��л����Ը��ݾ�����ȷ����Ҳ���Ը�����Ļ���ش�С���л�
	enum RangeMode
    {
        DISTANCE_FROM_EYE_POINT,	// ���ݵ��ӵ�ľ����л�
        PIXEL_SIZE_ON_SCREEN		// ������Ļ���ش�С�л�
    };
        
	// ����/��ȡ�л���Χֵ�Ľ���ģʽ����α����ͣ�
    virtual void setRangeMode(RangeMode mode) =0;
    virtual RangeMode getRangeMode() const  =0;


 	// ����/��ȡָ���ڵ�������С���ӷ�Χ
    virtual void setRange(unsigned int childNo, float min,float max) =0;
    virtual float getMinRange(unsigned int childNo) const  =0;
    virtual float getMaxRange(unsigned int childNo) const =0;
        
  	// ��ȡ��ǰ���õķ�Χ��������ȫ������ʱgetNumChildren()==getNumRanges()
    virtual unsigned int getNumRanges() const  =0;

	// ����/��ȡ���е��ӽڵ�������С���ӷ�Χ
    virtual void setRangeList(const RangeList& rangeList) =0;
    virtual const RangeList& getRangeList() const =0;
};

OSG_EXPORT IVBF_SGNodeGroupLOD* VBF_CreateSGNodeGroupLOD() ;
OSG_EXPORT IVBF_SGNodeGroupLOD* VBF_CreateSGNodeGroupLOD(const IVBF_SGNodeGroupLOD& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
