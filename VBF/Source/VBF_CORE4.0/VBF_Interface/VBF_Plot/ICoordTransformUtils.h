//***************************************************************************************
// FileName：CoordTransformUtils.h
// Function：与坐标转换有关的工具函数
// Author:   杜莹
// Date:     2014-04-04
//***************************************************************************************

#ifndef __IVBF_COORD_TRANSFORM_UTILS_H__
#define __IVBF_COORD_TRANSFORM_UTILS_H__

#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

const char VBF_INTERFACE_3DPLOTTRANSFORM[] = "三维标图坐标转换接口";
class ICoordTransformUtils : public CVBF_Referenced
{
public:
	virtual ~ICoordTransformUtils(){}
	// 函数描述：查找地图节点（注意：如果频繁调用该函数，会影响效率）
	virtual CVBFO_SGNodeMap* FindMapNode() = 0;
	virtual bool WorldToGeo( const osg::Vec3d& ptWorld, osg::Vec3d& ptGeo,CVBFO_SGNodeMap* pMapNode = NULL) = 0;
	virtual bool WorldToClient(const osg::Vec3d& ptWorld, osg::Vec3d& ptWin) = 0;
	virtual bool GeoToWorld(const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWorld,CVBFO_SGNodeMap* pMapNode = NULL) = 0;
	virtual bool GeoToClient(CVBFO_SGNodeMap* pMapNode, const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWin) = 0;
	virtual bool ClientToWorld( float x, float y, osg::Vec3d& ptWorld,IVBF_View* pView) = 0;
	virtual bool GetElevation(CVBFO_SGNodeMap* pMapNode, double L, double B, double& H) = 0;

	virtual double Get3DScale() = 0;

	virtual double GetWorldBufferWidth(double dWidth) = 0;
};


#endif
