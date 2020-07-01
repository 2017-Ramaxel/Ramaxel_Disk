#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QMouseEvent>
#include <stdio.h>
#include <algorithm>
#include <QPainter>

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    ui->logo->setPixmap(QPixmap(":/upload/logo.png").scaled(200,150));



    m_parent = parent;

    //设置按钮
    connect(ui->set,&QToolButton::clicked,[=](){
        //发送信号
        emit showsetwg();
    });

    //返回关闭按钮
    connect(ui->close,&QToolButton::clicked,[=](){
        emit closewindow();
    });
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_parent->move(event->globalPos() - m_pt);
    }
}

void TitleWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pt = event->globalPos() - m_parent->geometry().topLeft();
    }
}
void TitleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap bk("./images/title_bk.jpg");
    painter.drawPixmap(0, 0, width(), height(), bk);
}
