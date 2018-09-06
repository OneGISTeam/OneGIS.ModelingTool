#ifndef VBF_ARGUMENTPARSER_H
#define VBF_ARGUMENTPARSER_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Base/VBF_ApplicationUsage.h>

#include <map>
#include <string>
#include <ostream>

// 命令行参数解析器
class VBF_BASE_EXPORT ArgumentParser
{
    public:

        class VBF_BASE_EXPORT Parameter
        {
        public:
            enum ParameterType
            {
                BOOL_PARAMETER,
                FLOAT_PARAMETER,
                DOUBLE_PARAMETER,
                INT_PARAMETER,
                UNSIGNED_INT_PARAMETER,
                STRING_PARAMETER
            };
        
            union ValueUnion
            {
                bool*           _bool;
                float*          _float;
                double*         _double;
                int*            _int;
                unsigned int*   _uint;
                std::string*    _string;
            };

            Parameter(bool& value);
            Parameter(float& value);
            Parameter(double& value);
            Parameter(int& value);
            Parameter(unsigned int& value);
            Parameter(std::string& value);
            Parameter(const Parameter& param);
            Parameter& operator = (const Parameter& param);

            bool valid(const char* str) const;
            bool assign(const char* str);

        protected:
        
            ParameterType   _type;
            ValueUnion      _value;
        };

        /** Return true if the specified string is an option in the form  -option or --option. */
        static bool isOption(const char* str);
        
        /** Return true if string is non-NULL and not an option in the form  -option or --option. */
        static bool isString(const char* str);
        
        /** Return true if specified parameter is a number. */
        static bool isNumber(const char* str);

        /** Return true if specified parameter is a bool. */
        static bool isBool(const char* str);

    public:

        ArgumentParser(int* argc,char **argv);
        void setApplicationUsage(ApplicationUsage* usage) { _usage = usage; }
        ApplicationUsage* getApplicationUsage() { return _usage.get(); }
        const ApplicationUsage* getApplicationUsage() const { return _usage.get(); }

        /** Return the argument count. */
        int& argc() { return *_argc; }

        /** Return the argument array. */
        char** argv() { return _argv; }

        /** Return the char* argument at the specified position. */
        char* operator [] (int pos) { return _argv[pos]; }

        /** Return the const char* argument at the specified position. */
        const char* operator [] (int pos) const { return _argv[pos]; }

        /** Return the application name, as specified by argv[0]  */
        std::string getApplicationName() const;

        /** Return the position of an occurrence of a string in the argument list.
          * Return -1 if no string is found. */
        int find(const std::string& str) const;

        /** Return true if the specified parameter is an option in the form of
          * -option or --option. */
        bool isOption(int pos) const;
        
        /** Return true if the specified parameter is a string not in
          * the form of an option. */
        bool isString(int pos) const;
        
        /** Return true if the specified parameter is a number. */
        bool isNumber(int pos) const;
        
        bool containsOptions() const;

        /** Remove one or more arguments from the argv argument list,
          * and decrement the argc respectively. */
        void remove(int pos,int num=1);
        
        /** Return true if the specified argument matches the given string. */
        bool match(int pos, const std::string& str) const;

        /** Search for an occurrence of a string in the argument list. If found,
          * remove that occurrence and return true. Otherwise, return false. */
        bool read(const std::string& str);
        bool read(const std::string& str, Parameter value1);
        bool read(const std::string& str, Parameter value1, Parameter value2);
        bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3);
        bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4);
        bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5);
        bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6);
        bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7);
        bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7, Parameter value8);


        /** If the argument value at the specified position matches the given string,
          * and subsequent parameters are also matched, then set the parameter values,
          * remove the arguments from the list, and return true. Otherwise, return false. */
        bool read(int pos, const std::string& str);
        bool read(int pos, const std::string& str, Parameter value1);
        bool read(int pos, const std::string& str, Parameter value1, Parameter value2);
        bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3);
        bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4);
        bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5);
        bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6);
        bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7);
        bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7, Parameter value8);


        enum ErrorSeverity
        {
            BENIGN = 0,
            CRITICAL = 1
        };

        typedef std::map<std::string,ErrorSeverity> ErrorMessageMap;

        /** Return the error flag, true if an error has occurred when reading arguments. */
        bool errors(ErrorSeverity severity=BENIGN) const;

        /** Report an error message by adding to the ErrorMessageMap. */
        void reportError(const std::string& message,ErrorSeverity severity=CRITICAL);

        /** For each remaining option, report it as unrecognized. */
        void reportRemainingOptionsAsUnrecognized(ErrorSeverity severity=BENIGN);
        
        /** Return the error message, if any has occurred. */
        ErrorMessageMap& getErrorMessageMap() { return _errorMessageMap; }
      
        /** Return the error message, if any has occurred. */
        const ErrorMessageMap& getErrorMessageMap() const { return _errorMessageMap; }

        /** Write error messages to the given ostream, if at or above the given severity. */
        void writeErrorMessages(std::ostream& output,ErrorSeverity sevrity=BENIGN);

        
        /** This convenience method handles help requests on the command line.
          * Return the type(s) of help requested. The return value of this
          * function is suitable for passing into getApplicationUsage()->write().
          * If ApplicationUsage::NO_HELP is returned then no help commandline option 
          * was found on the command line. */
        ApplicationUsage::Type readHelpType();

  
  protected:
        
        int*                      _argc;
        char**                    _argv;
        ErrorMessageMap           _errorMessageMap;
        ref_ptr<ApplicationUsage> _usage;
        
};

#endif
