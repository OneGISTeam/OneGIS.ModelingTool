//**********************************************************************************
// 文件名：  VBF_Units.h
// 描述：    各种运算使用的单位，如距离单位、角度单位、速度单位等
// 作者:     杜莹
// 日期:     2013-07-03
//**********************************************************************************

#ifndef __VBF_UNITS_H__
#define __VBF_UNITS_H__

#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>

// unit types.
enum EVBF_UNITS_TYPE
{ 
    VBF_UNITS_TYPE_LINEAR, 
    VBF_UNITS_TYPE_ANGULAR, 
    VBF_UNITS_TYPE_TEMPORAL, 
    VBF_UNITS_TYPE_SPEED, 
    VBF_UNITS_TYPE_SCREEN_SIZE,
    VBF_UNITS_TYPE_INVALID
};

class VBF_UTILS_EXPORT CVBF_Units
{
public:

    // 长度单位
    static const CVBF_Units CENTIMETERS;
    static const CVBF_Units DATA_MILES;
    static const CVBF_Units FATHOMS;
    static const CVBF_Units FEET;
    static const CVBF_Units FEET_US_SURVEY;  // http://www.wsdot.wa.gov/reference/metrics/foottometer.htm
    static const CVBF_Units INCHES;
    static const CVBF_Units KILOFEET;
    static const CVBF_Units KILOMETERS;
    static const CVBF_Units KILOYARDS;
    static const CVBF_Units METERS;
    static const CVBF_Units MILES;           // statute miles
    static const CVBF_Units MILLIMETERS;
    static const CVBF_Units NAUTICAL_MILES;
    static const CVBF_Units YARDS;

    // 角度单位
    static const CVBF_Units BAM;
    static const CVBF_Units DEGREES;
    static const CVBF_Units NATO_MILS; // http://www.convertworld.com/en/angle/Mil+(NATO).html
    static const CVBF_Units RADIANS;

    // 时间单位
    static const CVBF_Units DAYS;
    static const CVBF_Units HOURS;
    static const CVBF_Units MICROSECONDS;
    static const CVBF_Units MILLISECONDS;
    static const CVBF_Units MINUTES;
    static const CVBF_Units SECONDS;
    static const CVBF_Units WEEKS;

    // 速度单位
    static const CVBF_Units FEET_PER_SECOND;
    static const CVBF_Units YARDS_PER_SECOND;
    static const CVBF_Units METERS_PER_SECOND;
    static const CVBF_Units KILOMETERS_PER_SECOND;
    static const CVBF_Units KILOMETERS_PER_HOUR;
    static const CVBF_Units MILES_PER_HOUR;
    static const CVBF_Units DATA_MILES_PER_HOUR;
    static const CVBF_Units KNOTS;

    // 屏幕单位
    static const CVBF_Units PIXELS;

public:

	// called by Registry to register system units
    static void registerAll();

	static const CVBF_Units* getUnits(const std::string& name);
	static void registerUnits(const CVBF_Units* units);

    static bool parse(const std::string& input, CVBF_Units& output);

    // parses a value+units string (like "15cm" or "24px")
    static bool parse(const std::string& input, double& out_value, CVBF_Units& out_units, const CVBF_Units& defaultUnits);
    static bool parse(const std::string& input, float& out_value, CVBF_Units& out_units, const CVBF_Units& defaultUnits);
    static bool parse(const std::string& input, int& out_value, CVBF_Units& out_units, const CVBF_Units& defaultUnits);

    static bool convert( const CVBF_Units& from, const CVBF_Units& to, double input, double& output ) 
	{
        if( canConvert(from, to) ) 
		{
            if ( from._type == VBF_UNITS_TYPE_LINEAR || from._type == VBF_UNITS_TYPE_ANGULAR || from._type == VBF_UNITS_TYPE_TEMPORAL )
                convertSimple( from, to, input, output );
            else if ( from._type == VBF_UNITS_TYPE_SPEED )
                convertSpeed( from, to, input, output );
            return true;
        }
        return false;
    }

