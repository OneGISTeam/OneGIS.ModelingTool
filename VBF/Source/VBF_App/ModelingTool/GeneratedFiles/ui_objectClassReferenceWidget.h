/********************************************************************************
** Form generated from reading UI file 'objectClassReferenceWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTCLASSREFERENCEWIDGET_H
#define UI_OBJECTCLASSREFERENCEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QScrollArea>
#include <QtGui/QTextEdit>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectClassReferenceWidget
{
public:
    QGridLayout *gridLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget_SRS;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_selectdSRS;
    QTextEdit *textEdit;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *treeWidget_TRS;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_selectdTRS;

    void setupUi(QWidget *ObjectClassReferenceWidget)
    {
        if (ObjectClassReferenceWidget->objectName().isEmpty())
            ObjectClassReferenceWidget->setObjectName(QString::fromUtf8("ObjectClassReferenceWidget"));
        ObjectClassReferenceWidget->resize(717, 569);
        gridLayout_6 = new QGridLayout(ObjectClassReferenceWidget);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        scrollArea = new QScrollArea(ObjectClassReferenceWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 697, 549));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget_SRS = new QTreeWidget(groupBox_2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/geographicalSRS.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/projectionSRS.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/userdefineSRS.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget_SRS);
        __qtreewidgetitem->setFont(0, font);
        __qtreewidgetitem->setIcon(0, icon);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget_SRS);
        __qtreewidgetitem1->setFont(0, font);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget_SRS);
        __qtreewidgetitem4->setFont(0, font);
        __qtreewidgetitem4->setIcon(0, icon2);
        treeWidget_SRS->setObjectName(QString::fromUtf8("treeWidget_SRS"));
        treeWidget_SRS->setMaximumSize(QSize(1600, 600));
        treeWidget_SRS->setWordWrap(false);
        treeWidget_SRS->header()->setDefaultSectionSize(300);
        treeWidget_SRS->header()->setHighlightSections(false);
        treeWidget_SRS->header()->setMinimumSectionSize(200);

        verticalLayout->addWidget(treeWidget_SRS);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        lineEdit_selectdSRS = new QLineEdit(groupBox_2);
        lineEdit_selectdSRS->setObjectName(QString::fromUtf8("lineEdit_selectdSRS"));

        horizontalLayout_3->addWidget(lineEdit_selectdSRS);


        verticalLayout->addLayout(horizontalLayout_3);

        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(textEdit);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        treeWidget_TRS = new QTreeWidget(groupBox_3);
        new QTreeWidgetItem(treeWidget_TRS);
        treeWidget_TRS->setObjectName(QString::fromUtf8("treeWidget_TRS"));
        treeWidget_TRS->setMaximumSize(QSize(1600, 200));
        treeWidget_TRS->header()->setDefaultSectionSize(120);

        verticalLayout_4->addWidget(treeWidget_TRS);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        lineEdit_selectdTRS = new QLineEdit(groupBox_3);
        lineEdit_selectdTRS->setObjectName(QString::fromUtf8("lineEdit_selectdTRS"));

        horizontalLayout_4->addWidget(lineEdit_selectdTRS);


        verticalLayout_4->addLayout(horizontalLayout_4);


        gridLayout_4->addLayout(verticalLayout_4, 0, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox_3);


        gridLayout_5->addLayout(verticalLayout_5, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_6->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ObjectClassReferenceWidget);

        QMetaObject::connectSlotsByName(ObjectClassReferenceWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectClassReferenceWidget)
    {
        ObjectClassReferenceWidget->setWindowTitle(QApplication::translate("ObjectClassReferenceWidget", "\346\227\266\347\251\272\345\217\202\347\205\247", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ObjectClassReferenceWidget", "\344\270\226\347\225\214\345\235\220\346\240\207\345\217\202\350\200\203\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_SRS->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("ObjectClassReferenceWidget", "\347\256\241\347\220\206\346\234\272\346\236\204\346\240\207\350\257\206\347\254\246", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("ObjectClassReferenceWidget", "\345\235\220\346\240\207\345\217\202\350\200\203\347\263\273", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget_SRS->isSortingEnabled();
        treeWidget_SRS->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_SRS->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("ObjectClassReferenceWidget", "\345\234\260\347\220\206\345\235\220\346\240\207\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(1, QApplication::translate("ObjectClassReferenceWidget", "EPSG:4202", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("ObjectClassReferenceWidget", "AGD66", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(1, QApplication::translate("ObjectClassReferenceWidget", "EPSG:4203", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem3->setText(0, QApplication::translate("ObjectClassReferenceWidget", "AGD84", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget_SRS->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("ObjectClassReferenceWidget", "\346\212\225\345\275\261\345\235\220\346\240\207\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("ObjectClassReferenceWidget", "Albers Equal Area", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(1, QApplication::translate("ObjectClassReferenceWidget", "EPSG:3577", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem6->setText(0, QApplication::translate("ObjectClassReferenceWidget", "GDA94/Australia Albers", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem5->child(1);
        ___qtreewidgetitem7->setText(1, QApplication::translate("ObjectClassReferenceWidget", "EPSG:2964", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem7->setText(0, QApplication::translate("ObjectClassReferenceWidget", "NAD27/Alaska Albers", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem4->child(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("ObjectClassReferenceWidget", "Cassini", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(1, QApplication::translate("ObjectClassReferenceWidget", "EPSG:3377", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem9->setText(0, QApplication::translate("ObjectClassReferenceWidget", "GDM2000/Johor Grid", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = treeWidget_SRS->topLevelItem(2);
        ___qtreewidgetitem10->setText(0, QApplication::translate("ObjectClassReferenceWidget", "\347\224\250\346\210\267\350\207\252\345\256\232\344\271\211\345\235\220\346\240\207\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        treeWidget_SRS->setSortingEnabled(__sortingEnabled);

        label_3->setText(QApplication::translate("ObjectClassReferenceWidget", "\351\200\211\346\213\251\347\232\204\345\257\271\350\261\241\347\261\273\345\235\220\346\240\207\345\217\202\347\205\247\347\263\273\357\274\232", 0, QApplication::UnicodeUTF8));
        lineEdit_selectdSRS->setText(QApplication::translate("ObjectClassReferenceWidget", "DHDN/Soldner Berlin", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("ObjectClassReferenceWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">+proj=cass +lat_0=52.41864827777778 +lon_0=13.62720366666667 +x_0=40000 +y_0=10000 +ellps=bessel +towgs84=582,105,414,1.04,0.35,-3.08,8.3 +units=m +no_defs</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ObjectClassReferenceWidget", "\346\227\266\351\227\264\345\217\202\350\200\203\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem11 = treeWidget_TRS->headerItem();
        ___qtreewidgetitem11->setText(1, QApplication::translate("ObjectClassReferenceWidget", "\350\257\246\347\273\206\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem11->setText(0, QApplication::translate("ObjectClassReferenceWidget", "\346\227\266\351\227\264\345\217\202\350\200\203\347\263\273", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = treeWidget_TRS->isSortingEnabled();
        treeWidget_TRS->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem12 = treeWidget_TRS->topLevelItem(0);
        ___qtreewidgetitem12->setText(1, QApplication::translate("ObjectClassReferenceWidget", "\345\215\217\350\260\203\344\270\226\347\225\214\346\227\266\357\274\214\344\273\245\345\216\237\345\255\220\346\227\266\347\247\222\351\225\277\344\270\272\345\237\272\347\241\200\357\274\214\345\234\250\346\227\266\345\210\273\344\270\212\345\260\275\351\207\217\346\216\245\350\277\221\344\272\216\344\270\226\347\225\214\346\227\266\347\232\204\344\270\200\347\247\215\346\227\266\351\227\264\350\256\241\351\207\217\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem12->setText(0, QApplication::translate("ObjectClassReferenceWidget", "UTC", 0, QApplication::UnicodeUTF8));
        treeWidget_TRS->setSortingEnabled(__sortingEnabled1);

        label_5->setText(QApplication::translate("ObjectClassReferenceWidget", "\351\200\211\346\213\251\347\232\204\345\257\271\350\261\241\347\261\273\346\227\266\351\227\264\345\217\202\350\200\203\347\263\273\357\274\232", 0, QApplication::UnicodeUTF8));
        lineEdit_selectdTRS->setText(QApplication::translate("ObjectClassReferenceWidget", "UTC", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectClassReferenceWidget: public Ui_ObjectClassReferenceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTCLASSREFERENCEWIDGET_H
