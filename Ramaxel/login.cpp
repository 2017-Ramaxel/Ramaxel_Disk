#include "login.h"
#include "ui_login.h"
#include "QPainter"
#include "common/common.h"

#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    this->setFont(QFont("",10,QFont::Normal,false));



    //接收标题栏发送的信号进行处理
    connect(ui->titlewidget,&TitleWidget::closewindow,[=](){
        if(ui->stackedWidget->currentWidget() == ui->set_page_3)
        {
            ui->stackedWidget->setCurrentWidget(ui->login_page_3);
        }
        else if (ui->stackedWidget->currentWidget() == ui->reg_page_3) {
            ui->stackedWidget->setCurrentWidget(ui->login_page_3);
            //清空注册数据
            ui->name_reg->clear();
            ui->pwd_reg->clear();
            ui->repwd_reg->clear();
            ui->nichen_reg->clear();
            ui->phone_reg->clear();
            ui->email_reg->clear();
        }
        else{
            this->close();
        }
    });

    //进入注册界面
    connect(ui->reg_log,&QToolButton::clicked,[=](){
        ui->stackedWidget->setCurrentWidget(ui->reg_page_3);
        ui->name_reg->setFocus();
    });

    //进入服务器设置界面
    connect(ui->titlewidget,&TitleWidget::showsetwg,[=](){
        ui->stackedWidget->setCurrentWidget(ui->set_page_3);
    });
}



Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap pixmap("RGB(255,255,255)");
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);

}

//注册按钮
void Login::on_regist_clicked()
{
    // 从控件中取出用户输入的数据
    QString userName = ui->name_reg->text();
    QString nickName = ui->nichen_reg->text();
    QString firstPwd = ui->pwd_reg->text();
    QString surePwd = ui->repwd_reg->text();
    QString phone = ui->phone_reg->text();
    QString email = ui->email_reg->text();

    //数据校验
    QRegExp regexp(USER_REG);
    if(!regexp.exactMatch(userName)){
        QMessageBox::warning(this, "警告", "用户名格式不正确");
        ui->name_reg->clear();
        ui->name_reg->setFocus();
        return;
    }
    if(!regexp.exactMatch(nickName))
    {
        QMessageBox::warning(this, "警告", "昵称格式不正确");
        ui->nichen_reg->clear();
        ui->nichen_reg->setFocus();
        return;
    }
    regexp.setPattern(PASSWD_REG);
    if(!regexp.exactMatch(firstPwd))
    {
        QMessageBox::warning(this, "警告", "密码格式不正确");
        ui->pwd_reg->clear();
        ui->pwd_reg->setFocus();
        return;
    }
    if(surePwd != firstPwd)
    {
        QMessageBox::warning(this, "警告", "两次输入的密码不匹配, 请重新输入");
        ui->repwd_reg->clear();
        ui->repwd_reg->setFocus();
        return;
    }
    regexp.setPattern(PHONE_REG);
    if(!regexp.exactMatch(phone))
    {
        QMessageBox::warning(this, "警告", "手机号码格式不正确");
        ui->phone_reg->clear();
        ui->phone_reg->setFocus();
        return;
    }
    regexp.setPattern(EMAIL_REG);
    if(!regexp.exactMatch(email))
    {
        QMessageBox::warning(this, "警告", "邮箱码格式不正确");
        ui->email_reg->clear();
        ui->email_reg->setFocus();
        return;
    }
}

//服务器设置完成按钮
void Login::on_server_ok_clicked()
{
    QString ip = ui->ip_addr->text();
    QString port = ui->port->text();
    QRegExp regexp(IP_REG);
    if(!regexp.exactMatch(ip))
    {
        QMessageBox::warning(this, "警告", "您输入的IP格式不正确, 请重新输入!");
        return;
    }
    // 端口号
    regexp.setPattern(PORT_REG);
    if(!regexp.exactMatch(port))
    {
        QMessageBox::warning(this, "警告", "您输入的端口格式不正确, 请重新输入!");
        return;
    }
    // 跳转到登陆界面
    ui->stackedWidget->setCurrentWidget(ui->login_page_3);
}

//登录按钮
void Login::on_login_ok_clicked()
{

}
