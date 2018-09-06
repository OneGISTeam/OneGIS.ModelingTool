#ifndef OSGEARTH_FADE_EFFECT_H
#define OSGEARTH_FADE_EFFECT_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/Uniform>


// �����嵭���������Ե�ѡ��
class OSGEARTH_EXPORT CVBF_FadeOptions
{
public:
    CVBF_FadeOptions(const CVBF_Config& conf =CVBF_Config());

	// ����ĳ���ʱ�䣨��λ�룩
    CVBF_Optional<float>& duration() { return _duration; }
    const CVBF_Optional<float>& duration() const { return _duration; }

 	// �������Ϊ���ɼ�ʱ�����߾���
    CVBF_Optional<float>& maxRange() { return _maxRange; }
    const CVBF_Optional<float>& maxRange() const { return _maxRange; }

	// ��ʼ����������ľ��루��maxRange֮��ľ��룩
    CVBF_Optional<float>& attentuationDistance() { return _attenDist; }
    const CVBF_Optional<float>& attenuationDistance() const { return _attenDist; }

public:
    virtual ~CVBF_FadeOptions() { }
    CVBF_Config getConfig() const;

private:
    CVBF_Optional<float> _duration;
    CVBF_Optional<float> _maxRange;
    CVBF_Optional<float> _attenDist;
};


// װ�νڵ㣬�������λ�ڸ�����elevation range�ڲ���ʾ���ӽڵ�
class OSGEARTH_EXPORT CVBFO_SGNodeFade : public osg::CVBF_SGNodeGroup
{
public:
    /**
        * Creates a uniform that set the start time for a timed fade. Typically you
        * will set this right after adding the node to the scene graph. The value
        * is a FLOAT in seconds. You can apply this uniform to the CVBFO_SGNodeFade node
        * or elsewhere in the scene graph.
        */
    static osg::Uniform* createStartTimeUniform();

public:
    CVBFO_SGNodeFade();
    virtual ~CVBFO_SGNodeFade() { }

    // ����/��ȡ����ĳ���ʱ�䣨��λ�룩
    void setFadeDuration( float seconds );
    float getFadeDuration() const;

 	// ����/��ȡ�ӽڵ��Ϊ���ɼ�ʱ�����߾���
    void setMaxRange( float range );
    float getMaxRange() const;

 	// ����/��ȡ��ʼ�����ӽڵ�ʱ�ľ��루��maxRange֮��ľ��룩
    void setAttenuationDistance( float dist );
    float getAttenuationDistance() const;

private:
    ref_ptr<osg::Uniform> _fadeDuration;
    ref_ptr<osg::Uniform> _maxRange;
    ref_ptr<osg::Uniform> _attenDist;
};


class OSGEARTH_EXPORT CVBFO_SGNodeLODFade : public osg::CVBF_SGNodeGroup
{
public:
    CVBFO_SGNodeLODFade();
    virtual ~CVBFO_SGNodeLODFade() { }

    void setMinPixelExtent( float value ) { _minPixelExtent = value; }
    float getMinPixelExtent() const { return _minPixelExtent; }

    void setMaxPixelExtent( float value ) { _maxPixelExtent = value; }
    float getMaxPixelExtent() const { return _maxPixelExtent; }

    void setMinFadeExtent( float value ) { _minFadeExtent = value; }
    float getMinFadeExtent() const { return _minFadeExtent; }

    void setMaxFadeExtent( float value ) { _maxFadeExtent = value; }
    float getMaxFadeExtent() const { return _maxFadeExtent; }

public: // osg::Node

    virtual void traverse(osg::NodeVisitor& nv );

protected:
    struct PerViewData
    {
        ref_ptr<osg::StateSet> _stateSet;
        ref_ptr<osg::Uniform>  _opacity;
    };
    CVBF_PerObjectMap<osg::NodeVisitor*, PerViewData> _perViewData;

    float _minPixelExtent;
    float _maxPixelExtent;
    float _minFadeExtent;
    float _maxFadeExtent;
};


#endif // OSGEARTH_FADE_EFFECT_H
