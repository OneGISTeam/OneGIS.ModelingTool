#ifndef __VBF_EFFECT_FLICKER_H__
#define __VBF_EFFECT_FLICKER_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>


class VBF_GLAUX_EXPORT CVBF_FlickerCallback : public ::CVBF_Referenced
{
public:
	
    CVBF_FlickerCallback(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways)
    {
		m_nFlickerTimes		= nFlickerTimes;
		m_nFlickerInterval	= nFlickerInterval;
		m_bFlickerAlways	= bFlickerAlways;

		m_nElapsTimes		= 0;
		m_nElapsFrames		= 0;	
		m_bFrameVisible		= false;
	}
    
    virtual void Step()
    {
		m_nElapsFrames++;

		if(m_bFlickerAlways) // 一直闪烁
		{
			if( (m_nElapsFrames % m_nFlickerInterval)==0 ) 
			{
				m_nElapsFrames  = 0;
				m_bFrameVisible = !m_bFrameVisible;
			} 
		}		
		else // 只闪烁几次
		{
			if( m_nElapsTimes < m_nFlickerTimes )
			{
				if( (m_nElapsFrames % m_nFlickerInterval)==0 )
				{
					m_nElapsFrames = 0;
					m_bFrameVisible = !m_bFrameVisible;
					if(m_bFrameVisible) m_nElapsTimes++;
				}				
			} 
			else
			{		
				m_bFrameVisible = true;
			}
		}
	}	

	// 判断本帧是否可见
	bool IsFrameVisible() { return m_bFrameVisible; }

protected:		

	// 用户设置的变量
	int			m_nFlickerTimes;		// 闪烁的总次数
	int			m_nFlickerInterval;		// 两次闪烁之间的帧数间隔	
	bool		m_bFlickerAlways;		// 是否一直闪烁，如果为true，参数m_nFlickerTimes将被忽略

	// 内部变量
	int			m_nElapsFrames;			// 已经过去的帧数
	int			m_nElapsTimes;			// 已经闪烁的次数
	bool		m_bFrameVisible;		// 本帧是否可见
};

class CVBF_FlickerCallbackNode : public osg::NodeCallback
{
public:

	CVBF_FlickerCallbackNode(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways)
    {
		m_piCallback = new CVBF_FlickerCallback(nFlickerTimes, nFlickerInterval, bFlickerAlways);
	}

	virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv)
    {
		if( m_piCallback.valid() )
		{
			m_piCallback->Step();
			if(m_piCallback->IsFrameVisible()) traverse(node, nv);  // 问题：如果node为叶节点，该做法无效
		}
	}	

private:
	ref_ptr<CVBF_FlickerCallback>	m_piCallback;
};


class CVBF_FlickerCallbackDrawable : public osg::Drawable::CullCallback
{
public:

	CVBF_FlickerCallbackDrawable(int nFlickerTimes, int nFlickerInterval, bool bFlickerAlways)
    {
		m_piCallback = new CVBF_FlickerCallback(nFlickerTimes, nFlickerInterval, bFlickerAlways);
	}

	virtual bool cull(osg::NodeVisitor*, osg::Drawable*, osg::State*) const
	{
		if( m_piCallback.valid() )
		{
			m_piCallback->Step();
			return (!m_piCallback->IsFrameVisible());
		}

		return false;
	}

private:
	ref_ptr<CVBF_FlickerCallback>	m_piCallback;
};


#endif
