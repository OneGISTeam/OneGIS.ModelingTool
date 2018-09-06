#ifndef VBF_THEMATICMAP_H
#define VBF_THEMATICMAP_H

#include <VBF_3DMap/VBF_Features/VBF_SourceFeature.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Aux/VBF_AuxThematicMap/VBF_AuxThematicMapExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupLOD.h>
class IVBF_GraphicsCreator;
class CVBF_ThematicSymbol;
class CVBF_GraphicsContext;
class VBF_AUXTHEMATICMAP_EXPORT CVBF_ThematicMap : public CVBF_Referenced
{
public:
    CVBF_ThematicMap(const std::string& sName,IVBF_SGNodeGroup* pINodeParent,IVBF_View* pIView);
    ~CVBF_ThematicMap();

    const std::string& GetName() { return m_sName; }

    void SetSymbol(IVBF_GraphicsCreator* pGraphicsCreator);
    void SetFeatureSource(osgEarth::Features::FeatureSource* pFeatureSource);

    void ReBuild(CVBFO_SGNodeMap* pMapNode);

    IVBF_SGNode* GetRootNode() { return m_ipHUDCamera.get(); }

    /* 模型可视的最小最大距离，分别默认为0.0和FLT_MAX (单位：米) */
    virtual void  SetDistance(float fDistMin,float fDistMax);

    static CVBF_ThematicMap* Find(const std::string& sName);
    static void Remove(const std::string& sName);
private:
    static std::list< ref_ptr<CVBF_ThematicMap> > ms_ThematicMaps;

private:
    std::string m_sName;
    observer_ptr<IVBF_SGNodeGroup> m_opNodeParent;

    observer_ptr<osgEarth::Features::FeatureSource> m_opFeatureSource;
    ref_ptr<CVBF_ThematicSymbol> m_ipSymbol;//符号

    ref_ptr<osg::Camera>	m_ipHUDCamera;// 该专题图的根节点
    ref_ptr<IVBF_View> m_opView;

    // 可见距离
    float m_fDistMin; // 最小可视距离
    float m_fDistMax; // 最大可视距离

    ref_ptr<osg::CVBF_SGNodeGroupLOD> m_ipLod;
};

#endif
