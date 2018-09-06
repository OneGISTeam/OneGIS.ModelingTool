
// QGSCONFIG.H

#ifndef QGSCONFIG_H
#define QGSCONFIG_H

// Version must be specified according to
// <int>.<int>.<int>-<any text>.
// or else upgrading old project file will not work
// reliably.
#define VERSION "2.0.1-Dufour"

//used in vim src/core/qgis.cpp
//The way below should work but it resolves to a number like 0110 which the compiler treats as octal I think
//because debuggin it out shows the decimal number 72 which results in incorrect version status.
//As a short term fix I (Tim) am defining the version in top level cmake. It would be good to 
//reinstate this more generic approach below at some point though
//#define VERSION_INT 201
#define VERSION_INT 20001
#define ABISYM(x) x ## 20001
//used in main.cpp and anywhere else where the release name is needed
#define RELEASE_NAME "Dufour"

#define QGIS_PLUGIN_SUBDIR "plugins"
#define QGIS_DATA_SUBDIR "."
#define QGIS_LIBEXEC_SUBDIR "."
#define QGIS_LIB_SUBDIR "lib"
#define CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/qgis2.0.1"
#define CMAKE_SOURCE_DIR "D:/Qt Workspace/qgis-2.0.1-src"

#define QSCINTILLA_VERSION_STR "2.8.4"
//used by Mac to find system Qt plugins when bundle is run from build directory
#define QTPLUGINSDIR "D:/Qt/4.8.6/plugins"

/* #undef USING_NMAKE */

/* #undef HAVE_POSTGRESQL */

#define HAVE_SPATIALITE

#define HAVE_MSSQL

/* #undef HAVE_ORACLE */

/* #undef HAVE_PYTHON */

/* #undef HAVE_TOUCH */

/* #undef HAVE_OSGEARTHQT */

/* #undef MAPSERVER_SKIP_ECW */

#endif

