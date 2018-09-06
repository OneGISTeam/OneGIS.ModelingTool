#ifndef OSGEARTH_FEATURES_SCRIPT_H
#define OSGEARTH_FEATURES_SCRIPT_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_Base/ref_ptr>
#include <list>
#include <map>
#include <stdlib.h>

namespace osgEarth { namespace Features
{

  /** 
   * Script contains code written in a scripting language (javascript is default).
   */
  class OSGEARTHFEATURES_EXPORT Script : public ::CVBF_Referenced
  {
  public:

    /**
     * Constructs a new script with code in the specified language.
     *
     * @param code
     *      Source code
     * @param language
     *      Script language (default is javascript)
     * @param name
     *      Name of the script
     */
    Script( const std::string& code="", const std::string& language="javascript", const std::string& name="" ) 
        : m_sName(name), _language(language), _code(code) { }

    virtual ~Script() { }
    
    /**
     * Sets the name of this script.
     *
     * @param name
     *      Name of the script
     */
    void setName( const std::string& name ) { m_sName = name; }

    /**
     * Gets the name of this script.
     *
     * @return Name of the script
     */
    const std::string& getName() const { return m_sName; }

    /** 
     * Sets the scripting language of the code.
     *
     * @param language
     *      Language in which the script is written (e.g., "javascript")
     */
    void setLanguage( const std::string& language ) { _language = language; }

    /**
     * Gets the scripting language the code is written in.
     *
     * @return Lanuage in which the script is written (e.g., "javascript")
     */
    const std::string& getLanguage() const { return _language; }

    /**
     * Sets the source code.
     *
     * @param code
     *      Source code
     */
    void setCode( const std::string& code ) { _code = code; }
    
    /**
     * Gets the source code.
     *
     * @return Source code
     */
    const std::string& getCode() const { return _code; }

  private:
    std::string m_sName;
    std::string _language;
    std::string _code;
  };


  typedef std::list< ref_ptr<Script> > ScriptList;
  typedef std::map<std::string, ref_ptr<Script> > ScriptMap;


  class OSGEARTHFEATURES_EXPORT ScriptResult : public ::CVBF_Referenced
  {
  public:
    ScriptResult()
        : _value(""), _success(false), _msg("Script result not set") {}

    ScriptResult(const std::string& val, bool success=true, const std::string& message="") 
        : _value(val), _success(success), _msg(message) {}

    bool success() const { return _success; }

    const std::string& message() const { return _msg; }

    std::string asString() { return _value; }

    double asDouble(double defaultValue=0.0) { return _value.length() > 0 ? ::atof(_value.c_str()) : defaultValue; }

  protected:
    std::string _value;
    bool        _success;
    std::string _msg;
  };

} } // namespace osgEarth::Features

#endif // OSGEARTH_FEATURES_SCRIPT_H
