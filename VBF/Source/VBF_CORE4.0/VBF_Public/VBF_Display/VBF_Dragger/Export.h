#ifndef OSGMANIPULATOR_EXPORT_
#define OSGMANIPULATOR_EXPORT_ 1

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
    #  if defined( OSG_LIBRARY_STATIC )
    #    define OSGMANIPULATOR_EXPORT
    #  elif defined( OSGMANIPULATOR_LIBRARY )
    #    define OSGMANIPULATOR_EXPORT   __declspec(dllexport)
    #  else
    #    define OSGMANIPULATOR_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define OSGMANIPULATOR_EXPORT
#endif

#define META_OSGMANIPULATOR_Object(library,name) \
virtual osg::CVBF_Object* cloneType() const { return new name (); } \
virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
virtual const char* libraryName() const { return #library; }\
virtual const char* className() const { return #name; }


/**

\namespace osgManipulator

The osgManipulator library is a NodeKit that extends the core scene graph to support 3D interactive manipulators.
*/

#endif
