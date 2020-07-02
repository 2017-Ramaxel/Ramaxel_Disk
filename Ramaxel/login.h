#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "common/common.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    // 设置登陆用户信息的json包
    QByteArray setLoginJson(QString user, QString pwd);

    // 设置注册用户信息的json包
    QByteArray setRegisterJson(QString userName, QString nickName,
                               QString firstPwd, QString phone, QString email);

    //得到服务器处理登录后的返回码
    QStringList getLoginStatus(QByteArray json);
private:
    // 读取配置信息，设置默认登录状态，默认设置信息
    void readCfg();

private:
    Ui::Login *ui;
    // 主窗口指针
    MainWindow* m_mainWin;
    Common m_cm;
    QNetworkAccessManager *m_manager;



protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_regist_clicked();
    void on_server_ok_clicked();
    void on_login_ok_clicked();

};

#endif // LOGIN_H
