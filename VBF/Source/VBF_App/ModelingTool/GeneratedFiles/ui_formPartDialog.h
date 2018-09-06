/********************************************************************************
** Form generated from reading UI file 'formPartDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMPARTDIALOG_H
#define UI_FORMPARTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FormPartDialog
{
public:
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_8;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *m_lineEdit_name;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *m_comboBox_type;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *m_lineEdit_dataFormat;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *m_lineEdit_url;
    QPushButton *m_btn_file;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_21;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_dX;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_dY;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_dZ;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_rX;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_rY;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_rZ;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_sX;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_sY;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_sZ;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_sX_2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_15;
    QDoubleSpinBox *doubleSpinBox_sY_2;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBox_sZ_2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btn_add;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *m_tableWidget_parts;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_btn_remove;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *m_btn_ok;
    QPushButton *m_btn_cancel;

    void setupUi(QDialog *FormPartDialog)
    {
        if (FormPartDialog->objectName().isEmpty())
            FormPartDialog->setObjectName(QString::fromUtf8("FormPartDialog"));
        FormPartDialog->resize(460, 490);
        gridLayout_9 = new QGridLayout(FormPartDialog);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox = new QGroupBox(FormPartDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_8 = new QGridLayout(groupBox);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        m_lineEdit_name = new QLineEdit(groupBox);
        m_lineEdit_name->setObjectName(QString::fromUtf8("m_lineEdit_name"));

        horizontalLayout_3->addWidget(m_lineEdit_name);


        gridLayout_6->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        m_comboBox_type = new QComboBox(groupBox);
        m_comboBox_type->setObjectName(QString::fromUtf8("m_comboBox_type"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_comboBox_type->sizePolicy().hasHeightForWidth());
        m_comboBox_type->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(m_comboBox_type);


        gridLayout_6->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        m_lineEdit_dataFormat = new QLineEdit(groupBox);
        m_lineEdit_dataFormat->setObjectName(QString::fromUtf8("m_lineEdit_dataFormat"));

        horizontalLayout_5->addWidget(m_lineEdit_dataFormat);


        gridLayout_6->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(36, 0));

        horizontalLayout_2->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_lineEdit_url = new QLineEdit(groupBox);
        m_lineEdit_url->setObjectName(QString::fromUtf8("m_lineEdit_url"));
        sizePolicy.setHeightForWidth(m_lineEdit_url->sizePolicy().hasHeightForWidth());
        m_lineEdit_url->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_lineEdit_url);

        m_btn_file = new QPushButton(groupBox);
        m_btn_file->setObjectName(QString::fromUtf8("m_btn_file"));
        m_btn_file->setEnabled(false);
        m_btn_file->setMinimumSize(QSize(20, 20));
        m_btn_file->setMaximumSize(QSize(20, 20));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btn_file->setIcon(icon);

        horizontalLayout->addWidget(m_btn_file);


        horizontalLayout_2->addLayout(horizontalLayout);


        gridLayout_6->addLayout(horizontalLayout_2, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_6);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        doubleSpinBox_dX = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_dX->setObjectName(QString::fromUtf8("doubleSpinBox_dX"));

        horizontalLayout_6->addWidget(doubleSpinBox_dX);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_10->addWidget(label_6);

        doubleSpinBox_dY = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_dY->setObjectName(QString::fromUtf8("doubleSpinBox_dY"));

        horizontalLayout_10->addWidget(doubleSpinBox_dY);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_11->addWidget(label_7);

        doubleSpinBox_dZ = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_dZ->setObjectName(QString::fromUtf8("doubleSpinBox_dZ"));

        horizontalLayout_11->addWidget(doubleSpinBox_dZ);


        verticalLayout->addLayout(horizontalLayout_11);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout_21->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_12->addWidget(label_8);

        doubleSpinBox_rX = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_rX->setObjectName(QString::fromUtf8("doubleSpinBox_rX"));

        horizontalLayout_12->addWidget(doubleSpinBox_rX);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_13->addWidget(label_9);

        doubleSpinBox_rY = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_rY->setObjectName(QString::fromUtf8("doubleSpinBox_rY"));

        horizontalLayout_13->addWidget(doubleSpinBox_rY);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_14->addWidget(label_10);

        doubleSpinBox_rZ = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_rZ->setObjectName(QString::fromUtf8("doubleSpinBox_rZ"));

        horizontalLayout_14->addWidget(doubleSpinBox_rZ);


        verticalLayout_2->addLayout(horizontalLayout_14);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);


        horizontalLayout_21->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_11 = new QLabel(groupBox_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_15->addWidget(label_11);

        doubleSpinBox_sX = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_sX->setObjectName(QString::fromUtf8("doubleSpinBox_sX"));
        doubleSpinBox_sX->setValue(1);

        horizontalLayout_15->addWidget(doubleSpinBox_sX);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_12 = new QLabel(groupBox_6);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_16->addWidget(label_12);

        doubleSpinBox_sY = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_sY->setObjectName(QString::fromUtf8("doubleSpinBox_sY"));
        doubleSpinBox_sY->setValue(1);

        horizontalLayout_16->addWidget(doubleSpinBox_sY);


        verticalLayout_4->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_13 = new QLabel(groupBox_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_17->addWidget(label_13);

        doubleSpinBox_sZ = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_sZ->setObjectName(QString::fromUtf8("doubleSpinBox_sZ"));
        doubleSpinBox_sZ->setValue(1);

        horizontalLayout_17->addWidget(doubleSpinBox_sZ);


        verticalLayout_4->addLayout(horizontalLayout_17);


        gridLayout_4->addLayout(verticalLayout_4, 0, 0, 1, 1);


        horizontalLayout_21->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(groupBox_3);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_5 = new QGridLayout(groupBox_7);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_14 = new QLabel(groupBox_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_18->addWidget(label_14);

        doubleSpinBox_sX_2 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_sX_2->setObjectName(QString::fromUtf8("doubleSpinBox_sX_2"));

        horizontalLayout_18->addWidget(doubleSpinBox_sX_2);


        verticalLayout_5->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_15 = new QLabel(groupBox_7);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_19->addWidget(label_15);

        doubleSpinBox_sY_2 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_sY_2->setObjectName(QString::fromUtf8("doubleSpinBox_sY_2"));

        horizontalLayout_19->addWidget(doubleSpinBox_sY_2);


        verticalLayout_5->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_16 = new QLabel(groupBox_7);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_20->addWidget(label_16);

        doubleSpinBox_sZ_2 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_sZ_2->setObjectName(QString::fromUtf8("doubleSpinBox_sZ_2"));

        horizontalLayout_20->addWidget(doubleSpinBox_sZ_2);


        verticalLayout_5->addLayout(horizontalLayout_20);


        gridLayout_5->addLayout(verticalLayout_5, 0, 0, 1, 1);


        horizontalLayout_21->addWidget(groupBox_7);


        gridLayout_7->addLayout(horizontalLayout_21, 0, 0, 1, 1);


        verticalLayout_6->addWidget(groupBox_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        m_btn_add = new QPushButton(groupBox);
        m_btn_add->setObjectName(QString::fromUtf8("m_btn_add"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/movedowm.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btn_add->setIcon(icon1);

        horizontalLayout_7->addWidget(m_btn_add);

        horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_7);


        gridLayout_8->addLayout(verticalLayout_6, 0, 0, 1, 1);


        verticalLayout_7->addWidget(groupBox);

        groupBox_2 = new QGroupBox(FormPartDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_tableWidget_parts = new QTableWidget(groupBox_2);
        if (m_tableWidget_parts->columnCount() < 5)
            m_tableWidget_parts->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_tableWidget_parts->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_tableWidget_parts->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_tableWidget_parts->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        m_tableWidget_parts->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        m_tableWidget_parts->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        m_tableWidget_parts->setObjectName(QString::fromUtf8("m_tableWidget_parts"));
        m_tableWidget_parts->setMinimumSize(QSize(370, 0));
        m_tableWidget_parts->setMaximumSize(QSize(16777215, 120));

        verticalLayout_3->addWidget(m_tableWidget_parts);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_3 = new QSpacerItem(85, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        m_btn_remove = new QPushButton(groupBox_2);
        m_btn_remove->setObjectName(QString::fromUtf8("m_btn_remove"));
        m_btn_remove->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btn_remove->setIcon(icon2);

        horizontalLayout_8->addWidget(m_btn_remove);


        verticalLayout_3->addLayout(horizontalLayout_8);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);


        verticalLayout_7->addWidget(groupBox_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_5 = new QSpacerItem(118, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        m_btn_ok = new QPushButton(FormPartDialog);
        m_btn_ok->setObjectName(QString::fromUtf8("m_btn_ok"));

        horizontalLayout_9->addWidget(m_btn_ok);

        m_btn_cancel = new QPushButton(FormPartDialog);
        m_btn_cancel->setObjectName(QString::fromUtf8("m_btn_cancel"));

        horizontalLayout_9->addWidget(m_btn_cancel);


        verticalLayout_7->addLayout(horizontalLayout_9);


        gridLayout_9->addLayout(verticalLayout_7, 0, 0, 1, 1);


        retranslateUi(FormPartDialog);

        QMetaObject::connectSlotsByName(FormPartDialog);
    } // setupUi

    void retranslateUi(QDialog *FormPartDialog)
    {
        FormPartDialog->setWindowTitle(QApplication::translate("FormPartDialog", "\347\274\226\350\276\221\345\275\242\346\200\201\351\203\250\344\273\266", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FormPartDialog", "\346\226\260\345\273\272\345\275\242\346\200\201\351\203\250\344\273\266", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormPartDialog", "\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        m_lineEdit_name->setText(QString());
        label_2->setText(QApplication::translate("FormPartDialog", "\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        m_comboBox_type->clear();
        m_comboBox_type->insertItems(0, QStringList()
         << QApplication::translate("FormPartDialog", "Image", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "3DModel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "TextureAboveEarth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "Map3D", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "Vector2D", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "DEM", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "Raster2D", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "Raster3D", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "PointCloud", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormPartDialog", "Vector3D", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("FormPartDialog", "\346\240\274\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        m_lineEdit_dataFormat->setText(QString());
        label_4->setText(QApplication::translate("FormPartDialog", "URL\357\274\232", 0, QApplication::UnicodeUTF8));
        m_lineEdit_url->setText(QString());
        m_btn_file->setText(QString());
        groupBox_3->setTitle(QApplication::translate("FormPartDialog", "\345\217\230\346\215\242\347\237\251\351\230\265", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("FormPartDialog", "\345\235\220\346\240\207\345\271\263\347\247\273", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FormPartDialog", "dX", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FormPartDialog", "dY", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FormPartDialog", "dZ", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("FormPartDialog", "\345\235\220\346\240\207\346\227\213\350\275\254", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FormPartDialog", "rX", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FormPartDialog", "rY", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FormPartDialog", "rZ", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("FormPartDialog", "\345\235\220\346\240\207\347\274\251\346\224\276", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("FormPartDialog", "sX", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("FormPartDialog", "sY", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("FormPartDialog", "sZ", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("FormPartDialog", "\345\234\260\347\220\206\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("FormPartDialog", "L", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("FormPartDialog", "B", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("FormPartDialog", "H", 0, QApplication::UnicodeUTF8));
        m_btn_add->setText(QApplication::translate("FormPartDialog", "\346\267\273\345\212\240\345\210\260\345\275\242\346\200\201\351\203\250\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FormPartDialog", "\345\275\242\346\200\201\351\203\250\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget_parts->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FormPartDialog", "\351\203\250\344\273\266\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget_parts->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FormPartDialog", "\351\203\250\344\273\266\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget_parts->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FormPartDialog", "\346\225\260\346\215\256\346\240\274\345\274\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = m_tableWidget_parts->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FormPartDialog", "URL", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = m_tableWidget_parts->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("FormPartDialog", "\345\217\230\346\215\242\347\237\251\351\230\265", 0, QApplication::UnicodeUTF8));
        m_btn_remove->setText(QApplication::translate("FormPartDialog", "\347\247\273\351\231\244\345\275\242\346\200\201\351\203\250\344\273\266", 0, QApplication::UnicodeUTF8));
        m_btn_ok->setText(QApplication::translate("FormPartDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btn_cancel->setText(QApplication::translate("FormPartDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormPartDialog: public Ui_FormPartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMPARTDIALOG_H
