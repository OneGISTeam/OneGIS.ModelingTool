#ifndef OSGEARTHSYMBOLOGY_SYMBOL_H
#define OSGEARTHSYMBOLOGY_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_Base/VBF_Referenced.h>
#include <vector>

#define META_Symbol(name) \
    virtual bool isSameKindAs(const Symbol* rhs) const { return dynamic_cast<const name *>(rhs)!=NULL; } \
    virtual const char* className() const { return #name; }


namespace osgEarth { namespace Symbology
{
    class OSGEARTHSYMBOLOGY_EXPORT Symbol : public ::CVBF_Referenced
    {
    public:
        const URIContext& uriContext() const { return _uriContext; }
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }

    public:
        virtual bool isSameKindAs(const Symbol* sym) const =0;
        virtual const char* className() const =0;

    protected:
        URIContext _uriContext; // 统一资源标识符上下文

		// 判断两个字符串是否相同（忽略大小写和"_"与"-"的区别）
        static bool match(const std::string& key, const char* pattern);

        Symbol( const CVBF_Config& conf = CVBF_Config() );
        virtual ~Symbol();
    };

    typedef std::vector<ref_ptr<Symbol> > SymbolList;

} } // namespace osgEarth::Symbology

#endif // OSGEARTH_SYMBOLOGY_SYMBOL_H
