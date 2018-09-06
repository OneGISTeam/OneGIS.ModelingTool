#include "C_ViewWidgetTimeAxis.h"
#include "qcustomplot.h"
#include "VBF_Common/VBF_Math/VBF_TimeConverter.h"

C_ViewWidgetTimeAxis::C_ViewWidgetTimeAxis(QWidget *parent)
	: IC_ViewWidget(parent)
{
	setupUi(this);

	//���������ÿ�
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

	//����Y��
	customPlot->yAxis->setTickLabels(false);
	customPlot->yAxis->setVisible(false);
	customPlot->xAxis2->setVisible(false);

	//��ȡ����ʱ��
	m_pISimulationTimer = VBF_GetSimulationTimer();

	// ���¼�Ԫ
	double dEpochUTC = CVF_TimeConverter::convertDTtoJD(2012, 3, 25, 6, 43, 22.702);
	//���÷���ʱ��
	m_pISimulationTimer->SetDDayTimeBegin(dEpochUTC);
	m_pISimulationTimer->Start();
	m_pISimulationTimer->Stop();
	m_pISimulationTimer->SetSimulateTimeRatio(1000);
	//������ʼʱ��
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
	connect(&mDataTimer,SIGNAL(timeout()),this,SLOT(on_TimerEvent()));//���ö�ʱ��
	isStarted = false;
	isTimePointFiexd = false;
	speed = 1.0;
}

void C_ViewWidgetTimeAxis::init()
{
	//ʱ����ĳ�ʼ������
	this->setWindowTitle(tr("ʱ����"));
	//����QCustomPlot ������뵽framePlot��

	//����Y��
	customPlot->yAxis->setVisible(false);
	customPlot->xAxis2->setVisible(false);

	//������ķ�Χ
	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime());
	dateTicker->setDateTimeFormat("hh::mm::ss\nyyyy.MM.dd");
	customPlot->xAxis->setTicker(dateTicker);
	customPlot->xAxis->setRange(startTime,endTime);
	customPlot->yAxis->setRange(0,1);

	//����ʱ�����᳤��
	customPlot->xAxis->setTickLengthIn(this->height());
	customPlot->xAxis->setTickLabelColor(Qt::yellow);
	customPlot->xAxis->setSubTickLengthIn(this->height());
	customPlot->xAxis->setSubTicks(false);

	//�رձ�������
	customPlot->xAxis->grid()->setVisible(false);

	//����QcustomPlot�Դ�������������ק
	customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

	//������߾�
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

	//������ʱʱ��ָ��Ļ�����ʽ
	QPen tempTimePointPen(Qt::yellow,2,Qt::DashLine);
	timeTempPointGraph->setLineStyle(QCPGraph::lsLine);
	timeTempPointGraph->setPen(tempTimePointPen);

	//������ʱʱ��ָ���������ʾ��ʽ
	tempTimeTip = new QCPItemText(customPlot);
	tempTimeTip->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
	tempTimeTip->position->setType(QCPItemPosition::ptAbsolute);
	QFont font;
	font.setPixelSize(25);
	tempTimeTip->setFont(font);
	tempTimeTip->setColor(Qt::yellow);

	//����ʱ��ָ�������ɫ
	timePointGraph->setPen(drawPen);
	timePointGraph->setBrush(QBrush(QColor(0,255,240,60)));
	timePointGraph->setLineStyle(QCPGraph::lsLine);
	timePointGraph_aux->setPen(drawPen);
	timePointGraph->setChannelFillGraph(timePointGraph_aux);

	//���ö����������������ɫ����ɫֵ��������õ�
	QPen pen;
	pen.setColor(QColor(0,255,255,200));
	timeSectionsGraph->setLineStyle(QCPGraph::lsLine);
	timeSectionsGraph->setBrush(QBrush(QColor(60,160,50,150)));
	timeSectionsGraph->setPen(pen);

	drawBackground();    //���Ʊ�����ɫ
	drawTimePoint();     //����ʱ��ָ��
	drawTempTimePoint(); //����������ʱʱ��ָ��,��ʱ����ƶ�ʱ�������������λ��
	drawTimeSections();  //����ʱ�������
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
	//˫����꣬ʵ��ʱ��ָ�����ת
	int x_pos = event->x();
	double x_val = customPlot->xAxis->pixelToCoord(x_pos);
	currentTime = x_val;
	drawTimePoint();
}

void C_ViewWidgetTimeAxis::mouseMove( QMouseEvent* event )
{
	//mouseMove ��Ҫ����������ƶ�ʱ������������ڵ�λ��������
	//�����´���ע�ʹ򿪼���
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
	//�����ѡԼ��ʱ��ָ�룬��ʱ��ָ���Լ�ʱ����̶��޷��϶�,�����ʼ�������Ὺʼ�����ƶ���ָ�벻��
	//�ر�ģ������ʱ��ָ���ߵĿ������ˣ���ѡ��ָ��ָ���ʱ��̶ȵ��м�λ��
	if(isTimePointFiexd)
	{
		QCPRange currentRange = customPlot->xAxis->range();
		customPlot->xAxis->setRange(currentTime,currentRange.size(),Qt::AlignCenter);
	}
	showbCurrentTime();
}

void C_ViewWidgetTimeAxis::on_playBtn_clicked()
{
	//�����ʼ���ٵ����ͣ
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
	//�����ֱ�ӽ�ʱ��Ӵ������
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

		//����QcustomPlot�Դ�������������ק
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
	//����vector���������ȡ2��ֵ���в���
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
	//����һ����ֱֱ��,���Ƴ�һ����������,�����ǵĿ��Ϊ�������ȵ�1/20��
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
	//������ʱʱ��ָ��
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
	//�ڸú����м��㵱ǰ��ʱ��ֵ��ʱ��ָ����ָ���ֵ
	QString timeDisplay = QDateTime::fromTime_t(currentTime).toString("yyyy-MM-dd hh:mm:ss");
	currentTimeLabel->setText(tr("��ǰʱ��:")+timeDisplay);
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
	//���Ƶ���ʱʱ��ָ��
	timeTempPointGraph->setVisible(isVisible);
}


