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
#ifndef OSGEARTH_FEATURES_SCRIPTENGINE_H
#define OSGEARTH_FEATURES_SCRIPTENGINE_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Script.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SGDB/ReaderWriter>

namespace osgEarth { namespace Features
{
  class Feature;
  class FilterContext;
}}


using namespace osgEarth::Features;

/**
* Configuration options for a models source.
*/
class OSGEARTHFEATURES_EXPORT CVBF_OptionsDriverScriptEngine : public CVBF_OptionsDriver
{
public:
    CVBF_OptionsDriverScriptEngine( const CVBF_Options& options =CVBF_Options() ) : 
    CVBF_OptionsDriver( options ) { fromConfig(m_conf); }

	virtual ~CVBF_OptionsDriverScriptEngine() { }

public: // properties

    /** optional script source */
    CVBF_Optional<Script>& script() { return _script; }
    const CVBF_Optional<Script>& script() const { return _script; }

public:
    virtual CVBF_Config getConfig() const;

protected:
    virtual void mergeConfig( const CVBF_Config& conf );
      
private:
    void fromConfig( const CVBF_Config& conf );

    CVBF_Optional<Script> _script;
};

//--------------------------------------------------------------------

class OSGEARTHFEATURES_EXPORT CVBFO_ScriptEngine : public osg::CVBF_Object
{
public:
	CVBFO_ScriptEngine(const CVBF_OptionsDriverScriptEngine& options =CVBF_OptionsDriverScriptEngine()) : _script(options.script()) {}

	virtual ~CVBFO_ScriptEngine() { }

	virtual bool supported(std::string lang) =0;
	virtual bool supported(Script* script) =0;

	virtual ScriptResult run(Script* script, Feature const* feature=0L, FilterContext const* context=0L) =0;
	virtual ScriptResult run(const std::string& code, Feature const* feature=0L, FilterContext const* context=0L) =0;

	virtual ScriptResult call(const std::string& function, Feature const* feature=0L, FilterContext const* context=0L) =0;

public:
	// META_Object specialization:
	virtual osg::CVBF_Object* cloneType() const { return 0; } // cloneType() not appropriate
	virtual osg::CVBF_Object* clone(const osg::CopyOp&) const { return 0; } // clone() not appropriate
	virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const CVBFO_ScriptEngine*>(obj)!=NULL; }
	virtual const char* className() const { return "CVBFO_ScriptEngine"; }
	virtual const char* libraryName() const { return "osgEarth::Features"; }

protected:
	CVBF_Optional<Script>  _script;
};

typedef std::list< ref_ptr<CVBFO_ScriptEngine> > ScriptEngineList;
typedef std::map<std::string, ref_ptr<CVBFO_ScriptEngine> > ScriptEngineMap;

//--------------------------------------------------------------------

class OSGEARTHFEATURES_EXPORT CVBFO_DriverScriptEngine : public osgDB::ReaderWriter
{
protected:
	const CVBF_OptionsDriverScriptEngine& getScriptEngineOptions( const osgDB::ReaderWriter::Options* rwOpt ) const;
    virtual const char* className() const;
};

//--------------------------------------------------------------------

class OSGEARTHFEATURES_EXPORT ScriptEngineFactory
{   
public:
	static CVBFO_ScriptEngine* create( const std::string& language, const std::string& engineName="" );
	static CVBFO_ScriptEngine* create( const Script& script, const std::string& engineName="" );
	static CVBFO_ScriptEngine* create( const CVBF_OptionsDriverScriptEngine& options );
};

#endif // OSGEARTH_FEATURES_SCRIPTENGINE_H
