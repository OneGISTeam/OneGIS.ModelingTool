#ifndef __IVBF_MARK_MODEL_NOT_POINT_H__
#define __IVBF_MARK_MODEL_NOT_POINT_H__


#include <VBF_Plot/IVBF_MarkModel.h>


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelNotPoint
// �ӿ��������ǵ�״ʵ��ģ��
//--------------------------------------------------------------------
class IVBF_MarkModelNotPoint : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelNotPoint() {}

public:
    // ����/��ȡ���Ƶ�ĵ������꣬���ڱ༭
    virtual void SetCtrlPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo) = 0;
    virtual std::vector<osg::Vec3d>& GetCtrlPointsGeo() = 0;

    virtual bool IsSameHeight() = 0;
    virtual void setHeight(double dHeight)=0;// ������Ҫ��������߶ȵ�ģ����˵����Ҫ����ӿ�
    virtual double getHeight()=0;


    // ���ȫ�ֱ༭�Ŀ��Ƶ㣨��γ�����꣩
    virtual osg::Vec3d GetLocationGeoPoint()=0;

};


#endif 
