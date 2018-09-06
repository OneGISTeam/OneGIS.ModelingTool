/********************************************************************************
** Form generated from reading UI file 'objectPositionWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTPOSITIONWIDGET_H
#define UI_OBJECTPOSITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectPositionWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QComboBox *cbTimeFormat;
    QLabel *sRefLabel_3;
    QComboBox *cbSpatialFormat;
    QLabel *trLabel;
    QLabel *sRefLabel_2;
    QComboBox *cbTimeRef;
    QLabel *sRefLabel;
    QComboBox *cbSpatialRef;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *PostionTable;
    QVBoxLayout *verticalLayout_3;
    QPushButton *PathImportBtn;
    QPushButton *PointEmptyBtn;
    QPushButton *PointAddBtn;
    QPushButton *PointDeleteBtn;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *orbitRadio;
    QRadioButton *dynamicPosRadio;
    QPushButton *OrbitBtn;
    QPushButton *DynamicPosBtn;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *ObjectPositionWidget)
    {
        if (ObjectPositionWidget->objectName().isEmpty())
            ObjectPositionWidget->setObjectName(QString::fromUtf8("ObjectPositionWidget"));
        ObjectPositionWidget->resize(584, 557);
        verticalLayout_4 = new QVBoxLayout(ObjectPositionWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea = new QScrollArea(ObjectPositionWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 560, 533));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbTimeFormat = new QComboBox(groupBox_2);
        cbTimeFormat->setObjectName(QString::fromUtf8("cbTimeFormat"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbTimeFormat->sizePolicy().hasHeightForWidth());
        cbTimeFormat->setSizePolicy(sizePolicy);
        cbTimeFormat->setMinimumSize(QSize(60, 0));
        cbTimeFormat->setInsertPolicy(QComboBox::NoInsert);

        gridLayout->addWidget(cbTimeFormat, 0, 3, 1, 1);

        sRefLabel_3 = new QLabel(groupBox_2);
        sRefLabel_3->setObjectName(QString::fromUtf8("sRefLabel_3"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        sRefLabel_3->setFont(font);

        gridLayout->addWidget(sRefLabel_3, 3, 2, 1, 1);

        cbSpatialFormat = new QComboBox(groupBox_2);
        cbSpatialFormat->setObjectName(QString::fromUtf8("cbSpatialFormat"));
        sizePolicy.setHeightForWidth(cbSpatialFormat->sizePolicy().hasHeightForWidth());
        cbSpatialFormat->setSizePolicy(sizePolicy);

        gridLayout->addWidget(cbSpatialFormat, 3, 3, 1, 1);

        trLabel = new QLabel(groupBox_2);
        trLabel->setObjectName(QString::fromUtf8("trLabel"));
        trLabel->setFont(font);

        gridLayout->addWidget(trLabel, 0, 2, 1, 1);

        sRefLabel_2 = new QLabel(groupBox_2);
        sRefLabel_2->setObjectName(QString::fromUtf8("sRefLabel_2"));
        sRefLabel_2->setFont(font);

        gridLayout->addWidget(sRefLabel_2, 0, 0, 1, 1);

        cbTimeRef = new QComboBox(groupBox_2);
        cbTimeRef->setObjectName(QString::fromUtf8("cbTimeRef"));
        sizePolicy.setHeightForWidth(cbTimeRef->sizePolicy().hasHeightForWidth());
        cbTimeRef->setSizePolicy(sizePolicy);
        cbTimeRef->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(cbTimeRef, 0, 1, 1, 1);

        sRefLabel = new QLabel(groupBox_2);
        sRefLabel->setObjectName(QString::fromUtf8("sRefLabel"));
        sRefLabel->setFont(font);

        gridLayout->addWidget(sRefLabel, 3, 0, 1, 1);

        cbSpatialRef = new QComboBox(groupBox_2);
        cbSpatialRef->setObjectName(QString::fromUtf8("cbSpatialRef"));
        sizePolicy.setHeightForWidth(cbSpatialRef->sizePolicy().hasHeightForWidth());
        cbSpatialRef->setSizePolicy(sizePolicy);

        gridLayout->addWidget(cbSpatialRef, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 4, 1, 1);

        cbSpatialRef->raise();
        sRefLabel->raise();
        cbTimeRef->raise();
        sRefLabel_2->raise();
        trLabel->raise();
        cbTimeFormat->raise();
        sRefLabel_3->raise();
        cbSpatialFormat->raise();

        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        PostionTable = new QTableWidget(groupBox_3);
        if (PostionTable->columnCount() < 7)
            PostionTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        PostionTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        PostionTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        PostionTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        PostionTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        PostionTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        PostionTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        PostionTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (PostionTable->rowCount() < 5)
            PostionTable->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        PostionTable->setVerticalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        PostionTable->setVerticalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        PostionTable->setVerticalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        PostionTable->setVerticalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        PostionTable->setVerticalHeaderItem(4, __qtablewidgetitem11);
        PostionTable->setObjectName(QString::fromUtf8("PostionTable"));

        horizontalLayout_3->addWidget(PostionTable);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        PathImportBtn = new QPushButton(groupBox_3);
        PathImportBtn->setObjectName(QString::fromUtf8("PathImportBtn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/PostionPathImport.ico"), QSize(), QIcon::Normal, QIcon::Off);
        PathImportBtn->setIcon(icon);

        verticalLayout_3->addWidget(PathImportBtn);

        PointEmptyBtn = new QPushButton(groupBox_3);
        PointEmptyBtn->setObjectName(QString::fromUtf8("PointEmptyBtn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/PostionPathEmpty.png"), QSize(), QIcon::Normal, QIcon::Off);
        PointEmptyBtn->setIcon(icon1);

        verticalLayout_3->addWidget(PointEmptyBtn);

        PointAddBtn = new QPushButton(groupBox_3);
        PointAddBtn->setObjectName(QString::fromUtf8("PointAddBtn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/PostionPointAdd.png"), QSize(), QIcon::Normal, QIcon::Off);
        PointAddBtn->setIcon(icon2);

        verticalLayout_3->addWidget(PointAddBtn);

        PointDeleteBtn = new QPushButton(groupBox_3);
        PointDeleteBtn->setObjectName(QString::fromUtf8("PointDeleteBtn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/PostionPointRemove.png"), QSize(), QIcon::Normal, QIcon::Off);
        PointDeleteBtn->setIcon(icon3);

        verticalLayout_3->addWidget(PointDeleteBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        orbitRadio = new QRadioButton(groupBox);
        orbitRadio->setObjectName(QString::fromUtf8("orbitRadio"));
        orbitRadio->setFont(font);

        horizontalLayout_2->addWidget(orbitRadio);

        dynamicPosRadio = new QRadioButton(groupBox);
        dynamicPosRadio->setObjectName(QString::fromUtf8("dynamicPosRadio"));
        dynamicPosRadio->setFont(font);

        horizontalLayout_2->addWidget(dynamicPosRadio);

        OrbitBtn = new QPushButton(groupBox);
        OrbitBtn->setObjectName(QString::fromUtf8("OrbitBtn"));

        horizontalLayout_2->addWidget(OrbitBtn);

        DynamicPosBtn = new QPushButton(groupBox);
        DynamicPosBtn->setObjectName(QString::fromUtf8("DynamicPosBtn"));

        horizontalLayout_2->addWidget(DynamicPosBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);


        retranslateUi(ObjectPositionWidget);

        QMetaObject::connectSlotsByName(ObjectPositionWidget);
    } // setupUi

    void retranslateUi(QDialog *ObjectPositionWidget)
    {
        ObjectPositionWidget->setWindowTitle(QApplication::translate("ObjectPositionWidget", "C_WidgetPosition", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ObjectPositionWidget", "\345\235\220\346\240\207\345\217\202\350\200\203\345\217\212\346\240\274\345\274\217", 0, QApplication::UnicodeUTF8));
        cbTimeFormat->clear();
        cbTimeFormat->insertItems(0, QStringList()
         << QApplication::translate("ObjectPositionWidget", "yyyy-MM-dd hh:mm:ss", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ObjectPositionWidget", "double", 0, QApplication::UnicodeUTF8)
        );
        sRefLabel_3->setText(QApplication::translate("ObjectPositionWidget", "\345\235\220\346\240\207\346\240\274\345\274\217", 0, QApplication::UnicodeUTF8));
        cbSpatialFormat->clear();
        cbSpatialFormat->insertItems(0, QStringList()
         << QApplication::translate("ObjectPositionWidget", "X Y Z", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ObjectPositionWidget", "L B H", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ObjectPositionWidget", "X Y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ObjectPositionWidget", "L B", 0, QApplication::UnicodeUTF8)
        );
        trLabel->setText(QApplication::translate("ObjectPositionWidget", "\346\227\266\351\227\264\346\240\274\345\274\217", 0, QApplication::UnicodeUTF8));
        sRefLabel_2->setText(QApplication::translate("ObjectPositionWidget", "\346\227\266\351\227\264\345\217\202\350\200\203", 0, QApplication::UnicodeUTF8));
        sRefLabel->setText(QApplication::translate("ObjectPositionWidget", "\347\251\272\351\227\264\345\217\202\350\200\203", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ObjectPositionWidget", "\345\235\220\346\240\207\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = PostionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ObjectPositionWidget", "\346\227\266\351\227\264\345\200\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = PostionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ObjectPositionWidget", "L", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = PostionTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ObjectPositionWidget", "B", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = PostionTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ObjectPositionWidget", "H", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = PostionTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("ObjectPositionWidget", "rx", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = PostionTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("ObjectPositionWidget", "ry", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = PostionTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("ObjectPositionWidget", "rz", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = PostionTable->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("ObjectPositionWidget", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = PostionTable->verticalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("ObjectPositionWidget", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = PostionTable->verticalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("ObjectPositionWidget", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = PostionTable->verticalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("ObjectPositionWidget", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = PostionTable->verticalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("ObjectPositionWidget", "5", 0, QApplication::UnicodeUTF8));
        PathImportBtn->setText(QApplication::translate("ObjectPositionWidget", "\345\257\274\345\205\245\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        PointEmptyBtn->setText(QApplication::translate("ObjectPositionWidget", "\346\270\205\347\251\272\347\202\271", 0, QApplication::UnicodeUTF8));
        PointAddBtn->setText(QApplication::translate("ObjectPositionWidget", "\345\242\236\345\212\240\347\202\271", 0, QApplication::UnicodeUTF8));
        PointDeleteBtn->setText(QApplication::translate("ObjectPositionWidget", "\345\210\240\351\231\244\347\202\271", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ObjectPositionWidget", "\345\205\266\345\256\203", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ObjectPositionWidget", "\350\257\245\345\212\237\350\203\275\344\270\272\344\277\235\347\225\231\357\274\214\347\224\250\344\272\216\350\256\276\347\275\256\344\273\245\350\275\250\351\201\223\345\217\202\346\225\260\350\256\241\347\256\227\344\275\215\347\275\256\345\222\214\345\205\263\350\201\224\345\236\213\345\212\250\346\200\201\350\256\241\347\256\227\344\275\215\347\275\256\347\232\204\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        orbitRadio->setText(QApplication::translate("ObjectPositionWidget", "\350\275\250\351\201\223", 0, QApplication::UnicodeUTF8));
        dynamicPosRadio->setText(QApplication::translate("ObjectPositionWidget", "\345\205\263\350\201\224", 0, QApplication::UnicodeUTF8));
        OrbitBtn->setText(QApplication::translate("ObjectPositionWidget", "\350\275\250\351\201\223\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        DynamicPosBtn->setText(QApplication::translate("ObjectPositionWidget", "\345\205\263\350\201\224\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectPositionWidget: public Ui_ObjectPositionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTPOSITIONWIDGET_H
