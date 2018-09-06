#ifndef OSGEARTHSYMBOLOGY_EXPRESSION_H
#define OSGEARTHSYMBOLOGY_EXPRESSION_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>

namespace osgEarth { namespace Symbology
{    

	// ���б����ļ���ֵ��ֵ�����ʽ
    class OSGEARTHSYMBOLOGY_EXPORT NumericExpression
    {
    public:
        typedef std::pair<std::string,unsigned> Variable;
        typedef std::vector<Variable> Variables;

    public:
        NumericExpression();
        NumericExpression( const CVBF_Config& conf );

		// ��׺���ʽ��һ��ͨ�õ��������߼���ʽ��ʾ������ ������������׺��ʽ���ڲ��������м䣨����3 + 4��
        NumericExpression( const std::string& expr );  // ��һ����׺�ַ����������ʽ
        NumericExpression( double staticValue );       // ��һ����ֵ�������ʽ

		NumericExpression( const NumericExpression& rhs );
        NumericExpression& operator = ( const NumericExpression& rhs );

        virtual ~NumericExpression();

		// ���ʱ��ʽ�ı���
        const Variables& variables() const { return _vars; }

		// ���ñ�����ֵ
        void set( const Variable& var, double value );

		// ���ʽ��ֵ
        double eval() const;

		// ��ȡ���ʽ�ַ���
        const std::string& expr() const { return _src; }

		// ���ʽ�Ƿ�Ϊ��
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

	// ������ֵ�ļ��ַ������ʽ����3+4��
    class OSGEARTHSYMBOLOGY_EXPORT StringExpression
    {
    public:
        typedef std::pair<std::string,unsigned> Variable;
        typedef std::vector<Variable> Variables;

    public:
        StringExpression();
        StringExpression( const CVBF_Config& conf );
	
		// ��׺���ʽ��һ��ͨ�õ��������߼���ʽ��ʾ������ ������������׺��ʽ���ڲ��������м䣨����3 + 4��

        // ������׺�ַ����������ʽ
        StringExpression( const std::string& expr );

        // ������׺�ַ�����URI�����ģ��������ʽ
        StringExpression( const std::string& expr, const URIContext& uriContext );
        StringExpression( const StringExpression& rhs );
        virtual ~StringExpression();


		// ������׺�ַ���
        void setInfix( const std::string& infix );

		// �������ִ�
        void setLiteral( const std::string& value );

		// ��ȡ���ʽ����
        const Variables& variables() const { return _vars; }

		// ���ñ�����ֵ
        void set( const Variable& var, const std::string& value );

		// ��������������ֵ��������ڵĻ���
        void set( const std::string& varName, const std::string& value );

        // �Ա��ʽ��ֵ
        const std::string& eval() const;

		// ��ñ��ʽ�ַ���
        const std::string& expr() const { return _src; }

		// ���ʽ�Ƿ�Ϊ��
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
