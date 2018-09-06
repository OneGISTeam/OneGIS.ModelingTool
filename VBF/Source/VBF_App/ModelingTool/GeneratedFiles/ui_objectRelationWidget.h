/********************************************************************************
** Form generated from reading UI file 'objectRelationWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTRELATIONWIDGET_H
#define UI_OBJECTRELATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectRelationWidget
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidget_relatedRelations;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBox_relations;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton_selectObject;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox_nodeType;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *doubleSpinBox_intensity;
    QPushButton *pushButton_intensityModel;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QTableWidget *tableWidget_params;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QDateTimeEdit *dateTimeEdit_beginTime;
    QLabel *label_7;
    QDateTimeEdit *dateTimeEdit_endTime;

    void setupUi(QWidget *ObjectRelationWidget)
    {
        if (ObjectRelationWidget->objectName().isEmpty())
            ObjectRelationWidget->setObjectName(QString::fromUtf8("ObjectRelationWidget"));
        ObjectRelationWidget->resize(590, 488);
        gridLayout = new QGridLayout(ObjectRelationWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(ObjectRelationWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 545, 487));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        treeWidget_relatedRelations = new QTreeWidget(groupBox);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/network.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/relation.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/object.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget_relatedRelations);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem3->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget_relatedRelations);
        __qtreewidgetitem4->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem5->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem5);
        __qtreewidgetitem6->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem5);
        __qtreewidgetitem7->setIcon(0, icon2);
        treeWidget_relatedRelations->setObjectName(QString::fromUtf8("treeWidget_relatedRelations"));
        treeWidget_relatedRelations->setWordWrap(false);
        treeWidget_relatedRelations->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget_relatedRelations);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon4);

        verticalLayout_2->addWidget(pushButton_2);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);


        horizontalLayout_8->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        comboBox_relations = new QComboBox(groupBox_2);
        comboBox_relations->addItem(icon, QString());
        comboBox_relations->addItem(icon, QString());
        comboBox_relations->addItem(icon, QString());
        comboBox_relations->addItem(icon, QString());
        comboBox_relations->setObjectName(QString::fromUtf8("comboBox_relations"));

        verticalLayout->addWidget(comboBox_relations);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 24));
        lineEdit->setSizeIncrement(QSize(0, 24));

        horizontalLayout_3->addWidget(lineEdit);

        pushButton_selectObject = new QPushButton(groupBox_2);
        pushButton_selectObject->setObjectName(QString::fromUtf8("pushButton_selectObject"));
        pushButton_selectObject->setMinimumSize(QSize(24, 24));
        pushButton_selectObject->setMaximumSize(QSize(24, 24));
        pushButton_selectObject->setIcon(icon2);
        pushButton_selectObject->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(pushButton_selectObject);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        comboBox_nodeType = new QComboBox(groupBox_2);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ModelingTool/Images/fromNode.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_nodeType->addItem(icon5, QString());
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/ModelingTool/Images/endNode.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox_nodeType->addItem(icon6, QString());
        comboBox_nodeType->setObjectName(QString::fromUtf8("comboBox_nodeType"));

        verticalLayout->addWidget(comboBox_nodeType);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        doubleSpinBox_intensity = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_intensity->setObjectName(QString::fromUtf8("doubleSpinBox_intensity"));
        doubleSpinBox_intensity->setMinimumSize(QSize(0, 24));
        doubleSpinBox_intensity->setMaximumSize(QSize(16777215, 24));
        doubleSpinBox_intensity->setMaximum(1);
        doubleSpinBox_intensity->setSingleStep(0.01);
        doubleSpinBox_intensity->setValue(1);

        horizontalLayout_6->addWidget(doubleSpinBox_intensity);

        pushButton_intensityModel = new QPushButton(groupBox_2);
        pushButton_intensityModel->setObjectName(QString::fromUtf8("pushButton_intensityModel"));
        pushButton_intensityModel->setMinimumSize(QSize(24, 24));
        pushButton_intensityModel->setMaximumSize(QSize(24, 24));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/ModelingTool/Images/mathModel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_intensityModel->setIcon(icon7);
        pushButton_intensityModel->setIconSize(QSize(20, 20));

        horizontalLayout_6->addWidget(pushButton_intensityModel);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_7->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_7);

        tableWidget_params = new QTableWidget(groupBox_2);
        tableWidget_params->setObjectName(QString::fromUtf8("tableWidget_params"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget_params->sizePolicy().hasHeightForWidth());
        tableWidget_params->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(tableWidget_params);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        dateTimeEdit_beginTime = new QDateTimeEdit(groupBox_2);
        dateTimeEdit_beginTime->setObjectName(QString::fromUtf8("dateTimeEdit_beginTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dateTimeEdit_beginTime->sizePolicy().hasHeightForWidth());
        dateTimeEdit_beginTime->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(dateTimeEdit_beginTime, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        dateTimeEdit_endTime = new QDateTimeEdit(groupBox_2);
        dateTimeEdit_endTime->setObjectName(QString::fromUtf8("dateTimeEdit_endTime"));
        sizePolicy1.setHeightForWidth(dateTimeEdit_endTime->sizePolicy().hasHeightForWidth());
        dateTimeEdit_endTime->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(dateTimeEdit_endTime, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout_8->addWidget(groupBox_2);


        gridLayout_5->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ObjectRelationWidget);

        QMetaObject::connectSlotsByName(ObjectRelationWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectRelationWidget)
    {
        ObjectRelationWidget->setWindowTitle(QApplication::translate("ObjectRelationWidget", "\345\257\271\350\261\241\345\205\263\350\201\224\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ObjectRelationWidget", "\346\266\211\345\217\212\350\257\245\345\257\271\350\261\241\347\232\204\345\205\263\350\201\224\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_relatedRelations->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("ObjectRelationWidget", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget_relatedRelations->isSortingEnabled();
        treeWidget_relatedRelations->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_relatedRelations->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("ObjectRelationWidget", "\345\215\217\345\220\214\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("ObjectRelationWidget", "\347\233\26495001->\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("ObjectRelationWidget", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("ObjectRelationWidget", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidget_relatedRelations->topLevelItem(1);
        ___qtreewidgetitem5->setText(0, QApplication::translate("ObjectRelationWidget", "\346\214\207\346\214\245\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(0, QApplication::translate("ObjectRelationWidget", "\347\233\26495002->\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem6->child(0);
        ___qtreewidgetitem7->setText(0, QApplication::translate("ObjectRelationWidget", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem6->child(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("ObjectRelationWidget", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495001", 0, QApplication::UnicodeUTF8));
        treeWidget_relatedRelations->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QApplication::translate("ObjectRelationWidget", "\346\267\273\345\212\240\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ObjectRelationWidget", "\347\247\273\351\231\244\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ObjectRelationWidget", "\345\205\263\350\201\224\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ObjectRelationWidget", "\350\257\267\351\200\211\346\213\251\350\246\201\346\267\273\345\212\240\347\232\204\345\205\263\347\263\273\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_relations->setItemText(0, QApplication::translate("ObjectRelationWidget", "\345\215\217\345\220\214\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        comboBox_relations->setItemText(1, QApplication::translate("ObjectRelationWidget", "\346\214\207\346\214\245\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        comboBox_relations->setItemText(2, QApplication::translate("ObjectRelationWidget", "\344\276\233\347\273\231\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        comboBox_relations->setItemText(3, QApplication::translate("ObjectRelationWidget", "\351\200\232\344\277\241\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));

        label_2->setText(QApplication::translate("ObjectRelationWidget", "\350\257\267\351\200\211\346\213\251\350\246\201\345\273\272\347\253\213\345\205\263\347\263\273\347\232\204\345\257\271\350\261\241\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_selectObject->setText(QString());
        label_3->setText(QApplication::translate("ObjectRelationWidget", "\350\257\267\351\200\211\346\213\251\350\257\245\345\257\271\350\261\241\347\232\204\350\212\202\347\202\271\346\200\247\350\264\250\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_nodeType->setItemText(0, QApplication::translate("ObjectRelationWidget", "\346\272\220\350\212\202\347\202\271", 0, QApplication::UnicodeUTF8));
        comboBox_nodeType->setItemText(1, QApplication::translate("ObjectRelationWidget", "\347\253\257\350\212\202\347\202\271", 0, QApplication::UnicodeUTF8));

        label_4->setText(QApplication::translate("ObjectRelationWidget", "\350\257\267\350\256\276\347\275\256\345\205\263\347\263\273\347\232\204\345\274\272\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_intensityModel->setText(QString());
        label_5->setText(QApplication::translate("ObjectRelationWidget", "\350\257\267\350\256\276\347\275\256\345\205\263\347\263\273\347\232\204\345\217\202\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ObjectRelationWidget", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ObjectRelationWidget", "\347\273\210\346\255\242\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectRelationWidget: public Ui_ObjectRelationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTRELATIONWIDGET_H
