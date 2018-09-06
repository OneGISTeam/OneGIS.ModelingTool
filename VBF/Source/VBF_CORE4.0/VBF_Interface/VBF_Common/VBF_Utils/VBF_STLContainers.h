//**********************************************************************************
// 文件名：  VBF_STLContainers.h
// 描述：    定义若干类似于STL容器的类
// 作者:     杜莹
// 日期:     2013-06-27
//**********************************************************************************

#ifndef __VBF_STL_CONTAINERS_H__
#define __VBF_STL_CONTAINERS_H__

#include <list>
#include <vector>

/**
* A std::map-like container that is faster than std::map for small amounts
* of data accessed by a single user
*/
template<typename KEY, typename DATA>
class CVBF_MapFast
{
public:
    typedef std::pair<KEY,DATA>		entry_t;
    typedef std::list<entry_t>		list_t;

    typedef typename list_t::iterator       iterator;
    typedef typename list_t::const_iterator const_iterator;

    DATA& operator[] (const KEY& key) 
	{
        for( iterator i = m_Data.begin(); i != m_Data.end(); ++i ) 
		{
            if ( i->first == key ) 
			{
                if ( m_LastKey == key && i != m_Data.begin() ) 
				{
                    m_Data.insert(begin(), *i);
                    m_Data.erase(i);
                    return m_Data.front().second;
                }
                else 
				{
                    m_LastKey = key;
                    return i->second;
                }
            }
        }
        m_Data.push_back(entry_t(key,DATA()));
        return m_Data.back().second;
    }

    iterator find( const KEY& key ) 
	{
        for( iterator i = m_Data.begin(); i != m_Data.end(); ++i ) 
		{
            if ( i->first == key ) 
			{
                return i;
            }
        }
        return end();
    }

    const_iterator find( const KEY& key ) const 
	{
        for( const_iterator i = m_Data.begin(); i != m_Data.end(); ++i ) 
		{
            if ( i->first == key ) 
			{
                return i;
            }
        }
        return end();
    }

    const_iterator begin()	const	{ return m_Data.begin(); }
    const_iterator end()	const	{ return m_Data.end(); }
    iterator	   begin()			{ return m_Data.begin(); }
    iterator       end()			{ return m_Data.end(); }

    bool empty() const { return m_Data.empty(); }

private:
    list_t		m_Data;
    KEY			m_LastKey;
};

//--------------------------------------------------------------------

/**
* Same of osg::CVBF_VectorMixin2, but with a superclass template parameter.
*/
template<class ValueT, class SuperClass>
class CVBF_VectorMixin2 : public SuperClass
{
    typedef typename std::vector<ValueT> vector_type;

public:
    typedef typename vector_type::allocator_type			allocator_type;
    typedef typename vector_type::value_type				value_type;
    typedef typename vector_type::const_pointer				const_pointer;
    typedef typename vector_type::pointer					pointer;
    typedef typename vector_type::const_reference			const_reference;
    typedef typename vector_type::reference					reference;
    typedef typename vector_type::const_iterator			const_iterator;
    typedef typename vector_type::iterator					iterator;
    typedef typename vector_type::const_reverse_iterator	const_reverse_iterator;
    typedef typename vector_type::reverse_iterator			reverse_iterator;
    typedef typename vector_type::size_type					size_type;
    typedef typename vector_type::difference_type			difference_type;

    explicit CVBF_VectorMixin2() 
		: m_Impl()
    {
    }

    explicit CVBF_VectorMixin2(size_type initial_size, const value_type& fill_value = value_type())
		: m_Impl(initial_size, fill_value)
    {
    }

    template<class InputIterator>
    CVBF_VectorMixin2(InputIterator first, InputIterator last)
		: m_Impl(first, last)
    {
    }

    CVBF_VectorMixin2(const vector_type& other)
		: m_Impl(other)
    {
    }

    CVBF_VectorMixin2(const CVBF_VectorMixin2& other)
		: m_Impl(other.m_Impl)
    {
    }

    CVBF_VectorMixin2& operator=(const vector_type& other)
    {
        m_Impl = other;
        return *this;
    }

    CVBF_VectorMixin2& operator=(const CVBF_VectorMixin2& other)
    {
        m_Impl = other.m_Impl;
        return *this;
    }

    virtual ~CVBF_VectorMixin2() {}

    void clear() { m_Impl.clear(); }

