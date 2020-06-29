#include "login.h"
#include "ui_login.h"
#include "QPainter"
#include "common/common.h"
#include "common/des.h"
#include "logininfoinstance.h"
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonArray>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    this->setFont(QFont("",10,QFont::Normal,false));
    this->setWindowTitle("Ramaxel登录");

    m_cm.getFileTypeList();

    // 初始化网络请求（http）类
    m_manager = Common::getNetManager();
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

    ui->name_log->setPlaceholderText("账号");
    ui->pwd_log->setPlaceholderText("密码");
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

    // 切换用户 - 重新登录
    connect(m_mainWin, &MainWindow::changeUser, [=]()
    {
        m_mainWin->hide();
        this->show();
    });
    readCfg();

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

    QString ip = ui->ip_addr->text();
    QString port = ui->port->text();

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

    // 将用户输入的注册信息 -> json对象
        QByteArray postData = setRegisterJson(userName,nickName, m_cm.getStrMd5(firstPwd), phone, email);

        // 发送http请求协议
        QNetworkAccessManager* manager = Common::getNetManager();
        // http请求协议头
        QNetworkRequest request;
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ContentLengthHeader, postData.size());
        // url

        QString url = QString("http://%1:%2/reg").arg(ip).arg(port);
        request.setUrl(QUrl(url));
        QNetworkReply* reply = manager->post(request, postData);

        // 接收server返回的数据
        connect(reply, &QNetworkReply::readyRead,[=]()
        {
            // 读返回的数据
            // 成功 {"code":"002"}
            // 该用户已存在 {"code":"003"}
            // 失败 {"code":"004"}
            QByteArray jsonData = reply->readAll();
            qDebug() << "服务器注册返回码" << jsonData;
            // 解析json字符串
            // 得到一个数 QString status
            QString status = m_cm.getCode(jsonData);

            if("002" == status){
                // success
                // 将当前注册的用户信息填写到登录的输入框中
                QMessageBox::information(this, "恭喜", "用户名注册成功");

                ui->name_log->setText(userName);
                ui->pwd_log->setText(firstPwd);
                // 当前注册信息清除
                ui->name_reg->clear();
                ui->nichen_reg->clear();
                ui->pwd_reg->clear();
                ui->repwd_reg->clear();
                ui->phone_reg->clear();
                ui->email_reg->clear();
                // 跳转到登录页面
                ui->stackedWidget->setCurrentWidget(ui->login_page_3);
            }
            else if("003" == status){
                // 该用户已存在
                QMessageBox::warning(this,"警告","当前注册的用户yicunzai");
                return;
            }
            else if("004" == status){
                // failed
                QMessageBox::critical(this,"警告","注册失败");
                return ;
            }
        });
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
    qDebug()<<"write:::"<<user.toStdString().data()<<pwd.toStdString().data();

    //设置登录信息json包，MD5加密
    QByteArray array = setLoginJson(user,m_cm.getStrMd5(pwd));
    //设置登录url
    QNetworkRequest request;
    QString url = QString("http://%1:%2/login").arg(address).arg(port);
    request.setUrl(QUrl(url));

    //请求头信息
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setHeader(QNetworkRequest::ContentLengthHeader,QVariant(array.size()));

    //向服务器发送post请求
    QNetworkReply* reply = m_manager->post(request,array);
    qDebug()<<array.data();

    connect(reply,&QNetworkReply::finished,[=]()
    {
        //出错
        if(reply->error() != QNetworkReply::NoError)
        {
            qDebug() << reply->errorString().toStdString().data();
            //释放资源
            reply->deleteLater();
            return ;
        }

        //将server回写的数据取出来
        QByteArray json = reply->readAll();

        //001:成功
        //002:失败

        qDebug()<<"server return value:" << json.toStdString().data();
        QStringList tmpList = getLoginStatus(json);

        if(tmpList.at(0) == "000")
        {
            qDebug() <<"登录成功";
            // 设置登陆信息，显示文件列表界面需要使用这些信息
            LoginInfoInstance *p = LoginInfoInstance::getInstance(); //获取单例
            p->setLoginInfo(user, address, port, tmpList.at(1));
            qDebug() << p->getUser().toUtf8().data() << ", " << p->getIp() << ", " << p->getPort() << tmpList.at(1);

            this->hide();
            m_mainWin->showMainWindow();
        }
        else
        {
            QMessageBox::warning(this, "登录失败", "用户名或密码不正确！！！");
        }
        reply->deleteLater();//释放资源;
    });
}

//读取本地配置文件，初始化用户填写登录信息
void Login::readCfg()
{
    //服务器设置初始化，读取本地配置文件设置默认IP和端口号
    QString c_ip = m_cm.getCfgValue("web_server","ip");
    QString c_port =m_cm.getCfgValue("web_server","port");
    ui->ip_addr->setText(c_ip);
    ui->port->setText(c_port);

    //初始化用户账号密码
    QString user = m_cm.getCfgValue("login", "user");
    QString pwd = m_cm.getCfgValue("login", "pwd");
    QString remeber = m_cm.getCfgValue("login", "remember");

    int ret = 0;

    if(remeber == "yes")//记住密码
    {
        //密码解密
        unsigned char encPwd[512] = {0};
        int encPwdLen = 0;
        //toLocal8Bit(), 转换为本地字符集，默认windows则为gbk编码，linux为utf-8编码
        QByteArray tmp = QByteArray::fromBase64( pwd.toLocal8Bit());
        ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encPwd, &encPwdLen);
        if(ret != 0)
        {
            qDebug() << "DesDec";
            return;
        }
        ui->rem_pwd->setChecked(true);

    }
    else //没有记住密码
    {
        ui->pwd_log->setText("");
        ui->rem_pwd->setChecked(false);
    }

    //用户解密
    unsigned char encUsr[512] = {0};
    int encUsrLen = 0;
    //toLocal8Bit(), 转换为本地字符集，如果windows则为gbk编码，如果linux则为utf-8编码
    QByteArray tmp = QByteArray::fromBase64( user.toLocal8Bit());
    ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encUsr, &encUsrLen);
    if(ret != 0)
    {
        qDebug() << "DesDec";
        return;
    }
}


//获取登录返回码
QStringList Login::getLoginStatus(QByteArray json)
{
    QJsonParseError error;
    QStringList list;

    // 将来源数据json转化为JsonDocument
    // 由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (doc.isNull() || doc.isEmpty())
        {
            qDebug() << "doc.isNull() || doc.isEmpty()";
            return list;
        }

        if( doc.isObject() )
        {
            //取得最外层这个大对象
            QJsonObject obj = doc.object();
            qDebug() << "服务器返回的数据";
            //状态码
            list.append( obj.value( "code" ).toString() );
            //登陆token
            list.append( obj.value( "token" ).toString() );
        }
    }
    else
    {
        qDebug() << "err = " << error.errorString().toStdString().data();
    }

    return list;

}






