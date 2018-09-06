#ifndef OSGGA_GUIACTIONADAPTER
#define OSGGA_GUIACTIONADAPTER 1 

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Engine/VBF_SceneGraph/VBF_CameraSlave.h>

/**
	抽象接口：用于向UI系统发出请求。
	事件处理器不仅接收事件进行处理，还希望向GUI请求一些操作。如，拖动模型并突然松开，使模型的持续旋转或移动。
	此时，事件处理器希望开启一个计时器，重复调用不停的刷新相机的位置和方向。
*/
class IVBF_GUIActionAdapter
{
public:
	virtual ~IVBF_GUIActionAdapter() {}

	virtual osg::IVBF_ViewBrief* asView() { return 0; }// 提供一种获取与之关联的View的机制。

	virtual void requestRedraw() = 0; // 请求重绘一次
	virtual void requestContinuousUpdate(bool needed=true) = 0; // 请求多次更新（空闲时不断绘制）
	virtual void requestWarpPointer(float x,float y) = 0;       // 请求光标位置重置

};

#endif

