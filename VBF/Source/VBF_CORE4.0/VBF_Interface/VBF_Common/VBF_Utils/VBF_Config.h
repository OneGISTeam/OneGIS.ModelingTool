//**********************************************************************************
// 文件名：  VBF_Config.h
// 描述:     用于配置串行化数据，
//           用户可将对象的各个属性存储到CVBF_Config中，或将其存储为特定的格式（如XML或JSON）；
//           同样，也可从一个CVBF_Config对象解析出各个属性值。支持CVBF_Optional<>模板。
// 作者:     
// 日期:     2013-07-01
//**********************************************************************************

#ifndef __VBF_CONFIG_H__
#define __VBF_CONFIG_H__


#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>
#include <Types/VBF_Optional.h>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_Referenced.h>
#include <list>
#include <stack>
#include <istream>


typedef std::list<class CVBF_Config> CVBF_ConfigList;

// 配置项：一般是从文件读取的、给定了明确值的项，由key和value组成
// CVBF_Config是一个通用目的串行化数据的容器，可串行化到特定的格式 (如 XML或JSON)，同理也可从文件反串行化。

class VBF_UTILS_EXPORT CVBF_Config
{
public:
    CVBF_Config();
    CVBF_Config(const std::string& key);
    CVBF_Config(const std::string& key, const std::string& value);
    CVBF_Config(const CVBF_Config& rhs);
    virtual ~CVBF_Config();

    CVBF_Config& operator = (const CVBF_Config& rhs);

    /** Context for resolving relative URIs that occur in this CVBF_Config */
    void setReferrer(const std::string& value);
    void inheritReferrer(const std::string& value);
    const std::string& referrer() const;

	// 为避免使用XmlUtils.h，将该函数调整为XmlUtils.h中的全局函数：VBF_GetConfigFromXML()
 // bool fromXML( std::istream& in );

	// 与JSON格式之间的互换
    std::string toJSON(bool pretty=false) const;
    bool fromJSON(const std::string& json);

    bool isEmpty()  const;
    bool isSimple() const;

//IE死机         std::string& key();
    const std::string& key() const;

    const std::string& value() const;
//IE死机          std::string& value();

    const CVBF_ConfigList& children() const;
    const CVBF_ConfigList children( const std::string& key ) const;

    bool hasChild( const std::string& key ) const;

    void remove( const std::string& key );

    CVBF_Config child( const std::string& key ) const;

    const CVBF_Config* child_ptr( const std::string& key ) const;

    CVBF_Config* mutable_child( const std::string& key );

    void merge( const CVBF_Config& rhs );

          CVBF_Config* find( const std::string& key, bool checkThis =true );
    const CVBF_Config* find( const std::string& key, bool checkThis =true) const;

    template<typename T>
    void addIfSet( const std::string& key, const CVBF_Optional<T>& opt ) 
	{
        if ( opt.isSet() ) 
		{
            add( key, VBF_toString<T>( opt.value() ) );
        }
    }
        
    template<typename T>
    void addObjIfSet( const std::string& key, const ref_ptr<T>& opt ) 
	{
        if ( opt.valid() ) 
		{
            CVBF_Config conf = opt->getConfig();
            conf.key() = key;
            add( conf );
        }
    }

    template<typename T>
    void addObjIfSet( const std::string& key, const CVBF_Optional<T>& obj ) 
	{
        if ( obj.isSet() ) 
		{
            CVBF_Config conf = obj->getConfig();
            // conf.key() = key;
            conf.SetKey(key);
            add( conf );
        }
    }

    template<typename X, typename Y>
    void addIfSet( const std::string& key, const std::string& val, const CVBF_Optional<X>& target, const Y& targetValue ) 
	{
        if ( target.isSetTo( targetValue ) )
            add( key, val );
    }

    template<typename T>
    void add( const std::string& key, const T& value )
	{
        _children.push_back( CVBF_Config(key, CVBF_Stringify() << value) );
        //_children.back().setReferrer( _referrer );
        _children.back().inheritReferrer( _referrer );
    }

    void add( const CVBF_Config& conf );
    void add( const std::string& key, const CVBF_Config& conf );
    void add( const CVBF_ConfigList& set );


    template<typename T>
    void addObj( const std::string& key, const T& value ) 
	{
        CVBF_Config conf = value.getConfig();
        //conf.key() = key;
        conf.SetKey(key);
        add( conf );
    }

    template<typename T>
    void updateIfSet( const std::string& key, const CVBF_Optional<T>& opt ) 
	{
        if ( opt.isSet() ) 
		{
            remove(key);
            add( key, VBF_toString<T>( opt.value() ) );
        }
    }
        
