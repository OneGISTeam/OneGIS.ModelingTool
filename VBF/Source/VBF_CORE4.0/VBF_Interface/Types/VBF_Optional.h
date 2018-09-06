//**********************************************************************************
// �ļ�����  VBF_Optional.h
// ������    ģ���࣬���ڶ����ѡ�����Ա������
//          ���û���ʽ����һ��ֵ֮ǰ���ñ�����ȱʡֵ����isSet()����ֵΪfalse��
//			���û���ʽ����һ��ֵ֮��isSet()����ֵΪtrue��
// ����:     ��Ө
// ����:     2013-06-24
//**********************************************************************************

#ifndef __VBF_OPTIONAL_H__
#define __VBF_OPTIONAL_H__


// �����ѡ�һ����ѡ����һ��Ĭ�ϵ�ֵ��һ������Ƿ����õı�־
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
	// ��������
	typedef T* CVBF_Optional::*unspecified_bool_type;

    operator unspecified_bool_type() const { return 0; }

private:
    bool	m_bSet;				// �û��Ƿ���ʽ������ֵ
    T		m_Value;			// �û����õ�ֵ
    T		m_DefaultValue;		// ȱʡֵ
};


#endif
