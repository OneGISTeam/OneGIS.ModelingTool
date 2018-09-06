
#ifndef OSGEARTH_URI
#define OSGEARTH_URI 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CacheBin.h>
#include <VBF_3DMap/VBF_Terrain/VBF_CachePolicy.h>
#include <VBF_Common/VBF_Utils/VBF_CacheLRU.h>
#include <VBF_Common/VBF_Utils/VBF_FileNameUtils.h>
#include <VBF_3DMap/VBF_Terrain/IOTypes.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>
#include <iostream>
#include <sstream>

namespace osgEarth
{
    class URI;

    /**
     URI的上下文，即URI所需要的信息

     * "referrer"是一个对象的定位， that "points" to the object in the
     * corresponding URI. The location conveyed by the URI will be relative to the location of
     * its referrer. For example, a referrer of "http://server/folder/hello.xml" applied
     * to the URI "there.jpg" will resolve to "http://server/folder/there.jpg". NOTE that referrer
     * it not itself a location (like a folder); rather it's the object that referred to the URI
     * being contextualized.
     */
    class OSGEARTH_EXPORT URIContext
    {
    public:
        
        URIContext() { }

        /** Creates a context that specifies a referring object. */
        URIContext( const std::string& referrer ) : _referrer(referrer) { }

        URIContext( const URIContext& rhs ) : _referrer(rhs._referrer) { }
        virtual ~URIContext() { }

        /** Serializes this context to an Options structure. This is useful when passing context information
            to an osgDB::ReaderWriter that takes a stream as input -- the stream is anonymous, therefore this
            is the preferred way to communicate the context information. */
        void apply( osgDB::Options* options );

        /** Creates a context from the serialized version in an Options structure (see above) */
        URIContext( const osgDB::Options* options );

        /** Returns the referring object. */
        const std::string& referrer() const { return _referrer; }

        bool empty() const { return _referrer.empty(); }// 上下文是否为空

        /** Parents the input context with the current object, placing the subContext's information
            under it. Used to re-parent relative locations with a higher-level referrer object. */
        URIContext add( const URIContext& subContext ) const;

        /** Returns a new context with the sub path appended to the current referrer path. */
        URIContext add( const std::string& subPath ) const;

        /** creates a string suitable for passing to an osgDB::ReaderWriter implementation */
        std::string getOSGPath( const std::string& target ) const;

    private:
        friend class URI;
        std::string _referrer;
    };

 
	// Stream容器用于从URI读取数据
    class OSGEARTH_EXPORT URIStream
    {
    public:
        URIStream( const URI& uri );
        virtual ~URIStream();
    public:
        operator std::istream& ();// 装换为标准流
    protected:
        friend class URI;
        std::istream*     _fileStream;
        std::stringstream _bufStream;
    };

   
	// 统一资源标识符URI:Uniform Resource Identifier。某些时候等同于URL：统一资源定位
    class OSGEARTH_EXPORT URI
    {
    public:    
        URI();
        URI( const std::string& location );  // 从URL构建   
		// 从URL和已存在的URIContext构建
        URI( const std::string& location, const URIContext& context );
        URI( const char* location );
        URI( const URI& rhs );
        virtual ~URI();
        URI& operator = (const URI& rhs);

    public:
        const std::string& base()const;// 基本（可能是相对的）定位字符串
        const std::string& full() const;// 完整描述的定位字符串
        const std::string& operator * () const;// 返回完整描述的定位字符串
        const URIContext& context() const; // 创建该URI所用的环境（上下文）

        bool empty() const;// 是否为空
        bool isRemote() const;// 对象是否可以缓冲 （远程）

        // 把该URI加上后缀
        URI append( const std::string& suffix ) const;

         // 获取用于缓存的key
        const std::string& cacheKey() const;
        // 设置一个缓冲的键值，默认的key为完整的URI，但可以重载它
        void setCacheKey( const std::string& key );

