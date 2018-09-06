#ifndef _VBF_QT_APP_H_
#define _VBF_QT_APP_H_

#ifdef QT4_FOUND
	#include <QApplication>
	#include <QDialog>
#else
	#include <QtWidgets/QApplication>
	#include <QtWidgets/QDialog>
#endif

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Macros.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>


class CVBF_QApp : public QApplication
{
public:
    CVBF_QApp(IVBF_3DMainCtrl* pI3DMainCtrl,int &argc, char **argv): QApplication(argc, argv)
    {
        m_idTimer = QObject::startTimer(10);
        m_pI3DMainCtrl = pI3DMainCtrl;
    }
    ~CVBF_QApp()
    {
        killTimer(m_idTimer);
    }

    virtual void timerEvent(QTimerEvent *)
    {
        if(m_pI3DMainCtrl)
        {
            m_pI3DMainCtrl->GetViewer()->frame();
        }
    }
    int m_idTimer;
    IVBF_3DMainCtrl* m_pI3DMainCtrl;
};

class CVBF_QAppHelper : public CVBF_Referenced
{
public:
    CVBF_QAppHelper(bool& bShowing,IVBF_3DMainCtrl* pI3DMainCtrl):m_bShowing(bShowing)
    {
        m_bShowing = true;
        m_pQApp = NULL;
        m_pWidget  = NULL;
        if(qApp==NULL)
        {
            int argc = 0;
            m_pQApp = new CVBF_QApp(pI3DMainCtrl,argc, 0);
        }
    }
    void ShowDialog(QDialog* pDlg,bool bModel)
    {
        if(pDlg==NULL) return;

        m_pWidget = pDlg;
        //pDlg->setWindowFlags( Qt::Dialog | Qt::WindowStaysOnTopHint); // 不需要在此处设置
        if(m_pQApp)
        {
            pDlg->setModal(true);
            pDlg->show();
            pDlg->setFocus();
        }
        else
        {
            if(bModel) pDlg->exec();
            else pDlg->show();
        }
    }
    void ShowWidget(QWidget* pWidget)
    {
        if(pWidget==NULL) return;
        m_pWidget = pWidget;
        m_pWidget->show();

    }


    ~CVBF_QAppHelper()
    {
        if(m_pQApp)
        {
            m_pQApp->exec();
 //           SAFE_DELETE(m_pWidget);
            SAFE_DELETE(m_pQApp);
            m_bShowing = false;
        }
    }

private:
    CVBF_QApp*  m_pQApp;
    QWidget*    m_pWidget;
    bool&       m_bShowing;
};

// 用法如下：
// ref_ptr<CVBF_QAppHelper> ipQAppHelper = new CVBF_QAppHelper(VBF_Get3DMainCtrl());
// ipQAppHelper->ShowDialog(new CVBF_DialogLayerControl(pMap),true);


#endif
