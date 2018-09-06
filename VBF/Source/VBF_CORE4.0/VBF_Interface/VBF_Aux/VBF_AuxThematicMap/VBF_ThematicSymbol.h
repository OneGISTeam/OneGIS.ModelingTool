#ifndef VBF_THEMATICSYMBOL_H
#define VBF_THEMATICSYMBOL_H

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_3DMap/VBF_Features/VBF_SourceFeature.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Aux/VBF_AuxThematicMap/VBF_AuxThematicMapExport.h>
#include <VBF_Aux/VBF_HUDAux/VBF_Graphics.h>

class IVBF_GraphicsCreator : public CVBF_Referenced
{
public:
    virtual CVBF_Graphics* CreateGraphics(osgEarth::Features::Feature* pFeature)=0;
};
class VBF_AUXTHEMATICMAP_EXPORT CVBF_ThematicSymbol : public CVBF_Referenced
{
public:
    CVBF_ThematicSymbol(IVBF_GraphicsCreator* pGraphicsCreator);
    osg::IVBF_SGNodeGroup* BuildSGNode(const CVBF_GraphicsContext& context,osgEarth::Features::Feature* pFeature,CVBFO_SGNodeMap* pMapNode);
protected:
    virtual CVBF_Graphics* CreateGraphics(osgEarth::Features::Feature* pFeature)
    {
        if(!m_ipGraphicsCreator.valid()) return NULL;

        return m_ipGraphicsCreator->CreateGraphics(pFeature);
    }

    osg::IVBF_SGNodeGeometry* CreateGeode(const CVBF_GraphicsContext& context,osgEarth::Features::Feature* pFeature);//{ return NULL; }
    ref_ptr<IVBF_GraphicsCreator> m_ipGraphicsCreator;
};
#endif
