//***************************************************************************************
// FileName：VBF_LabelControl.h
// Function：对LabelNode进行的扩展，使其支持中文
// Author:   
// Date:     2012-04-23
//***************************************************************************************

#ifndef __VBF_LABEL_CONTROL_H__
#define __VBF_LABEL_CONTROL_H__

#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_3DMap/VBF_EarthUtil/Controls>


using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Util::Controls;


class VBF_MAPAUX_EXPORT CVBF_LabelControl : public Control
{
public:
	//CVBF_LabelControl(const std::string& value    ="",
	//	float fontSize              =18.0f,
	//	const osg::Vec4f& foreColor =osg::Vec4f(1,1,1,1) );
	
	CVBF_LabelControl( const char[]    ="",
		float fontSize              =18.0f,
		const osg::Vec4f& foreColor =osg::Vec4f(1,1,1,1) );

	//CVBF_LabelControl(const std::string& value,const osg::Vec4f&  foreColor );

	void setText(const char* szText);
	const char* text() const { return _text; }

	void setEncoding( osgText::String::Encoding value );
	const osgText::String::Encoding& encoding() const { return _encoding; }

	void setFont( osgText::Font* font );
	osgText::Font* font() const { return _font.get(); }

	void setFontSize( float value );
	float fontSize() const { return _fontSize; }

	void setHaloColor( const osg::Vec4f& value );
	const CVBF_Optional<osg::Vec4f>& haloColor() const { return _haloColor; }

	

public: // Control
	virtual void calcSize( const ControlContext& context, osg::Vec2f& out_size );
	//virtual void calcPos ( const ControlContext& context, const osg::Vec2f& cursor, const osg::Vec2f& parentSize );
	virtual void draw    ( const ControlContext& context, DrawableList& out_drawables );

protected:
	virtual bool handle( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa, ControlContext& cx );

private:
	//std::string _text;
	char _text[128];
	ref_ptr<osgText::Font> _font;
	float _fontSize;
	ref_ptr<osgText::Text> _drawable;
	osg::Vec3 _bmin, _bmax;
	CVBF_Optional<osg::Vec4f> _haloColor;
	osgText::String::Encoding _encoding;
};

#endif
