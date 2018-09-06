#ifndef VBF_APPLICATIONUSAGE_H
#define VBF_APPLICATIONUSAGE_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <VBF_Base/VBF_Referenced.h>

#include <map>
#include <string>
#include <ostream>



class VBF_BASE_EXPORT ApplicationUsage : public ::CVBF_Referenced
{
    public:       
        static ApplicationUsage* instance();

        ApplicationUsage();
        ApplicationUsage(const std::string& commandLineUsage);

        typedef std::map<std::string,std::string> UsageMap;
        

        /** The ApplicationName is often displayed when logging errors, and frequently incorporated into the Description (below). */
        void setApplicationName(const std::string& name) { _applicationName = name; }
        const std::string& getApplicationName() const { return _applicationName; }

        /** If non-empty, the Description is typically shown by the Help Handler
          * as text on the Help display (which also lists keyboard abbreviations. */
        void setDescription(const std::string& desc) { _description = desc; }
        const std::string& getDescription() const { return _description; }

        enum Type
        {
            NO_HELP = 0x0,
            COMMAND_LINE_OPTION = 0x1,
            ENVIRONMENTAL_VARIABLE = 0x2,
            KEYBOARD_MOUSE_BINDING = 0x4,
            HELP_ALL = KEYBOARD_MOUSE_BINDING|ENVIRONMENTAL_VARIABLE|COMMAND_LINE_OPTION
        };
        
        void addUsageExplanation(Type type,const std::string& option,const std::string& explanation);
        
        void setCommandLineUsage(const std::string& explanation) { _commandLineUsage=explanation; }
        const std::string& getCommandLineUsage() const { return _commandLineUsage; }


        void addCommandLineOption(const std::string& option,const std::string& explanation, const std::string &defaultValue = "");     
        void setCommandLineOptions(const UsageMap& usageMap) { _commandLineOptions=usageMap; }
        const UsageMap& getCommandLineOptions() const { return _commandLineOptions; }

        void setCommandLineOptionsDefaults(const UsageMap& usageMap) { _commandLineOptionsDefaults=usageMap; }
        const UsageMap& getCommandLineOptionsDefaults() const { return _commandLineOptionsDefaults; }

        void addEnvironmentalVariable(const std::string& option,const std::string& explanation, const std::string& defaultValue = "");
        
        void setEnvironmentalVariables(const UsageMap& usageMap) { _environmentalVariables=usageMap; }
        const UsageMap& getEnvironmentalVariables() const { return _environmentalVariables; }

        void setEnvironmentalVariablesDefaults(const UsageMap& usageMap) { _environmentalVariablesDefaults=usageMap; }
        const UsageMap& getEnvironmentalVariablesDefaults() const { return _environmentalVariablesDefaults; }

        void addKeyboardMouseBinding(const std::string& option,const std::string& explanation);
        void setKeyboardMouseBindings(const UsageMap& usageMap) { _keyboardMouse=usageMap; }
        const UsageMap& getKeyboardMouseBindings() const { return _keyboardMouse; }


        void getFormattedString(std::string& str, const UsageMap& um,unsigned int widthOfOutput=80,bool showDefaults=false,const UsageMap& ud=UsageMap());

        void write(std::ostream& output,const UsageMap& um,unsigned int widthOfOutput=80,bool showDefaults=false,const UsageMap& ud=UsageMap());        
        void write(std::ostream& output,unsigned int type=COMMAND_LINE_OPTION, unsigned int widthOfOutput=80,bool showDefaults=false);

        void writeEnvironmentSettings(std::ostream& output);

    protected:   
        virtual ~ApplicationUsage();

        std::string _applicationName;
        std::string _description;
        std::string _commandLineUsage;
        UsageMap    _commandLineOptions;
        UsageMap    _environmentalVariables;
        UsageMap    _keyboardMouse;
        UsageMap    _environmentalVariablesDefaults;
        UsageMap    _commandLineOptionsDefaults;
        
};

class ApplicationUsageProxy
{   
    public:

        /** register an explanation of commandline/environmentvariable/keyboard mouse usage.*/
        ApplicationUsageProxy(ApplicationUsage::Type type,const std::string& option,const std::string& explanation)
        {
            ApplicationUsage::instance()->addUsageExplanation(type,option,explanation);
        }
		~ApplicationUsageProxy()
		{
		}
};


#endif
