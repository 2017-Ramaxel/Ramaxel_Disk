/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <titlewidget.h>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayout;
    TitleWidget *titlewidget;
    QStackedWidget *stackedWidget;
    QWidget *login_page_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QWidget *widget_13;
    QGridLayout *gridLayout_3;
    QLineEdit *pwd_log;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_14;
    QLineEdit *name_log;
    QSpacerItem *verticalSpacer_9;
    QWidget *widget_14;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *rem_pwd;
    QSpacerItem *horizontalSpacer_13;
    QToolButton *reg_log;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_15;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_9;
    QToolButton *login_ok;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_6;
    QWidget *reg_page_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *name_reg;
    QLabel *label_5;
    QLineEdit *nichen_reg;
    QLabel *label_3;
    QLineEdit *pwd_reg;
    QLabel *label_4;
    QLineEdit *repwd_reg;
    QLabel *label_6;
    QLineEdit *phone_reg;
    QLabel *label_10;
    QLineEdit *email_reg;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *regist;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_8;
    QWidget *set_page_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_18;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_7;
    QWidget *widget_6;
    QGridLayout *gridLayout_2;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *port;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *ip_addr;
    QSpacerItem *verticalSpacer_8;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *server_ok;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_19;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(647, 421);
        Login->setStyleSheet(QString::fromUtf8("\n"
"border-color: rgb(0, 0, 0);\n"
"border: 2px"));
        verticalLayout = new QVBoxLayout(Login);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titlewidget = new TitleWidget(Login);
        titlewidget->setObjectName(QString::fromUtf8("titlewidget"));
        titlewidget->setMinimumSize(QSize(0, 0));
        titlewidget->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(titlewidget);

        stackedWidget = new QStackedWidget(Login);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        login_page_3 = new QWidget();
        login_page_3->setObjectName(QString::fromUtf8("login_page_3"));
        verticalLayout_2 = new QVBoxLayout(login_page_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_12 = new QWidget(login_page_3);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        verticalLayout_3 = new QVBoxLayout(widget_12);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        widget_13 = new QWidget(widget_12);
        widget_13->setObjectName(QString::fromUtf8("widget_13"));
        gridLayout_3 = new QGridLayout(widget_13);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pwd_log = new QLineEdit(widget_13);
        pwd_log->setObjectName(QString::fromUtf8("pwd_log"));
        pwd_log->setMinimumSize(QSize(300, 40));
        pwd_log->setMaximumSize(QSize(150, 16777215));
        pwd_log->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout_3->addWidget(pwd_log, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_14, 0, 2, 1, 1);

        name_log = new QLineEdit(widget_13);
        name_log->setObjectName(QString::fromUtf8("name_log"));
        name_log->setMinimumSize(QSize(300, 40));
        name_log->setMaximumSize(QSize(150, 16777215));
        name_log->setAutoFillBackground(false);
        name_log->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout_3->addWidget(name_log, 0, 1, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_9, 1, 1, 1, 1);


        verticalLayout_3->addWidget(widget_13);

        widget_14 = new QWidget(widget_12);
        widget_14->setObjectName(QString::fromUtf8("widget_14"));
        horizontalLayout_5 = new QHBoxLayout(widget_14);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        rem_pwd = new QCheckBox(widget_14);
        rem_pwd->setObjectName(QString::fromUtf8("rem_pwd"));

        horizontalLayout_5->addWidget(rem_pwd);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_13);

        reg_log = new QToolButton(widget_14);
        reg_log->setObjectName(QString::fromUtf8("reg_log"));
        reg_log->setStyleSheet(QString::fromUtf8("font: 9pt \"Sans Serif\";\n"
"text-decoration: underline;\n"
"color: rgb(0, 85, 255);"));
        reg_log->setAutoRaise(true);

        horizontalLayout_5->addWidget(reg_log);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_3->addWidget(widget_14);

        widget_15 = new QWidget(widget_12);
        widget_15->setObjectName(QString::fromUtf8("widget_15"));
        horizontalLayout_6 = new QHBoxLayout(widget_15);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_9 = new QSpacerItem(82, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        login_ok = new QToolButton(widget_15);
        login_ok->setObjectName(QString::fromUtf8("login_ok"));
        login_ok->setMinimumSize(QSize(300, 40));
        login_ok->setMaximumSize(QSize(200, 50));
        login_ok->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 10pt \"Sans Serif\";\n"
"background-color: rgb(85, 170, 255);\n"
"border-radius:3px;"));
        login_ok->setIconSize(QSize(200, 47));
        login_ok->setAutoRaise(true);

        horizontalLayout_6->addWidget(login_ok);

        horizontalSpacer_10 = new QSpacerItem(81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);


        verticalLayout_3->addWidget(widget_15);


        verticalLayout_2->addWidget(widget_12);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        stackedWidget->addWidget(login_page_3);
        reg_page_3 = new QWidget();
        reg_page_3->setObjectName(QString::fromUtf8("reg_page_3"));
        horizontalLayout_3 = new QHBoxLayout(reg_page_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(59, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        widget = new QWidget(reg_page_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        name_reg = new QLineEdit(widget_2);
        name_reg->setObjectName(QString::fromUtf8("name_reg"));
        name_reg->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout->addWidget(name_reg, 0, 1, 1, 1);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        nichen_reg = new QLineEdit(widget_2);
        nichen_reg->setObjectName(QString::fromUtf8("nichen_reg"));
        nichen_reg->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout->addWidget(nichen_reg, 1, 1, 1, 1);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pwd_reg = new QLineEdit(widget_2);
        pwd_reg->setObjectName(QString::fromUtf8("pwd_reg"));
        pwd_reg->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout->addWidget(pwd_reg, 2, 1, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        repwd_reg = new QLineEdit(widget_2);
        repwd_reg->setObjectName(QString::fromUtf8("repwd_reg"));
        repwd_reg->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout->addWidget(repwd_reg, 3, 1, 1, 1);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        phone_reg = new QLineEdit(widget_2);
        phone_reg->setObjectName(QString::fromUtf8("phone_reg"));
        phone_reg->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout->addWidget(phone_reg, 4, 1, 1, 1);

        label_10 = new QLabel(widget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 5, 0, 1, 1);

        email_reg = new QLineEdit(widget_2);
        email_reg->setObjectName(QString::fromUtf8("email_reg"));
        email_reg->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout->addWidget(email_reg, 5, 1, 1, 1);


        verticalLayout_4->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        regist = new QToolButton(widget_3);
        regist->setObjectName(QString::fromUtf8("regist"));
        regist->setMinimumSize(QSize(300, 40));
        regist->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"font: 10pt \"Sans Serif\";\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(255, 255, 255);\n"
"border-radius:3px;"));
        regist->setAutoRaise(true);

        horizontalLayout_2->addWidget(regist);


        verticalLayout_4->addWidget(widget_3);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        widget_3->raise();
        widget_2->raise();

        horizontalLayout_3->addWidget(widget);

        horizontalSpacer_8 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        stackedWidget->addWidget(reg_page_3);
        set_page_3 = new QWidget();
        set_page_3->setObjectName(QString::fromUtf8("set_page_3"));
        horizontalLayout_7 = new QHBoxLayout(set_page_3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_18 = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_18);

        widget_4 = new QWidget(set_page_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_5 = new QVBoxLayout(widget_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_7);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        gridLayout_2 = new QGridLayout(widget_6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_12 = new QLabel(widget_6);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 0, 0, 1, 1);

        label_13 = new QLabel(widget_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 2, 0, 1, 2);

        port = new QLineEdit(widget_6);
        port->setObjectName(QString::fromUtf8("port"));
        port->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout_2->addWidget(port, 2, 2, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 1, 0, 1, 1);

        ip_addr = new QLineEdit(widget_6);
        ip_addr->setObjectName(QString::fromUtf8("ip_addr"));
        ip_addr->setMinimumSize(QSize(200, 0));
        ip_addr->setStyleSheet(QString::fromUtf8("border-bottom:2px solid "));

        gridLayout_2->addWidget(ip_addr, 0, 2, 1, 1);


        verticalLayout_5->addWidget(widget_6);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_8);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        server_ok = new QToolButton(widget_5);
        server_ok->setObjectName(QString::fromUtf8("server_ok"));
        server_ok->setMinimumSize(QSize(300, 40));
        server_ok->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);\n"
"font: 10pt \"Sans Serif\";\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;"));
        server_ok->setAutoRaise(true);

        horizontalLayout_4->addWidget(server_ok);


        verticalLayout_5->addWidget(widget_5);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);


        horizontalLayout_7->addWidget(widget_4);

        horizontalSpacer_19 = new QSpacerItem(67, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_19);

        stackedWidget->addWidget(set_page_3);

        verticalLayout->addWidget(stackedWidget);

        QWidget::setTabOrder(name_log, pwd_log);
        QWidget::setTabOrder(pwd_log, rem_pwd);
        QWidget::setTabOrder(rem_pwd, reg_log);
        QWidget::setTabOrder(reg_log, login_ok);
        QWidget::setTabOrder(login_ok, name_reg);
        QWidget::setTabOrder(name_reg, nichen_reg);
        QWidget::setTabOrder(nichen_reg, pwd_reg);
        QWidget::setTabOrder(pwd_reg, repwd_reg);
        QWidget::setTabOrder(repwd_reg, phone_reg);
        QWidget::setTabOrder(phone_reg, email_reg);
        QWidget::setTabOrder(email_reg, regist);
        QWidget::setTabOrder(regist, ip_addr);
        QWidget::setTabOrder(ip_addr, port);
        QWidget::setTabOrder(port, server_ok);

        retranslateUi(Login);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        pwd_log->setText(QString());
        name_log->setText(QString());
        rem_pwd->setText(QCoreApplication::translate("Login", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        reg_log->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        login_ok->setText(QCoreApplication::translate("Login", "\347\231\273   \345\275\225", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("Login", "\346\230\265\347\247\260", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("Login", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_6->setText(QCoreApplication::translate("Login", "\347\224\265\350\257\235\345\217\267\347\240\201", nullptr));
        label_10->setText(QCoreApplication::translate("Login", "\351\202\256\347\256\261", nullptr));
        regist->setText(QCoreApplication::translate("Login", "\346\263\250  \345\206\214", nullptr));
        label_12->setText(QCoreApplication::translate("Login", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        label_13->setText(QCoreApplication::translate("Login", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", nullptr));
        server_ok->setText(QCoreApplication::translate("Login", "\347\241\256 \345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
