#ifndef OSGEARTHFEATURES_TEXT_SYMBOLIZER_H
#define OSGEARTHFEATURES_TEXT_SYMBOLIZER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/FilterContext.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolText.h>

#include <VBF_Engine/VBF_Text/Text>

namespace osgEarth { namespace Features
{
    using namespace osgEarth::Symbology;

    // 把文字转换成OSG文本对象
    class OSGEARTHFEATURES_EXPORT TextSymbolizer
    {
    public:
        TextSymbolizer( const TextSymbol* symbol );

        virtual ~TextSymbolizer() { }

        // 根据文字创建drawable
        osgText::Text* create( Feature* feature =0L, const FilterContext* context =0L,
                               const std::string& text="" ) const;

        osgText::Text* create( const std::string& text ) const
        {
            return create(0L, 0L, text);
        }

    protected:
        ref_ptr<const TextSymbol> _symbol;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_TEXT_SYMBOLIZER_H
