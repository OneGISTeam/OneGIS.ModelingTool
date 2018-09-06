#ifndef OSG_VIEW
#define OSG_VIEW 1

#include <VBF_Base/VBF_Stats.h>
//#include <OpenThreads/Mutex>

#include <VBF_Engine/VBF_SceneGraph/IVBF_ViewBrief.h>

namespace osg {

class OSG_EXPORT Slave : public IVBF_Slave
{
public:
	// IE可能错误
	Slave(bool useMastersSceneData=true):
        _useMastersSceneData(useMastersSceneData) {}
              // IE可能错误  
    Slave(osg::IVBF_Camera* camera, const osg::Matrixd& projectionOffset, const osg::Matrixd& viewOffset, bool useMastersSceneData=true):
        _camera(camera), 
        _projectionOffset(projectionOffset), 
        _viewOffset(viewOffset),
        _useMastersSceneData(useMastersSceneData) {}
        
    Slave(const Slave& rhs) : // IE可能错误
        _camera(rhs._camera), 
        _projectionOffset(rhs._projectionOffset), 
        _viewOffset(rhs._viewOffset),
        _useMastersSceneData(rhs._useMastersSceneData),
        _updateSlaveCallback(rhs._updateSlaveCallback) {}
// IE可能错误
    virtual ~Slave() {}

    Slave& operator = (const Slave& rhs)
    {
        _camera = rhs._camera;
        _projectionOffset = rhs._projectionOffset;
        _viewOffset = rhs._viewOffset;
        _useMastersSceneData = rhs._useMastersSceneData;
        _updateSlaveCallback = rhs._updateSlaveCallback;
        return *this;
    }

	virtual osg::Matrixd& GetProjectionOffsetMatrix() { return _projectionOffset; }
	virtual const osg::Matrixd& GetProjectionOffsetMatrix() const { return _projectionOffset; }
	
	virtual osg::Matrixd& GetViewOffsetMatrix() { return _projectionOffset; }
	virtual const osg::Matrixd& GetViewOffsetMatrix()const { return _projectionOffset; }
	
	virtual ref_ptr<osg::IVBF_Camera>& GetCamera() { return _camera; }
	virtual const ref_ptr<osg::IVBF_Camera>& GetCamera() const { return _camera; }

	virtual ref_ptr<IVBF_UpdateSlaveCallback>& GetUpdateSlaveCallback() { return _updateSlaveCallback; } 

	virtual bool IsUseMastersSceneData() { return _useMastersSceneData; }
	virtual void SetUseMastersSceneData(bool bUse) { _useMastersSceneData = bUse; }



	
    virtual void updateSlave(IVBF_ViewBrief& view)// 根据主相机更新子相机
    {
        if (_updateSlaveCallback.valid()) _updateSlaveCallback->updateSlave(view, *this); // 外部实现
        else updateSlaveImplementation(view);                                             // 默认实现
    }
            
    virtual void updateSlaveImplementation(IVBF_ViewBrief& view);
public:
    ref_ptr<osg::IVBF_Camera>           _camera;
protected:
private:

    osg::Matrixd                             _projectionOffset;
    osg::Matrixd                             _viewOffset;	
    bool                                     _useMastersSceneData;// 帮助管理HUD和RTT的相机that are embedded in the Viewer's CVBF_ViewBrief
    ref_ptr<IVBF_UpdateSlaveCallback>   _updateSlaveCallback;
};

}

#endif
