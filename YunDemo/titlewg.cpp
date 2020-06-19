#include "titlewg.h"
#include "ui_titlewg.h"
#include <QMouseEvent>

TitleWg::TitleWg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWg)
{
    ui->setupUi(this);

    // logo图片
    ui->logo->setPixmap(QPixmap(":/images/logo.ico").scaled(40, 40));

    ui->wgtitle->setStyleSheet("color:rgb(255, 255, 255)");

    m_parent = parent;

}

TitleWg::~TitleWg()
{
    delete ui;
}

void TitleWg::mouseMoveEvent(QMouseEvent *event)
{
    // 只允许左键拖动
    if(event->buttons() & Qt::LeftButton)
    {
        // 窗口跟随鼠标移动
        // 窗口左上角点 = 鼠标当前位置 - 差值
        m_parent->move(event->globalPos() - m_pt);
    }
}

void TitleWg::mousePressEvent(QMouseEvent *ev)
{
    // 如果鼠标左键按下
    if(ev->button() == Qt::LeftButton)
    {
        // 求差值 = 鼠标当前位置 - 窗口左上角点
        m_pt = ev->globalPos() - m_parent->geometry().topLeft();
    }
}
