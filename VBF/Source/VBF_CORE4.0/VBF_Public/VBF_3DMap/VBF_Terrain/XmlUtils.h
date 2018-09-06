/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2008-2013 Pelican Mapping
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef OSGEARTH_XML_UTILS_H
#define OSGEARTH_XML_UTILS_H

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Common/VBF_Utils/VBF_StringUtils.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>
#include <string>
#include <vector>
#include <map>
#include <stack>

// general-purpose name/value pair set.
struct Properties : public std::map<std::string, std::string> 
{
    std::string get( const std::string& key ) const 
	{
        std::map<std::string,std::string>::const_iterator i = find(key);
        return i != end()? i->second : std::string();
    }
};

namespace osgEarth
{
    class OSGEARTH_EXPORT XmlNode : public ::CVBF_Referenced
    {
    public:
        XmlNode();       
        virtual ~XmlNode();

        virtual bool isElement() const =0;

        virtual bool isText() const =0;
    };

    typedef std::vector<ref_ptr<XmlNode> > XmlNodeList;

    typedef std::map<std::string,std::string> XmlAttributes;

    class OSGEARTH_EXPORT XmlElement : public XmlNode
    {
    public:
        XmlElement( const std::string& name );       
        XmlElement( const std::string& name, const XmlAttributes& attrs );
        XmlElement( const CVBF_Config& conf );      
        virtual ~XmlElement();

        const std::string& getName() const;

        void setName( const std::string& name );

        XmlAttributes& getAttrs();
        
        const XmlAttributes& getAttrs() const;

        const std::string& getAttr( const std::string& key ) const;

        XmlNodeList& getChildren();
        
        const XmlNodeList& getChildren() const;
        
        XmlElement* getSubElement( const std::string& name ) const;
        
        XmlNodeList getSubElements( const std::string& name ) const;
        
        std::string getText() const;
        
        std::string getSubElementText( const std::string& tag ) const;

        void addSubElement(const std::string& tag, const std::string& text);

        void addSubElement(const std::string& tag, const Properties& attrs, const std::string& text);

        virtual CVBF_Config getConfig() const;

    public: // XmlNode
        virtual bool isElement() const { return true; }

        virtual bool isText() const { return false; }

    private:
        std::string name;
        XmlAttributes attrs;
        XmlNodeList children;        
    };

    typedef std::vector<ref_ptr<XmlElement> > XmlElementList;
    
    typedef std::stack<ref_ptr<XmlElement> > XmlElementStack;
    
    typedef std::stack<XmlElement*> XmlElementNoRefStack;

    class OSGEARTH_EXPORT XmlText : public XmlNode
    {
    public:
        XmlText( const std::string& value );     
        virtual ~XmlText();

        const std::string& getValue() const;

    public: // XmlNode
        virtual bool isElement() const { return false; }

        virtual bool isText() const { return true; }
        
    private:
        std::string value;
    };  
    
    class OSGEARTH_EXPORT XmlDocument : public XmlElement
    {
    public:
        XmlDocument();
        XmlDocument( const CVBF_Config& conf );       
        virtual ~XmlDocument();

        static XmlDocument* load( const std::string& location, const osgDB::Options* dbOptions =0L );
        static XmlDocument* load( const URI& uri, const osgDB::Options* dbOptions =0L );      
        static XmlDocument* load( std::istream& in, const URIContext& context =URIContext() );

        void store( std::ostream& out ) const;

        const std::string& getName() const;

        virtual CVBF_Config getConfig() const;

    protected:
        URI                      _sourceURI;
        std::string              m_sName;
        ref_ptr<XmlElement> _root;
    };
}

// 全局函数：根据输入的xml文件名，获取其配置信息 （杜莹改编自：CVBF_Config::fromXML()函数）
OSGEARTH_EXPORT bool VBF_GetConfigFromXML(std::istream& in, CVBF_Config& config);

#endif // OSGEARTH_XML_UTILS_H
