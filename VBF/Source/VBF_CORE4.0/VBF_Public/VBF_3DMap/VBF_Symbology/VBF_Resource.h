#ifndef OSGEARTHSYMBOLOGY_RESOURCE_H
#define OSGEARTHSYMBOLOGY_RESOURCE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Tags.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <string>

namespace osgEarth { namespace Symbology
{
    // 符号资源的基类，由ResourceLibrary管理
    class OSGEARTHSYMBOLOGY_EXPORT Resource : public Taggable<CVBF_Referenced>
    {
    protected:
        Resource( const CVBF_Config& config =CVBF_Config() );
        virtual ~Resource();

    public:
        // 资源的名字
//IE死机        std::string& name() { return m_sName; }
        const std::string& name() const { return m_sName; }

    public: // 串行化功能
        virtual CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    private:
        std::string m_sName;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_SKIN_RESOURCE_H
