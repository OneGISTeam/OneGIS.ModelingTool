/********************************************************************************
** Form generated from reading UI file 'mergeRuleDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MERGERULEDLG_H
#define UI_MERGERULEDLG_H

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
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_C_DialogMergeRule
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QGroupBox *m_groupBox_pos;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_label_range;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *m_doubleSpinBox_H;
    QHBoxLayout *horizontalLayout_8;
    QLabel *m_label_range_2;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *m_doubleSpinBox_W;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *m_groupBox_field;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_label_main1;
    QComboBox *m_comboBox_main;
    QHBoxLayout *horizontalLayout_10;
    QLabel *m_label_ass1;
    QComboBox *m_comboBox_ass;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_label_simiField;
    QSpinBox *m_spinBox_field;
    QGroupBox *m_groupBox_form;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_label_ll;
    QSpinBox *m_spinBox_ll;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_label_la;
    QSpinBox *m_spinBox_la;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_label_aa;
    QSpinBox *m_spinBox_aa;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *m_btn_ok;
    QPushButton *m_btn_cancel;

    void setupUi(QDialog *C_DialogMergeRule)
    {
        if (C_DialogMergeRule->objectName().isEmpty())
            C_DialogMergeRule->setObjectName(QString::fromUtf8("C_DialogMergeRule"));
        C_DialogMergeRule->resize(360, 390);
        C_DialogMergeRule->setMinimumSize(QSize(360, 390));
        C_DialogMergeRule->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/conversionMap.png"), QSize(), QIcon::Normal, QIcon::Off);
        C_DialogMergeRule->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(C_DialogMergeRule);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(9, 9, 9, 9);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(9);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(C_DialogMergeRule);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 45));
        label->setMaximumSize(QSize(16777215, 45));
        label->setWordWrap(true);

        verticalLayout_3->addWidget(label);

        m_groupBox_pos = new QGroupBox(C_DialogMergeRule);
        m_groupBox_pos->setObjectName(QString::fromUtf8("m_groupBox_pos"));
        m_groupBox_pos->setMinimumSize(QSize(0, 60));
        m_groupBox_pos->setMaximumSize(QSize(16777215, 16777215));
        m_groupBox_pos->setCheckable(true);
        gridLayout_4 = new QGridLayout(m_groupBox_pos);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_label_range = new QLabel(m_groupBox_pos);
        m_label_range->setObjectName(QString::fromUtf8("m_label_range"));
        m_label_range->setMinimumSize(QSize(50, 0));
        m_label_range->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(m_label_range);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        m_doubleSpinBox_H = new QDoubleSpinBox(m_groupBox_pos);
        m_doubleSpinBox_H->setObjectName(QString::fromUtf8("m_doubleSpinBox_H"));
        m_doubleSpinBox_H->setMinimumSize(QSize(50, 20));
        m_doubleSpinBox_H->setMaximumSize(QSize(16777215, 20));
        m_doubleSpinBox_H->setMaximum(1e+06);
        m_doubleSpinBox_H->setValue(1);

        horizontalLayout_6->addWidget(m_doubleSpinBox_H);


        gridLayout_4->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_label_range_2 = new QLabel(m_groupBox_pos);
        m_label_range_2->setObjectName(QString::fromUtf8("m_label_range_2"));
        m_label_range_2->setMinimumSize(QSize(50, 0));
        m_label_range_2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_8->addWidget(m_label_range_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        m_doubleSpinBox_W = new QDoubleSpinBox(m_groupBox_pos);
        m_doubleSpinBox_W->setObjectName(QString::fromUtf8("m_doubleSpinBox_W"));
        m_doubleSpinBox_W->setMinimumSize(QSize(50, 20));
        m_doubleSpinBox_W->setMaximumSize(QSize(16777215, 20));
        m_doubleSpinBox_W->setMaximum(1e+06);
        m_doubleSpinBox_W->setValue(1);

        horizontalLayout_8->addWidget(m_doubleSpinBox_W);


        gridLayout_4->addLayout(horizontalLayout_8, 1, 0, 1, 1);


        verticalLayout_3->addWidget(m_groupBox_pos);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_groupBox_field = new QGroupBox(C_DialogMergeRule);
        m_groupBox_field->setObjectName(QString::fromUtf8("m_groupBox_field"));
        m_groupBox_field->setMinimumSize(QSize(160, 140));
        m_groupBox_field->setCheckable(true);
        m_groupBox_field->setChecked(false);
        gridLayout_2 = new QGridLayout(m_groupBox_field);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(5);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        m_label_main1 = new QLabel(m_groupBox_field);
        m_label_main1->setObjectName(QString::fromUtf8("m_label_main1"));
        m_label_main1->setMinimumSize(QSize(65, 0));
        m_label_main1->setMaximumSize(QSize(65, 16777215));

        horizontalLayout_9->addWidget(m_label_main1);

        m_comboBox_main = new QComboBox(m_groupBox_field);
        m_comboBox_main->setObjectName(QString::fromUtf8("m_comboBox_main"));

        horizontalLayout_9->addWidget(m_comboBox_main);


        gridLayout_2->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(5);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        m_label_ass1 = new QLabel(m_groupBox_field);
        m_label_ass1->setObjectName(QString::fromUtf8("m_label_ass1"));
        m_label_ass1->setMinimumSize(QSize(65, 0));
        m_label_ass1->setMaximumSize(QSize(65, 16777215));

        horizontalLayout_10->addWidget(m_label_ass1);

        m_comboBox_ass = new QComboBox(m_groupBox_field);
        m_comboBox_ass->setObjectName(QString::fromUtf8("m_comboBox_ass"));

        horizontalLayout_10->addWidget(m_comboBox_ass);


        gridLayout_2->addLayout(horizontalLayout_10, 1, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(5);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        m_label_simiField = new QLabel(m_groupBox_field);
        m_label_simiField->setObjectName(QString::fromUtf8("m_label_simiField"));
        m_label_simiField->setMinimumSize(QSize(40, 0));
        m_label_simiField->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_11->addWidget(m_label_simiField, 0, Qt::AlignLeft);

        m_spinBox_field = new QSpinBox(m_groupBox_field);
        m_spinBox_field->setObjectName(QString::fromUtf8("m_spinBox_field"));
        m_spinBox_field->setMinimumSize(QSize(40, 20));
        m_spinBox_field->setMaximumSize(QSize(60, 20));
        m_spinBox_field->setMaximum(100);
        m_spinBox_field->setValue(60);

        horizontalLayout_11->addWidget(m_spinBox_field, 0, Qt::AlignRight);


        gridLayout_2->addLayout(horizontalLayout_11, 2, 0, 1, 1);


        horizontalLayout_4->addWidget(m_groupBox_field);

        m_groupBox_form = new QGroupBox(C_DialogMergeRule);
        m_groupBox_form->setObjectName(QString::fromUtf8("m_groupBox_form"));
        m_groupBox_form->setMinimumSize(QSize(160, 140));
        m_groupBox_form->setCheckable(true);
        m_groupBox_form->setChecked(false);
        gridLayout = new QGridLayout(m_groupBox_form);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_label_ll = new QLabel(m_groupBox_form);
        m_label_ll->setObjectName(QString::fromUtf8("m_label_ll"));
        m_label_ll->setMinimumSize(QSize(85, 25));
        m_label_ll->setMaximumSize(QSize(85, 25));

        horizontalLayout->addWidget(m_label_ll);

        m_spinBox_ll = new QSpinBox(m_groupBox_form);
        m_spinBox_ll->setObjectName(QString::fromUtf8("m_spinBox_ll"));
        m_spinBox_ll->setMinimumSize(QSize(40, 20));
        m_spinBox_ll->setMaximumSize(QSize(16777215, 25));
        m_spinBox_ll->setMaximum(100);
        m_spinBox_ll->setValue(60);

        horizontalLayout->addWidget(m_spinBox_ll);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_label_la = new QLabel(m_groupBox_form);
        m_label_la->setObjectName(QString::fromUtf8("m_label_la"));
        m_label_la->setMinimumSize(QSize(85, 25));
        m_label_la->setMaximumSize(QSize(85, 25));

        horizontalLayout_2->addWidget(m_label_la);

        m_spinBox_la = new QSpinBox(m_groupBox_form);
        m_spinBox_la->setObjectName(QString::fromUtf8("m_spinBox_la"));
        m_spinBox_la->setMinimumSize(QSize(40, 20));
        m_spinBox_la->setMaximumSize(QSize(16777215, 25));
        m_spinBox_la->setMaximum(100);
        m_spinBox_la->setValue(60);

        horizontalLayout_2->addWidget(m_spinBox_la);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_label_aa = new QLabel(m_groupBox_form);
        m_label_aa->setObjectName(QString::fromUtf8("m_label_aa"));
        m_label_aa->setMinimumSize(QSize(85, 25));
        m_label_aa->setMaximumSize(QSize(85, 25));

        horizontalLayout_3->addWidget(m_label_aa);

        m_spinBox_aa = new QSpinBox(m_groupBox_form);
        m_spinBox_aa->setObjectName(QString::fromUtf8("m_spinBox_aa"));
        m_spinBox_aa->setMinimumSize(QSize(40, 20));
        m_spinBox_aa->setMaximumSize(QSize(16777215, 25));
        m_spinBox_aa->setMaximum(100);
        m_spinBox_aa->setValue(60);

        horizontalLayout_3->addWidget(m_spinBox_aa);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        horizontalLayout_4->addWidget(m_groupBox_form);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        m_btn_ok = new QPushButton(C_DialogMergeRule);
        m_btn_ok->setObjectName(QString::fromUtf8("m_btn_ok"));

        horizontalLayout_7->addWidget(m_btn_ok);

        m_btn_cancel = new QPushButton(C_DialogMergeRule);
        m_btn_cancel->setObjectName(QString::fromUtf8("m_btn_cancel"));

        horizontalLayout_7->addWidget(m_btn_cancel);


        horizontalLayout_5->addLayout(horizontalLayout_7);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 2);
        verticalLayout_3->setStretch(2, 3);
        verticalLayout_3->setStretch(3, 1);

        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(C_DialogMergeRule);

        QMetaObject::connectSlotsByName(C_DialogMergeRule);
    } // setupUi

    void retranslateUi(QDialog *C_DialogMergeRule)
    {
        C_DialogMergeRule->setWindowTitle(QApplication::translate("C_DialogMergeRule", "\350\256\276\347\275\256\350\236\215\345\220\210\350\247\204\345\210\231", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("C_DialogMergeRule", "    \346\240\271\346\215\256\350\256\276\345\256\232\347\232\204\346\235\241\344\273\266\350\277\233\350\241\214\345\257\271\350\261\241\350\236\215\345\220\210\357\274\214\345\220\214\346\227\266\346\273\241\350\266\263\346\211\200\346\234\211\351\200\211\345\256\232\346\235\241\344\273\266\346\211\215\350\203\275\350\277\233\350\241\214\350\236\215\345\220\210\345\217\212\345\257\271\350\261\241\347\224\237\346\210\220\343\200\202", 0, QApplication::UnicodeUTF8));
        m_groupBox_pos->setTitle(QApplication::translate("C_DialogMergeRule", "\345\237\272\344\272\216\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        m_label_range->setText(QApplication::translate("C_DialogMergeRule", "\346\220\234\347\264\242\350\214\203\345\233\264\351\253\230\345\272\246\357\274\210H\357\274\211", 0, QApplication::UnicodeUTF8));
        m_label_range_2->setText(QApplication::translate("C_DialogMergeRule", "\346\220\234\347\264\242\350\214\203\345\233\264\351\253\230\345\272\246\357\274\210W\357\274\211", 0, QApplication::UnicodeUTF8));
        m_groupBox_field->setTitle(QApplication::translate("C_DialogMergeRule", "\345\237\272\344\272\216\345\255\227\346\256\265", 0, QApplication::UnicodeUTF8));
        m_label_main1->setText(QApplication::translate("C_DialogMergeRule", "\344\270\273\346\225\260\346\215\256\351\233\206", 0, QApplication::UnicodeUTF8));
        m_label_ass1->setText(QApplication::translate("C_DialogMergeRule", "\345\214\271\351\205\215\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        m_label_simiField->setText(QApplication::translate("C_DialogMergeRule", "\347\233\270\344\274\274\346\200\247", 0, QApplication::UnicodeUTF8));
        m_groupBox_form->setTitle(QApplication::translate("C_DialogMergeRule", "\345\237\272\344\272\216\344\272\214\347\273\264\345\275\242\346\200\201", 0, QApplication::UnicodeUTF8));
        m_label_ll->setText(QApplication::translate("C_DialogMergeRule", "\347\272\277-\347\272\277\347\233\270\344\274\274\346\200\247", 0, QApplication::UnicodeUTF8));
        m_label_la->setText(QApplication::translate("C_DialogMergeRule", "\347\272\277-\351\235\242\347\233\270\344\274\274\346\200\247", 0, QApplication::UnicodeUTF8));
        m_label_aa->setText(QApplication::translate("C_DialogMergeRule", "\351\235\242-\351\235\242\347\233\270\344\274\274\346\200\247", 0, QApplication::UnicodeUTF8));
        m_btn_ok->setText(QApplication::translate("C_DialogMergeRule", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        m_btn_cancel->setText(QApplication::translate("C_DialogMergeRule", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class C_DialogMergeRule: public Ui_C_DialogMergeRule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MERGERULEDLG_H
