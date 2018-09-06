#ifndef OSGEARTH_TERRAIN_EFFECT_H
#define OSGEARTH_TERRAIN_EFFECT_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>

class CVBFO_SGNodeTerrainEngine;

namespace osgEarth
{  
    // ����Ч������TerrainEngineNodeʹ�õ�Ч�������Ե���TerrainEngineNode::addEffect()�������������Ч��
    // һ������Ч���������κ����飬ͨ����ʹ��ĳ�ַ�������״̬�����磬�Զ�����ɫ����
    class IVBF_TerrainEffect : public CVBF_Referenced
    {
    public:
        // ����װ��Ч��ʱ�������������
        virtual void onInstall(CVBFO_SGNodeTerrainEngine* engine) { }

        // ��ж�ظ�Ч��ʱ�������������
        virtual void onUninstall(CVBFO_SGNodeTerrainEngine* engine) { }

    public: // ���ڴ��л�
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }

    protected:
        IVBF_TerrainEffect() { }
        virtual ~IVBF_TerrainEffect() { }
    };
}
#endif
