#include "transfer.h"
#include "ui_transfer.h"
#include <QFile>

Transfer::Transfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transfer)
{
    ui->setupUi(this);

    //设置上传布局实例

    // 设置下载布局实例


    //此属性保存当前选项卡页面的索引位置
    ui->tabWidget->setCurrentIndex(0);

    //切换tab页
    connect(ui->tabWidget, &QTabWidget::currentChanged, [=](int index){
        if(index == 0){  //上传
            emit currentTabSignal("正在上传");
        } else if(index == 1){   //下载
            emit currentTabSignal("正在下载");
        } else {    //传输记录
            emit currentTabSignal("传输记录");
            displayDataRecord();    //显示数据传输记录
        }
    });

    //设置样式 tabWidget
    //styleSheet : QString
    //此属性保存小部件的样式表
    //样式表包含对小部件样式的自定义的文本描述，如Qt样式表文档中所述。
    ui->tabWidget->tabBar()->setStyleSheet(
                "QTabBar::tab{"
                "background-color: rgb(182, 202, 211);"
                "border-right: 1px solid gray;"
                "padding: 6px"
                "}"
                "QTabBar::tab:selected, QtabBar::tab:hover {"
                "background-color: rgb(20, 186, 248);"
                "}"
                );

    // 清空记录
}

Transfer::~Transfer()
{
    delete ui;
}

void Transfer::showUpload()
{
    ui->tabWidget->setCurrentWidget(ui->upload);
}

void Transfer::showDownload()
{
    ui->tabWidget->setCurrentWidget(ui->download);
}

// 显示数据传输记录
void Transfer::displayDataRecord(QString path)
{
}

