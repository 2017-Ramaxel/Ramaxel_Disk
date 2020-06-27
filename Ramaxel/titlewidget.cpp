#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QMouseEvent>
#include <stdio.h>
#include <algorithm>

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    ui->logo->setPixmap(QPixmap(":/upload/logo.png").scaled(200,150));



    m_parent = parent;

    //按钮关闭
    connect(ui->set,&QToolButton::clicked,[=](){
        //发送信号
        emit showsetwg();
    });
    connect(ui->min,&QToolButton::clicked,[=](){
        m_parent->showMinimized();
    });
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
