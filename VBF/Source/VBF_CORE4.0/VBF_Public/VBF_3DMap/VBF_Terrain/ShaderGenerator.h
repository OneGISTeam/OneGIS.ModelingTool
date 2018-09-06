#ifndef OSGEARTH_SHADER_GENERATOR_H
#define OSGEARTH_SHADER_GENERATOR_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/StateSetCache.h>
#include <VBF_3DMap/VBF_Terrain/VirtualProgram.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_StateMachine.h>

namespace osgEarth
{
   //工具类，用于遍历场景图，产生一系列VirtualProgram attributes to render it as best it can using shaders.
    class OSGEARTH_EXPORT ShaderGenerator : public osg::NodeVisitor
    {
    public:
        ShaderGenerator();
        ShaderGenerator( StateSetCache* cache );
        virtual ~ShaderGenerator() { }
		
	public: // 下面两个静态函数提取自osgEarth-2.6（杜莹添加：2018-04-08）

        /**
         * Marks a node with a hint that the shader generator should ignore it in
         * the future.
         */
        static void setIgnoreHint(osg::CVBF_Object* object, bool ignore);

        /**
         * Whether an object has been marked for ignore 
         */
        static bool ignore(const osg::CVBF_Object* object);

    public: // osg::NodeVisitor

        void apply(osg::IVBF_SGNode& );
        void apply(osg::IVBF_SGNodeGeometry& );
        void apply(osg::IVBF_SGNodeGroupLODPaged& );
        void apply(osg::IVBF_SGNodeGroupProxy& );

    protected:

        void apply(osg::Drawable* );
        bool processGeometry( osg::StateSet* stateSet, ref_ptr<osg::StateSet>& replacement );
        bool processText( osg::StateSet* stateSet, ref_ptr<osg::StateSet>& replacement );

        ref_ptr<osg::State> _state;
        ref_ptr<StateSetCache> _stateSetCache;
        ref_ptr<VirtualProgram> _defaultVP;
    };

} // namespace osgEarth

#endif // OSGEARTH_SHADER_GENERATOR_H
