//*******************************************************************
// FileName：IVBF_MarkAttrShipTrail.h
// Function：模型属性接口：舰船航迹
// Author:   杜莹
// Date:     2014-12-02
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_SHIP_TRAIL_H__
#define __IVBF_MARK_ATTR_SHIP_TRAIL_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


class IVBF_MarkAttrShipTrail : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrShipTrail() {}

    // 设置/获取头部航迹的宽度和高度（单位：米）
    virtual void SetFrontSize(float fWidth, float fHeight)=0;
    virtual void GetFrontSize(float& fWidth, float& fHeight)=0;

    // 设置/获取尾部航迹的宽度和高度（单位：米）
    virtual void SetBackSize(float fWidth, float fHeight)=0;
    virtual void GetBackSize(float& fWidth, float& fHeight)=0;

	// 设置头部航迹起点相对于模型中心点的偏移量（默认值为(0, 0, 0)）
	virtual void SetFrontOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
	virtual void GetFrontOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;

	// 设置尾部航迹起点相对于模型中心点的偏移量（默认值为(0, 0, 0)）
	virtual void SetBackOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
	virtual void GetBackOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;
};


#endif 
