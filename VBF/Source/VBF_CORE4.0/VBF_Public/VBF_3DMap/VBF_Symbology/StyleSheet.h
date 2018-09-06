#ifndef OSGEARTHSYMBOLOGY_STYLE_SHEET_H
#define OSGEARTHSYMBOLOGY_STYLE_SHEET_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Symbology/StyleSelector.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolSkins.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceLibrary.h>

namespace osgEarth { namespace Symbology 
{
    // style��Ϣ����������
    class OSGEARTHSYMBOLOGY_EXPORT StyleSheet : public ::CVBF_Referenced
    {
    public:
        // ��Ҫ����
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

        void addStyle( const Style& style );// ���һ��Style
        void removeStyle( const std::string& name );// �Ƴ�һ��Style
        
        // ͨ�����ֻ�ȡһ��style������Ҳ�������Ĭ�ϵģ���ѡ�
        // ˵����������ֺ���hashtagǰ׺(��"#name")��ͬʱ�������Ͳ���hash������. (���߱���Ϊ�ǵȼ۵�)
        Style* getStyle( const std::string& name, bool fallBackOnDefault =true );
        const Style* getStyle( const std::string& name, bool fallBackOnDefault =true ) const;

        // ��ȡĬ�ϵ�style
        Style* getDefaultStyle();
        const Style* getDefaultStyle() const;

        // Selectors����������sheet����ѡһ��style
        StyleSelectorList& selectors() { return _selectors; }
        const StyleSelectorList& selectors() const { return _selectors; }
        const StyleSelector* getSelector( const std::string& name ) const;

        // ���һ����Դ��
        void addResourceLibrary( ResourceLibrary* library );

        // ͨ�����ֻ�ȡ��Դ��
        ResourceLibrary* getResourceLibrary( const std::string& name ) const;

        // ��Ҫ����
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
