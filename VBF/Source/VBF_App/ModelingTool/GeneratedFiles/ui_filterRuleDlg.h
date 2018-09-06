/********************************************************************************
** Form generated from reading UI file 'filterRuleDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERRULEDLG_H
#define UI_FILTERRULEDLG_H

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
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_C_DialogFilterRule
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *m_label_2;
    QHBoxLayout *horizontalLayout_6;
    QListWidget *m_listWidget;
    QGroupBox *m_groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *m_btn_1;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_btn_2;
    QPushButton *m_btn_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_btn_4;
    QPushButton *m_btn_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btn_6;
    QPushButton *m_btn_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *m_label_set;
    QLineEdit *m_lineEdit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *m_btn_clear;
    QPushButton *m_btn_save;

    void setupUi(QDialog *C_DialogFilterRule)
    {
        if (C_DialogFilterRule->objectName().isEmpty())
            C_DialogFilterRule->setObjectName(QString::fromUtf8("C_DialogFilterRule"));
        C_DialogFilterRule->resize(320, 360);
        C_DialogFilterRule->setMinimumSize(QSize(320, 360));
        C_DialogFilterRule->setMaximumSize(QSize(320, 360));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/conversionMap.png"), QSize(), QIcon::Normal, QIcon::Off);
        C_DialogFilterRule->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(C_DialogFilterRule);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_label_2 = new QLabel(C_DialogFilterRule);
        m_label_2->setObjectName(QString::fromUtf8("m_label_2"));
        m_label_2->setMinimumSize(QSize(0, 36));
        m_label_2->setWordWrap(true);

        verticalLayout_3->addWidget(m_label_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_listWidget = new QListWidget(C_DialogFilterRule);
        m_listWidget->setObjectName(QString::fromUtf8("m_listWidget"));
        m_listWidget->setMaximumSize(QSize(180, 16777215));

        horizontalLayout_6->addWidget(m_listWidget);

        m_groupBox = new QGroupBox(C_DialogFilterRule);
        m_groupBox->setObjectName(QString::fromUtf8("m_groupBox"));
        gridLayout = new QGridLayout(m_groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_btn_1 = new QPushButton(m_groupBox);
        m_btn_1->setObjectName(QString::fromUtf8("m_btn_1"));
        m_btn_1->setMinimumSize(QSize(30, 25));
        m_btn_1->setMaximumSize(QSize(30, 25));

        verticalLayout->addWidget(m_btn_1, 0, Qt::AlignHCenter);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_btn_2 = new QPushButton(m_groupBox);
        m_btn_2->setObjectName(QString::fromUtf8("m_btn_2"));
        m_btn_2->setMinimumSize(QSize(30, 25));
        m_btn_2->setMaximumSize(QSize(30, 25));

        horizontalLayout_3->addWidget(m_btn_2);

        m_btn_3 = new QPushButton(m_groupBox);
        m_btn_3->setObjectName(QString::fromUtf8("m_btn_3"));
        m_btn_3->setMinimumSize(QSize(30, 25));
        m_btn_3->setMaximumSize(QSize(30, 25));

        horizontalLayout_3->addWidget(m_btn_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_btn_4 = new QPushButton(m_groupBox);
        m_btn_4->setObjectName(QString::fromUtf8("m_btn_4"));
        m_btn_4->setMinimumSize(QSize(30, 25));
        m_btn_4->setMaximumSize(QSize(30, 25));

        horizontalLayout_2->addWidget(m_btn_4);

        m_btn_5 = new QPushButton(m_groupBox);
        m_btn_5->setObjectName(QString::fromUtf8("m_btn_5"));
        m_btn_5->setMinimumSize(QSize(30, 25));
        m_btn_5->setMaximumSize(QSize(30, 25));

        horizontalLayout_2->addWidget(m_btn_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_btn_6 = new QPushButton(m_groupBox);
        m_btn_6->setObjectName(QString::fromUtf8("m_btn_6"));
        m_btn_6->setMinimumSize(QSize(30, 25));
        m_btn_6->setMaximumSize(QSize(30, 25));

        horizontalLayout->addWidget(m_btn_6);

        m_btn_7 = new QPushButton(m_groupBox);
        m_btn_7->setObjectName(QString::fromUtf8("m_btn_7"));
        m_btn_7->setMinimumSize(QSize(30, 25));
        m_btn_7->setMaximumSize(QSize(30, 25));

        horizontalLayout->addWidget(m_btn_7);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(m_groupBox);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_label_set = new QLabel(C_DialogFilterRule);
        m_label_set->setObjectName(QString::fromUtf8("m_label_set"));
        m_label_set->setMinimumSize(QSize(0, 15));

        verticalLayout_2->addWidget(m_label_set);

        m_lineEdit = new QLineEdit(C_DialogFilterRule);
        m_lineEdit->setObjectName(QString::fromUtf8("m_lineEdit"));
        m_lineEdit->setMinimumSize(QSize(0, 50));

        verticalLayout_2->addWidget(m_lineEdit);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_btn_clear = new QPushButton(C_DialogFilterRule);
        m_btn_clear->setObjectName(QString::fromUtf8("m_btn_clear"));

        horizontalLayout_4->addWidget(m_btn_clear);

        m_btn_save = new QPushButton(C_DialogFilterRule);
        m_btn_save->setObjectName(QString::fromUtf8("m_btn_save"));

        horizontalLayout_4->addWidget(m_btn_save);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout_5);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(C_DialogFilterRule);

        QMetaObject::connectSlotsByName(C_DialogFilterRule);
    } // setupUi

    void retranslateUi(QDialog *C_DialogFilterRule)
    {
        C_DialogFilterRule->setWindowTitle(QApplication::translate("C_DialogFilterRule", "\350\256\276\347\275\256\350\277\207\346\273\244\350\247\204\345\210\231", 0, QApplication::UnicodeUTF8));
        m_label_2->setText(QApplication::translate("C_DialogFilterRule", "    \346\240\271\346\215\256\346\225\260\346\215\256\346\272\220\345\261\236\346\200\247\345\255\227\346\256\265\345\217\226\345\200\274\350\277\233\350\241\214\350\277\207\346\273\244\357\274\214\345\275\223\346\273\241\350\266\263\350\277\207\346\273\244\346\235\241\344\273\266\346\227\266\346\211\215\350\203\275\350\275\254\346\215\242\344\270\272\345\257\271\350\261\241\343\200\202", 0, QApplication::UnicodeUTF8));
        m_groupBox->setTitle(QApplication::translate("C_DialogFilterRule", "\346\223\215\344\275\234\347\254\246", 0, QApplication::UnicodeUTF8));
        m_btn_1->setText(QApplication::translate("C_DialogFilterRule", "=", 0, QApplication::UnicodeUTF8));
        m_btn_2->setText(QApplication::translate("C_DialogFilterRule", ">", 0, QApplication::UnicodeUTF8));
        m_btn_3->setText(QApplication::translate("C_DialogFilterRule", "<", 0, QApplication::UnicodeUTF8));
        m_btn_4->setText(QApplication::translate("C_DialogFilterRule", ">=", 0, QApplication::UnicodeUTF8));
        m_btn_5->setText(QApplication::translate("C_DialogFilterRule", "<=", 0, QApplication::UnicodeUTF8));
        m_btn_6->setText(QApplication::translate("C_DialogFilterRule", "&&", 0, QApplication::UnicodeUTF8));
        m_btn_7->setText(QApplication::translate("C_DialogFilterRule", "||", 0, QApplication::UnicodeUTF8));
        m_label_set->setText(QApplication::translate("C_DialogFilterRule", "Select * From ", 0, QApplication::UnicodeUTF8));
        m_btn_clear->setText(QApplication::translate("C_DialogFilterRule", "\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
        m_btn_save->setText(QApplication::translate("C_DialogFilterRule", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class C_DialogFilterRule: public Ui_C_DialogFilterRule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERRULEDLG_H
