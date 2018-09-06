#ifndef OSGEARTHSYMBOLOGY_CSSUTILS_H
#define OSGEARTHSYMBOLOGY_CSSUTILS_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <vector>

namespace osgEarth { namespace Symbology
{
    class OSGEARTHSYMBOLOGY_EXPORT CssUtils
    {
    public:
        static void readConfig( 
            const std::string& inputCSS,
            const std::string& referrer,
            CVBF_ConfigList&         output );

        /**
         * Takes a string containing CSS text, and splits it up into 
         * multiple strings, each one containing a single style definition
         * (still in CSS). A nameless block is named "default".
         *
         * Example INPUT:
         *
         *   s1 {
         *      fill: #ffff00;
         *   }
         *   s2 {
         *      stroke: #ffff00;
         *      altitude-mode: absoulte;
         *   }
         *   {
         *      marker: "something.flt";
         *   }
         *
         * Example OUTPUT:
         *
         *   [0] : s1 { fill: #ffff00; }
         *   [1] : s2 { stroke: #ffff00; altitude-mode: absolute; }
         *   [2] : default { marker: "something.flt"; }
         *
         */
        static void split( const std::string& css, std::vector<std::string>& output );
    };

} } // namespace osgEarth::Features2

#endif // OSGEARTHFEATURES_CSSUTILS_H
