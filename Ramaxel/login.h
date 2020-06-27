#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "common/common.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();


private:
    Ui::Login *ui;
    // 主窗口指针
    MainWindow* m_mainWin;
    Common m_cm;



protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_regist_clicked();
    void on_server_ok_clicked();
    void on_login_ok_clicked();

    // 读取配置信息，设置默认登录状态，默认设置信息
    void readCfg();
};

#endif // LOGIN_H
