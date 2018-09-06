/********************************************************************************
** Form generated from reading UI file 'searcherobjectwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHEROBJECTWIDGET_H
#define UI_SEARCHEROBJECTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearcherObject
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_search;
    QPushButton *pushButton_search;

    void setupUi(QWidget *SearcherObject)
    {
        if (SearcherObject->objectName().isEmpty())
            SearcherObject->setObjectName(QString::fromUtf8("SearcherObject"));
        SearcherObject->resize(159, 26);
        gridLayout = new QGridLayout(SearcherObject);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_search = new QLineEdit(SearcherObject);
        lineEdit_search->setObjectName(QString::fromUtf8("lineEdit_search"));
        lineEdit_search->setMinimumSize(QSize(0, 20));
        lineEdit_search->setSizeIncrement(QSize(0, 20));

        horizontalLayout->addWidget(lineEdit_search);

        pushButton_search = new QPushButton(SearcherObject);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_search->sizePolicy().hasHeightForWidth());
        pushButton_search->setSizePolicy(sizePolicy);
        pushButton_search->setMinimumSize(QSize(24, 24));
        pushButton_search->setMaximumSize(QSize(24, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ModelingTool/Images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_search->setIcon(icon);
        pushButton_search->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButton_search);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(SearcherObject);

        QMetaObject::connectSlotsByName(SearcherObject);
    } // setupUi

    void retranslateUi(QWidget *SearcherObject)
    {
        SearcherObject->setWindowTitle(QApplication::translate("SearcherObject", "\345\257\271\350\261\241\346\237\245\346\211\276\345\231\250", 0, QApplication::UnicodeUTF8));
        pushButton_search->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearcherObject: public Ui_SearcherObject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHEROBJECTWIDGET_H
