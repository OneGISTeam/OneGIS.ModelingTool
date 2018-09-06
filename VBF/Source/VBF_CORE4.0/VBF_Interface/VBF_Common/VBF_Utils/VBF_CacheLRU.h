//**********************************************************************************
// 文件名：  VBF_CacheLRU.h
// 描述：    一种缓存算法：最近最少使用算法（Least-Rencently-Used）
// 作者:     杜莹
// 日期:     2013-06-27
//**********************************************************************************

#ifndef __VBF_CACHE_LRU_H__
#define __VBF_CACHE_LRU_H__


#include <list>
#include <vector>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Common/VBF_Utils/VBF_STLContainers.h>


/** 
* 统计缓存的信息 
*/
class CVBF_StatsCache
{
public:
    CVBF_StatsCache( unsigned entries, unsigned maxEntries, unsigned queries, float hitRatio )
        : _entries(entries), _maxEntries(maxEntries), _queries(queries), _hitRatio(hitRatio) {}
    
    virtual ~CVBF_StatsCache() {}

public:
    unsigned	_entries;
    unsigned	_maxEntries;
    unsigned	_queries;
    float		_hitRatio;
};


//------------------------------------------------------------------------

/**
* Least-recently-used cache class.
* K = key type, T = value type
*
* usage:
*    CVBF_CacheLRU<K,T> cache;
*    cache.put( key, value );
*    CVBF_CacheLRU.Record rec = cache.get( key );
*    if ( rec.valid() )
*        const T& value = rec.value();
*/
template<typename K, typename T, typename COMPARE=std::less<K> >
class CVBF_CacheLRU
{
public:
    struct Record 
	{
        Record() : _valid(false) { }
        Record(const T& value) : _value(value), _valid(true) { }

        bool valid() const { return _valid; }
        const T&   value() const { return _value; }

    private:
        bool			_valid;
        T				_value;
        friend class	CVBF_CacheLRU;
    };

protected:
    typedef typename std::list<K>::iterator      lru_iter;
    typedef typename std::list<K>                lru_type;
    typedef typename std::pair<T, lru_iter>      map_value_type;
    typedef typename std::map<K, map_value_type> map_type;
    typedef typename map_type::iterator          map_iter;

    map_type			_map;
    lru_type			_lru;
    unsigned			_max;
    unsigned			_buf;
    unsigned			_queries;
    unsigned			_hits;
    bool				_threadsafe;
    mutable CVBF_Mutex	_mutex;

public:
    CVBF_CacheLRU( unsigned max =100 ) : _max(max), _threadsafe(false) 
	{
        _buf = _max/10;
        if(_buf<1) _buf=1;
        _queries = 0;
        _hits = 0;
    }

    CVBF_CacheLRU( bool threadsafe, unsigned max =100 ) : _max(max), _threadsafe(threadsafe) 
	{
        _buf = _max/10;
        if(_buf<1) _buf=1;
        _queries = 0;
        _hits = 0;
    }

    /** dtor */
    virtual ~CVBF_CacheLRU() { }

    void insert( const K& key, const T& value ) 
	{
        if ( _threadsafe ) 
		{
            CVBF_ScopedMutexLock lock(_mutex);
            insert_impl( key, value );
        }
        else 
		{
            insert_impl( key, value );
        }
    }

    bool get( const K& key, Record& out ) 
	{
        if ( _threadsafe ) 
		{
            CVBF_ScopedMutexLock lock(_mutex);
            get_impl( key, out );
        }
        else 
		{
            get_impl( key, out );
        }
        return out.valid();
    }

    bool has( const K& key ) 
	{
        if ( _threadsafe ) 
		{
            CVBF_ScopedMutexLock lock(_mutex);
            return has_impl( key );
        }
        else 
		{
            return has_impl( key );
        }
    }

    void erase( const K& key ) 
	{
        if ( _threadsafe ) 
		{
            CVBF_ScopedMutexLock lock(_mutex);
            erase_impl( key );
        }
        else 
		{
            erase_impl( key );
        }
    }

    void clear() 
	{
        if ( _threadsafe ) 
		{
            CVBF_ScopedMutexLock lock(_mutex);
            clear_impl();
        }
        else 
		{
            clear_impl();
        }
    }

    void setMaxSize( unsigned max ) 
	{
        if ( _threadsafe ) 
		{
            CVBF_ScopedMutexLock lock(_mutex);
            setMaxSize_impl( max );
        }
        else 
		{
            setMaxSize_impl( max );
        }
    }

    unsigned getMaxSize() const 
	{
        return _max;
    }

    CVBF_StatsCache getStats() const 
	{
        return CVBF_StatsCache(_lru.size(), _max, _queries, _queries > 0 ? (float)_hits/(float)_queries : 0.0f );
    }

private:

    void insert_impl( const K& key, const T& value ) 
	{
        map_iter mi = _map.find( key );
        if ( mi != _map.end() ) 
		{
            _lru.erase( mi->second.second );
            mi->second.first = value;
            _lru.push_back( key );
            mi->second.second = _lru.end();
            mi->second.second--;
        }
        else 
		{
            _lru.push_back( key );
            lru_iter last = _lru.end(); last--;
            _map[key] = std::make_pair(value, last);
        }

        if ( _lru.size() > _max ) 
		{
            for( unsigned i=0; i < _buf; ++i ) 
			{
                const K& key = _lru.front();
                _map.erase( key );
                _lru.pop_front();
            }
        }
    }

    void get_impl( const K& key, Record& result ) 
	{
        _queries++;
        map_iter mi = _map.find( key );
        if ( mi != _map.end() ) 
		{
            _lru.erase( mi->second.second );
            _lru.push_back( key );
            lru_iter new_iter = _lru.end(); new_iter--;
            mi->second.second = new_iter;
            _hits++;
            result._value = mi->second.first;
            result._valid = true;
        }
    }

    bool has_impl( const K& key )
	{
        return _map.find( key ) != _map.end();
    }

    void erase_impl( const K& key )
	{
        map_iter mi = _map.find( key );
        if ( mi != _map.end() ) 
		{
            _lru.erase( mi->second.second );
            _map.erase( mi );
        }
    }

    void clear_impl() 
	{
        _lru.clear();
        _map.clear();
        _queries = 0;
        _hits = 0;
    }

    void setMaxSize_impl( unsigned max )
	{
        _max = max;
        _buf = max/10;

        while( _lru.size() > _max ) 
		{
            const K& key = _lru.front();
            _map.erase( key );
            _lru.pop_front();
        }
    }
};


#endif
