/********************************************************************************
** Form generated from reading UI file 'objectExportDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTEXPORTDIALOG_H
#define UI_OBJECTEXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectExportDialog
{
public:
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *m_groupBox_objects;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_objectView;
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget_objects;
    QWidget *tab_objectClassView;
    QGridLayout *gridLayout_5;
    QTreeWidget *treeWidget_objectclass;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *m_label_classCount;
    QLabel *label_3;
    QLabel *m_label_objectCount;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *m_groupBox_relations;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QTreeWidget *m_treeWidget_relations;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLabel *m_label_relationClassCount;
    QLabel *label_7;
    QLabel *m_label_relationCount;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lineEdit;
    QPushButton *m_btn_file;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *m_btn_ok;
    QPushButton *m_btn_cancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ObjectExportDialog)
    {
        if (ObjectExportDialog->objectName().isEmpty())
            ObjectExportDialog->setObjectName(QString::fromUtf8("ObjectExportDialog"));
        ObjectExportDialog->resize(466, 586);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/exportObject.png"), QSize(), QIcon::Normal, QIcon::Off);
        ObjectExportDialog->setWindowIcon(icon);
        gridLayout_4 = new QGridLayout(ObjectExportDialog);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_groupBox_objects = new QGroupBox(ObjectExportDialog);
        m_groupBox_objects->setObjectName(QString::fromUtf8("m_groupBox_objects"));
        m_groupBox_objects->setMinimumSize(QSize(400, 0));
        m_groupBox_objects->setMaximumSize(QSize(16777215, 200));
        gridLayout_3 = new QGridLayout(m_groupBox_objects);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(m_groupBox_objects);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(300, 0));
        tab_objectView = new QWidget();
        tab_objectView->setObjectName(QString::fromUtf8("tab_objectView"));
        gridLayout_2 = new QGridLayout(tab_objectView);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeWidget_objects = new QTreeWidget(tab_objectView);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_objects->setHeaderItem(__qtreewidgetitem);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/object.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget_objects);
        __qtreewidgetitem1->setCheckState(0, Qt::Checked);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setCheckState(0, Qt::Checked);
        __qtreewidgetitem2->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem3->setCheckState(0, Qt::Checked);
        __qtreewidgetitem3->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget_objects);
        __qtreewidgetitem4->setCheckState(0, Qt::Checked);
        __qtreewidgetitem4->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem5->setCheckState(0, Qt::Checked);
        __qtreewidgetitem5->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem6->setCheckState(0, Qt::Checked);
        __qtreewidgetitem6->setIcon(0, icon1);
        treeWidget_objects->setObjectName(QString::fromUtf8("treeWidget_objects"));
        treeWidget_objects->setMinimumSize(QSize(100, 0));
        treeWidget_objects->setMaximumSize(QSize(16777215, 16777215));
        treeWidget_objects->header()->setVisible(false);

        gridLayout_2->addWidget(treeWidget_objects, 0, 0, 1, 1);

        tabWidget->addTab(tab_objectView, QString());
        tab_objectClassView = new QWidget();
        tab_objectClassView->setObjectName(QString::fromUtf8("tab_objectClassView"));
        gridLayout_5 = new QGridLayout(tab_objectClassView);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        treeWidget_objectclass = new QTreeWidget(tab_objectClassView);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem();
        __qtreewidgetitem7->setText(0, QString::fromUtf8("1"));
        treeWidget_objectclass->setHeaderItem(__qtreewidgetitem7);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/class.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(treeWidget_objectclass);
        __qtreewidgetitem8->setCheckState(0, Qt::Checked);
        __qtreewidgetitem8->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem9->setCheckState(0, Qt::Checked);
        __qtreewidgetitem9->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem10->setCheckState(0, Qt::Checked);
        __qtreewidgetitem10->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(treeWidget_objectclass);
        __qtreewidgetitem11->setCheckState(0, Qt::Checked);
        __qtreewidgetitem11->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(__qtreewidgetitem11);
        __qtreewidgetitem12->setCheckState(0, Qt::Checked);
        __qtreewidgetitem12->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem11);
        __qtreewidgetitem13->setCheckState(0, Qt::Checked);
        __qtreewidgetitem13->setIcon(0, icon1);
        treeWidget_objectclass->setObjectName(QString::fromUtf8("treeWidget_objectclass"));
        treeWidget_objectclass->setMinimumSize(QSize(0, 0));
        treeWidget_objectclass->setMaximumSize(QSize(16777215, 16777215));
        treeWidget_objectclass->header()->setVisible(false);

        gridLayout_5->addWidget(treeWidget_objectclass, 0, 0, 1, 1);

        tabWidget->addTab(tab_objectClassView, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(m_groupBox_objects);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        m_label_classCount = new QLabel(m_groupBox_objects);
        m_label_classCount->setObjectName(QString::fromUtf8("m_label_classCount"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        m_label_classCount->setFont(font);

        horizontalLayout->addWidget(m_label_classCount);

        label_3 = new QLabel(m_groupBox_objects);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        m_label_objectCount = new QLabel(m_groupBox_objects);
        m_label_objectCount->setObjectName(QString::fromUtf8("m_label_objectCount"));
        m_label_objectCount->setFont(font);

        horizontalLayout->addWidget(m_label_objectCount);

        label_4 = new QLabel(m_groupBox_objects);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout_3->addWidget(m_groupBox_objects);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox = new QCheckBox(ObjectExportDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);

        horizontalLayout_3->addWidget(checkBox);

        horizontalSpacer_2 = new QSpacerItem(308, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        m_groupBox_relations = new QGroupBox(ObjectExportDialog);
        m_groupBox_relations->setObjectName(QString::fromUtf8("m_groupBox_relations"));
        m_groupBox_relations->setEnabled(true);
        m_groupBox_relations->setMinimumSize(QSize(400, 0));
        m_groupBox_relations->setMaximumSize(QSize(16777215, 200));
        m_groupBox_relations->setCheckable(false);
        gridLayout = new QGridLayout(m_groupBox_relations);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(m_groupBox_relations);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAcceptDrops(false);

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(83, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_4);

        m_treeWidget_relations = new QTreeWidget(m_groupBox_relations);
        QTreeWidgetItem *__qtreewidgetitem14 = new QTreeWidgetItem();
        __qtreewidgetitem14->setText(0, QString::fromUtf8("1"));
        m_treeWidget_relations->setHeaderItem(__qtreewidgetitem14);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/network.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/relation.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem15 = new QTreeWidgetItem(m_treeWidget_relations);
        __qtreewidgetitem15->setCheckState(0, Qt::Checked);
        __qtreewidgetitem15->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem16 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem16->setIcon(0, icon4);
        QTreeWidgetItem *__qtreewidgetitem17 = new QTreeWidgetItem(__qtreewidgetitem16);
        __qtreewidgetitem17->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem18 = new QTreeWidgetItem(__qtreewidgetitem16);
        __qtreewidgetitem18->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem19 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem19->setIcon(0, icon4);
        QTreeWidgetItem *__qtreewidgetitem20 = new QTreeWidgetItem(__qtreewidgetitem19);
        __qtreewidgetitem20->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem21 = new QTreeWidgetItem(__qtreewidgetitem19);
        __qtreewidgetitem21->setIcon(0, icon1);
        m_treeWidget_relations->setObjectName(QString::fromUtf8("m_treeWidget_relations"));
        m_treeWidget_relations->header()->setVisible(false);

        verticalLayout->addWidget(m_treeWidget_relations);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(m_groupBox_relations);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        m_label_relationClassCount = new QLabel(m_groupBox_relations);
        m_label_relationClassCount->setObjectName(QString::fromUtf8("m_label_relationClassCount"));
        m_label_relationClassCount->setFont(font);

        horizontalLayout_2->addWidget(m_label_relationClassCount);

        label_7 = new QLabel(m_groupBox_relations);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        m_label_relationCount = new QLabel(m_groupBox_relations);
        m_label_relationCount->setObjectName(QString::fromUtf8("m_label_relationCount"));
        m_label_relationCount->setFont(font);

        horizontalLayout_2->addWidget(m_label_relationCount);

        label_8 = new QLabel(m_groupBox_relations);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_2->addWidget(label_8);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_3->addWidget(m_groupBox_relations);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_9 = new QLabel(ObjectExportDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_6->addWidget(label_9);

        horizontalSpacer_6 = new QSpacerItem(175, 14, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        lineEdit = new QLineEdit(ObjectExportDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_7->addWidget(lineEdit);

        m_btn_file = new QPushButton(ObjectExportDialog);
        m_btn_file->setObjectName(QString::fromUtf8("m_btn_file"));
        m_btn_file->setMinimumSize(QSize(30, 30));
        m_btn_file->setMaximumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ModelingTool/Images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btn_file->setIcon(icon5);
        m_btn_file->setIconSize(QSize(24, 24));

        horizontalLayout_7->addWidget(m_btn_file);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        m_btn_ok = new QPushButton(ObjectExportDialog);
        m_btn_ok->setObjectName(QString::fromUtf8("m_btn_ok"));

        horizontalLayout_8->addWidget(m_btn_ok);

        m_btn_cancel = new QPushButton(ObjectExportDialog);
        m_btn_cancel->setObjectName(QString::fromUtf8("m_btn_cancel"));

        horizontalLayout_8->addWidget(m_btn_cancel);


        verticalLayout_3->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        gridLayout_4->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(ObjectExportDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ObjectExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ObjectExportDialog)
    {
        ObjectExportDialog->setWindowTitle(QApplication::translate("ObjectExportDialog", "\345\257\274\345\207\272\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        m_groupBox_objects->setTitle(QApplication::translate("ObjectExportDialog", "\345\257\274\345\207\272\345\257\271\350\261\241\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget_objects->isSortingEnabled();
        treeWidget_objects->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_objects->topLevelItem(0);
        ___qtreewidgetitem->setText(0, QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\241a", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = ___qtreewidgetitem->child(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("ObjectExportDialog", "\345\255\220\345\257\271\350\261\2411", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem->child(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("ObjectExportDialog", "\345\255\220\345\257\271\350\261\2412", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget_objects->topLevelItem(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\241b", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem3->child(0);
        ___qtreewidgetitem4->setText(0, QApplication::translate("ObjectExportDialog", "\345\255\220\345\257\271\350\261\2411", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem3->child(1);
        ___qtreewidgetitem5->setText(0, QApplication::translate("ObjectExportDialog", "\345\255\220\345\257\271\350\261\2412", 0, QApplication::UnicodeUTF8));
        treeWidget_objects->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab_objectView), QApplication::translate("ObjectExportDialog", "\346\214\211\345\257\271\350\261\241\346\240\221\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = treeWidget_objectclass->isSortingEnabled();
        treeWidget_objectclass->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem6 = treeWidget_objectclass->topLevelItem(0);
        ___qtreewidgetitem6->setText(0, QApplication::translate("ObjectExportDialog", "\347\261\273A", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem6->child(0);
        ___qtreewidgetitem7->setText(0, QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\2411", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem6->child(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\2412", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = treeWidget_objectclass->topLevelItem(1);
        ___qtreewidgetitem9->setText(0, QApplication::translate("ObjectExportDialog", "\347\261\273B", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem9->child(0);
        ___qtreewidgetitem10->setText(0, QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\2413", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem9->child(1);
        ___qtreewidgetitem11->setText(0, QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\2414", 0, QApplication::UnicodeUTF8));
        treeWidget_objectclass->setSortingEnabled(__sortingEnabled1);

        tabWidget->setTabText(tabWidget->indexOf(tab_objectClassView), QApplication::translate("ObjectExportDialog", "\346\214\211\345\257\271\350\261\241\347\261\273\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ObjectExportDialog", "\346\202\250\345\260\206\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));
        m_label_classCount->setText(QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\241\347\261\273\346\225\260\347\233\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ObjectExportDialog", "\347\261\273\345\257\271\350\261\241\357\274\214\345\205\261\350\256\241", 0, QApplication::UnicodeUTF8));
        m_label_objectCount->setText(QApplication::translate("ObjectExportDialog", "\345\257\271\350\261\241\346\225\260\347\233\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ObjectExportDialog", "\344\270\252\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("ObjectExportDialog", "\345\257\274\345\207\272\345\205\263\350\201\224\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        m_groupBox_relations->setTitle(QApplication::translate("ObjectExportDialog", "\345\205\263\347\263\273\345\257\274\345\207\272\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ObjectExportDialog", "\350\257\267\351\200\211\346\213\251\346\202\250\350\246\201\345\257\274\345\207\272\347\232\204\345\257\271\350\261\241\351\227\264\345\205\263\350\201\224\345\205\263\347\263\273\357\274\232", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = m_treeWidget_relations->isSortingEnabled();
        m_treeWidget_relations->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem12 = m_treeWidget_relations->topLevelItem(0);
        ___qtreewidgetitem12->setText(0, QApplication::translate("ObjectExportDialog", "\345\215\217\345\220\214\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem12->child(0);
        ___qtreewidgetitem13->setText(0, QApplication::translate("ObjectExportDialog", "\347\233\26495001-\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem13->child(0);
        ___qtreewidgetitem14->setText(0, QApplication::translate("ObjectExportDialog", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem13->child(1);
        ___qtreewidgetitem15->setText(0, QApplication::translate("ObjectExportDialog", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem12->child(1);
        ___qtreewidgetitem16->setText(0, QApplication::translate("ObjectExportDialog", "\347\233\26495004-\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem16->child(0);
        ___qtreewidgetitem17->setText(0, QApplication::translate("ObjectExportDialog", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495004", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem16->child(1);
        ___qtreewidgetitem18->setText(0, QApplication::translate("ObjectExportDialog", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495003", 0, QApplication::UnicodeUTF8));
        m_treeWidget_relations->setSortingEnabled(__sortingEnabled2);

        label_6->setText(QApplication::translate("ObjectExportDialog", "\346\202\250\345\260\206\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));
        m_label_relationClassCount->setText(QApplication::translate("ObjectExportDialog", "\345\205\263\347\263\273\347\261\273\346\225\260\347\233\256", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ObjectExportDialog", "\347\261\273\345\205\263\347\263\273\357\274\214\345\205\261\350\256\241", 0, QApplication::UnicodeUTF8));
        m_label_relationCount->setText(QApplication::translate("ObjectExportDialog", "\345\205\263\347\263\273\346\225\260\347\233\256", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ObjectExportDialog", "\345\257\271\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ObjectExportDialog", "\345\257\274\345\207\272\350\267\257\345\276\204\357\274\232", 0, QApplication::UnicodeUTF8));
        m_btn_file->setText(QString());
        m_btn_ok->setText(QApplication::translate("ObjectExportDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btn_cancel->setText(QApplication::translate("ObjectExportDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectExportDialog: public Ui_ObjectExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTEXPORTDIALOG_H
