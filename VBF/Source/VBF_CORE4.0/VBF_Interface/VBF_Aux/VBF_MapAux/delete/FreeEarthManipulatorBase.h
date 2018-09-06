
#ifndef FREE_KITS_EARTHMANIPULATORBASE
#define FREE_KITS_EARTHMANIPULATORBASE

//#include <FeKits/Export.h>
//#include <osgViewer/Viewer>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>
//#include <osg/CullSettings>
#include <VBF_Engine/VBF_SceneGraph/CullSettings>
#include <VBF_Aux/VBF_MapAux/IntersectUtil.h>
//#include <FeUtils/RenderContext.h>
#include <VBF_Aux/VBF_MapAux/RenderContext.h>
//#include <osgEarth/MapNode>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>

namespace FeKit
{
    class VBF_MAPAUX_EXPORT FreeEarthManipulatorBase
	{
		struct  EarthProjMatCallback : public osg::CullSettings::ClampProjectionMatrixCallback
		{
			EarthProjMatCallback(FreeEarthManipulatorBase* f);
			virtual bool clampProjectionMatrixImplementation(osg::Matrixf& projection, double& znear, double& zfar) const;
			virtual bool clampProjectionMatrixImplementation(osg::Matrixd& projection, double& znear, double& zfar) const;

		private:
			FreeEarthManipulatorBase* m_pFreeEarthManipulatorBase;
		};

        class TileNodeVisitor : public osg::NodeVisitor
        {
        public:
                    TileNodeVisitor(osg::Vec3d camPos,osg::IVBF_SGNodeGroup* pGroupNode,double west,double east,double north,double south);

                    virtual void apply(osg::IVBF_SGNodeGroupTransformMatrix& node);
                    virtual void apply(osg::IVBF_SGNodeGroupLODPaged & node);

                    virtual float getDistanceToViewPoint(const Vec3& pos, bool useLODScale) const;
                    osg::IVBF_SGNodeGroup* m_pGroupNode;
            double m_west,m_east,m_north,m_south;
                    osg::Vec3d m_curCamPos;

        };

	public:
		FreeEarthManipulatorBase(FeUtil::CRenderContext *pRenderContext);
	public:
        IVBF_Viewer* getViewer();
		virtual void modifyNearFar(double& inputNear,double &inputFar);
		bool checkCollision(osg::Vec3d& start, osg::Vec3d& end, osg::Vec3d& safePoint, osg::Vec3d& upPoint,double checkDis = 5.0);	
		bool checkCollisionWithCheckPoint(osg::Vec3d& start, osg::Vec3d& end, osg::Vec3d& safePoint, osg::Vec3d& checkPoint, double checkDis = 5.0);
	protected:
		double getAltFromTerrain(osg::Vec3d p);
		bool rayToWorld(osg::Vec3d start,osg::Vec3d end,osg::Vec3d& outPoint,osg::Vec3d& hitNormal);
		virtual osg::Matrixd getBaseMatrix() const;
        void getTileNode(osg::IVBF_SGNodeGroup* pGroup,double west,double east,double north,double south);
        bool getIntersectPointWithTerrain(double radius,osg::Vec3d positon,osg::IVBF_SGNodeGroup* tileGroup,osg::Vec3d& safePoint);
        bool getIntersectPointWithTerrain(double radius, osg::Vec3d start, osg::Vec3d end, osg::IVBF_SGNodeGroup* tileGroup, osg::Vec3d& safePoint);
	protected:
        ref_ptr<EarthProjMatCallback> m_rpProjCallback;
        observer_ptr<IVBF_Viewer> m_opViewer;
        observer_ptr<CVBFO_SGNodeMap> m_opMapNode;
		FeMath::COctreeTriangleSelector m_triangleSelector;
		FeMath::CSceneCollisionManager m_collisionManager;
        observer_ptr<FeUtil::CRenderContext>	m_opRenderContext;
	};
}

#endif // FREE_KITS_EARTHMANIPULATORBASE
