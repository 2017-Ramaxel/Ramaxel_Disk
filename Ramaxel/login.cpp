#include "login.h"
#include "ui_login.h"
#include "QPainter"
#include "common/common.h"

#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    this->setFont(QFont("",10,QFont::Normal,false));
    this->setWindowTitle("Ramaxel登录");
    // 此处无需指定父窗口
    m_mainWin = new MainWindow;
    // 窗口图标
    this->setWindowIcon(QIcon(":/images/logo.ico"));
    m_mainWin->setWindowIcon(QIcon(":/images/logo.ico"));

    this->setFont(QFont("新宋体", 12, QFont::Bold, false));
    // 密码
    ui->pwd_log->setEchoMode(QLineEdit::Password);
    ui->pwd_reg->setEchoMode(QLineEdit::Password);
    ui->repwd_reg->setEchoMode(QLineEdit::Password);
    // 当前显示的窗口
    ui->stackedWidget->setCurrentIndex(0);
    ui->name_log->setFocus();
    // 数据的格式提示
    ui->name_log->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->name_reg->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->nichen_reg->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->pwd_log->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");
    ui->pwd_reg->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");
    ui->repwd_reg->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");

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

    // 切换用户 - 重新登录
    connect(m_mainWin, &MainWindow::changeUser, [=]()
    {
        m_mainWin->hide();
        this->show();
    });

}



Login::~Login()
{
    delete ui;
}


// 登陆用户需要使用的json数据包
QByteArray Login::setLoginJson(QString user, QString pwd)
{
    QMap<QString, QVariant> login;
    login.insert("user",user);
    login.insert("pwd",pwd);
    /*json数据如
        {
            user:xxxx,
            pwd:xxx
        }
    */
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(login);
    if(jsonDocument.isNull()){
        cout << " jsonDocument.isNull() ";
        return "";
    }
    return jsonDocument.toJson();
}


// 注册用户需要使用的json数据包
QByteArray Login::setRegisterJson(QString userName, QString nickName, QString firstPwd, QString phone, QString email)
{
    QMap<QString, QVariant> reg;
    reg.insert("userName", userName);
    reg.insert("nickName", nickName);
    reg.insert("firstPwd", firstPwd);
    reg.insert("phone", phone);
    reg.insert("email", email);

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(reg);
    if(jsonDoc.isNull()){
        cout << " jsonDocument.isNull() ";
        return "";
    }
    return jsonDoc.toJson();
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

    //登录信息写入配置文件
    m_cm.writeLoginInfo(user,pwd,ui->rem_pwd->isChecked());

    // 当前窗口隐藏
    this->hide();
    // 主界面窗口显示
    m_mainWin->showMainWindow();
}