    public: // read methods return a ReadResult object

        ReadResult readObject( const osgDB::Options* dbOptions=0L, ProgressCallback* progress =0L ) const;
        ReadResult readImage( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;
        ReadResult readNode( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;
        ReadResult readString( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;
        ReadResult readConfig( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;

    public: // get methods call the read* methods, then just return the raw data.
        osg::CVBF_Object* getObject( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;
        osg::Image* getImage( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;
        osg::IVBF_SGNode* getNode( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;
        std::string getString( const osgDB::Options* dbOptions =0L, ProgressCallback* progress =0L ) const;

    public:
        bool operator < ( const URI& rhs ) const;

	protected:
        std::string _baseURI;
        std::string _fullURI;
        std::string _cacheKey;
        URIContext  _context;
    };
    

//------------------------------------------------------------------------


    /**
     * 一个映射表，that maps URI references to other URI references. This
     * is used as an optional resource mapping table. (See KML's ResourceMap
     * for usage example)
     *
     * WARNING: osgDB::Options will only store a raw pointer to the class, so
     * make sure the scope of the osgDB::Options does not exceed the scope of
     * the embedded alias map!
     */
    class OSGEARTH_EXPORT URIAliasMap
    {
    public:
        // Inserts a key-value pair into the map.
        void insert( const std::string& key, const std::string& value );

        // 把输入地址分解为URI字符串
        std::string resolve(const std::string& input, const URIContext& context) const;

        bool empty() const { return _map.empty(); }

        void clear() { _map.clear(); }

        // Loads an alias map from an Options.
        static URIAliasMap* from( const osgDB::Options* options ) 
		{
            return options ? static_cast<URIAliasMap*>(const_cast<osgDB::Options*>(options)->getPluginData("osgEarth::URIAliasMap")) : 0L;
        }

        // Stores an alias map in an Options
        void apply( osgDB::Options* options ) 
		{
            if ( options ) options->setPluginData("osgEarth::URIAliasMap", this);
        }

        std::map< std::string,std::string > _map;
        friend class CVBF_Config;
    };


    /**
     * A custom read callback (that you can set in an osgDB::Options) that will 
     * attempt to resolve pathnames using a URI alias map.
     */
    class OSGEARTH_EXPORT URIAliasMapReadCallback : public osgDB::ReadFileCallback
    {
    public:
        URIAliasMapReadCallback( const URIAliasMap& aliasMap, const URIContext& context );

        virtual osgDB::ReaderWriter::ReadResult openArchive(const std::string& filename, osgDB::ReaderWriter::ArchiveStatus status, unsigned int indexBlockSizeHint, const osgDB::Options* useObjectCache);
        virtual osgDB::ReaderWriter::ReadResult readObject(const std::string& filename, const osgDB::Options* options);
        virtual osgDB::ReaderWriter::ReadResult readImage(const std::string& filename, const osgDB::Options* options);
        virtual osgDB::ReaderWriter::ReadResult readHeightField(const std::string& filename, const osgDB::Options* options);
        virtual osgDB::ReaderWriter::ReadResult readNode(const std::string& filename, const osgDB::Options* options);
        virtual osgDB::ReaderWriter::ReadResult readShader(const std::string& filename, const osgDB::Options* options);

    protected:
        const URIAliasMap& _aliasMap;
        URIContext         _context;
    };


//------------------------------------------------------------------------

    /**
     * A URI result cache that you can embed in an osgDB::Options, and if found,
     * URI will attempt to use it. 
     *
     * WARNING: osgDB::Options will only store a raw pointer to the class, so
     * make sure the scope of the osgDB::Options does not exceed the scope of
     * the embedded cache!
     */
    struct /*header-only*/ URIResultCache : public CVBF_CacheLRU<URI, ReadResult>
    {
        URIResultCache( bool threadsafe =true )
            : CVBF_CacheLRU<URI,ReadResult>( threadsafe ) { }

        static URIResultCache* from(const osgDB::Options* options) 
		{
            return options ? static_cast<URIResultCache*>(const_cast<osgDB::Options*>(options)->getPluginData("osgEarth::URIResultCache")) : 0L;
        }

        void apply( osgDB::Options* options ) 
		{
            if ( options ) options->setPluginData("osgEarth::URIResultCache", this);
        }
    };


//------------------------------------------------------------------------

    /**
     * You can install a post-read callback in a osgDB::Options and the URI
     * class till invoke it on a ReadResult before returning.
     */
    class /*header-only*/ URIPostReadCallback : public ::CVBF_Referenced
    {
    public:
        URIPostReadCallback() { }
        virtual ~URIPostReadCallback() { }

        virtual void operator()( ReadResult& result ) =0;

    public:
        void apply(osgDB::Options* options) 
		{
            if ( options ) options->setPluginData("osgEarth::URIPostReadCallback", this);
        }

        static URIPostReadCallback* from(const osgDB::Options* options) 
		{
            return options ? static_cast<URIPostReadCallback*>(const_cast<osgDB::Options*>(options)->getPluginData("osgEarth::URIPostReadCallback")) : 0L;
        }
    };
}
    
//------------------------------------------------------------------------

// CVBF_Config specialization for URI:

template <> inline
void CVBF_Config::addIfSet<osgEarth::URI>( const std::string& key, const CVBF_Optional<osgEarth::URI>& opt ) 
{
    if ( opt.isSet() ) 
	{
        CVBF_Config conf(key, opt->base());
        conf.setReferrer(opt->context().referrer());
        add( conf );
    }
}

template<> inline
void CVBF_Config::updateIfSet<osgEarth::URI>( const std::string& key, const CVBF_Optional<osgEarth::URI>& opt )
{
    if ( opt.isSet() ) 
	{
        remove(key);
        CVBF_Config conf(key, opt->base());
        conf.setReferrer(opt->context().referrer());
        add( conf );
    }
}

template<> inline
bool CVBF_Config::getIfSet<osgEarth::URI>( const std::string& key, CVBF_Optional<osgEarth::URI>& output ) const 
{
    if ( hasValue(key) ) 
	{
        output = osgEarth::URI( value(key), referrer(key) );
        return true;
    }
    else
	{
        return false;
	}
}

// CVBF_Config specialization for URIAliasMap

template <> inline
void CVBF_Config::addIfSet<osgEarth::URIAliasMap>( const std::string& key, const CVBF_Optional<osgEarth::URIAliasMap>& map ) 
{
    if ( map.isSet() ) 
	{
        CVBF_Config conf( key );
        for( std::map<std::string,std::string>::const_iterator i = map->_map.begin(); i != map->_map.end(); ++i )
		{
            CVBF_Config alias( "alias" );
            alias.add( "source", i->first );
            alias.add( "target", i->second );
            conf.add( alias );
        }
        add(conf);
    }
}

template <> inline
void CVBF_Config::updateIfSet<osgEarth::URIAliasMap>( const std::string& key, const CVBF_Optional<osgEarth::URIAliasMap>& map ) 
{
    if ( map.isSet() )
	{
        remove( key );
        addIfSet( key, map );
    }
}

template <> inline
bool CVBF_Config::getIfSet<osgEarth::URIAliasMap>( const std::string& key, CVBF_Optional<osgEarth::URIAliasMap>& output ) const 
{
    CVBF_Config alias = child(key);
    if ( !alias.isEmpty() ) 
	{
        for( CVBF_ConfigList::const_iterator i = alias.children().begin(); i != alias.children().end(); ++i ) 
		{
            std::string source = i->value("source");
            std::string target = i->value("target");
            if ( !source.empty() && !target.empty() )
                output->insert( source, target );
        }
        return true;
    }
    else 
	{
        return false;
    }
}


#endif // OSGEARTH_URI
