/********************************************************************************
** Form generated from reading UI file 'selectTypeWizardPage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTTYPEWIZARDPAGE_H
#define UI_SELECTTYPEWIZARDPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_SelectTypeWizardPage
{
public:
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QTreeWidget *treeWidget_relation;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_relationName;
    QLabel *label_4;
    QLineEdit *lineEdit_relationID;
    QFrame *line;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit_begin;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit_end;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_one2many;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButton_many2one;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioButton_many2many;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWizardPage *SelectTypeWizardPage)
    {
        if (SelectTypeWizardPage->objectName().isEmpty())
            SelectTypeWizardPage->setObjectName(QString::fromUtf8("SelectTypeWizardPage"));
        SelectTypeWizardPage->resize(473, 380);
        SelectTypeWizardPage->setMinimumSize(QSize(0, 380));
        gridLayout_6 = new QGridLayout(SelectTypeWizardPage);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(SelectTypeWizardPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        treeWidget_relation = new QTreeWidget(groupBox);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/network.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ModelingTool/Images/relation.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ModelingTool/Images/object.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget_relation);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem3->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem4->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem5->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem6->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(treeWidget_relation);
        __qtreewidgetitem7->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem7);
        __qtreewidgetitem8->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem9->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem10->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem7);
        __qtreewidgetitem11->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(__qtreewidgetitem11);
        __qtreewidgetitem12->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem11);
        __qtreewidgetitem13->setIcon(0, icon2);
        treeWidget_relation->setObjectName(QString::fromUtf8("treeWidget_relation"));
        treeWidget_relation->setMinimumSize(QSize(0, 0));
        treeWidget_relation->header()->setVisible(false);

        gridLayout_5->addWidget(treeWidget_relation, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(SelectTypeWizardPage);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_relationName = new QLineEdit(groupBox_2);
        lineEdit_relationName->setObjectName(QString::fromUtf8("lineEdit_relationName"));

        gridLayout_3->addWidget(lineEdit_relationName, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        lineEdit_relationID = new QLineEdit(groupBox_2);
        lineEdit_relationID->setObjectName(QString::fromUtf8("lineEdit_relationID"));

        gridLayout_3->addWidget(lineEdit_relationID, 1, 1, 1, 1);

        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 2, 0, 1, 2);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 3, 0, 1, 1);

        dateTimeEdit_begin = new QDateTimeEdit(groupBox_2);
        dateTimeEdit_begin->setObjectName(QString::fromUtf8("dateTimeEdit_begin"));

        gridLayout_3->addWidget(dateTimeEdit_begin, 3, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 4, 0, 1, 1);

        dateTimeEdit_end = new QDateTimeEdit(groupBox_2);
        dateTimeEdit_end->setObjectName(QString::fromUtf8("dateTimeEdit_end"));

        gridLayout_3->addWidget(dateTimeEdit_end, 4, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(SelectTypeWizardPage);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButton_one2many = new QRadioButton(groupBox_3);
        radioButton_one2many->setObjectName(QString::fromUtf8("radioButton_one2many"));

        gridLayout->addWidget(radioButton_one2many, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        radioButton_many2one = new QRadioButton(groupBox_3);
        radioButton_many2one->setObjectName(QString::fromUtf8("radioButton_many2one"));

        gridLayout->addWidget(radioButton_many2one, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        radioButton_many2many = new QRadioButton(groupBox_3);
        radioButton_many2many->setObjectName(QString::fromUtf8("radioButton_many2many"));

        gridLayout->addWidget(radioButton_many2many, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(SelectTypeWizardPage);

        QMetaObject::connectSlotsByName(SelectTypeWizardPage);
    } // setupUi

    void retranslateUi(QWizardPage *SelectTypeWizardPage)
    {
        SelectTypeWizardPage->setWindowTitle(QApplication::translate("SelectTypeWizardPage", "WizardPage", 0, QApplication::UnicodeUTF8));
        SelectTypeWizardPage->setTitle(QApplication::translate("SelectTypeWizardPage", "\347\254\254\344\270\200\346\255\245\357\274\232\347\261\273\345\236\213\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        SelectTypeWizardPage->setSubTitle(QApplication::translate("SelectTypeWizardPage", "\351\200\211\346\213\251\346\211\200\350\246\201\346\236\204\345\273\272\347\232\204\345\205\263\347\263\273\347\261\273\345\236\213\344\273\245\345\217\212\346\211\271\351\207\217\346\236\204\345\273\272\347\232\204\346\226\271\345\274\217\357\274\214\345\271\266\350\256\276\347\275\256\346\234\254\346\254\241\346\211\271\351\207\217\346\236\204\345\273\272\347\232\204\345\205\263\350\201\224\345\205\263\347\263\273\347\232\204\347\224\237\345\221\275\345\221\250\346\234\237\343\200\202", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SelectTypeWizardPage", "\345\205\263\347\263\273\350\247\206\345\233\276", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_relation->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("SelectTypeWizardPage", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget_relation->isSortingEnabled();
        treeWidget_relation->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_relation->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("SelectTypeWizardPage", "\345\215\217\345\220\214\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\233\26495001->\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("SelectTypeWizardPage", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem5->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\233\26495002->\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(0, QApplication::translate("SelectTypeWizardPage", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem5->child(1);
        ___qtreewidgetitem7->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = treeWidget_relation->topLevelItem(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("SelectTypeWizardPage", "\346\214\207\346\214\245\345\205\263\347\263\273", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\233\26495003->\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem9->child(0);
        ___qtreewidgetitem10->setText(0, QApplication::translate("SelectTypeWizardPage", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem9->child(1);
        ___qtreewidgetitem11->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495001", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem8->child(1);
        ___qtreewidgetitem12->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\233\26495003->\347\233\26495002", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem12->child(0);
        ___qtreewidgetitem13->setText(0, QApplication::translate("SelectTypeWizardPage", "\350\265\267\345\247\213\345\257\271\350\261\241\357\274\232\347\233\26495003", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem12->child(1);
        ___qtreewidgetitem14->setText(0, QApplication::translate("SelectTypeWizardPage", "\347\273\210\346\255\242\345\257\271\350\261\241\357\274\232\347\233\26495002", 0, QApplication::UnicodeUTF8));
        treeWidget_relation->setSortingEnabled(__sortingEnabled);

        groupBox_2->setTitle(QApplication::translate("SelectTypeWizardPage", "\345\237\272\346\234\254\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SelectTypeWizardPage", "\345\205\263\347\263\273\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SelectTypeWizardPage", "\345\205\263\347\263\273\346\240\207\350\257\206\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SelectTypeWizardPage", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SelectTypeWizardPage", "\347\273\210\346\255\242\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("SelectTypeWizardPage", "\346\236\204\345\273\272\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        radioButton_one2many->setText(QApplication::translate("SelectTypeWizardPage", "\344\270\200\345\257\271\345\244\232\346\236\204\345\273\272\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        radioButton_many2one->setText(QApplication::translate("SelectTypeWizardPage", "\345\244\232\345\257\271\344\270\200\346\236\204\345\273\272\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        radioButton_many2many->setText(QApplication::translate("SelectTypeWizardPage", "\345\244\232\345\257\271\345\244\232\346\236\204\345\273\272\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectTypeWizardPage: public Ui_SelectTypeWizardPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTTYPEWIZARDPAGE_H
