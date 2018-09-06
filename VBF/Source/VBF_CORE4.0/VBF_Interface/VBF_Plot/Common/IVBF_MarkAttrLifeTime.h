//*******************************************************************
// FileName：IVBF_MarkAttrLifeTime.h
// Function：模型属性接口：生命期
// Author:   杜莹
// Date:     2015-04-14
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_LIFETIME_H__
#define __IVBF_MARK_ATTR_LIFETIME_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrLifeTime
// 接口描述：模型属性接口：生命期
//--------------------------------------------------------------------
class IVBF_MarkAttrLifeTime : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrLifeTime() {}

	// 设置生命期（单位：秒）
	virtual void   SetLifeTime(double dTime)=0;
	virtual double GetLifeTime()=0;
};



#endif 
