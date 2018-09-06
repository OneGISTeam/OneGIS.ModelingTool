//***************************************************************************************
// FileName：VBF_IntersectVisitor.h
// Function：重载osgUtil::IntersectionVisitor，解决Lod节点距离计算的问题
// Author:   杜莹
// Date:     2012-12-24
//***************************************************************************************

#ifndef __VBF_INTERSECT_VISITOR_H__
#define __VBF_INTERSECT_VISITOR_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SGUtil/IntersectionVisitor>


class VBF_GLAUX_EXPORT CVBF_IntersectVisitor : public osgUtil::IntersectionVisitor
{
public:
    CVBF_IntersectVisitor(osg::IVBF_Camera* pCamera, osgUtil::Intersector* intersector=0, ReadCallback* readCallback=0)
        : osgUtil::IntersectionVisitor(intersector, readCallback), m_piCamera(pCamera)
    {
        setReferenceEyePointCoordinateFrame(osgUtil::Intersector::VIEW);
    }

    virtual float getDistanceToViewPoint(const Vec3& pos, bool useLODScale) const
    {
        float fDist = (pos-getViewPoint()).length();

        if(useLODScale)
        {
            if(m_piCamera.valid()) fDist *= m_piCamera->getLODScale();
        }

        return fDist;
    }

private:
    observer_ptr<osg::IVBF_Camera>    m_piCamera;
};


#endif
