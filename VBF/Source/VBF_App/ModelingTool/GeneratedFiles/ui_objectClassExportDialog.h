/********************************************************************************
** Form generated from reading UI file 'objectClassExportDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTCLASSEXPORTDIALOG_H
#define UI_OBJECTCLASSEXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ObjectClassExportDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton_path;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *ObjectClassExportDialog)
    {
        if (ObjectClassExportDialog->objectName().isEmpty())
            ObjectClassExportDialog->setObjectName(QString::fromUtf8("ObjectClassExportDialog"));
        ObjectClassExportDialog->resize(350, 240);
        gridLayout = new QGridLayout(ObjectClassExportDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ObjectClassExportDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(ObjectClassExportDialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/class.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setCheckState(0, Qt::Checked);
        __qtreewidgetitem1->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem2->setCheckState(0, Qt::Checked);
        __qtreewidgetitem2->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem3->setCheckState(0, Qt::Checked);
        __qtreewidgetitem3->setIcon(0, icon);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ObjectClassExportDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit = new QLineEdit(ObjectClassExportDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(lineEdit);

        pushButton_path = new QPushButton(ObjectClassExportDialog);
        pushButton_path->setObjectName(QString::fromUtf8("pushButton_path"));
        pushButton_path->setMinimumSize(QSize(30, 30));
        pushButton_path->setSizeIncrement(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_path->setIcon(icon1);
        pushButton_path->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButton_path);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        pushButton_ok = new QPushButton(ObjectClassExportDialog);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        horizontalLayout_4->addWidget(pushButton_ok);

        pushButton_cancel = new QPushButton(ObjectClassExportDialog);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_4->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(ObjectClassExportDialog);

        QMetaObject::connectSlotsByName(ObjectClassExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ObjectClassExportDialog)
    {
        ObjectClassExportDialog->setWindowTitle(QApplication::translate("ObjectClassExportDialog", "\345\257\274\345\207\272\345\257\271\350\261\241\347\261\273\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ObjectClassExportDialog", "\351\200\211\346\213\251\350\246\201\345\257\274\345\207\272\347\232\204\345\257\271\350\261\241\347\261\273\357\274\232", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("ObjectClassExportDialog", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("ObjectClassExportDialog", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("ObjectClassExportDialog", "\345\257\271\350\261\241\347\261\273A", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("ObjectClassExportDialog", "\345\257\271\350\261\241\347\261\273B", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("ObjectClassExportDialog", "\345\257\271\350\261\241\347\261\273C", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        label_2->setText(QApplication::translate("ObjectClassExportDialog", "\351\200\211\346\213\251\345\257\274\345\207\272\344\275\215\347\275\256\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_path->setText(QString());
        pushButton_ok->setText(QApplication::translate("ObjectClassExportDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("ObjectClassExportDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectClassExportDialog: public Ui_ObjectClassExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTCLASSEXPORTDIALOG_H
