#include "C_2DWnd.h"
#include <QIcon>
#include "qgsvectorlayer.h"
#include "qgsmaplayerregistry.h"
#include "qgsmaptoolpan.h"

C_2DWnd::C_2DWnd(QWidget* pParent)
	:IC_Wnd(pParent)
{
	m_pMapCanvas = new QgsMapCanvas(this, UI_WND_2D.toStdString().c_str());

	QSettings settings;
	int iRed = settings.value( "/qgis/default_canvas_color_red", 255 ).toInt();
	int iGreen = settings.value( "/qgis/default_canvas_color_green", 255 ).toInt();
	int iBlue = settings.value( "/qgis/default_canvas_color_blue", 255 ).toInt();
	m_pMapCanvas->setCanvasColor(QColor( iRed, iGreen, iBlue ));
	m_pMapCanvas->setFocus();
	m_pMapCanvas->freeze(false);
	
	setWidget(m_pMapCanvas);
}


C_2DWnd::~C_2DWnd(void)
{
}

QString C_2DWnd::name()
{
	return UI_WND_2D;
}

void C_2DWnd::init()
{
	this->setWindowTitle(tr("2D显示窗口"));
	setWindowIcon(QIcon(":/ModelingTool/Images/2DMap.png"));

	load2DMaps();

	m_p2DStatusWidget = new C_2DCoordinateWidget;
}

bool C_2DWnd::load2DMaps()
{
	QString sCorePath = QCoreApplication::applicationDirPath(); //当前程序运行的路径
	QDir dir(sCorePath);
	dir.cdUp();
	dir.cdUp();
	dir.cdUp();
	
	QString vectorDataPath = dir.path() + "/VBF_DATA/vector/" + "Countries.shp"; 
	
	QFileInfo fileInfo(vectorDataPath);
	QgsVectorLayer* pVectorLayer = new QgsVectorLayer(vectorDataPath, fileInfo.baseName(), "ogr");
	if(pVectorLayer->isValid()){
		QgsMapLayerRegistry::instance()->addMapLayer(pVectorLayer);
		QgsMapToolPan* pPan = new QgsMapToolPan(m_pMapCanvas);

		QList<QgsMapCanvasLayer> layers;

		QgsMapCanvasLayer canvasLayer(pVectorLayer);
		layers.push_back(canvasLayer);
		m_pMapCanvas->setMapTool(pPan);
		m_pMapCanvas->setLayerSet(layers);	
		m_pMapCanvas->setVisible(true);
		m_pMapCanvas->zoomToFullExtent();
		//m_pMapCanvas->refresh();

		return true;
	}else
		return false;
	
	return true;
}
