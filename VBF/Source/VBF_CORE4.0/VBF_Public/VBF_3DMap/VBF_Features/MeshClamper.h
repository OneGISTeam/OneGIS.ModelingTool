#ifndef OSGEARTHFEATURES_MESH_CLAMPER_H
#define OSGEARTHFEATURES_MESH_CLAMPER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <Types/fast_back_stack>

namespace osgEarth { namespace Features
{
    using namespace osgEarth;

    // 工具类，用于更改一个OSG geometry，使其与地形匹配
    class OSGEARTHFEATURES_EXPORT MeshClamper : public osg::NodeVisitor
    {
    public:

        // scale：Scale factor for the clamped height value
        // offset：Static offset for the clamped height value
        // pTerrainPatch地形数据，pTerrainSRS地形的空间参考，bGeocentric是否ECEF
        // preserveZ是否保留原有的z值作为高出地面的偏移量
        MeshClamper( osg::IVBF_SGNode* pTerrainPatch, const CVBF_SpatialReference* pTerrainSRS,
            bool bGeocentric, bool preserveZ = false,
            double scale = 1.0, double offset = 0.0 );

        virtual ~MeshClamper() { }

        osg::IVBF_SGNode* getTerrainPatch() const { return _terrainPatch.get(); }
        const CVBF_SpatialReference* getTerrainSRS() const { return _terrainSRS.get(); }

        bool isGeocentric() const { return _geocentric; }

    public: // osg::NodeVisitor

        void apply(osg::IVBF_SGNodeGeometry& );
        void apply(osg::IVBF_SGNodeGroupTransform& );

    protected:
        ref_ptr<osg::IVBF_SGNode>            _terrainPatch;
        ref_ptr<const CVBF_SpatialReference> _terrainSRS;
        bool                                 _geocentric;
        bool                                 _preserveZ;
        double                               _scale;
        double                               _offset;
        osg::fast_back_stack<osg::Matrixd>   _matrixStack;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_MESH_CLAMPER_H
