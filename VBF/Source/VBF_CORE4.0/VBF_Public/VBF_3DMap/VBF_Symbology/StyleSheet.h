#ifndef OSGEARTHSYMBOLOGY_STYLE_SHEET_H
#define OSGEARTHSYMBOLOGY_STYLE_SHEET_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Symbology/StyleSelector.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolSkins.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceLibrary.h>

namespace osgEarth { namespace Symbology 
{
    // style信息的完整定义
    class OSGEARTHSYMBOLOGY_EXPORT StyleSheet : public ::CVBF_Referenced
    {
    public:
        // 简要描述
        struct Script : CVBF_Referenced
        {
            Script(const std::string& code, const std::string& language="javascript", const std::string& name="") :
                code(code), language(language), name(name)
            {
            }
            ~Script() {}

            std::string code;
            std::string language;
            std::string name;
        };

    public:
        StyleSheet();
        StyleSheet( const CVBF_Config& conf );
        ~StyleSheet();

        /** Gets the context for relative path resolution */
        const URIContext& uriContext() const { return _uriContext; }

        void addStyle( const Style& style );// 添加一个Style
        void removeStyle( const std::string& name );// 移除一个Style
        
        // 通过名字获取一个style，如果找不到返回默认的（可选项）
        // 说明：如果名字含有hashtag前缀(如"#name")，同时搜索带和不带hash的名字. (二者被认为是等价的)
        Style* getStyle( const std::string& name, bool fallBackOnDefault =true );
        const Style* getStyle( const std::string& name, bool fallBackOnDefault =true ) const;

        // 获取默认的style
        Style* getDefaultStyle();
        const Style* getDefaultStyle() const;

        // Selectors按照条件从sheet中挑选一个style
        StyleSelectorList& selectors() { return _selectors; }
        const StyleSelectorList& selectors() const { return _selectors; }
        const StyleSelector* getSelector( const std::string& name ) const;

        // 添加一个资源库
        void addResourceLibrary( ResourceLibrary* library );

        // 通过名字获取资源库
        ResourceLibrary* getResourceLibrary( const std::string& name ) const;

        // 简要描述
        void setScript( Script* script );
        Script* script() const { return _script.get(); }

    public: // serialization functions

        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );

    protected:
        URIContext                   _uriContext;
        ref_ptr<Script>         _script;
        StyleSelectorList            _selectors;
        StyleMap                     _styles;
        Style                        _emptyStyle;
        
        typedef std::map<std::string, ref_ptr<ResourceLibrary> > ResourceLibraries;
        ResourceLibraries          _resLibs;
        CVBF_ReadWriteMutex  _resLibsMutex;

    };

} } // namespace osgEarth::Symbology


#endif // OSGEARTHSYMBOLOGY_STYLE_SHEET_H
