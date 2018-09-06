#ifndef OSGEARTH_IOTYPES_H
#define OSGEARTH_IOTYPES_H 1

#include <VBF_3DMap/VBF_Terrain/Export>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SGDB/Options>

/**
 * A collectin of types used by the various I/O systems in osgEarth. These
 * are extended variations on some of OSG's ReaderWriter types.
 */
namespace osgEarth
{

//--------------------------------------------------------------------

    /**
     * String wrapped in an osg::Object (for I/O purposes)
     */
    class OSGEARTH_EXPORT StringObject : public osg::CVBF_Object
    {
    public:
        StringObject();
        StringObject( const StringObject& rhs, const osg::CopyOp& op );
        StringObject( const std::string& in );

        virtual ~StringObject();
        META_Object( osgEarth, StringObject );

        void setString( const std::string& value ) { _str = value; }
        const std::string& getString() const { return _str; }
    private:
        std::string _str;
    };


//--------------------------------------------------------------------

    /**
     * Convenience metadata tags
     */
    struct OSGEARTH_EXPORT IOMetadata
    {
        static const std::string CONTENT_TYPE;
    };

//--------------------------------------------------------------------

    struct OSGEARTH_EXPORT ReadResult
    {
        enum Code
        {
            RESULT_OK,
            RESULT_CANCELED,
            RESULT_NOT_FOUND,
            RESULT_SERVER_ERROR,
            RESULT_TIMEOUT,
            RESULT_NO_READER,
            RESULT_READER_ERROR,
            RESULT_UNKNOWN_ERROR,
            RESULT_NOT_IMPLEMENTED
        };

        ReadResult( Code code =RESULT_NOT_FOUND );
        ReadResult( osg::CVBF_Object* result );
        ReadResult( osg::CVBF_Object* result, const CVBF_Config& meta );
        ReadResult( Code code, osg::CVBF_Object* result, const CVBF_Config& meta );
        ReadResult( const ReadResult& rhs );
        virtual ~ReadResult();

        bool succeeded() const;
        bool failed() const;
        bool empty() const;
        const Code& code() const;
        bool isFromCache() const;

        osg::CVBF_Object* getObject() const;
        osg::Image* getImage() const;
        osg::IVBF_SGNode* getNode() const;

        /** The result, transfering ownership to the caller */
        osg::CVBF_Object* releaseObject();
        osg::Image* releaseImage()  ;
        osg::IVBF_SGNode* releaseNode();

        const CVBF_Config& metadata() const;

        /** The result, cast to a custom type */
        template<typename T>
        T* get() const { return dynamic_cast<T*>(_result.get()); }

        /** The result, cast to a custom type and transfering ownership to the caller*/
        template<typename T>
        T* release() { return dynamic_cast<T*>(_result.get())? static_cast<T*>(_result.release()) : 0L; }

        /** The result as a string */
        const std::string& getString() const;
        
        /** Gets a string describing the read result */
        static std::string getResultCodeString( unsigned code );

        std::string getResultCodeString() const;

    public:
        void setIsFromCache(bool value);

    protected:
        Code                      _code;
        ref_ptr<osg::CVBF_Object> _result;
        CVBF_Config                    _meta;
        std::string               _emptyString;
        CVBF_Config                    _emptyConfig;
        bool                      _fromCache;
    };

//--------------------------------------------------------------------

    /**
     * Callback that allows the developer to re-route URI read calls. 
     *
     * If the corresponding callback method returns NOT_IMPLEMENTED, URI will
     * fall back on its default mechanism.
     */
    class OSGEARTH_EXPORT URIReadCallback : public ::CVBF_Referenced
    {
    public:
        enum CachingSupport
        {
            CACHE_NONE        = 0,
            CACHE_OBJECTS     = 1 << 0,
            CACHE_NODES       = 1 << 1,
            CACHE_IMAGES      = 1 << 2,
            CACHE_STRINGS     = 1 << 3,
            CACHE_CONFIGS     = 1 << 4,
            CACHE_ALL         = ~0
        };

        /** 
         * Tells the URI class which data types (if any) from this callback should be subjected
         * to osgEarth's caching mechamism. By default, the answer is "none" - URI
         * will not attempt to read or write from its cache when using this callback.
         */
        virtual unsigned cachingSupport() const { return CACHE_NONE; }

    public:

        /** Override the readObject() implementation */
        virtual osgEarth::ReadResult readObject( const std::string& uri, const osgDB::Options* options ) {
            return osgEarth::ReadResult::RESULT_NOT_IMPLEMENTED; }

        /** Override the readNode() implementation */
        virtual osgEarth::ReadResult readNode( const std::string& uri, const osgDB::Options* options ) {
            return osgEarth::ReadResult::RESULT_NOT_IMPLEMENTED; }

        /** Override the readImage() implementation */
        virtual osgEarth::ReadResult readImage( const std::string& uri, const osgDB::Options* options ) {
            return osgEarth::ReadResult::RESULT_NOT_IMPLEMENTED; }

        /** Override the readString() implementation */
        virtual osgEarth::ReadResult readString( const std::string& uri, const osgDB::Options* options ) {
            return osgEarth::ReadResult::RESULT_NOT_IMPLEMENTED; }

        /** Override the readConfig() implementation */
        virtual osgEarth::ReadResult readConfig( const std::string& uri, const osgDB::Options* options ) {
            return osgEarth::ReadResult::RESULT_NOT_IMPLEMENTED; }

    protected:

        URIReadCallback();
        virtual ~URIReadCallback() { }
    };

}

#endif // OSGEARTH_IOTYPES_H
