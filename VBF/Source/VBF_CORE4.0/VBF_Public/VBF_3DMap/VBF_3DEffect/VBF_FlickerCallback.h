#ifndef __VBF_FLICKER_CALLBACK_H__
#define __VBF_FLICKER_CALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>

class CVBF_FlickerCallback : public osg::NodeCallback
{
public:
    CVBF_FlickerCallback(int nFlickerTimes, int nFlickerInterval, bool bNeverStop)
    {
		m_nFlickerTimes		= nFlickerTimes;
		m_nFlickerInterval	= nFlickerInterval;
		m_bNeverStop		= bNeverStop;

		m_nElapsTimes		= 0;
		m_nElapsFrames		= 0;	
		m_bFrameVisible		= false;
	}
    
    virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv)
    {
		m_nElapsFrames++;

		if(m_bNeverStop) // 一直闪烁
		{
			if( (m_nElapsFrames % m_nFlickerInterval)==0 ) 
			{
				m_nElapsFrames  = 0;
				m_bFrameVisible = !m_bFrameVisible;
			} 
		}		
		else // 只闪烁几次
		{
			if( m_nElapsTimes <= m_nFlickerTimes+1 ) 
			{
				if( (m_nElapsFrames % m_nFlickerInterval)==0 )
				{
					m_nElapsFrames = 0;
					m_nElapsTimes++;
					m_bFrameVisible = !m_bFrameVisible;
				}				
			} 
			else
			{		
				m_bFrameVisible = true;
			}
		}
		

		if(m_bFrameVisible) traverse(node, nv);
	}	

protected:		
	int			m_nFlickerTimes;	// 闪烁的总次数
	int			m_nFlickerInterval;	// 两次闪烁之间的帧数间隔	
	bool		m_bNeverStop;		// 是否一直闪烁，如果为true，参数nCount将被忽略
	int			m_nElapsFrames;		// 已经过去的帧数
	int			m_nElapsTimes;		// 已经闪烁的次数
	bool		m_bFrameVisible;	// 本帧是否可见
};

#endif
