#ifndef OSGEARTHSYMBOLOGY_MARKER_SYMBOLIZER_H
#define OSGEARTHSYMBOLOGY_MARKER_SYMBOLIZER_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolText.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>

namespace osgEarth { namespace Features
{
    // 给注记创建一个文字节点，目前没用到
    class OSGEARTHFEATURES_EXPORT BuildTextOperator
    {
    public:
        BuildTextOperator(bool hideClutter=false) : _hideClutter(hideClutter) { };
        virtual ~BuildTextOperator() { }
    public:
        osg::IVBF_SGNode* operator()( const FeatureList& features, const osgEarth::Symbology::TextSymbol* symbol, const FilterContext& context);

    protected:
        bool _hideClutter;
    };

} } // namespace osgEarth::Features

#endif
