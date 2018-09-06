#ifndef OSGEARTHSYMBOLOGY_MODEL_SYMBOL_H
#define OSGEARTHSYMBOLOGY_MODEL_SYMBOL_H 1

#include <climits>

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolInstance.h>
#include <Types/Vec3f>

namespace osgEarth { namespace Symbology
{
    class InstanceResource;

    // ʹ���ⲿ����άģ��
    class OSGEARTHSYMBOLOGY_EXPORT ModelSymbol : public InstanceSymbol
    {
    public:
        META_Symbol(ModelSymbol);

        ModelSymbol( const CVBF_Config& conf =CVBF_Config() );
        virtual ~ModelSymbol();

        // heading(��λ��)
        CVBF_Optional<NumericExpression>& heading() { return _heading; }
        const CVBF_Optional<NumericExpression>& heading() const { return _heading; }

        // pitch(��λ��)
        CVBF_Optional<NumericExpression>& pitch() { return _pitch; }
        const CVBF_Optional<NumericExpression>& pitch() const { return _pitch; }
        
        // roll(��λ��)
        CVBF_Optional<NumericExpression>& roll() { return _roll; }
        const CVBF_Optional<NumericExpression>& roll() const { return _roll; }
        
    public: // ���ܴ��л������� (ֻ��ͨ������)
        // ����ģ��
        void setModel( osg::IVBF_SGNode* node ) { _node = node; }
        osg::IVBF_SGNode* getModel() const { return _node.get(); }

    public:
        virtual CVBF_Config getConfig() const;
        virtual void mergeConfig( const CVBF_Config& conf );
        static void parseSLD(const CVBF_Config& c, class Style& style);
    
    public: // InstanceSymbol
        /** Creates a new (empty) resource appropriate for this symbol */
        virtual InstanceResource* createResource() const;

    protected:
        CVBF_Optional<NumericExpression>  _heading;
        CVBF_Optional<NumericExpression>  _pitch;
        CVBF_Optional<NumericExpression>  _roll;
        ref_ptr<osg::IVBF_SGNode>      _node;
    };

} } // namespace osgEarth::Symbology

#endif
