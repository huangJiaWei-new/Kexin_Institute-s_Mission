/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *displayImg;
    QPushButton *detectLines;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1069, 595);
        displayImg = new QPushButton(Widget);
        displayImg->setObjectName(QString::fromUtf8("displayImg"));
        displayImg->setGeometry(QRect(60, 70, 131, 51));
        detectLines = new QPushButton(Widget);
        detectLines->setObjectName(QString::fromUtf8("detectLines"));
        detectLines->setGeometry(QRect(60, 160, 131, 51));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        displayImg->setText(QCoreApplication::translate("Widget", "\345\212\240\350\275\275\345\233\276\345\203\217", nullptr));
        detectLines->setText(QCoreApplication::translate("Widget", "\351\234\215\345\244\253\347\233\264\347\272\277\346\243\200\346\265\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