    void resize(size_type new_size, const value_type& fill_value = value_type()) { m_Impl.resize(new_size, fill_value); }
    void reserve(size_type new_capacity) { m_Impl.reserve(new_capacity); }
        
    void swap(vector_type& other)		{ m_Impl.swap(other); }
    void swap(CVBF_VectorMixin2& other) { m_Impl.swap(other.m_Impl); }

    bool empty() const { return m_Impl.empty(); }

    size_type size()	 const	{ return m_Impl.size(); }
    size_type capacity() const	{ return m_Impl.capacity(); }
    size_type max_size() const	{ return m_Impl.max_size(); }
    allocator_type get_allocator() const { return m_Impl.get_allocator(); }

    const_iterator begin() const	{ return m_Impl.begin(); }
    iterator       begin()			{ return m_Impl.begin(); }
    const_iterator end() const		{ return m_Impl.end(); }
    iterator       end()			{ return m_Impl.end(); }

    const_reverse_iterator rbegin() const	{ return m_Impl.rbegin(); }
    reverse_iterator	   rbegin()			{ return m_Impl.rbegin(); }
    const_reverse_iterator rend() const		{ return m_Impl.rend(); }
    reverse_iterator       rend()			{ return m_Impl.rend(); }

    const_reference operator[](size_type index) const	{ return m_Impl[index]; }
    reference       operator[](size_type index)			{ return m_Impl[index]; }

    const_reference at(size_type index) const	{ return m_Impl.at(index); }
    reference       at(size_type index)			{ return m_Impl.at(index); }

    void assign(size_type count, const value_type& value) { m_Impl.assign(count, value); }

    template<class Iter>
    void assign(Iter first, Iter last)		{ m_Impl.assign(first, last); }

    void push_back(const value_type& value) { m_Impl.push_back(value); }
    void pop_back()							{ m_Impl.pop_back(); }

    iterator erase(iterator where)					{ return m_Impl.erase(where); }
    iterator erase(iterator first, iterator last)	{ return m_Impl.erase(first, last); }

    iterator insert(iterator where, const value_type& value) { return m_Impl.insert(where, value); }

    template<class InputIterator>
    void insert(iterator where, InputIterator first, InputIterator last)
    {
        m_Impl.insert(where, first, last);
    }

    void insert(iterator where, size_type count, const value_type& value)
    {
        m_Impl.insert(where, count, value);
    }

    const_reference back() const	{ return m_Impl.back(); }
    reference       back()			{ return m_Impl.back(); }
    const_reference front() const	{ return m_Impl.front(); }
    reference       front()			{ return m_Impl.front(); }

    vector_type&       asVector()		{ return m_Impl; }
    const vector_type& asVector() const { return m_Impl; }

    friend inline bool operator==(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left.m_Impl == right.m_Impl; }
    friend inline bool operator==(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const std::vector<ValueT>& right) { return left.m_Impl == right; }
    friend inline bool operator==(const std::vector<ValueT>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left == right.m_Impl; }

    friend inline bool operator!=(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left.m_Impl != right.m_Impl; }
    friend inline bool operator!=(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const std::vector<ValueT>& right) { return left.m_Impl != right; }
    friend inline bool operator!=(const std::vector<ValueT>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left != right.m_Impl; }

    friend inline bool operator<(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left.m_Impl < right.m_Impl; }
    friend inline bool operator<(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const std::vector<ValueT>& right) { return left.m_Impl < right; }
    friend inline bool operator<(const std::vector<ValueT>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left < right.m_Impl; }

    friend inline bool operator>(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left.m_Impl > right.m_Impl; }
    friend inline bool operator>(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const std::vector<ValueT>& right) { return left.m_Impl > right; }
    friend inline bool operator>(const std::vector<ValueT>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left > right.m_Impl; }

    friend inline bool operator<=(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left.m_Impl <= right.m_Impl; }
    friend inline bool operator<=(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const std::vector<ValueT>& right) { return left.m_Impl <= right; }
    friend inline bool operator<=(const std::vector<ValueT>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left <= right.m_Impl; }

    friend inline bool operator>=(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left.m_Impl >= right.m_Impl; }
    friend inline bool operator>=(const CVBF_VectorMixin2<ValueT,SuperClass>& left, const std::vector<ValueT>& right) { return left.m_Impl >= right; }
    friend inline bool operator>=(const std::vector<ValueT>& left, const CVBF_VectorMixin2<ValueT,SuperClass>& right) { return left >= right.m_Impl; }

private:
    vector_type		m_Impl;
};



#endif
