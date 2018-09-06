#ifndef _VBF_MARK_POINT_INPUTOR_
#define _VBF_MARK_POINT_INPUTOR_

#include <VBF_Plot/IVBF_MarkInputorImpl.h>
#include <VBF_Aux/VBF_MapAux/IVBF_3DGlobalData.h>
#include <VBF_Plot/IVBF_MarkModelPoint.h>
class CVBF_MarkPointInputor : public IVBF_MarkInputorImpl
{
public:
    CVBF_MarkPointInputor(unsigned int nCode) :IVBF_MarkInputorImpl(nCode)
    {
        m_fScale = 1.0f;
    }
    ~CVBF_MarkPointInputor(){}
public:
    virtual bool handle(const osgGA::GUIEventAdapter& ea, IVBF_GUIActionAdapter& aa)
    {
        if(ea.IsHandled()) return false;

        m_opView = dynamic_cast<IVBF_View*>(&aa);

        osg::Vec3d ptGeo;
        if (!GetMousePointGeo(ea,aa, ptGeo)) return false;

        if( IsLButtonDown(ea) ) // 左键按下
        {
            if (!m_ipMarkPoint.valid())
            {
                m_ipMarkPoint = CreateMarkPoint(ptGeo);
                m_pI3DPlotLayer->AddMark(m_ipMarkPoint.get());
            }
            return false;
        }
        else if( IsLButtonUp(ea) ) //  左键抬起
        {
            return false;
        }
        else if( IsRButtonUp(ea) ) // 右键抬起
        {
            if(m_ipMarkPoint.valid())m_ipMarkPoint->SetGeoPos(ptGeo);
//!!!       m_pI3DMainCtrl->SendMessage(this, VBF_MESSAGE_3DPLOT_MARK_ADD, 1, m_ipMarkPoint.get());
            m_ipMarkPoint = NULL;
            return true;
        }
        else if( IsMouseMove(ea) )
        {
            if(m_ipMarkPoint.valid() ) m_ipMarkPoint->SetGeoPos(ptGeo);
            return true;
        }
        else if(ea.getEventType()==osgGA::GUIEventAdapter::SCROLL)
        {
            if(m_ipMarkPoint.valid()==false) return false;

            if(ea.getScrollingMotion()==osgGA::GUIEventAdapter::SCROLL_UP)
            {
                m_fScale*=0.92;
            }
            else if(ea.getScrollingMotion()==osgGA::GUIEventAdapter::SCROLL_DOWN)//ACTION_ZOOM_OUT
            {
                m_fScale*=1.08;
            }
            m_ipMarkPoint->SetScale(m_fScale,m_fScale,m_fScale);

            ea.setHandled(true);
            return true;
        }

        return false;
    }

protected:
    void CalcDefaultScale()// 计算默认的缩放比例
    {
        IVBF_GlobalDataPerView* pData = VBF_Get3DGlobalData(this->m_opView.get());
        m_fScale = pData->GetResolution();
    }

    virtual IVBF_MarkModelPoint* CreateMarkPoint(const osg::Vec3d& vGeoPos)=0;

protected:
    double m_fScale;// 缩放比例
    ref_ptr<IVBF_MarkModelPoint> m_ipMarkPoint;// 当前正在创建的Mark
};

#endif