    template<typename T>
    void updateObjIfSet( const std::string& key, const ref_ptr<T>& opt ) 
	{
        if ( opt.valid() ) 
		{
            remove(key);
            CVBF_Config conf = opt->getConfig();
            //conf.key() = key;
            conf.SetKey(key);
            add( conf );
        }
    }

    template<typename T>
    void updateObjIfSet( const std::string& key, const CVBF_Optional<T>& obj ) 
	{
        if ( obj.isSet() ) 
		{
            remove(key);
            CVBF_Config conf = obj->getConfig();
            //conf.key() = key;
            conf.SetKey(key);
            add( conf );
        }
    }

    template<typename X, typename Y>
    void updateIfSet( const std::string& key, const std::string& val, const CVBF_Optional<X>& target, const Y& targetValue ) 
	{
        if ( target.isSetTo( targetValue ) ) 
		{
            remove(key);
            add( key, val );
        }
    }

    template<typename T>
    void update( const std::string& key, const T& value ) 
	{
        update( CVBF_Config(key, CVBF_Stringify() << value) );
    }

    void update( const CVBF_Config& conf );


    template<typename T>
    void updateObj( const std::string& key, const T& value ) 
	{
        remove(key);
        CVBF_Config conf = value.getConfig();
        //conf.key() = key;
        conf.SetKey(key);
        add( conf );
    }

    template<typename T>
    void set( const std::string& key, const T& value ) 
	{
        update( key, value );
    }

    bool hasValue( const std::string& key ) const;

    const std::string value( const std::string& key ) const;

    const std::string referrer( const std::string& key ) const;

	// 填充一个原始值
    template<typename T>
    T value( const std::string& key, T fallback ) const 
	{
        std::string r;
        if ( hasChild( key ) ) r = child(key).value();

        return VBF_as<T>( r, fallback );
    }

    bool boolValue( bool fallback ) const;

    // populates the output value iff the CVBF_Config exists.
    template<typename T>
    bool getIfSet( const std::string& key, CVBF_Optional<T>& output ) const 
	{
        std::string r;
        if ( hasChild(key) ) r = child(key).value();

        if ( r.empty() ) return false;

		output = VBF_as<T>( r, output.defaultValue() );
        return true;       
    }

    // for Configurable's
    template<typename T>
    bool getObjIfSet( const std::string& key, CVBF_Optional<T>& output ) const 
	{
        if ( hasChild( key ) ) 
		{
            output = T( child(key) );
            return true;
        }
        else
            return false;
    }

    // populates a CVBF_Referenced that takes a CVBF_Config in the constructor.
    template<typename T>
    bool getObjIfSet( const std::string& key, ref_ptr<T>& output ) const 
	{
        if ( hasChild( key ) ) 
		{
            output = new T( child(key) );
            return true;
        }
        else
            return false;
    }

    template<typename T>
    bool getObjIfSet( const std::string& key, T& output ) const 
	{
        if ( hasChild(key) ) 
		{
            output = T( child(key) );
            return true;
        }
        return false;
    }

    template<typename X, typename Y>
    bool getIfSet( const std::string& key, const std::string& val, CVBF_Optional<X>& target, const Y& targetValue ) const 
	{
        if ( hasValue( key ) && value( key ) == val ) 
		{
            target = targetValue;
            return true;
        }
        else 
            return false;
    }

    template<typename X, typename Y>
    bool getIfSet( const std::string& key, const std::string& val, X& target, const Y& targetValue ) const 
	{
        if ( hasValue(key) && value(key) == val ) 
		{
            target = targetValue;
            return true;
        }
        return false;
    }

    template<typename T>
    bool getIfSet( const std::string& key, T& output ) const
	{
        if ( hasValue(key) ) 
		{
            output = value<T>(key, output);
            return true;
        }
        return false;
    }

    /** support for conveying non-serializable objects in a CVBF_Config (in memory only) */

    typedef std::map<std::string, ref_ptr<CVBF_Referenced> > RefMap;

    void addNonSerializable( const std::string& key, CVBF_Referenced* obj );
    void updateNonSerializable( const std::string& key, CVBF_Referenced* obj ) ;


    template<typename X>
    X* getNonSerializable( const std::string& key ) const 
	{
        RefMap::const_iterator i = _refMap.find(key);
        return i == _refMap.end() ? 0 : dynamic_cast<X*>( i->second.get() );
    }

    // remove everything from (this) that also appears in rhs
    CVBF_Config operator - ( const CVBF_Config& rhs ) const;

