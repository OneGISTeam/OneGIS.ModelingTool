#ifndef __IVBF_GEO_IMAGESTREAM_H__
#define __IVBF_GEO_IMAGESTREAM_H__

#include <VBF_Engine/VBF_SceneGraph/ImageStream>

namespace osg {

// 带有地理属性的图像流
class IVBF_GeoImageStream : public osg::ImageStream
{
public:
	IVBF_GeoImageStream() {}
	IVBF_GeoImageStream(const IVBF_GeoImageStream& image,const CopyOp& copyop=CopyOp::SHALLOW_COPY) : osg::ImageStream(image, copyop) {}

	// 获取经纬度范围
	virtual double GetL0()=0;
	virtual double GetL1()=0;
	virtual double GetB0()=0;
	virtual double GetB1()=0;

	virtual int GetNumX()=0;
    virtual int GetNumY()=0;
	virtual int GetNumDepth()=0;
};

}

#endif
