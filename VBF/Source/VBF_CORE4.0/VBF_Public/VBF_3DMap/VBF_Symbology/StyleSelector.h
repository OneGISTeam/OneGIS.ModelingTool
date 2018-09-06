#ifndef OSGEARTHSYMBOLOGY_STYLE_SELECTOR_H
#define OSGEARTHSYMBOLOGY_STYLE_SELECTOR_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>
#include <VBF_3DMap/VBF_Symbology/Query.h>
namespace osgEarth { namespace Symbology 
{

    // StyleSelector���ڰ�����������ѯ����styles���ࡣ
    // Ĭ������£�selector��ѡ�����Լ�ͬ����style������ͨ������styleName���Ը���Ĭ��ֵ
    class OSGEARTHSYMBOLOGY_EXPORT StyleSelector
    {
    public:
        StyleSelector( const CVBF_Config& conf =CVBF_Config() );
        virtual ~StyleSelector();

    public:
        //IE���� std::string& name() { return m_sName; }
        const std::string& name() const { return m_sName; }

        // ѡ���style������
        CVBF_Optional<std::string>& styleName() { return _styleName; }
        const CVBF_Optional<std::string>& styleName() const { return _styleName; }

        // Script that returns the name of the style to select
        CVBF_Optional<StringExpression>& styleExpression() { return _styleExpression; }
        const CVBF_Optional<StringExpression>& styleExpression() const { return _styleExpression; }

        // ����ѡ��ı��ʽ����ռ��������
        CVBF_Optional<Query>& query() { return _query; }
        const CVBF_Optional<Query>& query() const { return _query; }

        /** Returns the styleClass() property, if set; otherwise returns the selector name. */
        std::string getSelectedStyleName() const;

        //Configurable
        virtual void mergeConfig( const CVBF_Config& conf );
        virtual CVBF_Config getConfig() const;

    protected:
        std::string                m_sName;
        CVBF_Optional<std::string>      _styleName;
        CVBF_Optional<StringExpression> _styleExpression;
        CVBF_Optional<Query>            _query;
    };

    typedef std::list<StyleSelector>   StyleSelectorList;
    typedef std::vector<StyleSelector> StyleSelectorVector;

} } // namespace osgEarth::Symbology


#endif // OSGEARTHSYMBOLOGY_STYLE_SELECTOR_H
