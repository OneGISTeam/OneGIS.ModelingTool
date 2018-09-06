#ifndef OSGEARTHUTIL_VERTICAL_SCALE_H
#define OSGEARTHUTIL_VERTICAL_SCALE_H

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_Engine/VBF_SceneGraph/Uniform>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Base/observer_ptr>


namespace osgEarth { namespace Util
{

	// ���Ƶ��εĴ�ֱ����
    class OSGEARTHUTIL_EXPORT VerticalScale
    {
    public:
        VerticalScale();
        virtual ~VerticalScale();

		// ���ù����ĵ��νڵ�
        void setTerrainNode( osg::IVBF_SGNode* node );

		// ���ñ������ӣ�Ĭ��Ϊ1��
        void setScale( float value );
        float getScale() const { return _scale; }

    protected:
        observer_ptr<osg::IVBF_SGNode> _terrain;
        float                        _scale;

        ref_ptr<osg::Uniform>   _scaleUniform;
    };

    // ���Ƶ��εĸ߶�
    class OSGEARTHUTIL_EXPORT CVBF_HeightLimit:public CVBF_Referenced
    {
    public:
        CVBF_HeightLimit();
        virtual ~CVBF_HeightLimit();

        // ���ù����ĵ��νڵ�
        void setTerrainNode( osg::IVBF_SGNode* pINode );

        // ���ø߶�
        void  SetHeight( float fH ,osg::Vec4f vBound);
        float GetHeight() const { return m_fHeight; }

    protected:
        void Cancel(osg::IVBF_SGNode* pINode);// ȡ��

        observer_ptr<osg::IVBF_SGNode> _terrain;
        float      m_fHeight;
        osg::Vec4f m_vBound;

        ref_ptr<osg::Uniform> m_ipHeightUniform;
        ref_ptr<osg::Uniform> m_ipBoundUniform;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTHUTIL_VERTICAL_SCALE_H
