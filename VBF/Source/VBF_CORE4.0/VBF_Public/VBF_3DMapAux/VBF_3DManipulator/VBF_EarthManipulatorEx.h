#ifndef __VBF_EARTH_MANIPULATOR_EX_H__
#define __VBF_EARTH_MANIPULATOR_EX_H__

#include "VBF_3DMapAux/VBF_3DManipulator/VBF_EarthManipulator.h"
#include <VBF_3DMapAux/VBF_3DManipulator/VBF_3DManipulator_Global.h>

class VBF_3DMANIPULATORSHARED_EXPORT CVBF_EarthManipulatorEx : public VBF_EarthManipulator
{
    typedef VBF_EarthManipulator BaseClass;
public:
    CVBF_EarthManipulatorEx();

    // 处理事件, 如果已经处理返回 true,否则返回 false.
    virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa)
    {
        bool bHandled = BaseClass::handle(ea,aa);
        if(bHandled) return true;

        switch(ea.getEventType())
        {
        case osgGA::GUIEventAdapter::FRAME:
            OnFrame( ea, aa );
            break;
        case osgGA::GUIEventAdapter::PUSH:
            OnMouseDown( ea, aa );
            break;

        case osgGA::GUIEventAdapter::RELEASE:
            OnMouseUp( ea, aa );
            break;

        case osgGA::GUIEventAdapter::SCROLL:
            OnMouseScroll( ea, aa );
            break;

        case osgGA::GUIEventAdapter::KEYDOWN:
            OnKeyDown( ea, aa );
            break;

        case osgGA::GUIEventAdapter::KEYUP:
            OnKeyUp( ea, aa );
            break;
        }
        return false;
    }
public:
    void OnFrame(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
    void OnMouseDown(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
    void OnMouseUp(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
    void OnMouseScroll(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
    void OnKeyDown(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
    void OnKeyUp(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

    void EnableAutoRotate(bool bAuto, float fTimeWait=0.0);

private:

    // 场景基本操作
    void ZoomIn(double dScale);					// 放大，与ZoomOut对偶，dScale小于1即缩小
    void ZoomOut(double dScale);				// 缩小

    void Forward(double dStep);					// 前进，与Backward对偶，dStep为负即后退
    void Backward(double dStep);				// 后退
    void Left(double dStep);					// 左移，与Right对偶，dStep为负即右移
    void Right(double dStep);					// 右移

    void PitchUp(double dAngle);				// 垂直旋转，向上
    void PitchDown(double dAngle);				// 垂直旋转，向下

    void RotateCCW(double dAngle);				// 水平旋转，顺时针
    void RotateCW(double dAngle);				// 水平旋转，逆时针


    // 场景惯性操作
    void AutoFrameOrtho();
    void AutoFrameNorth();
    void AutoFrameIncline();
    void AutoFrameRotateCCW();
    void AutoFrameRotateCW();
    void AutoFramePicthUp();
    void AutoFramePicthDown();
    void AutoFrameFoward();
    void AutoFrameBackward();
    void AutoFrameLeft();
    void AutoFrameRight();
    void AutoFrameZoomIn(double dEyeHeight);
    void AutoFrameZoomOut(double dEyeHeight);
    void AutoFrameRotate();


    // 场景惯性操作开关
    void EnableAutoNorth(bool bAuto){ m_bAutoNorth = bAuto;}
    void EnableAutoOrtho(bool bAuto){ m_bAutoOrtho = bAuto;}
    void EnableAutoIncline(bool bAuto){ m_bAutoIncline = bAuto;}

    void EnableAutoRotateCCW(bool bAuto);
    void EnableAutoRotateCW(bool bAuto);
    void EnableAutoPitchUp(bool bAuto);
    void EnableAutoPitchDown(bool bAuto);

    void EnableAutoFoward(bool bAuto);
    void EnableAutoBackward(bool bAuto);
    void EnableAutoLeft(bool bAuto);
    void EnableAutoRight(bool bAuto);

    void EnableAutoZoomIn(bool bAuto) { m_bAutoZoomIn	= bAuto; }
    void EnableAutoZoomOut(bool bAuto){ m_bAutoZoomOut	= bAuto; }

    bool IsAutoRotate();
    void SetAutoZoomRangeValue(double fValue);

    // 根据视点高度计算缩放比（视点越低，缩放比越小，杜莹添加：2017-03-06）
    float CalZoomFactorFromEyeHeight(double dEyeHeight);


    double	m_dTimeLast;//上一帧的时间
    double	m_dTimeNow;//当前帧的时间
    double	m_delta_t;
    float	m_fRotateWaitTime;


    bool m_bAutoNorth;
    bool m_bAutoOrtho;
    bool m_bAutoIncline;
    bool m_bAutoRotateCCW;
    bool m_bAutoRotateCW;
    bool m_bAutoPitchUp;
    bool m_bAutoPitchDown;
    bool m_bAutoRotate;

    bool m_bAutoFoward;
    bool m_bAutoBackward;
    bool m_bAutoLeft;
    bool m_bAutoRight;

    bool m_bAutoZoomIn;   // 惯性放大
    bool m_bAutoZoomOut;  // 惯性缩小


    double m_dRotate;
    double m_dPitch;
    double m_dFront;
    double m_dLR;
    double m_dZoom;

    // 键盘状态
    bool m_bLeftPressed;
    bool m_bRightPressed;
    bool m_bUpPressed;
    bool m_bDownPressed;
    bool m_bShiftPressed;
    bool m_bLCtrlPressed;
    bool m_bRCtrlPressed;

    bool m_bAPressed;
    bool m_bZPressed;

};


#endif
