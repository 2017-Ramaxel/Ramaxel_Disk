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
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    // 绘图事件函数
    void paintEvent(QPaintEvent *event);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
