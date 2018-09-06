#ifndef OSGEARTH_HTTP_CLIENT_H
#define OSGEARTH_HTTP_CLIENT_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/IOTypes.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace osgEarth;

/**
    * Proxy server configuration.
    */
class OSGEARTH_EXPORT CVBF_ProxySettings
{
public:
    CVBF_ProxySettings( const CVBF_Config& conf =CVBF_Config() );
    CVBF_ProxySettings( const std::string& host, int port );

    virtual ~CVBF_ProxySettings() { }

    std::string& hostName() { return _hostName; }
    const std::string& hostName() const { return _hostName; }

    int& port() { return _port; }
    const int& port() const { return _port; }

    std::string& userName() { return _userName; }
    const std::string& userName() const { return _userName; }

    std::string& password() { return _password; }
    const std::string& password() const { return _password; }

    void apply(osgDB::Options* dbOptions) const;
    static bool fromOptions( const osgDB::Options* dbOptions, CVBF_Optional<CVBF_ProxySettings>& out );

public:
    virtual CVBF_Config getConfig() const;
    virtual void mergeConfig( const CVBF_Config& conf );

protected:
    std::string _hostName;
    int _port;
    std::string _userName;
    std::string _password;
};


/**
    * An HTTP request for use with the CVBF_HTTPClient class.
    */
class OSGEARTH_EXPORT CVBF_HTTPRequest
{
public:
    /** Constructs a new HTTP request that will acces the specified base URL. */
    CVBF_HTTPRequest( const std::string& url );

    /** copy constructor. */
    CVBF_HTTPRequest( const CVBF_HTTPRequest& rhs );

    /** dtor */
    virtual ~CVBF_HTTPRequest() { }

    /** Adds an HTTP parameter to the request query string. */
    void addParameter( const std::string& name, const std::string& value );
    void addParameter( const std::string& name, int value );
    void addParameter( const std::string& name, double value );
        
    typedef std::map<std::string,std::string> Parameters;

    /** Ready-only access to the parameter list (as built with addParameter) */
    const Parameters& getParameters() const;

    /** Gets a copy of the complete URL (base URL + query string) for this request */
    std::string getURL() const;
        
private:
    Parameters _parameters;
    std::string _url;
};

/**
    * An HTTP response object for use with the CVBF_HTTPClient class - supports
    * multi-part mime responses.
    */
class OSGEARTH_EXPORT CVBF_HTTPResponse
{
public:
    enum Code 
	{
        NONE         = 0,
        OK           = 200,
        BAD_REQUEST  = 400,
        NOT_FOUND    = 404,
        CONFLICT     = 409,
        SERVER_ERROR = 500
    };

public:
    /** Constructs a response with the specified HTTP response code */
    CVBF_HTTPResponse( long code =0L );

    /** Copy constructor */
    CVBF_HTTPResponse( const CVBF_HTTPResponse& rhs );

    /** dtor */
    virtual ~CVBF_HTTPResponse() { }

    /** Gets the HTTP response code (Code) in this response */
    unsigned getCode() const;

    /** True is the HTTP response code is OK (200) */
    bool isOK() const;

    /** True if the request associated with this response was cancelled before it completed */
    bool isCancelled() const;

    /** Gets the number of parts in a (possibly multipart mime) response */
    unsigned int getNumParts() const;

    /** Gets the input stream for the nth part in the response */
    std::istream& getPartStream( unsigned int n ) const;

    /** Gets the nth response part as a string */
    std::string getPartAsString( unsigned int n ) const;

    /** Gets the length of the nth response part */
    unsigned int getPartSize( unsigned int n ) const;
        
    /** Gets the HTTP header associated with the nth multipart/mime response part */
    const std::string& getPartHeader( unsigned int n, const std::string& name ) const;

    /** Gets the master mime-type returned by the request */
    const std::string& getMimeType() const;

private:
    struct Part : public ::CVBF_Referenced
    {
        Part() : _size(0) { }
        typedef std::map<std::string,std::string> Headers;
        Headers _headers;
        unsigned int _size;
        std::stringstream _stream;
    };
    typedef std::vector< ref_ptr<Part> > Parts;
    Parts       _parts;
    long        _response_code;
    std::string _mimeType;
    bool        _cancelled;

    CVBF_Config getHeadersAsConfig() const;

    friend class CVBF_HTTPClient;
};

/**
    * Utility class for making HTTP requests.
    *
    * TODO: This class will actually read data from disk as well, and therefore should
    * probably be renamed. It analyzes the URI and decides whether to make an  HTTP request
    * or to read from disk.
    */
