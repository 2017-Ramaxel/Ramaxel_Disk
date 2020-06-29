/********************************************************************************
** Form generated from reading UI file 'titlewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLEWIDGET_H
#define UI_TITLEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TitleWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *logo;
    QToolButton *set;
    QToolButton *close;

    void setupUi(QWidget *TitleWidget)
    {
        if (TitleWidget->objectName().isEmpty())
            TitleWidget->setObjectName(QString::fromUtf8("TitleWidget"));
        TitleWidget->resize(669, 110);
        TitleWidget->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(TitleWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(TitleWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        logo = new QLabel(widget);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setLayoutDirection(Qt::LeftToRight);
        logo->setPixmap(QPixmap(QString::fromUtf8(":/upload/images/logo.ico")));
        logo->setScaledContents(false);
        logo->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(logo);

        set = new QToolButton(widget);
        set->setObjectName(QString::fromUtf8("set"));
        set->setLayoutDirection(Qt::RightToLeft);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/upload/images/login_setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        set->setIcon(icon);
        set->setIconSize(QSize(32, 32));
        set->setAutoRaise(true);

        horizontalLayout->addWidget(set);

        close = new QToolButton(widget);
        close->setObjectName(QString::fromUtf8("close"));
        close->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/upload/images/login_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        close->setIcon(icon1);
        close->setIconSize(QSize(32, 32));
        close->setAutoRaise(true);

        horizontalLayout->addWidget(close);


        verticalLayout->addWidget(widget);


        retranslateUi(TitleWidget);

        QMetaObject::connectSlotsByName(TitleWidget);
    } // setupUi

    void retranslateUi(QWidget *TitleWidget)
    {
        TitleWidget->setWindowTitle(QCoreApplication::translate("TitleWidget", "Form", nullptr));
        logo->setText(QString());
        set->setText(QCoreApplication::translate("TitleWidget", "...", nullptr));
        close->setText(QCoreApplication::translate("TitleWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TitleWidget: public Ui_TitleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLEWIDGET_H
