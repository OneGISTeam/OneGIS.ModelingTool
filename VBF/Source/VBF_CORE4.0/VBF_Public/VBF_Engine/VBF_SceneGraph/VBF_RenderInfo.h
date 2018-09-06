#ifndef OSG_RENDERINFO
#define OSG_RENDERINFO 1


#include <VBF_Engine/VBF_SceneGraph/IVBF_ViewBrief.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_StateMachine.h>


namespace osg {



/* ��Ⱦ��Ϣ��������������ÿ֡������£����𱣴�͹����볡��������صļ�����Ҫ���ݣ���ǰ�������Ӿ�������ǰ������Ӧ�������������
   ��ǰ����OpenGL��Ⱦ״̬�Ͷ������ݣ�ʹ��State�ౣ�棩
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

	// ����/��ȡ��ǰ��״̬��
	void  setState(State* state) { _state = state; }    
	const State* getState() const { return _state.get(); }
		  State* getState() { return _state.get(); }

  
	// ����/��ȡ��ǰ����ͼ
	void  setView(IVBF_ViewBrief* view) { _view = view; }    
	const IVBF_ViewBrief* getView() const { return _view; }
		  IVBF_ViewBrief* getView() { return _view; }

    // ѹ��/�������
    void pushCamera(IVBF_Camera* camera) { _cameras.push_back(camera); }    
    void popCamera() { if (!_cameras.empty()) _cameras.pop_back(); }    

	// ��ȡ��ǰ�����
    IVBF_Camera* getCurrentCamera() { return _cameras.empty() ? 0 : _cameras.back(); }

	// ����/��ȡ�û��Զ�������
    void  setUserData(::CVBF_Referenced* userData) { _userData = userData; }
    const ::CVBF_Referenced* getUserData() const { return _userData.get(); }    
	      ::CVBF_Referenced* getUserData() { return _userData.get(); }


protected:

    typedef std::vector<IVBF_Camera*> Cameras;

    ref_ptr<State>          _state;		// ״̬��
    IVBF_ViewBrief*         _view;		// ��ͼ
    Cameras                 _cameras;	// �����ջ
    ref_ptr< ::CVBF_Referenced >     _userData;
};

}

#endif
