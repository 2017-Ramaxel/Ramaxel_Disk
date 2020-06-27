/********************************************************************************
** Form generated from reading UI file 'buttongroup.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONGROUP_H
#define UI_BUTTONGROUP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ButtonGroup
{
public:
    QHBoxLayout *horizontalLayout_3;
    QWidget *btns_wg;
    QHBoxLayout *horizontalLayout;
    QToolButton *login_usr;
    QToolButton *myfile;
    QToolButton *sharelist;
    QToolButton *download;
    QToolButton *transform;
    QToolButton *switchuser;

    void setupUi(QWidget *ButtonGroup)
    {
        if (ButtonGroup->objectName().isEmpty())
            ButtonGroup->setObjectName(QString::fromUtf8("ButtonGroup"));
        ButtonGroup->resize(795, 115);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ButtonGroup->sizePolicy().hasHeightForWidth());
        ButtonGroup->setSizePolicy(sizePolicy);
        ButtonGroup->setMaximumSize(QSize(16777215, 115));
        horizontalLayout_3 = new QHBoxLayout(ButtonGroup);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(9, 9, 9, 9);
        btns_wg = new QWidget(ButtonGroup);
        btns_wg->setObjectName(QString::fromUtf8("btns_wg"));
        horizontalLayout = new QHBoxLayout(btns_wg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        login_usr = new QToolButton(btns_wg);
        login_usr->setObjectName(QString::fromUtf8("login_usr"));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(8);
        login_usr->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/upload/images/title_user.png"), QSize(), QIcon::Normal, QIcon::Off);
        login_usr->setIcon(icon);
        login_usr->setIconSize(QSize(70, 70));
        login_usr->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        login_usr->setAutoRaise(true);

        horizontalLayout->addWidget(login_usr);

        myfile = new QToolButton(btns_wg);
        myfile->setObjectName(QString::fromUtf8("myfile"));
        myfile->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/upload/images/tile_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        myfile->setIcon(icon1);
        myfile->setIconSize(QSize(50, 50));
        myfile->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        myfile->setAutoRaise(true);

        horizontalLayout->addWidget(myfile);

        sharelist = new QToolButton(btns_wg);
        sharelist->setObjectName(QString::fromUtf8("sharelist"));
        sharelist->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/upload/images/title_share.png"), QSize(), QIcon::Normal, QIcon::Off);
        sharelist->setIcon(icon2);
        sharelist->setIconSize(QSize(50, 50));
        sharelist->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        sharelist->setAutoRaise(true);

        horizontalLayout->addWidget(sharelist);

        download = new QToolButton(btns_wg);
        download->setObjectName(QString::fromUtf8("download"));
        download->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/upload/images/tile_hot.png"), QSize(), QIcon::Normal, QIcon::Off);
        download->setIcon(icon3);
        download->setIconSize(QSize(50, 50));
        download->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        download->setAutoRaise(true);

        horizontalLayout->addWidget(download);

        transform = new QToolButton(btns_wg);
        transform->setObjectName(QString::fromUtf8("transform"));
        transform->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/upload/images/title_data.png"), QSize(), QIcon::Normal, QIcon::Off);
        transform->setIcon(icon4);
        transform->setIconSize(QSize(50, 50));
        transform->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        transform->setAutoRaise(true);

        horizontalLayout->addWidget(transform);

        switchuser = new QToolButton(btns_wg);
        switchuser->setObjectName(QString::fromUtf8("switchuser"));
        switchuser->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/upload/images/title_change.png"), QSize(), QIcon::Normal, QIcon::Off);
        switchuser->setIcon(icon5);
        switchuser->setIconSize(QSize(50, 50));
        switchuser->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        switchuser->setAutoRaise(true);

        horizontalLayout->addWidget(switchuser);


        horizontalLayout_3->addWidget(btns_wg);


        retranslateUi(ButtonGroup);

        QMetaObject::connectSlotsByName(ButtonGroup);
    } // setupUi

    void retranslateUi(QWidget *ButtonGroup)
    {
        ButtonGroup->setWindowTitle(QCoreApplication::translate("ButtonGroup", "Form", nullptr));
        login_usr->setText(QCoreApplication::translate("ButtonGroup", "kevin", nullptr));
        myfile->setText(QCoreApplication::translate("ButtonGroup", "\346\210\221\347\232\204\346\226\207\344\273\266", nullptr));
        sharelist->setText(QCoreApplication::translate("ButtonGroup", "\345\205\261\344\272\253\345\210\227\350\241\250", nullptr));
        download->setText(QCoreApplication::translate("ButtonGroup", "\344\270\213\350\275\275\346\246\234", nullptr));
        transform->setText(QCoreApplication::translate("ButtonGroup", "\344\274\240\350\276\223\345\210\227\350\241\250", nullptr));
        switchuser->setText(QCoreApplication::translate("ButtonGroup", "\345\210\207\346\215\242\347\224\250\346\210\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonGroup: public Ui_ButtonGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONGROUP_H
