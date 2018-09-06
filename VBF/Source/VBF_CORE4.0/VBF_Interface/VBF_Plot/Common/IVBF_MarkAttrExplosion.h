//*******************************************************************
// FileName：IVBF_MarkAttrExplosion.h
// Function：模型属性接口：爆炸
// Author:   杜莹
// Date:     2014-12-02
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_EXPLOSION_H__
#define __IVBF_MARK_ATTR_EXPLOSION_H__


#include <VBF_Plot/IVBF_MarkAttr.h>


class IVBF_MarkAttrExplosion : public IVBF_MarkAttr
{
public:
	virtual ~IVBF_MarkAttrExplosion() {}

	// 设置/获取爆炸开始的时间（从该爆炸属性被添加到模型之后起算，单位：秒）
	virtual void  SetStartTime(float fTime)=0;
	virtual float GetStartTime()=0;

	// 设置/获取相邻两幅爆炸纹理切换的帧间隔（默认值为2）
	virtual void SetFrameInterval(int nFrameInterval)=0;
	virtual int  GetFrameInterval()=0;

	// 设置/获取爆炸时的声音文件（完整路径）
	virtual void               SetSoundFileName(const std::string& strFileName)=0;
	virtual const std::string& GetSoundFileName()=0;

	// 设置/获取爆炸半径（单位：米）
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
