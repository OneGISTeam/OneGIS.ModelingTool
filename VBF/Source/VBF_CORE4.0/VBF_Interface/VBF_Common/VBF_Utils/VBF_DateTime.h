//*******************************************************************
// FileName：  VBF_DateTime.h
// Function：  封装与日期和时间有关的算法
// Author:     杜莹（提取自osgEarth-2.6）
// Date:       2018-04-06
//*******************************************************************

#ifndef __VBF_DATE_TIME_H__
#define __VBF_DATE_TIME_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <ctime>
#include <string>


/** Basic timestamp (seconds from the epoch) */
typedef ::time_t TimeStamp;

/** Time span (in seconds) */
typedef long TimeSpan;

/**
* General-purpose UTC date/time object.
* One second resolution, GMT time zone.
*/
class VBF_UTILS_EXPORT CVBF_DateTime
{
public:
    /** CVBF_DateTime representing "now" */
    CVBF_DateTime();

    /** CVBF_DateTime copy */
    CVBF_DateTime(const CVBF_DateTime& rhs);

    /** CVBF_DateTime from a tm (in the local time zone) */
    CVBF_DateTime(const ::tm& tm);

    /** CVBF_DateTime from UTC seconds since the epoch */
    CVBF_DateTime(TimeStamp utc);

    /** CVBF_DateTime from year, month, date, hours */
    CVBF_DateTime(int year, int month, int day, double hours);

    /** CVBF_DateTime from an ISO 8601 string */
    CVBF_DateTime(const std::string& iso8601);

    /** As a date/time string in RFC 1123 format (e.g., HTTP) */
    const std::string asRFC1123() const;

    /** As a date/time string in ISO 8601 format (lexigraphic order). */
    const std::string asISO8601() const;

    /** As a date/time string in compact ISO 8601 format (lexigraphic
        * order with no delimiters). */
    const std::string asCompactISO8601() const;

public:
    int    year()  const;
    int    month() const;
    int    day()   const;
    double hours() const;

    TimeStamp   asTimeStamp() const { return _time_t; }

protected:
    ::tm     _tm;
    ::time_t _time_t;

private:
    // since timegm is not cross-platform
    ::time_t timegm(const ::tm* tm) const;
};

#endif 
