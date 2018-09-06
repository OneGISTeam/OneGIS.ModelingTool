//**********************************************************************************
// 文件名：  VBF_Optional.h
// 描述：    模板类，用于定义可选的类成员变量，
//          在用户显式设置一个值之前，该变量有缺省值，且isSet()返回值为false；
//			在用户显式设置一个值之后，isSet()返回值为true。
// 作者:     杜莹
// 日期:     2013-06-24
//**********************************************************************************

#ifndef __VBF_OPTIONAL_H__
#define __VBF_OPTIONAL_H__


// 定义可选项，一个可选项有一个默认的值和一个标记是否设置的标志
template<typename T> 
struct CVBF_Optional
{
    CVBF_Optional() : m_bSet(false), m_Value(T()), m_DefaultValue(T()) { }
    CVBF_Optional(T defaultValue) : m_bSet(false), m_Value(defaultValue), m_DefaultValue(defaultValue) { }
    CVBF_Optional(T defaultValue, T value) : m_bSet(true), m_Value(value), m_DefaultValue(defaultValue) { }
    CVBF_Optional(const CVBF_Optional<T>& rhs) { (*this)=rhs; }

    virtual ~CVBF_Optional() { }

    CVBF_Optional<T>& operator =(const CVBF_Optional<T>& rhs)	{ m_bSet=rhs.m_bSet; m_Value=rhs.m_Value; m_DefaultValue=rhs.m_DefaultValue; return *this; }
    const T& operator =(const T& value)							{ m_bSet=true; m_Value=value; return m_Value; }

    bool operator ==(const CVBF_Optional<T>& rhs) const	{ return m_bSet && rhs.m_bSet && m_Value==rhs.m_Value; }
    bool operator !=(const CVBF_Optional<T>& rhs) const	{ return !( (*this)==rhs); }
    bool operator ==(const T& value) const				{ return m_Value==value; }
    bool operator !=(const T& value) const				{ return m_Value!=value; }
    bool operator > (const T& value) const				{ return m_Value>value; }
    bool operator >=(const T& value) const				{ return m_Value>=value; }
    bool operator < (const T& value) const				{ return m_Value<value; }
    bool operator <=(const T& value) const				{ return m_Value<=value; }

    bool isSetTo(const T& value) const	{ return m_bSet && m_Value==value; } // differs from == in that the value must be explicity set
    bool isSet() const					{ return m_bSet; }
    void unset()						{ m_bSet = false; m_Value=m_DefaultValue; }

    const T& get() const			{ return m_Value; }
    const T& value() const			{ return m_Value; }
    const T& defaultValue() const	{ return m_DefaultValue; }
    T temp_copy() const				{ return m_Value; }

    const T& getOrUse(const T& fallback) const { return m_bSet ? m_Value : fallback; }

    // gets a mutable reference, automatically setting
    T& mutable_value() { m_bSet = true; return m_Value; }

    void init(T defValue) { m_Value=defValue; m_DefaultValue=defValue; unset(); }

    operator const T*() const { return &m_Value; }

    T* operator ->()					{ m_bSet=true; return &m_Value; }
    const T* operator ->() const		{ return &m_Value; }

public:
	// 定义类型
	typedef T* CVBF_Optional::*unspecified_bool_type;

    operator unspecified_bool_type() const { return 0; }

private:
    bool	m_bSet;				// 用户是否显式设置了值
    T		m_Value;			// 用户设置的值
    T		m_DefaultValue;		// 缺省值
};


#endif