class OSGEARTH_EXPORT CVBF_HTTPClient // : public ::CVBF_Referenced
{
public:
    /**
        * Returns true is the result code represents a recoverable situation,
        * i.e. one in which retrying might work.
        */
    static bool isRecoverable( ReadResult::Code code )
    {
        return
            code == ReadResult::RESULT_OK ||
            code == ReadResult::RESULT_SERVER_ERROR ||
            code == ReadResult::RESULT_TIMEOUT ||
            code == ReadResult::RESULT_CANCELED;
    }

    /** Gest the user-agent string that all HTTP requests will use.
        TODO: This should probably move into the Registry */
    static const std::string& getUserAgent();

    /** Sets a user-agent string to use in all HTTP requests.
        TODO: This should probably move into the Registry */
    static void setUserAgent(const std::string& userAgent);

    /** Sets up proxy info to use in all HTTP requests.
        TODO: This should probably move into the Registry */
    static void setProxySettings( const CVBF_ProxySettings &proxySettings );

    /**
        Gets the timeout in seconds to use for HTTP requests.*/
    static long getTimeout();

    /**
        Sets the timeout in seconds to use for HTTP requests.
        Setting to 0 (default) is infinite timeout */
    void setTimeout( long timeout );

    /**
        * One time thread safe initialization. In osgEarth, you don't need
        * to call this directly; osgEarth::Registry will call it at
        * startup.
        */
    static void globalInit();


public:
    /**
        * Reads an image.
        */
    static ReadResult readImage(
        const std::string&    location,
        const osgDB::Options* dbOptions =0L,
        ProgressCallback*     progress  =0L );

    /**
        * Reads an osg::Node.
        */
    static ReadResult readNode(
        const std::string&    location,
        const osgDB::Options* dbOptions =0L,
        ProgressCallback*     progress  =0L );

    /**
        * Reads an object.
        */
    static ReadResult readObject(
        const std::string&    location,
        const osgDB::Options* dbOptions =0L,
        ProgressCallback*     progress  =0L );

    /**
        * Reads a string.
        */
    static ReadResult readString(
        const std::string&    location,
        const osgDB::Options* dbOptions =0L,
        ProgressCallback*     progress  =0L );

    /**
        * Downloads a file directly to disk.
        */
    static bool download(
        const std::string& uri,
        const std::string& localPath );

public:

    /**
        * Performs an HTTP "GET".
        */
    static CVBF_HTTPResponse get( const CVBF_HTTPRequest&    request,
                                const osgDB::Options* dbOptions =0L,
                                ProgressCallback*     progress  =0L );

    static CVBF_HTTPResponse get( const std::string&    url,
                                const osgDB::Options* options  =0L,
                                ProgressCallback*     progress =0L );

public:
    CVBF_HTTPClient();
    virtual ~CVBF_HTTPClient();

private:

    void readOptions( const osgDB::ReaderWriter::Options* options, std::string &proxy_host, std::string &proxy_port ) const;

    CVBF_HTTPResponse doGet( const CVBF_HTTPRequest&    request,
                        const osgDB::Options* options  =0L,
                        ProgressCallback*     callback =0L ) const;

    CVBF_HTTPResponse doGet( const std::string&    url,
                        const osgDB::Options* options  =0L,
                        ProgressCallback*     callback =0L ) const;

    ReadResult doReadObject(
        const std::string&    location,
        const osgDB::Options* dbOptions,
        ProgressCallback*     progress );

    ReadResult doReadImage(
        const std::string&    location,
        const osgDB::Options* dbOptions,
        ProgressCallback*     progress );

    ReadResult doReadNode(
        const std::string&    location,
        const osgDB::Options* dbOptions,
        ProgressCallback*     progress );

    ReadResult doReadString(
        const std::string&    location,
        const osgDB::Options* dbOptions,
        ProgressCallback*     progress );

    /**
        * Convenience method for downloading a URL directly to a file
        */
    bool doDownload(const std::string& url, const std::string& filename);

private:
    void*       _curl_handle;
    std::string _previousPassword;
    long        _previousHttpAuthentication;
    bool        _initialized;
    long        _simResponseCode;

    void initialize() const;
    void initializeImpl();


    static CVBF_HTTPClient& getClient();

private:
    void decodeMultipartStream(
        const std::string&   boundary,
        CVBF_HTTPResponse::Part*  input,
        CVBF_HTTPResponse::Parts& output) const;
};


#endif // OSGEARTH_HTTP_CLIENT_H
