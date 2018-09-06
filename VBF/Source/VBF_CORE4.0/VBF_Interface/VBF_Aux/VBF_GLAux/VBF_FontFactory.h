#ifndef _VBF_FONT_FACTORY_H_
#define _VBF_FONT_FACTORY_H_

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_Text/Font>
#include <map>
#include <string>

class IVBF_FontFactory : public CVBF_Referenced
{
protected:
    ~IVBF_FontFactory(){}
public:
    virtual osgText::Font* getDefaultFont()=0;
    virtual osgText::Font* getFont(const std::string &name, bool bold = false, bool italic = false)=0;
};
VBF_GLAUX_EXPORT IVBF_FontFactory* VBF_GetFontFactory();

class CVBF_FontFactory : public IVBF_FontFactory
{
    typedef std::map<std::string, ref_ptr<osgText::Font> > FontsMap;

public:
    ~CVBF_FontFactory();
    static CVBF_FontFactory *instance();
    virtual osgText::Font* getDefaultFont();
    virtual osgText::Font* getFont(const std::string &name, bool bold = false, bool italic = false);
private:
    CVBF_FontFactory();

    static ref_ptr<CVBF_FontFactory> _singleObject;

    FontsMap _fontsMap;
};



#endif
