#ifndef OSGEARTH_DRAW_INSTANCED_H
#define OSGEARTH_DRAW_INSTANCED_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VirtualProgram.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>

/**
 * Some utilities to support *DrawInstanced rendering.
 */
namespace osgEarth
{
    namespace DrawInstanced
    {
        /**
         * Visitor that converts all the primitive sets in a graph to use
         * instanced draw calls.
         * Called by convertGraphToUseDrawInstanced().
         */
        class OSGEARTH_EXPORT ConvertToDrawInstanced : public osg::NodeVisitor
        {
        public:
            /**
             * Create the visitor that will convert primitive sets to draw
             * <num> instances.
             */
            ConvertToDrawInstanced( unsigned numInstances, const osg::BoundingBox& bbox, bool optimize );

            void apply(osg::IVBF_SGNodeGeometry&);

        protected:
            unsigned _numInstances;
            bool     _optimize;
            ref_ptr<osg::Drawable::ComputeBoundingBoxCallback> _staticBBoxCallback;
        };


        /**
         * Creates a virtual shader program that implements DrawInstanced rendering.
         * You should prepare the scene graph with the ConvertToDrawInstanced
         * visitor first.
         * Called by convertGraphToUseDrawInstanced().
         */
        extern OSGEARTH_EXPORT VirtualProgram* createDrawInstancedProgram();


        /**
         * Processes a scene graph and converts all the top-level MatrixTransform
         * nodes into shader uniforms that can be used with the VirtualProgram
         * created by createDrawInstacedShaders.
         */
        extern OSGEARTH_EXPORT void convertGraphToUseDrawInstanced( 
            osg::IVBF_SGNodeGroup* graph );
    }
}

#endif // OSGEARTH_DRAW_INSTANCED_H
