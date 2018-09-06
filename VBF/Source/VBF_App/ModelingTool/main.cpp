#include "MainWindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include <QPixmap>
#include <QSettings>
#include "qgsproviderregistry.h"
#include "qgsapplication.h"

#include "VBF_Base/IVBF_System.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTextCodec *codec = QTextCodec::codecForName("system");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);

	QSplashScreen* pSpashScreen = new QSplashScreen;
	pSpashScreen->setPixmap(QPixmap(":/ModelingTool/Images/splashscreen.jpg"));
	pSpashScreen->show();
	a.processEvents();

	QString configpath = QgsApplication::qgisSettingsDirPath();
	QString optionpath;
	if ( !optionpath.isEmpty() || !configpath.isEmpty() )
	{
		// tell QSettings to use INI format and save the file in custom config path
		QSettings::setDefaultFormat( QSettings::IniFormat );
		QSettings::setPath( QSettings::IniFormat, QSettings::UserScope, optionpath.isEmpty() ? configpath : optionpath );
	}
	configpath = QCoreApplication::applicationDirPath();

	QString libPath = configpath + "/2dmap_plugins";
	a.addLibraryPath(libPath);

	QString sCorePath = QCoreApplication::applicationDirPath(); //当前程序运行的路径
	QDir dir(sCorePath);
	dir.cdUp(); //向上一级到bin
	dir.cdUp(); //向上一级到OneGIS

#ifdef _DEBUG
	QString filePath = dir.path() + "/bin/Debug/2dmap_plugins";
#else
	QString filePath = dir.path() + "/bin/Release/2dmap_plugins";
#endif

	QgsProviderRegistry::instance(filePath);

	MainWindow w(pSpashScreen);
	w.showMaximized();

	pSpashScreen->finish(&w);
	delete pSpashScreen;

	return a.exec();
}