    void SetValue(const std::string& sV);
    void SetKey(const std::string& sKey);
protected:
    std::string		_key;
    std::string		_defaultValue;
    CVBF_ConfigList	_children;
    std::string		_referrer;
    CVBF_Config*	_emptyConfig;
    RefMap			_refMap;
};


// specialization for CVBF_Config
template <> 
inline void CVBF_Config::addIfSet<CVBF_Config>( const std::string& key, const CVBF_Optional<CVBF_Config>& opt ) 
{
    if ( opt.isSet() ) 
	{
        CVBF_Config conf = opt.value();
//        conf.key() = key;
        conf.SetKey(key);
        add( conf );
    }
}

template <> 
inline void CVBF_Config::updateIfSet<CVBF_Config>( const std::string& key, const CVBF_Optional<CVBF_Config>& opt ) 
{
    if ( opt.isSet() ) 
	{
        remove(key);
        CVBF_Config conf = opt.value();
        //conf.key() = key;
        conf.SetKey(key);
        add( conf );
    }
}

template <> 
inline bool CVBF_Config::getIfSet<CVBF_Config>( const std::string& key, CVBF_Optional<CVBF_Config>& output ) const
{
    if ( hasChild( key ) ) 
	{
        output = child(key);
        return true;
    }
    else
        return false;
}

template <> 
inline void CVBF_Config::add<std::string>( const std::string& key, const std::string& value ) 
{
    _children.push_back( CVBF_Config( key, value ) );
    //_children.back().setReferrer( _referrer );
    _children.back().inheritReferrer( _referrer );
}

template <> 
inline void CVBF_Config::update<std::string>( const std::string& key, const std::string& value )
{
    remove(key);
    add( CVBF_Config(key, value) );
}

template <> 
inline void CVBF_Config::update<CVBF_Config>( const std::string& key, const CVBF_Config& conf ) 
{
    remove(key);
    CVBF_Config temp = conf;
//    temp.key() = key;
    temp.SetKey(key);
    add( temp );
}

template <> 
inline void CVBF_Config::add<float>( const std::string& key, const float& value ) 
{
    add( key, CVBF_Stringify() << std::setprecision(8) << value );
    //add( key, CVBF_Stringify() << std::fixed << std::setprecision(8) << value );
}

template <> 
inline void CVBF_Config::add<double>( const std::string& key, const double& value ) 
{
    add( key, CVBF_Stringify() << std::setprecision(16) << value );
    //add( key, CVBF_Stringify() << std::fixed << std::setprecision(16) << value );
}

template <> 
inline void CVBF_Config::update<float>( const std::string& key, const float& value ) 
{
    update( key, CVBF_Stringify() << std::setprecision(8) << value );
    //update( key, CVBF_Stringify() << std::fixed << std::setprecision(8) << value );
}

template <> 
inline void CVBF_Config::update<double>( const std::string& key, const double& value ) 
{
    update( key, CVBF_Stringify() << std::setprecision(16) << value );
}


// 选项： 
// 对于配置项来说，每个key都对应一个用户明确的值；对于选项来说，每个key不一定对应一个用户明确的值（可能是缺省值）
// 选项中的一部分或全部key可以从配置项赋值
class VBF_UTILS_EXPORT CVBF_Options // header-only (no export required)
{
public:
    CVBF_Options( const CVBF_Config& conf=CVBF_Config() );
    CVBF_Options( const CVBF_Options& rhs );

    virtual ~CVBF_Options();
        
    const std::string& referrer() const;

    CVBF_Options& operator = ( const CVBF_Options& rhs );

    void merge( const CVBF_Options& rhs );

    virtual CVBF_Config getConfig() const;
    virtual CVBF_Config getConfig( bool isolate ) const;

    CVBF_Config newConfig() const;

    bool isEmpty() const;

protected:
    virtual void mergeConfig( const CVBF_Config& conf );

protected:
    CVBF_Config	 m_conf;
};

// 数据驱动器选项
class VBF_UTILS_EXPORT CVBF_OptionsDriver : public CVBF_Options // header-only (no export required)
{
public:
    CVBF_OptionsDriver( const CVBF_Options& rhs =CVBF_Options() );
   
    virtual ~CVBF_OptionsDriver();

 	// 获取/设置数据驱动器的名字
    void setDriver(const std::string& value );
    const std::string& getDriver() const;

public:
    virtual CVBF_Config getConfig() const;
    virtual CVBF_Config getConfig( bool isolate )const;
    virtual void mergeConfig( const CVBF_Config& conf );
    void fromConfig( const CVBF_Config& conf );
private:
	std::string		m_strDriver;
};

#endif 

