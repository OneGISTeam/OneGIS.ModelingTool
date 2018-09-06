#ifndef OSGEARTHSYMBOLOGY_MESH_CONSOLIDATOR
#define OSGEARTHSYMBOLOGY_MESH_CONSOLIDATOR

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

// ���飺�Ƶ�Features����
namespace osgEarth { namespace Symbology
{
    /**
     * Consolidates all the like-moded primitive sets in a geometry.
     *
     * This utility will attempt to extract all triangular primitives
     * from a geometry and regroup them into a smaller number of primitive sets. For
     * example, if you have a geometry with triangle strips, fans, and triangles, it will
     * combines them into one a minimal number of primitive sets containing GL_TRIANGLES.
     *
     * Limitations:
     *
     * - Will not operate on geometry with vertex attributes.
     * 
     * - For geometries with tex coord arrays, all geometries must have the same configuration
     * (i.e., number of texcoord arrays, and the same unit bindings).
     */
    // ���������ʹ��������գ�Ч�ʸ���
    class OSGEARTHSYMBOLOGY_EXPORT MeshConsolidator
    {
    public:
        /**
         * Converts all polygon primitive sets (tristrips, trifans, polygons, etc)
         * into GL_TRIANGLES. Similar to the IndexMeshVisitor, except that this
         * retians user data pointers on the primsets.
         */
        static void convertToTriangles( osg::Geometry& geom );

        /**
         * Consolidates compatible geometries in the geode. First runs the 
         * convertToTriangles method on each Geometry if applicable, them combines
         * geometies into a minimal set for performance purposes.
         */
        static void run( osg::IVBF_SGNodeGeometry& geode );
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_MESH_CONSOLIDATOR
