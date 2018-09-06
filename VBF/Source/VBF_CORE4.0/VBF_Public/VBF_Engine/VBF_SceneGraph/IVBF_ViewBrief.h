#ifndef IVBF_VIEW_BRIEF_H
#define IVBF_VIEW_BRIEF_H 1

#include <Types/VBF_Matrixf.h>
#include <Types/VBF_Matrixd.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLight.h>	

namespace osg {

class IVBF_Slave;

class IVBF_ViewBrief : virtual public osg::CVBF_Object
{
public:
	enum LightingMode // ��ͼ��ȫ�ֹ�ѡ��
	{
		NO_LIGHT,
		HEADLIGHT,
		SKY_LIGHT
	};

    // ����/��ȡ��ͼ��ȫ�ֹ�ѡ�Ĭ����HEADLIGHT
	virtual void setLightingMode(LightingMode lightingMode)=0;
	virtual LightingMode getLightingMode() const =0;

    // ����/��ȡ��ͼ��ȫ�ֹ�
	virtual void setLight(osg::Light* light)=0;
	virtual osg::Light* getLight()=0;
	virtual const osg::Light* getLight() const =0;

	// ����/��ȡ�����
    virtual void setCamera(osg::IVBF_Camera* camera)=0;
    virtual osg::IVBF_Camera* getCamera()=0;
    virtual const osg::IVBF_Camera* getCamera() const =0;

    virtual void setFrameStamp(::CVBF_FrameStamp* fs)  =0;
    virtual ::CVBF_FrameStamp* getFrameStamp()  =0;
    virtual const ::CVBF_FrameStamp* getFrameStamp() const =0;

    virtual bool addSlave(osg::IVBF_Camera* camera, bool useMastersSceneData=true)  =0;
    virtual bool addSlave(osg::IVBF_Camera* camera, const osg::Matrix& projectionOffset, const osg::Matrix& viewOffset, bool useMastersSceneData=true) =0;
    virtual bool removeSlave(unsigned int pos) =0;

    virtual unsigned int getNumSlaves() const =0;

    virtual IVBF_Slave& getSlave(unsigned int pos) =0;
    virtual const IVBF_Slave& getSlave(unsigned int pos) const  =0;

    virtual unsigned int findSlaveIndexForCamera(osg::IVBF_Camera* camera) const =0;
    virtual IVBF_Slave* findSlaveForCamera(osg::IVBF_Camera* camera) =0;

};


class IVBF_UpdateSlaveCallback : public virtual ::CVBF_Referenced
{
public:
	virtual void updateSlave(osg::IVBF_ViewBrief& view, osg::IVBF_Slave& slave) = 0;
};

/** Slave allows one to up a camera that follows the master with a local offset to the project and view matrices.*/
/*��ν����������书����Ҫ��ʵ��ͬһ�����ķִ����Լ�����Ļ��ʾ���μ�osgcamera ���ӣ���*/
class IVBF_Slave
{
public:
	virtual osg::Matrixd& GetProjectionOffsetMatrix()=0;
	virtual const osg::Matrixd& GetProjectionOffsetMatrix() const =0;

	virtual osg::Matrixd& GetViewOffsetMatrix()=0;
	virtual const osg::Matrixd& GetViewOffsetMatrix()const =0;

	virtual ref_ptr<osg::IVBF_Camera>& GetCamera()=0;
	virtual const ref_ptr<osg::IVBF_Camera>& GetCamera() const =0;

	virtual ref_ptr<IVBF_UpdateSlaveCallback>& GetUpdateSlaveCallback() = 0;

	virtual bool IsUseMastersSceneData()=0;
	virtual void SetUseMastersSceneData(bool bUse) =0;

	virtual void updateSlave(IVBF_ViewBrief& view)=0;// ������������������
    virtual void updateSlaveImplementation(IVBF_ViewBrief& view)=0;

    virtual ~IVBF_Slave() {}
};
}
#endif
