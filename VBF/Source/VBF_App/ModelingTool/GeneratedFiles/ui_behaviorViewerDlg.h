/********************************************************************************
** Form generated from reading UI file 'behaviorViewerDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEHAVIORVIEWERDLG_H
#define UI_BEHAVIORVIEWERDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_C_DialogBehaviorViewer
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *m_label_path;
    QTreeWidget *m_treeWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btn_addPath;
    QPushButton *m_btn_removePath;
    QPushButton *m_btn_search;
    QGroupBox *m_groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *m_label_id;
    QLineEdit *m_lineEdit_id;
    QVBoxLayout *verticalLayout_3;
    QLabel *m_label_name;
    QLineEdit *m_lineEdit_name;
    QVBoxLayout *verticalLayout_4;
    QLabel *m_label_des;
    QLineEdit *m_lineEdit_des;
    QVBoxLayout *verticalLayout_6;
    QLabel *m_label_list;
    QTableWidget *m_tableWidget;
    QPushButton *m_btn_ok;

    void setupUi(QDialog *C_DialogBehaviorViewer)
    {
        if (C_DialogBehaviorViewer->objectName().isEmpty())
            C_DialogBehaviorViewer->setObjectName(QString::fromUtf8("C_DialogBehaviorViewer"));
        C_DialogBehaviorViewer->resize(508, 480);
        gridLayout_2 = new QGridLayout(C_DialogBehaviorViewer);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_label_path = new QLabel(C_DialogBehaviorViewer);
        m_label_path->setObjectName(QString::fromUtf8("m_label_path"));

        verticalLayout->addWidget(m_label_path);

        m_treeWidget = new QTreeWidget(C_DialogBehaviorViewer);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/openProject.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setIcon(0, icon);
        m_treeWidget->setHeaderItem(__qtreewidgetitem);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/behaviorComponent.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(m_treeWidget);
        __qtreewidgetitem1->setIcon(0, icon1);
        m_treeWidget->setObjectName(QString::fromUtf8("m_treeWidget"));

        verticalLayout->addWidget(m_treeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btn_addPath = new QPushButton(C_DialogBehaviorViewer);
        m_btn_addPath->setObjectName(QString::fromUtf8("m_btn_addPath"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/PostionPointAdd.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btn_addPath->setIcon(icon2);

        horizontalLayout->addWidget(m_btn_addPath);

        m_btn_removePath = new QPushButton(C_DialogBehaviorViewer);
        m_btn_removePath->setObjectName(QString::fromUtf8("m_btn_removePath"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ModelingTool/Images/PostionPointRemove.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btn_removePath->setIcon(icon3);

        horizontalLayout->addWidget(m_btn_removePath);

        m_btn_search = new QPushButton(C_DialogBehaviorViewer);
        m_btn_search->setObjectName(QString::fromUtf8("m_btn_search"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ModelingTool/Images/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btn_search->setIcon(icon4);

        horizontalLayout->addWidget(m_btn_search);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        m_groupBox = new QGroupBox(C_DialogBehaviorViewer);
        m_groupBox->setObjectName(QString::fromUtf8("m_groupBox"));
        gridLayout = new QGridLayout(m_groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_label_id = new QLabel(m_groupBox);
        m_label_id->setObjectName(QString::fromUtf8("m_label_id"));
        m_label_id->setMinimumSize(QSize(0, 20));
        m_label_id->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(m_label_id);

        m_lineEdit_id = new QLineEdit(m_groupBox);
        m_lineEdit_id->setObjectName(QString::fromUtf8("m_lineEdit_id"));

        verticalLayout_2->addWidget(m_lineEdit_id);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_label_name = new QLabel(m_groupBox);
        m_label_name->setObjectName(QString::fromUtf8("m_label_name"));
        m_label_name->setMinimumSize(QSize(0, 20));
        m_label_name->setMaximumSize(QSize(16777215, 20));

        verticalLayout_3->addWidget(m_label_name);

        m_lineEdit_name = new QLineEdit(m_groupBox);
        m_lineEdit_name->setObjectName(QString::fromUtf8("m_lineEdit_name"));

        verticalLayout_3->addWidget(m_lineEdit_name);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        m_label_des = new QLabel(m_groupBox);
        m_label_des->setObjectName(QString::fromUtf8("m_label_des"));
        m_label_des->setMinimumSize(QSize(0, 20));
        m_label_des->setMaximumSize(QSize(16777215, 20));

        verticalLayout_4->addWidget(m_label_des);

        m_lineEdit_des = new QLineEdit(m_groupBox);
        m_lineEdit_des->setObjectName(QString::fromUtf8("m_lineEdit_des"));
        m_lineEdit_des->setMinimumSize(QSize(150, 40));

        verticalLayout_4->addWidget(m_lineEdit_des);


        verticalLayout_5->addLayout(verticalLayout_4);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(m_groupBox);


        verticalLayout_7->addLayout(horizontalLayout_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        m_label_list = new QLabel(C_DialogBehaviorViewer);
        m_label_list->setObjectName(QString::fromUtf8("m_label_list"));

        verticalLayout_6->addWidget(m_label_list);

        m_tableWidget = new QTableWidget(C_DialogBehaviorViewer);
        if (m_tableWidget->columnCount() < 4)
            m_tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        m_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        m_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        m_tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        m_tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        m_tableWidget->setObjectName(QString::fromUtf8("m_tableWidget"));

        verticalLayout_6->addWidget(m_tableWidget);


        verticalLayout_7->addLayout(verticalLayout_6);

        m_btn_ok = new QPushButton(C_DialogBehaviorViewer);
        m_btn_ok->setObjectName(QString::fromUtf8("m_btn_ok"));
        m_btn_ok->setMaximumSize(QSize(70, 16777215));

        verticalLayout_7->addWidget(m_btn_ok, 0, Qt::AlignHCenter);


        gridLayout_2->addLayout(verticalLayout_7, 0, 0, 1, 1);


        retranslateUi(C_DialogBehaviorViewer);

        QMetaObject::connectSlotsByName(C_DialogBehaviorViewer);
    } // setupUi

    void retranslateUi(QDialog *C_DialogBehaviorViewer)
    {
        C_DialogBehaviorViewer->setWindowTitle(QApplication::translate("C_DialogBehaviorViewer", "\346\237\245\347\234\213\350\241\214\344\270\272\347\273\204\344\273\266\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        m_label_path->setText(QApplication::translate("C_DialogBehaviorViewer", "\350\241\214\344\270\272\347\273\204\344\273\266\350\267\257\345\276\204\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = m_treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("C_DialogBehaviorViewer", "D://OneGIS.ModelingTool", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = m_treeWidget->isSortingEnabled();
        m_treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = m_treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("C_DialogBehaviorViewer", "flyComponent", 0, QApplication::UnicodeUTF8));
        m_treeWidget->setSortingEnabled(__sortingEnabled);

        m_btn_addPath->setText(QApplication::translate("C_DialogBehaviorViewer", "\346\267\273\345\212\240\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        m_btn_removePath->setText(QApplication::translate("C_DialogBehaviorViewer", "\345\210\240\351\231\244\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        m_btn_search->setText(QApplication::translate("C_DialogBehaviorViewer", "\351\207\215\346\226\260\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        m_groupBox->setTitle(QApplication::translate("C_DialogBehaviorViewer", "\350\241\214\344\270\272\347\273\204\344\273\266\345\237\272\346\234\254\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        m_label_id->setText(QApplication::translate("C_DialogBehaviorViewer", "\347\261\273\345\210\253\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        m_label_name->setText(QApplication::translate("C_DialogBehaviorViewer", "\347\273\204\344\273\266\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        m_label_des->setText(QApplication::translate("C_DialogBehaviorViewer", "\347\273\204\344\273\266\346\217\217\350\277\260", 0, QApplication::UnicodeUTF8));
        m_label_list->setText(QApplication::translate("C_DialogBehaviorViewer", "\350\241\214\344\270\272\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = m_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("C_DialogBehaviorViewer", "\350\241\214\344\270\272\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = m_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("C_DialogBehaviorViewer", "\350\241\214\344\270\272\346\217\217\350\277\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = m_tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("C_DialogBehaviorViewer", "\345\217\202\346\225\260\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = m_tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("C_DialogBehaviorViewer", "\350\276\223\345\205\245\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        m_btn_ok->setText(QApplication::translate("C_DialogBehaviorViewer", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class C_DialogBehaviorViewer: public Ui_C_DialogBehaviorViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEHAVIORVIEWERDLG_H
