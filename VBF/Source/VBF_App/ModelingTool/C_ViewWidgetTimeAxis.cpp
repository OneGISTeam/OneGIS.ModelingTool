#include "C_ViewWidgetTimeAxis.h"
#include "qcustomplot.h"
#include "VBF_Common/VBF_Math/VBF_TimeConverter.h"

C_ViewWidgetTimeAxis::C_ViewWidgetTimeAxis(QWidget *parent)
	: IC_ViewWidget(parent)
{
	setupUi(this);

	//将标题栏置空
	QWidget* pNullTitleWidget = new QWidget(this);
	this->setTitleBarWidget(pNullTitleWidget);

	customPlot = new QCustomPlot;
	customPlot->setObjectName("customPlot");

	QSizePolicy sizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
	customPlot->setSizePolicy(sizePolicy);
	framePlotLayout->addWidget(customPlot);

	connect(toolButton_reset, SIGNAL(clicked()), this, SLOT(on_resetBtn_clicked()));
	connect(toolButton_play,SIGNAL(clicked()),this,SLOT(on_playBtn_clicked()));
	connect(toolButton_speedUp,SIGNAL(clicked()),this,SLOT(on_speedUpBtn_clicked()));
	connect(toolButton_speedDown,SIGNAL(clicked()),this,SLOT(on_speedDownBtn_clicked()));
	connect(toolButton_forward,SIGNAL(clicked()),this,SLOT(on_forwardBtn_clicked()));
	connect(toolButton_backward,SIGNAL(clicked()),this,SLOT(on_backwardBtn_clicked()));
	connect(cbFixTimePoint,SIGNAL(stateChanged(int)),this,SLOT(On_timePointCheckBox_stateChanged(int)));

	//隐藏Y轴
	customPlot->yAxis->setTickLabels(false);
	customPlot->yAxis->setVisible(false);
	customPlot->xAxis2->setVisible(false);

	//获取仿真时钟
	m_pISimulationTimer = VBF_GetSimulationTimer();

	// 更新纪元
	double dEpochUTC = CVF_TimeConverter::convertDTtoJD(2012, 3, 25, 6, 43, 22.702);
	//设置仿真时钟
	m_pISimulationTimer->SetDDayTimeBegin(dEpochUTC);
	m_pISimulationTimer->Start();
	m_pISimulationTimer->Stop();
	m_pISimulationTimer->SetSimulateTimeRatio(1000);
	//设置起始时间
	int iYear, iMonth, iDay, iHour, iMinute;
	double dSecond;
	CVF_TimeConverter::convertJDtoDT(m_pISimulationTimer->GetDDayTimeBegin(),iYear, iMonth, iDay, iHour, iMinute, dSecond);
	startTime = QDateTime(QDate(iYear, iMonth, iDay), QTime(iHour, iMinute, (int)dSecond, dSecond - (int)dSecond)).toTime_t();
	
	//startTime = QDateTime::fromString("2018-07-01 11:00:30","yyyy-MM-dd hh:mm:ss").toTime_t();
	endTime = QDateTime::fromString("2018-07-01 11:10:30","yyyy-MM-dd hh:mm:ss").toTime_t();
	currentTime = startTime;
	timeSections<<TimeSection(startTime+100,startTime+200);
	timeSections<<TimeSection(startTime+240,startTime+300);
	currentTime= startTime;
	connect(&mDataTimer,SIGNAL(timeout()),this,SLOT(on_TimerEvent()));//设置定时器
	isStarted = false;
	isTimePointFiexd = false;
	speed = 1.0;
}

void C_ViewWidgetTimeAxis::init()
{
	//时间轴的初始化工作
	this->setWindowTitle(tr("时间轴"));
	//构造QCustomPlot 将其插入到framePlot中

	//隐藏Y轴
	customPlot->yAxis->setVisible(false);
	customPlot->xAxis2->setVisible(false);

	//设置轴的范围
	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime());
	dateTicker->setDateTimeFormat("hh::mm::ss\nyyyy.MM.dd");
	customPlot->xAxis->setTicker(dateTicker);
	customPlot->xAxis->setRange(startTime,endTime);
	customPlot->yAxis->setRange(0,1);

	//设置时间纵轴长度
	customPlot->xAxis->setTickLengthIn(this->height());
	customPlot->xAxis->setTickLabelColor(Qt::yellow);
	customPlot->xAxis->setSubTickLengthIn(this->height());
	customPlot->xAxis->setSubTicks(false);

	//关闭背景格网
	customPlot->xAxis->grid()->setVisible(false);

	//启用QcustomPlot自带的轴缩放与拖拽
	customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

	//设置外边距
	customPlot->setContentsMargins(1,1,1,1);

	connect(customPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mousePress(QMouseEvent*)));
	connect(customPlot,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(mouseWheel(QWheelEvent*)));
	connect(customPlot,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(mouseDoubleClick(QMouseEvent*)));
	connect(customPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(mouseMove(QMouseEvent*)));
	connect(customPlot,SIGNAL(leaveEvent(QEvent*)),this,SLOT(leaveEvent(QEvent*)));
	connect(customPlot,SIGNAL(enterEvent(QEvent*)),this,SLOT(enterEvent(QEvent*)));

	timePointGraph = customPlot->addGraph();
	timeSectionsGraph = customPlot->addGraph();
	timeTempPointGraph = customPlot->addGraph();
	timePointGraph_aux = customPlot->addGraph();

	QPen drawPen;
	drawPen.setColor(Qt::yellow);
	drawPen.setWidth(1);

	//设置临时时间指针的绘制样式
	QPen tempTimePointPen(Qt::yellow,2,Qt::DashLine);
	timeTempPointGraph->setLineStyle(QCPGraph::lsLine);
	timeTempPointGraph->setPen(tempTimePointPen);

	//设置临时时间指针的文字提示样式
	tempTimeTip = new QCPItemText(customPlot);
	tempTimeTip->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
	tempTimeTip->position->setType(QCPItemPosition::ptAbsolute);
	QFont font;
	font.setPixelSize(25);
	tempTimeTip->setFont(font);
	tempTimeTip->setColor(Qt::yellow);

	//设置时间指针绘制颜色
	timePointGraph->setPen(drawPen);
	timePointGraph->setBrush(QBrush(QColor(0,255,240,60)));
	timePointGraph->setLineStyle(QCPGraph::lsLine);
	timePointGraph_aux->setPen(drawPen);
	timePointGraph->setChannelFillGraph(timePointGraph_aux);

	//设置对象生命区间绘制颜色，颜色值是随便设置的
	QPen pen;
	pen.setColor(QColor(0,255,255,200));
	timeSectionsGraph->setLineStyle(QCPGraph::lsLine);
	timeSectionsGraph->setBrush(QBrush(QColor(60,160,50,150)));
	timeSectionsGraph->setPen(pen);

	drawBackground();    //绘制背景颜色
	drawTimePoint();     //绘制时间指针
	drawTempTimePoint(); //绘制鼠标的临时时间指针,当时鼠标移动时，绘制鼠标的鼠标位置
	drawTimeSections();  //绘制时间区间段
}

C_ViewWidgetTimeAxis::~C_ViewWidgetTimeAxis()
{

}

QString C_ViewWidgetTimeAxis::name()
{
	return UI_VIEWWIDGET_TIMEAXIS;
}


void C_ViewWidgetTimeAxis::mousePress( QMouseEvent *event )
{
	customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
}


void C_ViewWidgetTimeAxis::mouseWheel( QWheelEvent *event )
{
	customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
	drawTimePoint();
}
void C_ViewWidgetTimeAxis::mouseDoubleClick( QMouseEvent *event )
{
	//双击鼠标，实现时间指针的跳转
	int x_pos = event->x();
	double x_val = customPlot->xAxis->pixelToCoord(x_pos);
	currentTime = x_val;
	drawTimePoint();
}

void C_ViewWidgetTimeAxis::mouseMove( QMouseEvent* event )
{
	//mouseMove 主要作用是鼠标移动时，绘制鼠标所在的位置线条，
	//将以下代码注释打开即可
	if(!customPlot->viewport().contains(event->pos()))
	{
		timeTempPointGraph->setVisible(false);
		return;
	}

	    int x_pos = event->x();
	    double x_val = customPlot->xAxis->pixelToCoord(x_pos);
	    tempTime = x_val;
	    timeTempPointGraph->setVisible(true);
	    drawTempTimePoint();
		//height set 1/3
		drawTempTimeTip( QPoint(x_pos,this->rect().height()/3),x_val);

}
void C_ViewWidgetTimeAxis::leaveEvent( QEvent * )
{
	timeTempPointGraph->setVisible(false);
	customPlot->replot();
}

void C_ViewWidgetTimeAxis::enterEvent( QEvent * )
{
	timeTempPointGraph->setVisible(true);
	customPlot->replot();
}


void C_ViewWidgetTimeAxis::on_TimerEvent()
{
	
	int iYear, iMonth, iDay, iHour, iMinute;
	double dSecond;
	CVF_TimeConverter::convertJDtoDT(m_pISimulationTimer->GetDDayTimeCurrent(),iYear, iMonth, iDay, iHour, iMinute, dSecond);
	currentTime = QDateTime(QDate(iYear, iMonth, iDay), QTime(iHour, iMinute, (int)dSecond, dSecond - (int)dSecond)).toTime_t();
	
	//currentTime +=1*speed;
	drawTimePoint();
	//如果勾选约束时间指针，则时间指针以及时间轴刻度无法拖动,点击开始后，坐标轴开始向左移动，指针不动
	//特别的，如果在时间指针走的看不见了，勾选后，指针恢复到时间刻度的中间位置
	if(isTimePointFiexd)
	{
		QCPRange currentRange = customPlot->xAxis->range();
		customPlot->xAxis->setRange(currentTime,currentRange.size(),Qt::AlignCenter);
	}
	showbCurrentTime();
}

void C_ViewWidgetTimeAxis::on_playBtn_clicked()
{
	//点击开始，再点击暂停
	if(!m_pISimulationTimer->IsPause())
	{
		m_pISimulationTimer->Pause();
		toolButton_play->setIcon(QIcon(":/ModelingTool/Images/play.png"));
		mDataTimer.stop();
	}	
	else{
		if(isStarted){
			m_pISimulationTimer->Continue();
		}else{
			m_pISimulationTimer->Start();
			isStarted = true;
		}
		m_pISimulationTimer->Continue();
		toolButton_play->setIcon(QIcon(":/ModelingTool/Images/pause.png"));
		mDataTimer.start(10);
	}
}

void C_ViewWidgetTimeAxis::on_speedUpBtn_clicked()
{
	//快进，直接将时间加大就行了
	//curTime+=10;
	m_pISimulationTimer->SetSimulateTimeRatio(m_pISimulationTimer->GetSimulateTimeRatio()*2.0);
}

void C_ViewWidgetTimeAxis::on_speedDownBtn_clicked()
{
	 //curTime-=10;
	m_pISimulationTimer->SetSimulateTimeRatio(m_pISimulationTimer->GetSimulateTimeRatio()/2.0);
}

void C_ViewWidgetTimeAxis::on_forwardBtn_clicked()
{
	int delta = 2;
	m_pISimulationTimer->SetSimulateTimeCurrent(m_pISimulationTimer->GetSimulateTimeCurrent() + delta);
}

void C_ViewWidgetTimeAxis::on_backwardBtn_clicked()
{
	int delta = 2;
	m_pISimulationTimer->SetSimulateTimeCurrent(m_pISimulationTimer->GetSimulateTimeCurrent() - delta);
}

void C_ViewWidgetTimeAxis::on_resetBtn_clicked()
{
	if(m_pISimulationTimer->IsPause()){
		m_pISimulationTimer->Start();
		m_pISimulationTimer->Stop();
	}else{
		m_pISimulationTimer->Start();
	}
}

void C_ViewWidgetTimeAxis::setStartTime( double startTime )
{
	 this->startTime = startTime;
}

void C_ViewWidgetTimeAxis::setEndTime( double endTime )
{
	endTime = endTime;
}

void C_ViewWidgetTimeAxis::setCurrentTime( double time )
{
	currentTime = time;
}

double C_ViewWidgetTimeAxis::getCurrentTime()
{
	return currentTime;
}

void C_ViewWidgetTimeAxis::setSpeed( double speed )
{
	this->speed = speed;
}

double C_ViewWidgetTimeAxis::getSpeed()
{
	return speed;
}

QVector<TimeSection> C_ViewWidgetTimeAxis::getTimeSections()
{
	return timeSections;
}

void C_ViewWidgetTimeAxis::setTimeSections( QVector<TimeSection> t )
{
	timeSections = t;
}

void C_ViewWidgetTimeAxis::setTimePointFixed( bool isFiexed )
{
	isTimePointFiexd = isFiexed;
	if(isTimePointFiexd)
	{
		//clos drag
		customPlot->setInteractions(0);
		//set tempTimePoint hide
		setTempTimePointVisible(false);
		disconnect(this,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(mouseWheel(QWheelEvent*)));
		disconnect(this,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(mouseDoubleClick(QMouseEvent*)));
		disconnect(this,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(mouseMove(QMouseEvent*)));
	}
	else
	{

		//启用QcustomPlot自带的轴缩放与拖拽
		customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
		setTempTimePointVisible(true);
		connect(this,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(mouseWheel(QWheelEvent*)));
		connect(this,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(mouseDoubleClick(QMouseEvent*)));
		connect(this,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(mouseMove(QMouseEvent*)));
	}
}

bool C_ViewWidgetTimeAxis::isTimePointFixed()
{
	return isTimePointFiexd;
}

void C_ViewWidgetTimeAxis::drawBackground()
{
	QLinearGradient gradient(0,0,0,400);
	gradient.setColorAt(0,QColor(90,90,90));
	gradient.setColorAt(0.38,QColor(100,100,100));
	gradient.setColorAt(1,QColor(70,70,70));
	customPlot->setBackground(QBrush(gradient));
	customPlot->replot();
}

void C_ViewWidgetTimeAxis::drawTimeSections()
{
	//遍历vector，在这里就取2个值进行测试
	QVector<QCPGraphData> timeData(2);
	timeData[0].key = timeSections[0].Obj_StartTime;
	timeData[0].value = 1;
	timeData[1].key = timeSections[0].Obj_EndTime;
	timeData[1].value = 1;
	timeSectionsGraph->data()->set(timeData);
	customPlot->replot();
}

void C_ViewWidgetTimeAxis::drawTimePoint()
{
	//绘制一个竖直直线,绘制成一个倒三角形,到三角的宽度为整个轴宽度的1/20，
	double triangleWidth = customPlot->xAxis->range().size()/100.0;
	xLineVector.clear();
	yLineVector.clear();
	xLineVector<<currentTime-triangleWidth<<currentTime<<currentTime+triangleWidth;
	yLineVector<<1<<0<<1;

	xLineVector_aux.clear();
	yLineVector_aux.clear();
	xLineVector_aux<<currentTime-triangleWidth<<currentTime+triangleWidth;
	yLineVector_aux<<1<<1;
	timePointGraph->setData(xLineVector,yLineVector);
	timePointGraph_aux->setData(xLineVector_aux,yLineVector_aux);
	customPlot->replot();
}

void C_ViewWidgetTimeAxis::drawTempTimePoint()
{
	//绘制临时时间指针
	xLineVector2.clear();
	yLineVector2.clear();
	xLineVector2<<tempTime<<tempTime;
	yLineVector2<<0<<1;
	timeTempPointGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,2));
	timeTempPointGraph->setData(xLineVector2,yLineVector2);
	customPlot->replot();
}

void C_ViewWidgetTimeAxis::showbCurrentTime()
{
	//在该函数中计算当前的时间值，时间指针所指向的值
	QString timeDisplay = QDateTime::fromTime_t(currentTime).toString("yyyy-MM-dd hh:mm:ss");
	currentTimeLabel->setText(tr("当前时间:")+timeDisplay);
}

void C_ViewWidgetTimeAxis::On_timePointCheckBox_stateChanged( int state )
{
	if(state==Qt::Checked) setTimePointFixed(true);
	else                   setTimePointFixed(false);
}

void C_ViewWidgetTimeAxis::drawTempTimeTip( QPoint p,time_t t )
{
	tempTimeTip->setText(QDateTime::fromTime_t(t).toString("hh::mm::ss\nyyyy.MM.dd"));
	tempTimeTip->position->setCoords(p.x()+3*tempTimeTip->font().pixelSize(),p.y());
	customPlot->replot();
}

void C_ViewWidgetTimeAxis::setTempTimePointVisible( bool isVisible )
{
	//绘制的临时时间指针
	timeTempPointGraph->setVisible(isVisible);
}


