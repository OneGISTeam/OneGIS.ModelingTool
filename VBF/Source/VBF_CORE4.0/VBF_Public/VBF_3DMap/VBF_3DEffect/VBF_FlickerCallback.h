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

		if(m_bNeverStop) // һֱ��˸
		{
			if( (m_nElapsFrames % m_nFlickerInterval)==0 ) 
			{
				m_nElapsFrames  = 0;
				m_bFrameVisible = !m_bFrameVisible;
			} 
		}		
		else // ֻ��˸����
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
	int			m_nFlickerTimes;	// ��˸���ܴ���
	int			m_nFlickerInterval;	// ������˸֮���֡�����	
	bool		m_bNeverStop;		// �Ƿ�һֱ��˸�����Ϊtrue������nCount��������
	int			m_nElapsFrames;		// �Ѿ���ȥ��֡��
	int			m_nElapsTimes;		// �Ѿ���˸�Ĵ���
	bool		m_bFrameVisible;	// ��֡�Ƿ�ɼ�
};

#endif
