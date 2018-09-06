#ifndef __VBF_EARTH_MANIPULATOR_EX_H__
#define __VBF_EARTH_MANIPULATOR_EX_H__

#include "VBF_3DMapAux/VBF_3DManipulator/VBF_EarthManipulator.h"
#include <VBF_3DMapAux/VBF_3DManipulator/VBF_3DManipulator_Global.h>

class VBF_3DMANIPULATORSHARED_EXPORT CVBF_EarthManipulatorEx : public VBF_EarthManipulator
{
    typedef VBF_EarthManipulator BaseClass;
public:
    CVBF_EarthManipulatorEx();

    // �����¼�, ����Ѿ������� true,���򷵻� false.
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

    // ������������
    void ZoomIn(double dScale);					// �Ŵ���ZoomOut��ż��dScaleС��1����С
    void ZoomOut(double dScale);				// ��С

    void Forward(double dStep);					// ǰ������Backward��ż��dStepΪ��������
    void Backward(double dStep);				// ����
    void Left(double dStep);					// ���ƣ���Right��ż��dStepΪ��������
    void Right(double dStep);					// ����

    void PitchUp(double dAngle);				// ��ֱ��ת������
    void PitchDown(double dAngle);				// ��ֱ��ת������

    void RotateCCW(double dAngle);				// ˮƽ��ת��˳ʱ��
    void RotateCW(double dAngle);				// ˮƽ��ת����ʱ��


    // �������Բ���
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


    // �������Բ�������
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

    // �����ӵ�߶ȼ������űȣ��ӵ�Խ�ͣ����ű�ԽС����Ө��ӣ�2017-03-06��
    float CalZoomFactorFromEyeHeight(double dEyeHeight);


    double	m_dTimeLast;//��һ֡��ʱ��
    double	m_dTimeNow;//��ǰ֡��ʱ��
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

    bool m_bAutoZoomIn;   // ���ԷŴ�
    bool m_bAutoZoomOut;  // ������С


    double m_dRotate;
    double m_dPitch;
    double m_dFront;
    double m_dLR;
    double m_dZoom;

    // ����״̬
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
