#ifndef OSGEARTHSYMBOLOGY_TEXT_SYMBOL_H
#define OSGEARTHSYMBOLOGY_TEXT_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>
#include <VBF_3DMap/VBF_Symbology/Fill.h>
#include <VBF_3DMap/VBF_Symbology/Stroke.h>

namespace osgEarth { namespace Symbology
{

	// 文本符号，渲染文字注记的符号
    class OSGEARTHSYMBOLOGY_EXPORT TextSymbol : public Symbol
    {
    public:
        enum Encoding 
		{
            ENCODING_ASCII,
            ENCODING_UTF8,
            ENCODING_UTF16,
            ENCODING_UTF32
        };

        // note: these are identical to the values in osgText::Text::AlignmentType
        enum Alignment 
		{
            ALIGN_LEFT_TOP,
            ALIGN_LEFT_CENTER,
            ALIGN_LEFT_BOTTOM,

            ALIGN_CENTER_TOP,
            ALIGN_CENTER_CENTER,
            ALIGN_CENTER_BOTTOM,

            ALIGN_RIGHT_TOP,
            ALIGN_RIGHT_CENTER,
            ALIGN_RIGHT_BOTTOM,
            
            ALIGN_LEFT_BASE_LINE,
            ALIGN_CENTER_BASE_LINE,
            ALIGN_RIGHT_BASE_LINE,
        
            ALIGN_LEFT_BOTTOM_BASE_LINE,
            ALIGN_CENTER_BOTTOM_BASE_LINE,
            ALIGN_RIGHT_BOTTOM_BASE_LINE,
        
            ALIGN_BASE_LINE = ALIGN_LEFT_BASE_LINE /// default.        
        };

        META_Symbol(TextSymbol);

        TextSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~TextSymbol();

		// 文本填充色（文字颜色）
        CVBF_Optional<Fill>& fill() { return _fill; }
        const CVBF_Optional<Fill>& fill() const { return _fill; }

		// 轮廓线颜色
        CVBF_Optional<Stroke>& halo() { return _halo; }
        const CVBF_Optional<Stroke>& halo() const { return _halo; }

		// 轮廓线偏移
        CVBF_Optional<float>& haloOffset() { return _haloOffset; }
        const CVBF_Optional<float>& haloOffset() const { return _haloOffset; }

		// 字体名字
        CVBF_Optional<std::string>& font() { return _font; }
        const CVBF_Optional<std::string>& font() const { return _font; }

		// 需要渲染的实际文本（如果可用）
        CVBF_Optional<StringExpression>& content() { return _content; }
        const CVBF_Optional<StringExpression>& content() const { return _content; }

		// 优先级of the label (applicable when the renderer sorts labels)
        CVBF_Optional<NumericExpression>& priority() { return _priority; }
        const CVBF_Optional<NumericExpression>& priority() const { return _priority; }

		// 字体大小
        CVBF_Optional<float>& size() { return _size; }
        const CVBF_Optional<float>& size() const { return _size; }

		// 偏移量（像素）
        CVBF_Optional<osg::Vec2s>& pixelOffset() { return _pixelOffset; }
        const CVBF_Optional<osg::Vec2s>& pixelOffset() const { return _pixelOffset; }

		// 文本对齐，相对于（0,0）像素
        CVBF_Optional<Alignment>& alignment() { return _alignment; }
        const CVBF_Optional<Alignment>& alignment() const { return _alignment; }

		// 绘制多个label时，是否移除重复的
        CVBF_Optional<bool>& removeDuplicateLabels() { return _removeDuplicateLabels; }
        const CVBF_Optional<bool>& removeDuplicateLabels() const { return _removeDuplicateLabels; }

		// 是否启用聚簇裁剪（如果可用的话）
        CVBF_Optional<bool>& declutter() { return _declutter; }
        const CVBF_Optional<bool>& declutter() const { return _declutter; }

        /** Label generation provider to use */
        CVBF_Optional<std::string>& provider() { return _provider; }
        const CVBF_Optional<std::string>& provider() const { return _provider; }

		// 文本的编码
        CVBF_Optional<Encoding>& encoding() { return _encoding; }
        const CVBF_Optional<Encoding>& encoding() const { return _encoding; }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<Fill>              _fill;
        CVBF_Optional<Stroke>            _halo;
        CVBF_Optional<float>             _haloOffset;
        CVBF_Optional<std::string>       _font;
        CVBF_Optional<float>             _size;
        CVBF_Optional<StringExpression>  _content;
        CVBF_Optional<NumericExpression> _priority;
        CVBF_Optional<bool>              _removeDuplicateLabels;
        CVBF_Optional<osg::Vec2s>        _pixelOffset;
        CVBF_Optional<std::string>       _provider;
        CVBF_Optional<Encoding>          _encoding;
        CVBF_Optional<Alignment>         _alignment;
        CVBF_Optional<bool>              _declutter;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_TEXT_SYMBOL_H
