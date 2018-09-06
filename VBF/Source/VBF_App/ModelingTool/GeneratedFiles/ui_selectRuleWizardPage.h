/********************************************************************************
** Form generated from reading UI file 'selectRuleWizardPage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTRULEWIZARDPAGE_H
#define UI_SELECTRULEWIZARDPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_SelectRuleWizardPage
{
public:
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_one2many;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton_sourceRule;
    QListWidget *listWidget_source;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_one2manyRemove;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QPushButton *pushButton_destinRule;
    QListWidget *listWidget_destin;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_many2many;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_4;
    QLabel *label_3;
    QPushButton *pushButton_rule;
    QListWidget *listWidget_nodes;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_many2manyRemove;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWizardPage *SelectRuleWizardPage)
    {
        if (SelectRuleWizardPage->objectName().isEmpty())
            SelectRuleWizardPage->setObjectName(QString::fromUtf8("SelectRuleWizardPage"));
        SelectRuleWizardPage->resize(470, 375);
        gridLayout_6 = new QGridLayout(SelectRuleWizardPage);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_one2many = new QGroupBox(SelectRuleWizardPage);
        groupBox_one2many->setObjectName(QString::fromUtf8("groupBox_one2many"));
        gridLayout_3 = new QGridLayout(groupBox_one2many);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox_one2many);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_sourceRule = new QPushButton(groupBox_one2many);
        pushButton_sourceRule->setObjectName(QString::fromUtf8("pushButton_sourceRule"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_sourceRule->sizePolicy().hasHeightForWidth());
        pushButton_sourceRule->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/rule.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_sourceRule->setIcon(icon);

        gridLayout->addWidget(pushButton_sourceRule, 0, 1, 1, 1);

        listWidget_source = new QListWidget(groupBox_one2many);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/object.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget_source);
        __qlistwidgetitem->setIcon(icon1);
        listWidget_source->setObjectName(QString::fromUtf8("listWidget_source"));

        gridLayout->addWidget(listWidget_source, 1, 0, 1, 2);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton_one2manyRemove = new QPushButton(groupBox_one2many);
        pushButton_one2manyRemove->setObjectName(QString::fromUtf8("pushButton_one2manyRemove"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/remove_circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_one2manyRemove->setIcon(icon2);

        verticalLayout->addWidget(pushButton_one2manyRemove);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox_one2many);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        pushButton_destinRule = new QPushButton(groupBox_one2many);
        pushButton_destinRule->setObjectName(QString::fromUtf8("pushButton_destinRule"));
        sizePolicy.setHeightForWidth(pushButton_destinRule->sizePolicy().hasHeightForWidth());
        pushButton_destinRule->setSizePolicy(sizePolicy);
        pushButton_destinRule->setIcon(icon);

        gridLayout_2->addWidget(pushButton_destinRule, 0, 1, 1, 1);

        listWidget_destin = new QListWidget(groupBox_one2many);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget_destin);
        __qlistwidgetitem1->setIcon(icon1);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget_destin);
        __qlistwidgetitem2->setIcon(icon1);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget_destin);
        __qlistwidgetitem3->setIcon(icon1);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget_destin);
        __qlistwidgetitem4->setIcon(icon1);
        listWidget_destin->setObjectName(QString::fromUtf8("listWidget_destin"));

        gridLayout_2->addWidget(listWidget_destin, 1, 0, 1, 2);


        horizontalLayout->addLayout(gridLayout_2);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox_one2many);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        groupBox_many2many = new QGroupBox(SelectRuleWizardPage);
        groupBox_many2many->setObjectName(QString::fromUtf8("groupBox_many2many"));
        gridLayout_5 = new QGridLayout(groupBox_many2many);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_3 = new QLabel(groupBox_many2many);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        pushButton_rule = new QPushButton(groupBox_many2many);
        pushButton_rule->setObjectName(QString::fromUtf8("pushButton_rule"));
        sizePolicy.setHeightForWidth(pushButton_rule->sizePolicy().hasHeightForWidth());
        pushButton_rule->setSizePolicy(sizePolicy);
        pushButton_rule->setIcon(icon);

        gridLayout_4->addWidget(pushButton_rule, 0, 1, 1, 1);

        listWidget_nodes = new QListWidget(groupBox_many2many);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget_nodes);
        __qlistwidgetitem5->setIcon(icon1);
        listWidget_nodes->setObjectName(QString::fromUtf8("listWidget_nodes"));

        gridLayout_4->addWidget(listWidget_nodes, 1, 0, 1, 2);


        horizontalLayout_2->addLayout(gridLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(17, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        pushButton_many2manyRemove = new QPushButton(groupBox_many2many);
        pushButton_many2manyRemove->setObjectName(QString::fromUtf8("pushButton_many2manyRemove"));
        pushButton_many2manyRemove->setIcon(icon2);

        verticalLayout_2->addWidget(pushButton_many2manyRemove);

        verticalSpacer_4 = new QSpacerItem(17, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        horizontalLayout_2->addLayout(verticalLayout_2);


        gridLayout_5->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox_many2many);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox = new QCheckBox(SelectRuleWizardPage);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);

        horizontalLayout_3->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_4);


        gridLayout_6->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(SelectRuleWizardPage);

        QMetaObject::connectSlotsByName(SelectRuleWizardPage);
    } // setupUi

    void retranslateUi(QWizardPage *SelectRuleWizardPage)
    {
        SelectRuleWizardPage->setWindowTitle(QApplication::translate("SelectRuleWizardPage", "WizardPage", 0, QApplication::UnicodeUTF8));
        SelectRuleWizardPage->setTitle(QApplication::translate("SelectRuleWizardPage", "\347\254\254\344\272\214\346\255\245\357\274\232\350\212\202\347\202\271\347\255\233\351\200\211", 0, QApplication::UnicodeUTF8));
        SelectRuleWizardPage->setSubTitle(QApplication::translate("SelectRuleWizardPage", "\345\246\202\346\236\234\346\230\257\342\200\235\344\270\200\345\257\271\345\244\232/\345\244\232\345\257\271\344\270\200\342\200\234\346\236\204\345\273\272\357\274\214\346\202\250\351\234\200\350\246\201\345\210\206\345\210\253\350\256\276\347\275\256\350\265\267\345\247\213\350\212\202\347\202\271\351\233\206\345\220\210\345\222\214\347\273\210\346\255\242\350\212\202\347\202\271\351\233\206\345\220\210\357\274\233\345\246\202\346\236\234\346\230\257\342\200\235\345\244\232\345\257\271\345\244\232\342\200\234\346\236\204\345\273\272\357\274\214\345\210\231\344\270\215\345\206\215\345\214\272\345\210\206\350\265\267\345\247\213\350\212\202\347\202\271\351\233\206\345\220\210\345\222\214\347\273\210\346\255\242\350\212\202\347\202\271\351\233\206\345\220\210\343\200\202", 0, QApplication::UnicodeUTF8));
        groupBox_one2many->setTitle(QApplication::translate("SelectRuleWizardPage", "\342\200\234\344\270\200\345\257\271\345\244\232/\345\244\232\345\257\271\344\270\200\342\200\235\350\212\202\347\202\271\347\255\233\351\200\211", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SelectRuleWizardPage", "\350\265\267\345\247\213\350\212\202\347\202\271\351\233\206\345\220\210\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_sourceRule->setText(QApplication::translate("SelectRuleWizardPage", "\347\255\233\351\200\211\346\235\241\344\273\266", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget_source->isSortingEnabled();
        listWidget_source->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_source->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("SelectRuleWizardPage", "\347\233\26495001", 0, QApplication::UnicodeUTF8));
        listWidget_source->setSortingEnabled(__sortingEnabled);

        pushButton_one2manyRemove->setText(QString());
        label_2->setText(QApplication::translate("SelectRuleWizardPage", "\347\273\210\346\255\242\350\212\202\347\202\271\351\233\206\345\220\210\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_destinRule->setText(QApplication::translate("SelectRuleWizardPage", "\347\255\233\351\200\211\346\235\241\344\273\266", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = listWidget_destin->isSortingEnabled();
        listWidget_destin->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem1 = listWidget_destin->item(0);
        ___qlistwidgetitem1->setText(QApplication::translate("SelectRuleWizardPage", "\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_destin->item(1);
        ___qlistwidgetitem2->setText(QApplication::translate("SelectRuleWizardPage", "\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_destin->item(2);
        ___qlistwidgetitem3->setText(QApplication::translate("SelectRuleWizardPage", "\347\233\26495004", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_destin->item(3);
        ___qlistwidgetitem4->setText(QApplication::translate("SelectRuleWizardPage", "\347\233\26495005", 0, QApplication::UnicodeUTF8));
        listWidget_destin->setSortingEnabled(__sortingEnabled1);

        groupBox_many2many->setTitle(QApplication::translate("SelectRuleWizardPage", "\342\200\234\345\244\232\345\257\271\345\244\232\342\200\235\350\212\202\347\202\271\347\255\233\351\200\211", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SelectRuleWizardPage", "\350\212\202\347\202\271\351\233\206\345\220\210\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_rule->setText(QApplication::translate("SelectRuleWizardPage", "\347\255\233\351\200\211\346\235\241\344\273\266", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = listWidget_nodes->isSortingEnabled();
        listWidget_nodes->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem5 = listWidget_nodes->item(0);
        ___qlistwidgetitem5->setText(QApplication::translate("SelectRuleWizardPage", "\347\233\26495001", 0, QApplication::UnicodeUTF8));
        listWidget_nodes->setSortingEnabled(__sortingEnabled2);

        pushButton_many2manyRemove->setText(QString());
        checkBox->setText(QApplication::translate("SelectRuleWizardPage", "\345\217\214\345\220\221\346\236\204\345\273\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectRuleWizardPage: public Ui_SelectRuleWizardPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTRULEWIZARDPAGE_H
