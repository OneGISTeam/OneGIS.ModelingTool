#ifndef OSG_RENDERINFO
#define OSG_RENDERINFO 1


#include <VBF_Engine/VBF_SceneGraph/IVBF_ViewBrief.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_StateMachine.h>


namespace osg {



/* 渲染信息管理器：其内容每帧都会更新，负责保存和管理与场景绘制相关的几个重要数据：当前场景的视景器，当前场景对应的所有摄像机，
   当前所有OpenGL渲染状态和顶点数据（使用State类保存）
*/
class RenderInfo
{
public:

    RenderInfo():
        _view(0) {}

    RenderInfo(const RenderInfo& rhs):
        _state(rhs._state),
        _view(rhs._view),
        _cameras(rhs._cameras),
        _userData(rhs._userData) {}

    RenderInfo(State* state, IVBF_ViewBrief* view):
        _state(state),
        _view(view) {}
        
    RenderInfo& operator = (const RenderInfo& rhs)
    {
        _state    = rhs._state;
        _view     = rhs._view;
        _cameras  = rhs._cameras;
        _userData = rhs._userData;
        return *this;
    }

	unsigned int getContextID() const { return _state.valid() ? _state->getContextID() : 0; }

	// 设置/获取当前的状态机
	void  setState(State* state) { _state = state; }    
	const State* getState() const { return _state.get(); }
		  State* getState() { return _state.get(); }

  
	// 设置/获取当前的视图
	void  setView(IVBF_ViewBrief* view) { _view = view; }    
	const IVBF_ViewBrief* getView() const { return _view; }
		  IVBF_ViewBrief* getView() { return _view; }

    // 压入/弹出相机
    void pushCamera(IVBF_Camera* camera) { _cameras.push_back(camera); }    
    void popCamera() { if (!_cameras.empty()) _cameras.pop_back(); }    

	// 获取当前的相机
    IVBF_Camera* getCurrentCamera() { return _cameras.empty() ? 0 : _cameras.back(); }

	// 设置/获取用户自定义数据
    void  setUserData(::CVBF_Referenced* userData) { _userData = userData; }
    const ::CVBF_Referenced* getUserData() const { return _userData.get(); }    
	      ::CVBF_Referenced* getUserData() { return _userData.get(); }


protected:

    typedef std::vector<IVBF_Camera*> Cameras;

    ref_ptr<State>          _state;		// 状态机
    IVBF_ViewBrief*         _view;		// 视图
    Cameras                 _cameras;	// 相机堆栈
    ref_ptr< ::CVBF_Referenced >     _userData;
};

}

#endif
