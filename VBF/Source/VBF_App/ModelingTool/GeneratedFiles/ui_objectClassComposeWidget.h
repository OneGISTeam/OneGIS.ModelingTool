/********************************************************************************
** Form generated from reading UI file 'objectClassComposeWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTCLASSCOMPOSEWIDGET_H
#define UI_OBJECTCLASSCOMPOSEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectClassComposeWidget
{
public:
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_addPart;
    QPushButton *pushButton_removePart;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget_2;

    void setupUi(QWidget *ObjectClassComposeWidget)
    {
        if (ObjectClassComposeWidget->objectName().isEmpty())
            ObjectClassComposeWidget->setObjectName(QString::fromUtf8("ObjectClassComposeWidget"));
        ObjectClassComposeWidget->resize(733, 473);
        gridLayout_4 = new QGridLayout(ObjectClassComposeWidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        scrollArea = new QScrollArea(ObjectClassComposeWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 709, 449));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeWidget = new QTreeWidget(groupBox);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/class.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setIcon(0, icon);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->header()->setVisible(true);
        treeWidget->header()->setDefaultSectionSize(100);

        gridLayout_2->addWidget(treeWidget, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton_addPart = new QPushButton(scrollAreaWidgetContents);
        pushButton_addPart->setObjectName(QString::fromUtf8("pushButton_addPart"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_addPart->setIcon(icon1);

        verticalLayout->addWidget(pushButton_addPart);

        pushButton_removePart = new QPushButton(scrollAreaWidgetContents);
        pushButton_removePart->setObjectName(QString::fromUtf8("pushButton_removePart"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_removePart->setIcon(icon2);

        verticalLayout->addWidget(pushButton_removePart);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeWidget_2 = new QTreeWidget(groupBox_2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/object.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget_2);
        __qtreewidgetitem2->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem3->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem4->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem5->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem6->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem7->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem8->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem2);
        __qtreewidgetitem9->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem9);
        __qtreewidgetitem10->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem9);
        __qtreewidgetitem11->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(__qtreewidgetitem9);
        __qtreewidgetitem12->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem9);
        __qtreewidgetitem13->setIcon(0, icon3);
        treeWidget_2->setObjectName(QString::fromUtf8("treeWidget_2"));
        treeWidget_2->header()->setVisible(false);

        gridLayout->addWidget(treeWidget_2, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ObjectClassComposeWidget);

        QMetaObject::connectSlotsByName(ObjectClassComposeWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectClassComposeWidget)
    {
        ObjectClassComposeWidget->setWindowTitle(QApplication::translate("ObjectClassComposeWidget", "\345\257\271\350\261\241\347\261\273\347\273\204\346\210\220\347\273\223\346\236\204", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ObjectClassComposeWidget", "\345\267\262\346\234\211\347\273\204\346\210\220\345\255\220\347\261\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("ObjectClassComposeWidget", "\347\273\204\346\210\220\347\261\273\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("ObjectClassComposeWidget", "\347\273\204\346\210\220\347\261\273\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(1, QApplication::translate("ObjectClassComposeWidget", "C201113", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\234\272\350\272\253", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(1, QApplication::translate("ObjectClassComposeWidget", "C201488", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\234\272\347\277\274", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        pushButton_addPart->setText(QString());
        pushButton_removePart->setText(QString());
        groupBox_2->setTitle(QApplication::translate("ObjectClassComposeWidget", "\347\261\273\350\247\206\345\233\276", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget_2->headerItem();
        ___qtreewidgetitem3->setText(0, QApplication::translate("ObjectClassComposeWidget", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = treeWidget_2->isSortingEnabled();
        treeWidget_2->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget_2->topLevelItem(0);
        ___qtreewidgetitem4->setText(0, QApplication::translate("ObjectClassComposeWidget", "\351\243\236\346\234\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\255\274\345\207\273\346\234\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\234\272\350\272\253", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem5->child(1);
        ___qtreewidgetitem7->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\234\272\347\277\274", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem5->child(2);
        ___qtreewidgetitem8->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\255\274\345\207\273\346\234\272001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem5->child(3);
        ___qtreewidgetitem9->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\255\274\345\207\273\346\234\272002", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem5->child(4);
        ___qtreewidgetitem10->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\255\274\345\207\273\346\234\272003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem4->child(1);
        ___qtreewidgetitem11->setText(0, QApplication::translate("ObjectClassComposeWidget", "\351\242\204\350\255\246\346\234\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem11->child(0);
        ___qtreewidgetitem12->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\234\272\350\272\253", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem11->child(1);
        ___qtreewidgetitem13->setText(0, QApplication::translate("ObjectClassComposeWidget", "\346\234\272\347\277\274", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem11->child(2);
        ___qtreewidgetitem14->setText(0, QApplication::translate("ObjectClassComposeWidget", "\351\242\204\350\255\246\346\234\272001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem11->child(3);
        ___qtreewidgetitem15->setText(0, QApplication::translate("ObjectClassComposeWidget", "\351\242\204\350\255\246\346\234\272002", 0, QApplication::UnicodeUTF8));
        treeWidget_2->setSortingEnabled(__sortingEnabled1);

    } // retranslateUi

};

namespace Ui {
    class ObjectClassComposeWidget: public Ui_ObjectClassComposeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTCLASSCOMPOSEWIDGET_H
