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

		if(m_bFlickerAlways) // һֱ��˸
		{
			if( (m_nElapsFrames % m_nFlickerInterval)==0 ) 
			{
				m_nElapsFrames  = 0;
				m_bFrameVisible = !m_bFrameVisible;
			} 
		}		
		else // ֻ��˸����
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

	// �жϱ�֡�Ƿ�ɼ�
	bool IsFrameVisible() { return m_bFrameVisible; }

protected:		

	// �û����õı���
	int			m_nFlickerTimes;		// ��˸���ܴ���
	int			m_nFlickerInterval;		// ������˸֮���֡�����	
	bool		m_bFlickerAlways;		// �Ƿ�һֱ��˸�����Ϊtrue������m_nFlickerTimes��������

	// �ڲ�����
	int			m_nElapsFrames;			// �Ѿ���ȥ��֡��
	int			m_nElapsTimes;			// �Ѿ���˸�Ĵ���
	bool		m_bFrameVisible;		// ��֡�Ƿ�ɼ�
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
			if(m_piCallback->IsFrameVisible()) traverse(node, nv);  // ���⣺���nodeΪҶ�ڵ㣬��������Ч
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
