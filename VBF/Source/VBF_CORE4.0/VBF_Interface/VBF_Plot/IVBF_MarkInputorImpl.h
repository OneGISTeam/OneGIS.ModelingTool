/////////////////////////////////////////////////////////////////////////////////
//    IVBF_MarkInputorImpl.h
//    ��ά������봦����
/////////////////////////////////////////////////////////////////////////////////

#ifndef _MARK_INPUTOR_IMPL_H_
#define _MARK_INPUTOR_IMPL_H_

#include <VBF_3DMap/VBF_Terrain/ElevationQuery.h>

#include <Types/VBF_3DStyles.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Aux/VBF_MapAux/VBF_CoordTransformUtils.h>
#include <VBF_Plot/IVBF_3DPlot.h>
#include <VBF_Plot/IVBF_3DPlotDoc.h>
#include <VBF_Plot/IVBF_3DPlotLayer.h>
#include <VBF_Plot/IVBF_MarkInputHandler.h>

class IVBF_MarkInputorImpl : public IVBF_MarkInputHandler
{
public:
    IVBF_MarkInputorImpl(unsigned int nHandlerType):m_nHandlerType(nHandlerType)
    {
        m_pI3DPlot = NULL;
        m_pI3DPlotLayer = NULL;

        m_LineStyle.fWidth = 2.0f;
        m_LineStyle.color = osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f);
        m_LineStyle.nStipplePattern = 0xFFFF;
    }

    ~IVBF_MarkInputorImpl()
    {
        if(m_opI3DPlotLayerTemp.valid()) m_opI3DPlotLayerTemp->DeleteAllMarks();
    }
    virtual unsigned int GetType() { return m_nHandlerType; }
    virtual unsigned int GetMarkType() { return m_nMarkType;}
    virtual std::string  GetMarkCode() { return m_strMarkCode; }

	// ��Ӧ�˻�������Ϣ
    bool Initilize( IVBF_3DPlot* pI3DPlot )
    {
        if(NULL==pI3DPlot) return false;

        m_pI3DPlot = pI3DPlot;

        // ��ȡ��ǰ����ı�ͼ�ĵ�
        IVBF_3DPlotDoc* pI3DPlotDoc = m_pI3DPlot->GetActiveDoc();
        if(!pI3DPlotDoc) return false;

        m_opI3DPlotLayerTemp = pI3DPlotDoc->AddLayer("Temp Input Layer");

        m_pI3DPlotLayer = pI3DPlotDoc->GetActiveLayer();
        if(!m_pI3DPlotLayer.valid()) return false;

        m_ipPlotContext = pI3DPlotDoc->GetContext();

        return true;
    }

protected:
    bool GetMousePointGeo(const osgGA::GUIEventAdapter& ea,IVBF_GUIActionAdapter& aa,osg::Vec3d& ptGeo)
    {
        IVBF_View* pView = dynamic_cast<IVBF_View*>(&aa);
        if(!pView) return false;

        float x = ea.getX();
        float y = ea.getY();
        if(m_ipPlotContext->ClientToGeo(pView, x, y, ptGeo) == false) return false;

        // ��ȡ�߳�ֵ
        double dElevation=0.0;
        if(m_ipPlotContext->GetElevationAvail( pView->getCamera(), ptGeo.x(), ptGeo.y(), dElevation )==false) return false;
        ptGeo.z()= dElevation;

        return true;
    }

    bool IsLButtonDown(const osgGA::GUIEventAdapter& ea)
    {
        return (ea.getEventType()==osgGA::GUIEventAdapter::PUSH && ea.getButton()==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON);
    }
    bool IsLButtonUp(const osgGA::GUIEventAdapter& ea)
    {
        return (ea.getEventType()==osgGA::GUIEventAdapter::RELEASE && ea.getButton()==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON);
    }
    bool IsRButtonDown(const osgGA::GUIEventAdapter& ea)
    {
        return (ea.getEventType()==osgGA::GUIEventAdapter::PUSH && ea.getButton()==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON);
    }
    bool IsRButtonUp(const osgGA::GUIEventAdapter& ea)
    {
        return (ea.getEventType()==osgGA::GUIEventAdapter::RELEASE && ea.getButton()==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON);
    }
    bool IsMouseMove(const osgGA::GUIEventAdapter& ea)
    {
        return (ea.getEventType()==osgGA::GUIEventAdapter::MOVE);
    }

    // ������������
    unsigned int m_nHandlerType;

    observer_ptr<IVBF_View> m_opView;

	observer_ptr<IVBF_3DPlot> m_pI3DPlot;
	observer_ptr<IVBF_3DPlotLayer> m_pI3DPlotLayer;	// ͼ��
    observer_ptr<IVBF_3DPlotLayer> m_opI3DPlotLayerTemp;	// ͼ��

    VBF_LINESTYLE m_LineStyle;// ������ʽ

    unsigned int m_nMarkType;   // ��ŵ�����
    std::string  m_strMarkCode;           // ��ŵı���

    ref_ptr<IVBF_MarkContext> m_ipPlotContext;

};

#endif
