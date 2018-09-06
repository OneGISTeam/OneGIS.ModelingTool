#ifndef OSGEARTH_UTIL_MGRS_FORMATTER_H
#define OSGEARTH_UTIL_MGRS_FORMATTER_H

#include <VBF_3DMap/VBF_EarthUtil/VBF_Formatter.h>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>

namespace osgEarth { namespace Util
{
    using namespace osgEarth;

    /**
     * Represents an MGRS coordinate in its parts 
     */
    struct MGRSCoord
    {
        std::string gzd;
        std::string sqid;
        unsigned    x;
        unsigned    y;
    };

    /**
     * Formats coordinate data as MGRS.
     *
     * NOTE: This class does not yet handle the special UTM zone exceptions for
     *       southwest Norway (zone 32V) and Svalbard (31X, 33X, 35X, 37X).. 
     *       mainly because I have not found sufficient documentation on them
     *
     * See: http://en.wikipedia.org/wiki/Military_grid_reference_system
     */
    class OSGEARTHUTIL_EXPORT MGRSFormatter : public Formatter
    {
    public:
        enum Precision
        {
            PRECISION_100000M = 100000,     // i.e., omit the numerical offsets altogether
            PRECISION_10000M  = 10000,
            PRECISION_1000M   = 1000,
            PRECISION_100M    = 100,
            PRECISION_10M     = 10,
            PRECISION_1M      = 1
        };

        enum Options
        {
            USE_SPACES        = 1 << 0,     // insert spaces between MGRS elements
            FORCE_AA_SCHEME   = 1 << 1,     // use the AA row lettering scheme regardless of ellipsoid
            FORCE_AL_SCHEME   = 1 << 2      // use the AL row lettering scheme regardless of ellipsoid
        };

    public:
        /**
         * Initialized an MGRS formatter. 
         *
         * @param precision Precision with which to print the MGRS string (see Precision above)
         * @param refSRS    Reference geographic SRS for MGRS encoding. Older datums
         *                  (Clark and Bessel) change the row lettering scheme. Default=WGS84.
         * @param options   Formatting options (see Options above)
         */
        MGRSFormatter(
            Precision               precision =PRECISION_1M,
            const CVBF_SpatialReference* refSRS    =0L,
            unsigned                options   =0);

        /** dtor */
        virtual ~MGRSFormatter() { }

        /**
         * Transforms input coords into MGRS.
         */
        bool transform( const GeoPoint& input, MGRSCoord& out_mgrs ) const;


    public: // Formatter

        virtual std::string format( const GeoPoint& coords ) const;


    private:
        ref_ptr<const CVBF_SpatialReference> _refSRS;
        bool                                 _useAL;
        Precision                            _precision;
        unsigned                             _options;

        std::map< std::string, ref_ptr<const CVBF_SpatialReference> > _srsCache;
    };

} } // namespace osgEarth::Util

#endif // OSGEARTH_UTIL_MGRS_FORMATTER_H
