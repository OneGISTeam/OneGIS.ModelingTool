//*******************************************************************
// FileName：VBF_Graphics.h
// Function：各种自定义2D图形，绘制在统一的画布上：CVBF_GraphicsCanvas
// Author:   杜莹
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
// 定义结构体：CVBF_GraphicsContext
// 结构体描述：画布的图形环境
//=============================================================================
struct CVBF_GraphicsContext
{
    observer_ptr<IVBF_View> m_opView;           // 视图
    ref_ptr<osg::Viewport>  m_ipViewport;       // 视口
};


//=============================================================================
// 定义类：CVBF_Graphics
// 类描述：所有2D图形的基类
//=============================================================================
class VBF_HUDAUX_EXPORT CVBF_Graphics : public ::CVBF_Referenced
{
public:
    CVBF_Graphics(const std::string& strName="");
    virtual ~CVBF_Graphics();

    // 设置/获取图形的名称，以便调试
    void               SetName(const std::string& strName) { m_strName = strName; }
    const std::string& GetName()                           { return m_strName; }

    void SetVisible(bool bVisible) { m_bVisible = bVisible; }
    bool IsVisible()               { return m_bVisible; }

    // 使场景图内容失效，以便在下一帧重新创建Drawable
    void DirtyModel()   { m_bDirtyModel = true; DirtyStateSet(); }
    bool IsModelDirty() { return m_bDirtyModel; }

    // 使渲染状态失效，以便在下一帧重新创建Drawable
    void DirtyStateSet()   { m_bDirtyStateSet = true; }
    bool IsStateSetDirty() { return m_bDirtyStateSet; }

    void DirtyData()   { m_bDirtyData = true; }
    bool IsDataDirty() { return m_bDirtyData; }


    // 创建Drawable
    virtual void CreateDrawables(const CVBF_GraphicsContext& context, CVBF_DrawableList& vDrawables,bool bClear=true)=0;

    // 设置渲染状态
    virtual void SetStateSet() { m_bDirtyStateSet = false; }
    virtual void Update(){ } // 更新
protected:
    std::string     m_strName;          // 该2D图形的名称，以便调试
    bool            m_bVisible;         // 是否可见
    bool            m_bDirtyModel;      // 场景图内容是否失效
    bool            m_bDirtyStateSet;   // 渲染状态是否失效
    bool            m_bDirtyData;       // 数据值是否更改
};

typedef std::vector< ref_ptr<CVBF_Graphics> > CVBF_GraphicsList;


//-----------------------------------------------------
// 定义枚举：EVBF_CANVAS_ORIGN_MODE
// 枚举描述：画布坐标原点的类型
//-----------------------------------------------------
enum EVBF_CANVAS_ORIGN_MODE
{
    VBF_CANVAS_ORIGN_LOWER_LEFT    = 0,     // 画布原点位于屏幕左下角（默认值）
    VBF_CANVAS_ORIGN_UPPER_LEFT    = 1      // 画布原点位于屏幕左上角
};


//=============================================================================
// 定义类：CVBF_GraphicsCanvas
// 类描述：2D图形的画布，是图形的总容器，继承自一个正射相机
//=============================================================================
class VBF_HUDAUX_EXPORT CVBF_GraphicsCanvas : public osg::Camera
{
public:

    // 静态函数：获取与View关联的图形画布
    // 参数：bInstallInSceneData -- 是否需要将画布添加到场景图中
    static CVBF_GraphicsCanvas* Get(IVBF_View* pIView, bool bInstallInSceneData=true);

private:
    typedef std::map<IVBF_View*, CVBF_GraphicsCanvas*> CVBF_ViewCanvasMap;

    static CVBF_ViewCanvasMap ms_mapViewCanvas;
    static OpenThreads::Mutex ms_ViewCanvasMapMutex;


public:
    CVBF_GraphicsCanvas(IVBF_View* pIView);
    virtual ~CVBF_GraphicsCanvas();

    // 设置画布所在的图形环境
    void SetGraphicsContext(const CVBF_GraphicsContext& cx);

    // 设置/获取画布的坐标原点类型
    void SetCoordOrignMode(EVBF_CANVAS_ORIGN_MODE mode);
    EVBF_CANVAS_ORIGN_MODE GetCoordOrignMode()  { return m_nCoordOrignMode; }

    // 添加一个2D图形
    void AddGraphics(CVBF_Graphics* pGraphics);

    // 移除一个2D图形
    void RemoveGraphics(CVBF_Graphics* pGraphics);
    void RemoveGraphics(const std::string& strName);

    // 移除所有2D图形
    void RemoveAll();

    // 获取画布中具有指定名称的所有2D图形（图形的名称允许重复）
    void GetGraphicsList(const std::string& strName, CVBF_GraphicsList& vGraphics);

    // 获取画布中具有指定名称的第一个2D图形
    CVBF_Graphics* GetFirstGraphics(const std::string& strName);

    // 获取画布中的所有2D图形
    const CVBF_GraphicsList& GetGraphicsList() const { return m_vGraphics; }

    // 重载函数
    virtual void traverse(osg::NodeVisitor& nv);

    // 处理交互事件
    bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

private:
    CVBF_GraphicsCanvas(IVBF_View* pIView, bool bRegisterCanvas);

    // 初始化画布
    void Init(IVBF_View* view, bool bRegisterCanvas);

    // 每帧绘制前更新
    void Update();

    // 颠倒顶点坐标
    void FlipVerts(osg::Drawable* pDrawable);

private:
    CVBF_GraphicsContext        m_Context;              // 画布所在的环境（视图、视口等）
//    bool                        m_bContextDirty;        // 图形环境是否改变了
//    bool                        m_bUpdatePending;
    EVBF_CANVAS_ORIGN_MODE      m_nCoordOrignMode;      // 坐标原点类型

    // 画布中的2D图形
    CVBF_GraphicsList           m_vGraphics;            // 所有参与绘制的2D图形
    CVBF_GraphicsList           m_vGraphicsToAdd;       // 所有待添加的2D图形
    CVBF_GraphicsList           m_vGraphicsToRemove;    // 所有待移除的2D图形
    CVBF_GraphicsGeodeMap       m_mapGraphicsGeode;     // 映射表：每个2D图形与其对应的叶节点

    typedef std::map< observer_ptr<osgGA::GUIEventHandler>, observer_ptr<IVBF_View> > CVBF_EventHandlersMap;
    CVBF_EventHandlersMap       m_mapEventHandlers;     // 事件处理器列表，为了析构时从View中清除
};


#endif
