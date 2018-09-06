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
	/// @brief ����ʱ����Ŀ�ʼʱ��
	void setStartTime(double startTime);

	/// @brief ����ʱ����Ľ���ʱ��,�������Ϊ��ֵ����-1���������ʱ��Ϊ����
	void setEndTime(double endTime);

	/// @brief ���õ�ǰʱ��,��ǰʱ��Ϳ�ʼʱ�䡢����ʱ�䲻ͬ
	void setCurrentTime(double time);

	/// @brief �õ���ǰʱ��
	double getCurrentTime();

	/// @brief ���ò�������
	void setSpeed(double speed);

	/// @brief �õ���������
	double getSpeed();

	/// @brief �õ�����������������伯��
	QVector<TimeSection> getTimeSections();

	/// @brief ���ö���������������伯��
	void setTimeSections(QVector<TimeSection> t);

	/// @brief ����ʱ��ָ���Ƿ�̶�,true-�̶�,false-���̶�
	void setTimePointFixed(bool isFiexed);

	/// @brief �õ�ʱ��ָ���Ƿ�̶�
	bool isTimePointFixed();

private slots:
	//ʱ����Ӧ�¼�
	void on_TimerEvent();

	//������Ӧ�¼�
	void mousePress(QMouseEvent *event);
	void mouseWheel(QWheelEvent *event);
	void mouseDoubleClick(QMouseEvent *event);
	void mouseMove(QMouseEvent*);
	void leaveEvent(QEvent *);
	void enterEvent(QEvent *);

	//��ť��Ӧ�¼�
	void on_playBtn_clicked();
	void on_speedUpBtn_clicked() ;
	void on_speedDownBtn_clicked();
	void on_forwardBtn_clicked() ;
	void on_backwardBtn_clicked();
	void on_resetBtn_clicked();

	//checkBox��Ӧ�¼�
	void On_timePointCheckBox_stateChanged(int state);

private:
	/// @brief ����ͼ�εı���ɫ
	void drawBackground();
	/// @brief �������ж����������������
	void drawTimeSections();
	/// @brief ����ʱ��ָ��
	void drawTimePoint();
	/// @brief ������ʱʱ��ָ�����ʾ
	/// @param p ����λ��
	void drawTempTimeTip(QPoint p,time_t t);
	/// @brief ������ʱʱ��ָ��
	void drawTempTimePoint();
	/// @brief �������ػ���ʾ��ʱʱ��ָ��
	void setTempTimePointVisible(bool isVisible);
	/// @brief ��ʾ��ǰʱ��ֵ
	void showbCurrentTime(); 

private:
	QCPGraph* timePointGraph;                 //��¼ʱ��ָ���ͼ��
	QCPGraph* timeSectionsGraph;              //��¼�����������������ͼ��
	QCPGraph* timeTempPointGraph;             //��¼����ƶ�����ʱʱ��ָ��
	QCPItemText* tempTimeTip; //��¼����ƶ�ʱ����ʱʱ����ʾ�������ߵ��Ա���ʾʱ����ʾ��
	QVector<double> xLineVector,yLineVector;   //��¼ʱ��ָ���ֵ
	QVector<double> xLineVector2,yLineVector2; //��¼��ʱʱ���ֵ

	//���ڼ�¼ʱ��ָ��ĸ���ͼ�Σ���aux����
	//�����뽫ʱ��ָ����Ƴ�Ϊһ�������ǣ���Ҫ��
	//һ��ֱ����Ϊʱ��ָ���ChannelFillGraph
	QVector<double> xLineVector_aux,yLineVector_aux;
	QCPGraph* timePointGraph_aux;

private:
	IVBF_SimulationTimer* m_pISimulationTimer; //����ʱ��
	double currentTime;       //��¼��ǰʱ��
	double tempTime;          //��¼����ƶ�ʱ����ʱʱ��
	double startTime;         //��¼ʱ����Ŀ�ʼʱ��
	double endTime;           //��¼ʱ����Ľ���ʱ��
	bool isStarted;           //�ж��Ƿ��Ѿ������У�
	bool isTimePointFiexd;    //�ж�ʱ��ָ���Ƿ�̶�
	double speed;             //��������
	QVector<TimeSection> timeSections;   //��¼���ж���������������䣬�������ڻ���
	QTimer mDataTimer;        //��ʱ��

private:
	QCustomPlot* customPlot;
};

#endif // C_VIEWWIDGETTIMEAXIS_H
