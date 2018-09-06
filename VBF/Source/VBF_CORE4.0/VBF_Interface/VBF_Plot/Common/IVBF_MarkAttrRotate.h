//*******************************************************************
// FileName：IVBF_MarkAttrRotate.h
// Function：模型属性接口：绕轴旋转
// Author:
// Date:     2013-10-22
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_ROTATE_H__
#define __IVBF_MARK_ATTR_ROTATE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


//--------------------------------------------------------------------
// 定义枚举：EVBF_ROTATE_TYPE
// 枚举描述：绕轴旋转的方式
//--------------------------------------------------------------------
enum EVBF_ROTATE_TYPE
{
	VBF_ROTATE_TYPE_CIRCLE		= 0,	// 循环
	VBF_ROTATE_TYPE_SWING		= 1,	// 摆动
	VBF_ROTATE_TYPE_POSITIVE	= 2,	// 单向旋转，正向
	VBF_ROTATE_TYPE_NEGATIVE	= 3,	// 单向旋转，负向
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrRotate
// 接口描述：模型属性接口的基类：绕某个轴旋转
//--------------------------------------------------------------------
class IVBF_MarkAttrRotate : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrRotate() {}

	// 设置/获取旋转方式
	virtual void			 SetRotateType(EVBF_ROTATE_TYPE nType)=0;
	virtual EVBF_ROTATE_TYPE GetRotateType()=0;

	// 设置/获取旋转的角度范围
	virtual void SetAngleRange(float fAngleMin, float fAngleMax)=0;
	virtual void GetAngleRange(float& fAngleMin, float& fAngleMax)=0;
	
	// 设置/获取旋转的速度（单位：度/秒）
	virtual void  SetSpeedAnglePerSecond(float fSpeed)=0;
	virtual float GetSpeedAnglePerSecond()=0;

	// 设置/获取在每个位置停留的帧数（默认值为0，即不停留）
	virtual void SetNumPausalFrames(int num)=0;
	virtual int  GetNumPausalFrames()=0;

	// 设置/获取当前的旋转角
	virtual void  SetAngleCurr(float fAngle)=0;
	virtual float GetAngleCurr()=0;
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrRotateX
// 接口描述：模型属性接口：绕X轴旋转
//--------------------------------------------------------------------
class IVBF_MarkAttrRotateX : public IVBF_MarkAttrRotate
{
public:
	virtual ~IVBF_MarkAttrRotateX() {}
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrRotateY
// 接口描述：模型属性：绕Y轴旋转
//--------------------------------------------------------------------
class IVBF_MarkAttrRotateY : public IVBF_MarkAttrRotate
{
public:
	virtual ~IVBF_MarkAttrRotateY() {}
};

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrRotateZ
// 接口描述：模型属性：绕Z轴旋转
//--------------------------------------------------------------------
class IVBF_MarkAttrRotateZ : public IVBF_MarkAttrRotate
{
public:
	virtual ~IVBF_MarkAttrRotateZ() {}
};

#endif 
