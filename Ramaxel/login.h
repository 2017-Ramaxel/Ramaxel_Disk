#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

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

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_regist_clicked();
    void on_server_ok_clicked();
    void on_login_ok_clicked();
};

#endif // LOGIN_H