    static double convert( const CVBF_Units& from, const CVBF_Units& to, double input )
	{
        double output = input;
        convert( from, to, input, output );
        return output;
    }

    static bool canConvert( const CVBF_Units& from, const CVBF_Units& to ) { return from._type == to._type; }
    bool canConvert( const CVBF_Units& to ) const { return _type == to._type; }

    bool convertTo( const CVBF_Units& to, double input, double& output )  const { return convert( *this, to, input, output ); }

    double convertTo( const CVBF_Units& to, double input ) const { return convert( *this, to, input ); }
        
    const std::string& getName() const { return m_sName; }
    const std::string& getAbbr() const { return _abbr; }

    const EVBF_UNITS_TYPE& getType() const { return _type; }

    bool operator == ( const CVBF_Units& rhs ) const { return _type == rhs._type && _toBase == rhs._toBase; }
    bool operator != ( const CVBF_Units& rhs ) const { return _type != rhs._type || _toBase != rhs._toBase; }
    CVBF_Units& operator = ( const CVBF_Units& rhs );

    bool isLinear()		const { return _type == VBF_UNITS_TYPE_LINEAR; }
    bool isAngular()	const { return _type == VBF_UNITS_TYPE_ANGULAR; }
    bool isTemporal()	const { return _type == VBF_UNITS_TYPE_TEMPORAL; }
    bool isSpeed()		const { return _type == VBF_UNITS_TYPE_SPEED; }
    bool isScreenSize() const { return _type == VBF_UNITS_TYPE_SCREEN_SIZE; }

public:

    // Make a new unit definition (LINEAR, ANGULAR, TEMPORAL, SCREEN)
    CVBF_Units(const std::string& name, const std::string& abbr, const EVBF_UNITS_TYPE& type, double toBase);

    // Maks a new unit definition (SPEED)
    CVBF_Units(const std::string& name, const std::string& abbr, const CVBF_Units& distance, const CVBF_Units& time);

    CVBF_Units();
    virtual ~CVBF_Units();
private:

    static void convertSimple( const CVBF_Units& from, const CVBF_Units& to, double input, double& output ) 
	{
        output = input * from._toBase / to._toBase;
    }

    static void convertSpeed( const CVBF_Units& from, const CVBF_Units& to, double input, double& output ) 
	{
        double t = from._distance->convertTo( *to._distance, input );
        output = to._time->convertTo( *from._time, t );
    }

private:
    std::string				m_sName;
	std::string				_abbr;
    EVBF_UNITS_TYPE			_type;
    double					_toBase;
    const CVBF_Units*		_distance;
    const CVBF_Units*		_time;

	friend struct CVBF_RegisterAllUnitsProxy;
};


struct Linear;

template<typename T>
class qualified_double
{
public:
    qualified_double<T>( double value, const CVBF_Units& units ) : _value(value), _units(units) { }
    qualified_double<T>( const T& rhs ) : _value(rhs._value), _units(rhs._units) { }

    qualified_double<T>( const CVBF_Config& conf, const CVBF_Units& defaultUnits ) 
	{
        _value = conf.value<double>("value", 0.0);
        if ( !CVBF_Units::parse( conf.value("units"), _units ) )
            _units = defaultUnits;
    }

    void set( double value, const CVBF_Units& units ) 
	{
        _value = value;
        _units = units;
    }

    T& operator = ( const T& rhs ) 
	{
        set( rhs._value, rhs._units );
        return static_cast<T&>(*this);
    }

    T operator + ( const T& rhs ) const 
	{
        return _units.canConvert(rhs._units)? T(_value + rhs.as(_units), _units) : T(0, CVBF_Units());
    }

    T operator - ( const T& rhs ) const
	{
        return _units.canConvert(rhs._units)? T(_value - rhs.as(_units), _units) : T(0, CVBF_Units());
    }

