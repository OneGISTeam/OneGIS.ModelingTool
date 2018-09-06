/********************************************************************************
** Form generated from reading UI file 'createRelationDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATERELATIONDIALOG_H
#define UI_CREATERELATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateRelationDialog
{
public:
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit_begin;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit_end;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_intensity;
    QDoubleSpinBox *m_doubleSpinBox_intensity;
    QCheckBox *m_checkBox_mathModel;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_paramInfo;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *m_tableWidget_params;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;

    void setupUi(QDialog *CreateRelationDialog)
    {
        if (CreateRelationDialog->objectName().isEmpty())
            CreateRelationDialog->setObjectName(QString::fromUtf8("CreateRelationDialog"));
        CreateRelationDialog->resize(546, 341);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/manualCreateRelation.png"), QSize(), QIcon::Normal, QIcon::Off);
        CreateRelationDialog->setWindowIcon(icon);
        gridLayout_4 = new QGridLayout(CreateRelationDialog);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_2 = new QGroupBox(CreateRelationDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        dateTimeEdit_begin = new QDateTimeEdit(groupBox_2);
        dateTimeEdit_begin->setObjectName(QString::fromUtf8("dateTimeEdit_begin"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dateTimeEdit_begin->sizePolicy().hasHeightForWidth());
        dateTimeEdit_begin->setSizePolicy(sizePolicy);

        gridLayout->addWidget(dateTimeEdit_begin, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        dateTimeEdit_end = new QDateTimeEdit(groupBox_2);
        dateTimeEdit_end->setObjectName(QString::fromUtf8("dateTimeEdit_end"));
        sizePolicy.setHeightForWidth(dateTimeEdit_end->sizePolicy().hasHeightForWidth());
        dateTimeEdit_end->setSizePolicy(sizePolicy);

        gridLayout->addWidget(dateTimeEdit_end, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox = new QGroupBox(CreateRelationDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_intensity = new QLabel(groupBox);
        label_intensity->setObjectName(QString::fromUtf8("label_intensity"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_intensity->sizePolicy().hasHeightForWidth());
        label_intensity->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_intensity);

        m_doubleSpinBox_intensity = new QDoubleSpinBox(groupBox);
        m_doubleSpinBox_intensity->setObjectName(QString::fromUtf8("m_doubleSpinBox_intensity"));
        sizePolicy.setHeightForWidth(m_doubleSpinBox_intensity->sizePolicy().hasHeightForWidth());
        m_doubleSpinBox_intensity->setSizePolicy(sizePolicy);
        m_doubleSpinBox_intensity->setMinimumSize(QSize(80, 0));
        m_doubleSpinBox_intensity->setMaximum(1);
        m_doubleSpinBox_intensity->setSingleStep(0.01);
        m_doubleSpinBox_intensity->setValue(1);

        horizontalLayout_4->addWidget(m_doubleSpinBox_intensity);

        m_checkBox_mathModel = new QCheckBox(groupBox);
        m_checkBox_mathModel->setObjectName(QString::fromUtf8("m_checkBox_mathModel"));

        horizontalLayout_4->addWidget(m_checkBox_mathModel);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(168, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        label_paramInfo = new QLabel(groupBox);
        label_paramInfo->setObjectName(QString::fromUtf8("label_paramInfo"));
        sizePolicy1.setHeightForWidth(label_paramInfo->sizePolicy().hasHeightForWidth());
        label_paramInfo->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_paramInfo);

        horizontalSpacer_3 = new QSpacerItem(168, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_5);

        m_tableWidget_params = new QTableWidget(groupBox);
        if (m_tableWidget_params->columnCount() < 5)
            m_tableWidget_params->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_tableWidget_params->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_tableWidget_params->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_tableWidget_params->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        m_tableWidget_params->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        m_tableWidget_params->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        m_tableWidget_params->setObjectName(QString::fromUtf8("m_tableWidget_params"));

        verticalLayout->addWidget(m_tableWidget_params);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(CreateRelationDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);

        horizontalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(CreateRelationDialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon2);

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(CreateRelationDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(CreateRelationDialog);

        QMetaObject::connectSlotsByName(CreateRelationDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateRelationDialog)
    {
        CreateRelationDialog->setWindowTitle(QApplication::translate("CreateRelationDialog", "\345\210\233\345\273\272\345\205\263\350\201\224\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CreateRelationDialog", "\345\205\263\347\263\273\347\224\237\345\221\275\345\221\250\346\234\237", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CreateRelationDialog", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CreateRelationDialog", "\347\273\210\346\255\242\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CreateRelationDialog", "\345\205\263\347\263\273\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_intensity->setText(QApplication::translate("CreateRelationDialog", "\345\205\263\347\263\273\345\274\272\345\272\246\345\200\274\357\274\232", 0, QApplication::UnicodeUTF8));
        m_checkBox_mathModel->setText(QApplication::translate("CreateRelationDialog", "\345\205\263\350\201\224\350\256\241\347\256\227\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
        label_paramInfo->setText(QApplication::translate("CreateRelationDialog", "---------------\345\205\263\347\263\273\345\217\202\346\225\260\350\241\250---------------", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget_params->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CreateRelationDialog", "\345\217\202\346\225\260\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget_params->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CreateRelationDialog", "\345\217\202\346\225\260\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget_params->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CreateRelationDialog", "\345\217\202\346\225\260\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = m_tableWidget_params->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CreateRelationDialog", "\351\273\230\350\256\244\345\200\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = m_tableWidget_params->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("CreateRelationDialog", "\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CreateRelationDialog", "\345\210\233\345\273\272\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("CreateRelationDialog", "\345\210\240\351\231\244\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("CreateRelationDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreateRelationDialog: public Ui_CreateRelationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATERELATIONDIALOG_H
