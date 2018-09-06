#ifndef OSGEARTHSYMBOLOGY_EXPRESSION_H
#define OSGEARTHSYMBOLOGY_EXPRESSION_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>

namespace osgEarth { namespace Symbology
{    

	// 带有变量的简单数值求值器表达式
    class OSGEARTHSYMBOLOGY_EXPORT NumericExpression
    {
    public:
        typedef std::pair<std::string,unsigned> Variable;
        typedef std::vector<Variable> Variables;

    public:
        NumericExpression();
        NumericExpression( const CVBF_Config& conf );

		// 中缀表达式是一个通用的算术或逻辑公式表示方法， 操作符是以中缀形式处于操作数的中间（例：3 + 4）
        NumericExpression( const std::string& expr );  // 从一个中缀字符串构建表达式
        NumericExpression( double staticValue );       // 从一个定值构建表达式

		NumericExpression( const NumericExpression& rhs );
        NumericExpression& operator = ( const NumericExpression& rhs );

        virtual ~NumericExpression();

		// 访问表达式的变量
        const Variables& variables() const { return _vars; }

		// 设置变量的值
        void set( const Variable& var, double value );

		// 表达式求值
        double eval() const;

		// 获取表达式字符串
        const std::string& expr() const { return _src; }

		// 表达式是否为空
        bool empty() const { return _src.empty(); }

    public:
        CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    private:
        enum Op { OPERAND, VARIABLE, ADD, SUB, MULT, DIV, MOD, MIN, MAX, LPAREN, RPAREN, COMMA }; // in low-high precedence order
        typedef std::pair<Op,double> Atom;
        typedef std::vector<Atom> AtomVector;
        typedef std::stack<Atom> AtomStack;
        
        std::string _src;
        AtomVector  _rpn;
        Variables   _vars;
        double      _value;
        bool        m_bDirty;

        void init();
    };

    //--------------------------------------------------------------------

	// 变量求值的简单字符串表达式（如3+4）
    class OSGEARTHSYMBOLOGY_EXPORT StringExpression
    {
    public:
        typedef std::pair<std::string,unsigned> Variable;
        typedef std::vector<Variable> Variables;

    public:
        StringExpression();
        StringExpression( const CVBF_Config& conf );
	
		// 中缀表达式是一个通用的算术或逻辑公式表示方法， 操作符是以中缀形式处于操作数的中间（例：3 + 4）

        // 利用中缀字符串构建表达式
        StringExpression( const std::string& expr );

        // 利用中缀字符串和URI上下文，构建表达式
        StringExpression( const std::string& expr, const URIContext& uriContext );
        StringExpression( const StringExpression& rhs );
        virtual ~StringExpression();


		// 设置中缀字符串
        void setInfix( const std::string& infix );

		// 设置文字串
        void setLiteral( const std::string& value );

		// 获取表达式变量
        const Variables& variables() const { return _vars; }

		// 设置变量的值
        void set( const Variable& var, const std::string& value );

		// 设置命名变量的值（如果存在的话）
        void set( const std::string& varName, const std::string& value );

        // 对表达式求值
        const std::string& eval() const;

		// 获得表达式字符串
        const std::string& expr() const { return _src; }

		// 表达式是否为空
        bool empty() const { return _src.empty(); }

        void setURIContext( const URIContext& uriContext ) { _uriContext = uriContext; }
        const URIContext& uriContext() const { return _uriContext; }

    public:
        CVBF_Config getConfig() const;
        void mergeConfig( const CVBF_Config& conf );

    private:
        enum Op { OPERAND, VARIABLE }; // in low-high precedence order
        typedef std::pair<Op,std::string> Atom;
        typedef std::vector<Atom> AtomVector;
        
        std::string  _src;
        AtomVector   _infix;
        Variables    _vars;
        std::string  _value;
        bool         m_bDirty;
        URIContext   _uriContext;

        void init();
    };

} } // namespace osgEarth::Symbology

#endif // OSGEARTHSYMBOLOGY_EXPRESSION_H
