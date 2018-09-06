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

    /* ģ�Ϳ��ӵ���С�����룬�ֱ�Ĭ��Ϊ0.0��FLT_MAX (��λ����) */
    virtual void  SetDistance(float fDistMin,float fDistMax);

    static CVBF_ThematicMap* Find(const std::string& sName);
    static void Remove(const std::string& sName);
private:
    static std::list< ref_ptr<CVBF_ThematicMap> > ms_ThematicMaps;

private:
    std::string m_sName;
    observer_ptr<IVBF_SGNodeGroup> m_opNodeParent;

    observer_ptr<osgEarth::Features::FeatureSource> m_opFeatureSource;
    ref_ptr<CVBF_ThematicSymbol> m_ipSymbol;//����

    ref_ptr<osg::Camera>	m_ipHUDCamera;// ��ר��ͼ�ĸ��ڵ�
    ref_ptr<IVBF_View> m_opView;

    // �ɼ�����
    float m_fDistMin; // ��С���Ӿ���
    float m_fDistMax; // �����Ӿ���

    ref_ptr<osg::CVBF_SGNodeGroupLOD> m_ipLod;
};

#endif
