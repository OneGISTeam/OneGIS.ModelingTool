/********************************************************************************
** Form generated from reading UI file 'objectBasicinfoWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTBASICINFOWIDGET_H
#define UI_OBJECTBASICINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectBasicInfoWidget
{
public:
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_oid;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_type;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QTreeWidget *treeWidget_inherit;
    QPushButton *pushButton_changeInherit;
    QPushButton *pushButton_upInherit;
    QPushButton *pushButton_downInherit;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *textEdit;
    QLabel *label_5;

    void setupUi(QWidget *ObjectBasicInfoWidget)
    {
        if (ObjectBasicInfoWidget->objectName().isEmpty())
            ObjectBasicInfoWidget->setObjectName(QString::fromUtf8("ObjectBasicInfoWidget"));
        ObjectBasicInfoWidget->resize(615, 536);
        gridLayout_3 = new QGridLayout(ObjectBasicInfoWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        scrollArea = new QScrollArea(ObjectBasicInfoWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::StyledPanel);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 570, 527));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_name = new QLineEdit(groupBox);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setMinimumSize(QSize(264, 0));

        horizontalLayout->addWidget(lineEdit_name);

        horizontalSpacer = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_oid = new QLineEdit(groupBox);
        lineEdit_oid->setObjectName(QString::fromUtf8("lineEdit_oid"));
        lineEdit_oid->setMinimumSize(QSize(200, 0));

        horizontalLayout_2->addWidget(lineEdit_oid);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_2->addWidget(checkBox);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        lineEdit_type = new QLineEdit(groupBox);
        lineEdit_type->setObjectName(QString::fromUtf8("lineEdit_type"));
        lineEdit_type->setMinimumSize(QSize(264, 0));

        horizontalLayout_6->addWidget(lineEdit_type);

        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setMinimumSize(QSize(24, 24));
        toolButton->setMaximumSize(QSize(24, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/type.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(20, 20));
        toolButton->setAutoRaise(true);

        horizontalLayout_6->addWidget(toolButton);

        horizontalSpacer_4 = new QSpacerItem(88, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_6);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        treeWidget_inherit = new QTreeWidget(scrollAreaWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_inherit->setHeaderItem(__qtreewidgetitem);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/class.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font;
        font.setPointSize(10);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/selectedObjectClass.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget_inherit);
        __qtreewidgetitem1->setFont(0, font);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setFont(0, font);
        __qtreewidgetitem2->setIcon(0, icon2);
        treeWidget_inherit->setObjectName(QString::fromUtf8("treeWidget_inherit"));
        treeWidget_inherit->setMinimumSize(QSize(160, 0));
        treeWidget_inherit->setMaximumSize(QSize(300, 16777215));
        treeWidget_inherit->setIconSize(QSize(30, 30));
        treeWidget_inherit->setAllColumnsShowFocus(false);
        treeWidget_inherit->setHeaderHidden(true);

        verticalLayout->addWidget(treeWidget_inherit);

        pushButton_changeInherit = new QPushButton(scrollAreaWidgetContents);
        pushButton_changeInherit->setObjectName(QString::fromUtf8("pushButton_changeInherit"));

        verticalLayout->addWidget(pushButton_changeInherit);

        pushButton_upInherit = new QPushButton(scrollAreaWidgetContents);
        pushButton_upInherit->setObjectName(QString::fromUtf8("pushButton_upInherit"));

        verticalLayout->addWidget(pushButton_upInherit);

        pushButton_downInherit = new QPushButton(scrollAreaWidgetContents);
        pushButton_downInherit->setObjectName(QString::fromUtf8("pushButton_downInherit"));

        verticalLayout->addWidget(pushButton_downInherit);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        textEdit = new QTextEdit(scrollAreaWidgetContents);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMinimumSize(QSize(360, 300));
        textEdit->setFrameShape(QFrame::Box);
        textEdit->setFrameShadow(QFrame::Plain);

        verticalLayout_2->addWidget(textEdit);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font1;
        font1.setItalic(true);
        label_5->setFont(font1);
        label_5->setLineWidth(1);
        label_5->setWordWrap(true);

        verticalLayout_4->addWidget(label_5);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ObjectBasicInfoWidget);

        QMetaObject::connectSlotsByName(ObjectBasicInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectBasicInfoWidget)
    {
        ObjectBasicInfoWidget->setWindowTitle(QApplication::translate("ObjectBasicInfoWidget", "\345\257\271\350\261\241\345\237\272\346\234\254\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ObjectBasicInfoWidget", "\345\237\272\346\234\254\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ObjectBasicInfoWidget", "\345\257\271\350\261\241\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ObjectBasicInfoWidget", "\345\257\271\350\261\241\346\240\207\350\257\206\357\274\232", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("ObjectBasicInfoWidget", "\350\207\252\345\212\250\347\224\237\346\210\220\345\257\271\350\261\241\345\224\257\344\270\200\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ObjectBasicInfoWidget", "\345\257\271\350\261\241\347\261\273\345\210\253\357\274\232", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QString());
        label_3->setText(QApplication::translate("ObjectBasicInfoWidget", "\347\273\247\346\211\277\345\210\227\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget_inherit->isSortingEnabled();
        treeWidget_inherit->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_inherit->topLevelItem(0);
        ___qtreewidgetitem->setText(0, QApplication::translate("ObjectBasicInfoWidget", "\351\243\236\346\234\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = ___qtreewidgetitem->child(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("ObjectBasicInfoWidget", "\347\233\26495", 0, QApplication::UnicodeUTF8));
        treeWidget_inherit->setSortingEnabled(__sortingEnabled);

        pushButton_changeInherit->setText(QApplication::translate("ObjectBasicInfoWidget", "\346\233\264\346\215\242\347\273\247\346\211\277\346\240\221", 0, QApplication::UnicodeUTF8));
        pushButton_upInherit->setText(QApplication::translate("ObjectBasicInfoWidget", "\345\220\221\344\270\212\347\273\247\346\211\277", 0, QApplication::UnicodeUTF8));
        pushButton_downInherit->setText(QApplication::translate("ObjectBasicInfoWidget", "\345\220\221\344\270\213\347\273\247\346\211\277", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ObjectBasicInfoWidget", "\347\273\247\346\211\277\347\261\273\347\232\204\344\277\241\346\201\257\346\237\245\347\234\213\357\274\232", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("ObjectBasicInfoWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&lt;?xml version=&quot;1.0&quot; encoding=&quot;GB2312&quot; standalone=&quot;yes&quot; ?&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&lt;!--\345\257\271\350\261\241\346\217\217\350\277\260\346\226\207\344\273\266\357\274\214\346\240\274\345\274\217\350\247\201\343\200\220\345\257\271\350\261\241\346\240\274\345\274\217\350\257\264\346\230\216.xml\343\200\221--&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text"
                        "-indent:0px;\">&lt;Root Desc=&quot;\345\257\271\350\261\241\346\217\217\350\277\260\346\226\207\344\273\266&quot; Version=&quot;1.0&quot; Author=&quot;wuyuguo&quot; Date=&quot;2017-10-10&quot; Path=&quot;F:/VBF_DATA&quot;&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">	&lt;DocRef URL=&quot;./Airplane.stc&quot;/&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">	&lt;ObjectTemplate TemplateID=&quot;PALNE00000&quot; ID=&quot;Z9500000&quot; Name=&quot;\347\233\264\344\271\235\344\272\224&quot; Type=&quot;70000001&quot; SRSID=&quot;epsg:4610&quot; TRSID=&quot;UTC&quot; TimeFormat=&quot;yyyy-mm-dd:hh-mm-ss.xxx&quot; BeginTime=&quot;2017-10-10:10-00-00.000&quot; EndTime=&quot;2017-10-10:00-12-00.000&quot;&gt;</p>\n"
"<p"
                        " style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;Parameters&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Parameter Name=&quot;\346\265\213\350\257\225\345\217\202\346\225\260&quot; ValueType=&quot;string&quot; Value=&quot;UnKnown&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;/Parameters&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;Attrs&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Attr Name=&quot;\346\234\200\345\244\247\351\243\236\350\241\214\351\253\230\345\272\246&quot; Type=&quot;static&quot; ValueType=&quot;int&quot;"
                        " Value=&quot;8000&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;/Attrs&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;Position Type=&quot;static&quot; Shape=&quot;Point&quot; Format=&quot;BL&quot; SRSID=&quot;epsg:4610&quot; TRSID=&quot;UTC&quot; TimeFormat=&quot;yyyy-mm-dd:hh-mm-ss.xxx&quot;&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">			&lt;Point&gt;(120.0,24.0)&lt;/Point&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">		&lt;/Position&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;Forms&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:"
                        "0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Form Name=&quot;Default&quot; Time=&quot;2017-10-10&quot; State=&quot;Normal&quot; Scale=&quot;10000&quot; LocationDependence=&quot;false&quot;&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                &lt;Part Name=&quot;\346\234\272\350\272\253&quot; Type=&quot;3DModel&quot; DataFormat=&quot;VMESH&quot; URL=&quot;Model/Zhi9Wu/JiTi.VMESH&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                &lt;Part Name=&quot;QianLuoXuanJiang&quot; Type=&quot;3DModel&quot; DataFormat=&quot;VMESH&quot; URL=&quot;Model/Zhi9Wu/DaLuoXuanJiang.VMESH&quot; Translation=&quot;(-2.225, 0.0, 1.15)&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">               "
                        " &lt;Part Name=&quot;HouLuoXuanJiang&quot; Type=&quot;3DModel&quot; DataFormat=&quot;VMESH&quot; URL=&quot;Model/Zhi9Wu/XiaoLuoXuanJiang.VMESH&quot; Translation=&quot;(5.58, -0.023, -0.603)&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;/Form&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Form Name=&quot;2D&quot; Time=&quot;2017-10-10&quot; State=&quot;Normal&quot; Scale=&quot;10000&quot; LocationDependence=&quot;true&quot;&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                &lt;Part Name=&quot;All&quot; Type=&quot;Image&quot; DataFormat=&quot;svg&quot; URL=&quot;&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    "
                        "        &lt;/Form&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;/Forms&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;Parts&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Part Name=&quot;\346\234\272\350\272\253&quot; ID=&quot;ID&quot; RefObjectID=&quot;RefObjectID&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Part Name=&quot;\345\211\215\350\236\272\346\227\213\346\241\250&quot; ID=&quot;ID&quot; RefObjectID=&quot;RefObjectID&quot; Translation=&quot;(-2.225, 0.0, 1.15)&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\""
                        ">            &lt;Part Name=&quot;\345\220\216\350\236\272\346\227\213\346\241\250&quot; ID=&quot;ID&quot; RefObjectID=&quot;RefObjectID&quot; Translation=&quot;(5.58, -0.023, -0.603)&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;/Parts&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;Actions&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Action Name=&quot;\345\211\215\350\236\272\346\227\213\346\241\250\350\275\254\345\212\250&quot; ObjectID=&quot;QianLuoXuanJiang&quot; Type=&quot;RotateAxis&quot; Trigger=&quot;COMMAND&quot;&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                &lt;Parameters&gt;</p>\n"
"<p style=\" m"
                        "argin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                    &lt;Parameter Name=&quot;Direction&quot; ValueType=&quot;string&quot; Value=&quot;CCW&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">					&lt;Parameter Name=&quot;Axis&quot; ValueType=&quot;string&quot; Value=&quot;(0, 0, -1)&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                    &lt;Parameter Name=&quot;Speed&quot; ValueType=&quot;int&quot; Value=&quot;720&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                &lt;/Parameters&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;/Action&gt;</p>"
                        "\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;Action Name=&quot;\345\220\216\350\236\272\346\227\213\346\241\250\350\275\254\345\212\250&quot; ObjectID=&quot;HouLuoXuanJiang&quot; Type=&quot;RotateAxis&quot; Trigger=&quot;COMMAND&quot;&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                &lt;Parameters&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                    &lt;Parameter Name=&quot;Direction&quot; ValueType=&quot;string&quot; Value=&quot;CCW&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">					&lt;Parameter Name=&quot;Axis&quot; ValueType=&quot;string&quot; Value=&quot;(0, 1, 0)&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bo"
                        "ttom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                    &lt;Parameter Name=&quot;Speed&quot; ValueType=&quot;int&quot; Value=&quot;540&quot; /&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                &lt;/Parameters&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">            &lt;/Action&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        &lt;/Actions&gt;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    &lt;/ObjectTemplate&gt;</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&lt;/Root&gt;</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ObjectBasicInfoWidget", "\345\217\257\344\273\245\346\233\264\346\224\271\347\273\247\346\211\277\347\232\204\347\261\273\357\274\214\345\257\271\350\261\241\347\273\247\346\211\277\345\271\266\350\246\206\347\233\226\347\210\266\347\261\273\347\232\204\347\211\271\345\276\201\351\241\271\357\274\214\344\275\206\347\273\247\346\211\277\350\207\252\347\210\266\347\261\273\347\232\204\347\211\271\345\276\201\351\241\271\345\217\252\350\203\275\346\233\264\346\224\271\345\205\266\345\200\274\357\274\214\350\200\214\344\270\215\345\217\257\344\273\245\346\233\264\346\224\271\347\261\273\345\236\213\346\210\226\345\210\240\351\231\244\343\200\202", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectBasicInfoWidget: public Ui_ObjectBasicInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTBASICINFOWIDGET_H
