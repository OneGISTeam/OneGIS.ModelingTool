//*******************************************************************
// FileName��VBF_Graphics.h
// Function�������Զ���2Dͼ�Σ�������ͳһ�Ļ����ϣ�CVBF_GraphicsCanvas
// Author:   ��Ө
// Date:     2015-12-29
//*******************************************************************

#ifndef __VBF_GRAPHICS_H__
#define __VBF_GRAPHICS_H__


#include <VBF_Aux/VBF_HUDAux/VBF_HUDAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <Types/Vec2f>
#include <Types/VBF_3DStyles.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <vector>
#include <map>


typedef std::vector< ref_ptr<osg::Drawable> > CVBF_DrawableList;
typedef std::map<class CVBF_Graphics*, osg::IVBF_SGNodeGeometry*> CVBF_GraphicsGeodeMap;


//=============================================================================
// ����ṹ�壺CVBF_GraphicsContext
// �ṹ��������������ͼ�λ���
//=============================================================================
struct CVBF_GraphicsContext
{
    observer_ptr<IVBF_View> m_opView;           // ��ͼ
    ref_ptr<osg::Viewport>  m_ipViewport;       // �ӿ�
};


//=============================================================================
// �����ࣺCVBF_Graphics
// ������������2Dͼ�εĻ���
//=============================================================================
class VBF_HUDAUX_EXPORT CVBF_Graphics : public ::CVBF_Referenced
{
public:
    CVBF_Graphics(const std::string& strName="");
    virtual ~CVBF_Graphics();

    // ����/��ȡͼ�ε����ƣ��Ա����
    void               SetName(const std::string& strName) { m_strName = strName; }
    const std::string& GetName()                           { return m_strName; }

    void SetVisible(bool bVisible) { m_bVisible = bVisible; }
    bool IsVisible()               { return m_bVisible; }

    // ʹ����ͼ����ʧЧ���Ա�����һ֡���´���Drawable
    void DirtyModel()   { m_bDirtyModel = true; DirtyStateSet(); }
    bool IsModelDirty() { return m_bDirtyModel; }

    // ʹ��Ⱦ״̬ʧЧ���Ա�����һ֡���´���Drawable
    void DirtyStateSet()   { m_bDirtyStateSet = true; }
    bool IsStateSetDirty() { return m_bDirtyStateSet; }

    void DirtyData()   { m_bDirtyData = true; }
    bool IsDataDirty() { return m_bDirtyData; }


    // ����Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true)=0;

    // ������Ⱦ״̬
    virtual void SetStateSet() { m_bDirtyStateSet = false; }
    virtual void Update(){ } // ����
protected:
    std::string     m_strName;          // ��2Dͼ�ε����ƣ��Ա����
    bool            m_bVisible;         // �Ƿ�ɼ�
    bool            m_bDirtyModel;      // ����ͼ�����Ƿ�ʧЧ
    bool            m_bDirtyStateSet;   // ��Ⱦ״̬�Ƿ�ʧЧ
    bool            m_bDirtyData;       // ����ֵ�Ƿ����
};

typedef std::vector< ref_ptr<CVBF_Graphics> > CVBF_GraphicsList;


//-----------------------------------------------------
// ����ö�٣�EVBF_CANVAS_ORIGN_MODE
// ö����������������ԭ�������
//-----------------------------------------------------
enum EVBF_CANVAS_ORIGN_MODE
{
    VBF_CANVAS_ORIGN_LOWER_LEFT    = 0,     // ����ԭ��λ����Ļ���½ǣ�Ĭ��ֵ��
    VBF_CANVAS_ORIGN_UPPER_LEFT    = 1      // ����ԭ��λ����Ļ���Ͻ�
};


//=============================================================================
// �����ࣺCVBF_GraphicsCanvas
// ��������2Dͼ�εĻ�������ͼ�ε����������̳���һ���������
//=============================================================================
class VBF_HUDAUX_EXPORT CVBF_GraphicsCanvas : public osg::Camera
{
public:

    // ��̬��������ȡ��View������ͼ�λ���
    // ������bInstallInSceneData -- �Ƿ���Ҫ��������ӵ�����ͼ��
    static CVBF_GraphicsCanvas* Get(IVBF_View* pIView, bool bInstallInSceneData=true);

private:
    typedef std::map<IVBF_View*, CVBF_GraphicsCanvas*> CVBF_ViewCanvasMap;

    static CVBF_ViewCanvasMap ms_mapViewCanvas;
    static OpenThreads::Mutex ms_ViewCanvasMapMutex;


public:
    CVBF_GraphicsCanvas(IVBF_View* pIView);
    virtual ~CVBF_GraphicsCanvas();

    // ���û������ڵ�ͼ�λ���
    void SetGraphicsContext(const CVBF_GraphicsContext& cx);

    // ����/��ȡ����������ԭ������
    void SetCoordOrignMode(EVBF_CANVAS_ORIGN_MODE mode);
    EVBF_CANVAS_ORIGN_MODE GetCoordOrignMode()  { return m_nCoordOrignMode; }

    // ���һ��2Dͼ��
    void AddGraphics(CVBF_Graphics* pGraphics);

    // �Ƴ�һ��2Dͼ��
    void RemoveGraphics(CVBF_Graphics* pGraphics);
    void RemoveGraphics(const std::string& strName);

    // �Ƴ�����2Dͼ��
    void RemoveAll();

    // ��ȡ�����о���ָ�����Ƶ�����2Dͼ�Σ�ͼ�ε����������ظ���
    void GetGraphicsList(const std::string& strName, CVBF_GraphicsList& vGraphics);

    // ��ȡ�����о���ָ�����Ƶĵ�һ��2Dͼ��
    CVBF_Graphics* GetFirstGraphics(const std::string& strName);

    // ��ȡ�����е�����2Dͼ��
    const CVBF_GraphicsList& GetGraphicsList() const { return m_vGraphics; }

    // ���غ���
    virtual void traverse(osg::NodeVisitor& nv);

    // �������¼�
    bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

private:
    CVBF_GraphicsCanvas(IVBF_View* pIView, bool bRegisterCanvas);

    // ��ʼ������
    void Init(IVBF_View* view, bool bRegisterCanvas);

    // ÿ֡����ǰ����
    void Update();

    // �ߵ���������
    void FlipVerts(osg::Drawable* pDrawable);

private:
    CVBF_GraphicsContext        m_Context;              // �������ڵĻ�������ͼ���ӿڵȣ�
//    bool                        m_bContextDirty;        // ͼ�λ����Ƿ�ı���
//    bool                        m_bUpdatePending;
    EVBF_CANVAS_ORIGN_MODE      m_nCoordOrignMode;      // ����ԭ������

    // �����е�2Dͼ��
    CVBF_GraphicsList           m_vGraphics;            // ���в�����Ƶ�2Dͼ��
    CVBF_GraphicsList           m_vGraphicsToAdd;       // ���д���ӵ�2Dͼ��
    CVBF_GraphicsList           m_vGraphicsToRemove;    // ���д��Ƴ���2Dͼ��
    CVBF_GraphicsGeodeMap       m_mapGraphicsGeode;     // ӳ���ÿ��2Dͼ�������Ӧ��Ҷ�ڵ�

    typedef std::map< observer_ptr<osgGA::GUIEventHandler>, observer_ptr<IVBF_View> > CVBF_EventHandlersMap;
    CVBF_EventHandlersMap       m_mapEventHandlers;     // �¼��������б�Ϊ������ʱ��View�����
};


#endif
