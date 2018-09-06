/********************************************************************************
** Form generated from reading UI file 'addBehaviorDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDBEHAVIORDIALOG_H
#define UI_ADDBEHAVIORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addBehaviorDialog
{
public:
    QFormLayout *formLayout;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *addBehaviorDialog)
    {
        if (addBehaviorDialog->objectName().isEmpty())
            addBehaviorDialog->setObjectName(QString::fromUtf8("addBehaviorDialog"));
        addBehaviorDialog->resize(529, 285);
        formLayout = new QFormLayout(addBehaviorDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout);

        scrollArea = new QScrollArea(addBehaviorDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 501, 257));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(scrollAreaWidgetContents);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_2 = new QComboBox(scrollAreaWidgetContents);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        horizontalSpacer_2 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        textEdit = new QTextEdit(scrollAreaWidgetContents);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        buttonBox = new QDialogButtonBox(scrollAreaWidgetContents);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_3);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        textEdit->raise();
        textEdit->raise();

        formLayout->setWidget(1, QFormLayout::FieldRole, scrollArea);


        retranslateUi(addBehaviorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), addBehaviorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), addBehaviorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(addBehaviorDialog);
    } // setupUi

    void retranslateUi(QDialog *addBehaviorDialog)
    {
        addBehaviorDialog->setWindowTitle(QApplication::translate("addBehaviorDialog", "\346\267\273\345\212\240\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("addBehaviorDialog", "\350\241\214\344\270\272\347\261\273\345\210\253\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("addBehaviorDialog", "\351\243\236\350\241\214\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\346\211\223\345\207\273\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\346\216\242\346\265\213\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\350\277\275\350\270\252\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\347\210\206\347\202\270\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("addBehaviorDialog", "\350\241\214\344\270\272\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("addBehaviorDialog", "\346\273\221\350\241\214", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\347\233\230\346\227\213", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\347\233\264\345\215\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\351\231\215\350\220\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\346\211\223\345\207\273", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\346\216\242\346\265\213", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\350\277\275\350\270\252", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("addBehaviorDialog", "\347\210\206\347\202\270", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("addBehaviorDialog", "\350\241\214\344\270\272\350\257\246\347\273\206\344\277\241\346\201\257\357\274\232", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("addBehaviorDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">\346\273\221\350\241\214\350\241\214\344\270\272\345\215\263\351\243\236\346\234\272\343\200\201\351\243\236\350\241\214\345\231\250\347\255\211\345\257\271\350\261\241\350\265\267\351\243\236\345\211\215\345\222\214\351\231\215\350\220\275\345\220\216\347\232\204\346\273\221\345\212\250\350\277\207\347\250\213\343\200\202</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class addBehaviorDialog: public Ui_addBehaviorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDBEHAVIORDIALOG_H
