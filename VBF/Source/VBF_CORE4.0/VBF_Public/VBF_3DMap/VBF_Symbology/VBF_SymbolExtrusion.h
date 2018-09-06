#ifndef OSGEARTHSYMBOLOGY_EXTRUSION_SYMBOL_H
#define OSGEARTHSYMBOLOGY_EXTRUSION_SYMBOL_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Symbology/VBF_Symbol.h>
#include <VBF_3DMap/VBF_Symbology/Expression.h>

namespace osgEarth { namespace Symbology
{
    using namespace osgEarth;

    // 凸起符号。指示GeometryCompiler根据2D矢量数据挤出3D图形
    class OSGEARTHSYMBOLOGY_EXPORT ExtrusionSymbol : public Symbol
    {
    public:
        enum HeightReference
        {            
            HEIGHT_REFERENCE_Z,// 高度值是相对于输入的几何体的Z值，使用该参数是从几何体原来的位置挤出
            HEIGHT_REFERENCE_MSL// 高度值是相对于MSL（平均海水面），使用该参数是从水平面挤出
        };
    public:
        META_Symbol(ExtrusionSymbol);

        ExtrusionSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~ExtrusionSymbol();

        // 几何体挤出的高度，与HeightReference相关
        CVBF_Optional<float>& height() { return _height; }
        const CVBF_Optional<float>& height() const { return _height; }

        // 计算高度的简单表达式
        CVBF_Optional<NumericExpression>& heightExpression() { return _heightExpr; }
        const CVBF_Optional<NumericExpression>& heightExpression() const { return _heightExpr; }

        // 高度值的参考基准
        CVBF_Optional<HeightReference>& heightReference() { return _heightRef; }
        const CVBF_Optional<HeightReference>& heightReference() const { return _heightRef; }

        // 挤出的几何体的顶部是否是平的
        CVBF_Optional<bool>& flatten() { return _flatten; }
        const CVBF_Optional<bool>& flatten() const { return _flatten; }

        // 侧面所使用的style的名字
        CVBF_Optional<std::string>& wallStyleName() { return _wallStyleName; }
        const CVBF_Optional<std::string>& wallStyleName() const { return _wallStyleName; }

        // 顶面所使用的style的名字
        CVBF_Optional<std::string>& roofStyleName() { return _roofStyleName; }
        const CVBF_Optional<std::string>& roofStyleName() const { return _roofStyleName; }

        /** 百分比to darken the color of the bottom of the walls relative
            to the main wall color (default = 0.0, range = [0..1]) */
        CVBF_Optional<float>& wallGradientPercentage() { return _wallGradientPercentage; }
        const CVBF_Optional<float>& wallGradientPercentage() const { return _wallGradientPercentage; }
        
    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);

    protected:
        CVBF_Optional<float>             _height;
        CVBF_Optional<bool>              _flatten; // 平的，即所有顶点一样高
        CVBF_Optional<NumericExpression> _heightExpr;
        CVBF_Optional<HeightReference>   _heightRef;
        CVBF_Optional<std::string>       _wallStyleName;
        CVBF_Optional<std::string>       _roofStyleName;
        CVBF_Optional<float>             _wallGradientPercentage;
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_EXTRUSION_SYMBOL_H
