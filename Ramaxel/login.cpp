#include "login.h"
#include "ui_login.h"
#include "QPainter"
#include "common/common.h"

#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <common/des.h>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setFont(QFont("",10,QFont::Normal,false));
    this->setWindowTitle("Ramaxel登录");
    // 此处无需指定父窗口
    m_mainWin = new MainWindow;
    // 读取配置文件信息，并初始化
    readCfg();
    // 窗口图标
    this->setWindowIcon(QIcon(":/images/logo.ico"));
    m_mainWin->setWindowIcon(QIcon(":/images/logo.ico"));

    // 设置当前窗口的字体信息
    this->setFont(QFont("新宋体", 12, QFont::Bold, false));
    // 密码
    ui->pwd_log->setEchoMode(QLineEdit::Password);
    ui->pwd_reg->setEchoMode(QLineEdit::Password);
    ui->repwd_reg->setEchoMode(QLineEdit::Password);
    // 当前显示的窗口
    ui->stackedWidget->setCurrentIndex(0);
    ui->name_log->setFocus();
    // 数据的格式提示
    ui->name_log->setToolTip("字符个数: 3~16");
    ui->name_reg->setToolTip("字符个数: 3~16");
    ui->nichen_reg->setToolTip("字符个数: 3~16");
    ui->pwd_log->setToolTip("字符个数: 6~18");
    ui->pwd_reg->setToolTip("字符个数: 6~18");
    ui->repwd_reg->setToolTip("字符个数: 6~18");

    //接收标题栏发送的信号进行处理
    connect(ui->titlewidget,&TitleWidget::closewindow,[=](){
        //如果是设置界面
        if(ui->stackedWidget->currentWidget() == ui->set_page_3)
        {
            ui->stackedWidget->setCurrentWidget(ui->login_page_3);
        }
        //如果是注册界面
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
    m_cm.writeWebInfo(ip,port);
}

//登录按钮
void Login::on_login_ok_clicked()
{
    // 获取用户登录信息
    QString user = ui->name_log->text();
    QString pwd = ui->pwd_log->text();
    QString address = ui->ip_addr->text();
    QString port = ui->port->text();

    // 数据校验
    QRegExp regexp(USER_REG);
    if(!regexp.exactMatch(user))
    {
        QMessageBox::warning(this, "警告", "用户名格式不正确");
        ui->name_log->clear();
        ui->name_log->setFocus();
        return;
    }
    regexp.setPattern(PASSWD_REG);
    if(!regexp.exactMatch(pwd))
    {
        QMessageBox::warning(this, "警告", "密码格式不正确");
        ui->pwd_log->clear();
        ui->pwd_log->setFocus();
        return;
    }

    // 当前窗口隐藏
    this->hide();
    // 主界面窗口显示
    m_mainWin->show();
}

// 读取配置信息，设置默认登录状态，默认设置信息
void Login::readCfg()
{
    QString user = m_cm.getCfgValue("login", "user");
    QString pwd = m_cm.getCfgValue("login", "pwd");
    QString remeber = m_cm.getCfgValue("login", "remember");
//    int ret = 0;
//    if(remeber == "yes")//记住密码
//    {

//        //密码解密
//        unsigned char encPwd[512] = {0};
//        int encPwdLen = 0;
//        //toLocal8Bit(), 转换为本地字符集，默认windows则为gbk编码，linux为utf-8编码
//        QByteArray tmp = QByteArray::fromBase64( pwd.toLocal8Bit());
//        ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encPwd, &encPwdLen);
//        cout<<"hhh"<<ret;
//        if(ret != 0)
//        {
//            cout << "DesDec";
//            return;
//        }

//    #ifdef _WIN32 //如果是windows平台
//        //fromLocal8Bit(), 本地字符集转换为utf-8
//        ui->log_pwd->setText( QString::fromLocal8Bit( (const char *)encPwd, encPwdLen ) );
//    #else //其它平台
//        ui->pwd_log->setText( (const char *)encPwd );
//    #endif

//        ui->rem_pwd->setChecked(true);

//    }
//    else //没有记住密码
//    {
//        ui->pwd_log->setText("");
//        ui->rem_pwd->setChecked(false);
//    }

//    //用户解密
//    unsigned char encUsr[512] = {0};
//    int encUsrLen = 0;
//    //toLocal8Bit(), 转换为本地字符集，如果windows则为gbk编码，如果linux则为utf-8编码
//    QByteArray tmp = QByteArray::fromBase64( user.toLocal8Bit());
//    ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encUsr, &encUsrLen);
//    if(ret != 0)
//    {
//        cout << "DesDec";
//        return;
//    }

//    #ifdef _WIN32 //如果是windows平台
//        //fromLocal8Bit(), 本地字符集转换为utf-8
//        ui->log_usr->setText( QString::fromLocal8Bit( (const char *)encUsr, encUsrLen ) );
//    #else //其它平台
//        ui->name_log->setText( (const char *)encUsr );
//    #endif


    QString ip = m_cm.getCfgValue("web_server", "ip");
    QString port = m_cm.getCfgValue("web_server", "port");
    ui->ip_addr->setText(ip);
    ui->port->setText(port);
}
