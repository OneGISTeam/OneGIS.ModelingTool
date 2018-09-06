#ifndef C_VIEWWIDGETTIMEAXIS_H
#define C_VIEWWIDGETTIMEAXIS_H

#include <QDockWidget>
#include "ui_timeAxisViewWidget.h"
#include "IC_ViewWidget.h"
#include "qcustomplot.h"
#include "VBF_Base/IVBF_SimulationTimer.h"

typedef struct TimeSection{
	TimeSection(){}
	TimeSection(time_t t1,time_t t2):Obj_StartTime(t1),Obj_EndTime(t2){}
	time_t Obj_StartTime;
	time_t Obj_EndTime;
}TimeSection;

class C_ViewWidgetTimeAxis : public IC_ViewWidget, public Ui::ViewWidgetTimeAxis
{
	Q_OBJECT

public:
	C_ViewWidgetTimeAxis(QWidget *parent = 0);
	~C_ViewWidgetTimeAxis();

	virtual QString name();
	virtual void init();

public:
	/// @brief 设置时间轴的开始时间
	void setStartTime(double startTime);

	/// @brief 设置时间轴的结束时间,如果设置为负值（如-1），则结束时间为无穷
	void setEndTime(double endTime);

	/// @brief 设置当前时间,当前时间和开始时间、结束时间不同
	void setCurrentTime(double time);

	/// @brief 得到当前时间
	double getCurrentTime();

	/// @brief 设置播放速率
	void setSpeed(double speed);

	/// @brief 得到播放速率
	double getSpeed();

	/// @brief 得到对象的生命周期区间集合
	QVector<TimeSection> getTimeSections();

	/// @brief 设置对象的生命周期区间集合
	void setTimeSections(QVector<TimeSection> t);

	/// @brief 设置时间指针是否固定,true-固定,false-不固定
	void setTimePointFixed(bool isFiexed);

	/// @brief 得到时间指针是否固定
	bool isTimePointFixed();

private slots:
	//时间响应事件
	void on_TimerEvent();

	//鼠标的响应事件
	void mousePress(QMouseEvent *event);
	void mouseWheel(QWheelEvent *event);
	void mouseDoubleClick(QMouseEvent *event);
	void mouseMove(QMouseEvent*);
	void leaveEvent(QEvent *);
	void enterEvent(QEvent *);

	//按钮响应事件
	void on_playBtn_clicked();
	void on_speedUpBtn_clicked() ;
	void on_speedDownBtn_clicked();
	void on_forwardBtn_clicked() ;
	void on_backwardBtn_clicked();
	void on_resetBtn_clicked();

	//checkBox响应事件
	void On_timePointCheckBox_stateChanged(int state);

private:
	/// @brief 绘制图形的背景色
	void drawBackground();
	/// @brief 绘制所有对象的生命周期区间
	void drawTimeSections();
	/// @brief 绘制时间指针
	void drawTimePoint();
	/// @brief 绘制临时时间指针的提示
	/// @param p 坐标位置
	void drawTempTimeTip(QPoint p,time_t t);
	/// @brief 绘制临时时间指针
	void drawTempTimePoint();
	/// @brief 设置隐藏或显示临时时间指针
	void setTempTimePointVisible(bool isVisible);
	/// @brief 显示当前时间值
	void showbCurrentTime(); 

private:
	QCPGraph* timePointGraph;                 //记录时间指针的图形
	QCPGraph* timeSectionsGraph;              //记录对象生命周期区间的图形
	QCPGraph* timeTempPointGraph;             //记录鼠标移动的临时时间指针
	QCPItemText* tempTimeTip; //记录鼠标移动时的临时时间提示（在竖线的旁边显示时间提示）
	QVector<double> xLineVector,yLineVector;   //记录时间指针的值
	QVector<double> xLineVector2,yLineVector2; //记录临时时间的值

	//用于记录时间指针的辅助图形，用aux命名
	//由于想将时间指针绘制成为一个倒三角，需要有
	//一个直线作为时间指针的ChannelFillGraph
	QVector<double> xLineVector_aux,yLineVector_aux;
	QCPGraph* timePointGraph_aux;

private:
	IVBF_SimulationTimer* m_pISimulationTimer; //仿真时钟
	double currentTime;       //记录当前时间
	double tempTime;          //记录鼠标移动时的临时时间
	double startTime;         //记录时间轴的开始时间
	double endTime;           //记录时间轴的结束时间
	bool isStarted;           //判断是否已经在运行；
	bool isTimePointFiexd;    //判断时间指针是否固定
	double speed;             //播放速率
	QVector<TimeSection> timeSections;   //记录所有对象的生命周期区间，主演用于绘制
	QTimer mDataTimer;        //计时器

private:
	QCustomPlot* customPlot;
};

#endif // C_VIEWWIDGETTIMEAXIS_H
