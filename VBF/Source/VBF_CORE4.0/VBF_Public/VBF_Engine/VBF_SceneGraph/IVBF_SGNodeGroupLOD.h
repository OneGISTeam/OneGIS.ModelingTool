#ifndef IVBF_SG_NODE_GROUP_LOD_H
#define IVBF_SG_NODE_GROUP_LOD_H 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>

namespace osg {

// 细节层次（LOD）节点：当视点靠近物体时用详细的细节表示；当视点远离物体时用简化的细节来表示。
//                    LOD节点是一次性装入内存的，只是有选择性的渲染。

class IVBF_SGNodeGroupLOD : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupLOD(){}
	IVBF_SGNodeGroupLOD(const IVBF_SGNodeGroupLOD& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	explicit IVBF_SGNodeGroupLOD(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}
	
	// 视点到节点的距离就是视点到节点中心的距离，节点中心可以是包围球的中心，也可以是其他点（如模型坐标系的原点）
	enum CenterMode // 节点中心模式
	{
		USE_BOUNDING_SPHERE_CENTER, // 包围球中心
		USER_DEFINED_CENTER			// 自定义中心，需要调用setCenter()
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

 	// LOD子模型的切换可以根据距离来确定，也可以根据屏幕像素大小来切换
	enum RangeMode
    {
        DISTANCE_FROM_EYE_POINT,	// 根据到视点的距离切换
        PIXEL_SIZE_ON_SCREEN		// 根据屏幕像素大小切换
    };
        
	// 设置/获取切换范围值的解释模式（如何被解释）
    virtual void setRangeMode(RangeMode mode) =0;
    virtual RangeMode getRangeMode() const  =0;


 	// 设置/获取指定节点的最大最小可视范围
    virtual void setRange(unsigned int childNo, float min,float max) =0;
    virtual float getMinRange(unsigned int childNo) const  =0;
    virtual float getMaxRange(unsigned int childNo) const =0;
        
  	// 获取当前设置的范围的数量，全部设置时getNumChildren()==getNumRanges()
    virtual unsigned int getNumRanges() const  =0;

	// 设置/获取所有的子节点的最大最小可视范围
    virtual void setRangeList(const RangeList& rangeList) =0;
    virtual const RangeList& getRangeList() const =0;
};

OSG_EXPORT IVBF_SGNodeGroupLOD* VBF_CreateSGNodeGroupLOD() ;
OSG_EXPORT IVBF_SGNodeGroupLOD* VBF_CreateSGNodeGroupLOD(const IVBF_SGNodeGroupLOD& cs, const CopyOp& copyop=CopyOp::SHALLOW_COPY) ;

}
#endif
