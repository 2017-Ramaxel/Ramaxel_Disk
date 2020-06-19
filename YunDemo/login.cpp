#include "login.h"
#include "ui_login.h"
#include <QPainter>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // 去掉创建的边框
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // 设置当前窗口所有的字体
    this->setFont(QFont("华文彩云", 16, QFont::Bold, false));

}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    // 给窗口画背景图
    QPainter p(this);
    QPixmap pixmap(":/images/login_bk.jpg");
    p.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}