    T operator * ( double rhs ) const {  return T(_value * rhs, _units); }
    T operator / ( double rhs ) const { return T(_value / rhs, _units);}

    bool operator == ( const T& rhs ) const { return _units.canConvert( rhs._units ) && rhs.as(_units) == _value; }
    bool operator != ( const T& rhs ) const { return !_units.canConvert(rhs._units) || rhs.as(_units) != _value; }

    bool operator < ( const T& rhs )  const { return _units.canConvert(rhs._units) && _value < rhs.as(_units); }
    bool operator <= ( const T& rhs ) const { return _units.canConvert(rhs._units) && _value <= rhs.as(_units); }
    bool operator > ( const T& rhs )  const { return _units.canConvert(rhs._units) && _value > rhs.as(_units); }
    bool operator >= ( const T& rhs ) const { return _units.canConvert(rhs._units) && _value >= rhs.as(_units); }

    double as( const CVBF_Units& convertTo ) const { return _units.convertTo( convertTo, _value ); }

    const CVBF_Units& getUnits() const { return _units; }

    CVBF_Config getConfig() const 
	{
        CVBF_Config conf;
        conf.set("value", _value);
        conf.set("units", _units.getAbbr());
        return conf;
    }

private:
    double		_value;
    CVBF_Units  _units;
};

struct Linear : public qualified_double<Linear>
{
    Linear() : qualified_double<Linear>(0, CVBF_Units::METERS) { }
    Linear(double value ) : qualified_double<Linear>(value, CVBF_Units::METERS) { }
    Linear(double value, const CVBF_Units& units) : qualified_double<Linear>(value, units) { }
    Linear(const CVBF_Config& conf) : qualified_double<Linear>(conf, CVBF_Units::METERS) { }
};
typedef Linear Distance;

struct Angular : public qualified_double<Angular> 
{
    Angular() : qualified_double<Angular>(0, CVBF_Units::DEGREES) { }
    Angular(double value) : qualified_double<Angular>(value, CVBF_Units::DEGREES) { }
    Angular(double value, const CVBF_Units& units) : qualified_double<Angular>(value, units) { }
    Angular(const CVBF_Config& conf) : qualified_double<Angular>(conf, CVBF_Units::DEGREES) { }
};
typedef Angular Angle;

struct Temporal : public qualified_double<Temporal> 
{
    Temporal() : qualified_double<Temporal>(0, CVBF_Units::SECONDS) { }
    Temporal(double value) : qualified_double<Temporal>(value, CVBF_Units::SECONDS) { }
    Temporal(double value, const CVBF_Units& units) : qualified_double<Temporal>(value, units) { }
    Temporal(const CVBF_Config& conf) : qualified_double<Temporal>(conf, CVBF_Units::SECONDS) { }
};
typedef Temporal Duration;

struct Speed : public qualified_double<Speed> 
{
    Speed() : qualified_double<Speed>(0, CVBF_Units::METERS_PER_SECOND) { }
    Speed(double value) : qualified_double<Speed>(value, CVBF_Units::METERS_PER_SECOND) { }
    Speed(double value, const CVBF_Units& units) : qualified_double<Speed>(value, units) { }
    Speed(const CVBF_Config& conf) : qualified_double<Speed>(conf, CVBF_Units::METERS_PER_SECOND) { }
};

struct ScreenSize : public qualified_double<ScreenSize> 
{
    ScreenSize() : qualified_double<ScreenSize>(0, CVBF_Units::PIXELS) { }
    ScreenSize(double value) : qualified_double<ScreenSize>(value, CVBF_Units::PIXELS) { }
    ScreenSize(double value, const CVBF_Units& units) : qualified_double<ScreenSize>(value, units) { }
    ScreenSize(const CVBF_Config& conf) : qualified_double<ScreenSize>(conf, CVBF_Units::PIXELS) { }
};

#endif 
