//*******************************************************************
// FileName：IVBF_AnalysisContext.h
// Function：分析所需要的上下文环境
// Author:
// Date:     2016-12-26
//*******************************************************************

#ifndef __IVBF_ANALYSIS_CONTEXT_H__
#define __IVBF_ANALYSIS_CONTEXT_H__

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupCoordSys.h>

class IVBF_Map;
class IVBF_View;

class IVBF_AnalysisContext : public CVBF_Referenced
{
public:
    virtual ~IVBF_AnalysisContext() {}

    virtual bool GetElevationAvail(osg::IVBF_Camera* pICamera,double L, double B, double& H)=0;
    virtual const osg::EllipsoidModel* GetEllipsoid() const=0;
    virtual bool GeoToWorld(const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWorld)=0;
    virtual bool WorldToGeo(const osg::Vec3d& vWorld, osg::Vec3d& ptGeo)=0;
    virtual bool GeoToClient(osg::IVBF_Camera* pICamera,const osg::Vec3d& ptGeo, bool bAltAbsolute, osg::Vec3d& ptWin)=0;
    virtual bool ClientToGeo(IVBF_View* pIView,float x, float y, osg::Vec3d& ptGeo)=0;
    virtual void InterpolateGreatCircle(const std::vector<osg::Vec3d>& vGeoSrc, std::vector<osg::Vec3d>& vGeoDst)=0;
    virtual void InterpolateGreatCircle(const std::vector<osg::Vec3d>& vGeoSrc, double hMin, std::vector<osg::Vec3d>& vGeoDst)=0;
    virtual void InterpolateGreatCircle(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                      std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0)=0;
    virtual void InterpolateGreatCircle(const osg::Vec3d& ptGeo0, const osg::Vec3d& ptGeo1,
                                                      const double& hMin, std::vector<osg::Vec3d>& vOutGeo, double dDeltaH=1.0)=0;
    virtual void ProjectToLocal(const osg::Matrixd& matWorldToLocal, const osg::Vec3d& ptGeo, osg::Vec3& ptLocal)=0;
    virtual void ComputeLocalizers(const std::vector<osg::Vec3d>& vPointsGeo, osg::Matrixd& matLocalToWorld, osg::Matrixd& matWorldToLocal)=0;
    virtual bool ComputeEllipMatrix(const osg::Vec3d& vGeo, osg::Matrixd& matOut)=0;
    virtual bool ComputeEllipMatrix(const osg::Vec3d& vGeo, float fWidth, float fHeight,
                                                  float fRotateZ, osg::Matrixd& matOut)=0;
    virtual bool ComputeResInDegrees(osg::IVBF_Camera* pICamera, const osg::Vec3d& ptGeo, float& fRes)=0;
    virtual bool ComputeResInMeters(osg::IVBF_Camera* pICamera, const osg::Vec3d& ptGeo, float& fRes)=0;


    virtual IVBF_Map* GetMap()=0; //!! 暂时的，要优化掉
    virtual osg::IVBF_SGNode* GetMapNode()=0; //!! 暂时的，要优化掉
    virtual osg::IVBF_SGNodeGroup* GetParentNode()=0;


};
//IVBF_AnalysisContext* VBF_GetAnalysisContext();

#endif 
