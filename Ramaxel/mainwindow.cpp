#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ramaxel网盘");
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 处理所有信号
    managerSignals();
    // 默认显示我的文件窗口
    ui->stackedWidget->setCurrentWidget(ui->myfiles_page);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMainWindow()
{
    m_common.moveToCenter(this); //居中显示
    // 切换到我的文件页面
    ui->stackedWidget->setCurrentWidget(ui->myfiles_page);
    // 刷新用户文件列表
    ui->myfiles_page->refreshFiles();
}

void MainWindow::managerSignals()
{
    // 我的文件
    connect(ui->btn_group, &ButtonGroup::sigMyFile, [=]()
    {
        ui->stackedWidget->setCurrentIndex(0);
        // 刷新文件列表
        ui->myfiles_page->refreshFiles();
    });
    // 分享列表
    connect(ui->btn_group, &ButtonGroup::sigShareList, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->sharefile_page);
        // 刷新分享列表
        //ui->sharefile_page->refreshFiles();
    });
    // 下载榜
    connect(ui->btn_group, &ButtonGroup::sigDownload, [=]()
   {

        ui->stackedWidget->setCurrentWidget(ui->ranking_page);
        // 刷新下载榜列表
        //ui->ranking_page->refreshFiles();
    });
    // 传输列表
    connect(ui->btn_group, &ButtonGroup::sigTransform, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->transfer_page);
    });
    // 切换用户
    connect(ui->btn_group, &ButtonGroup::sigSwitchUser, [=]()
    {
        int choose;
        choose=QMessageBox::question(this, tr("退出登录"),
                                     QString(tr("确认退出登录?")),
                                     QMessageBox::Yes | QMessageBox::No);

      if (choose== QMessageBox::No)
       {
          //如果点否就什么都不做
      }
      else if (choose== QMessageBox::Yes)
      {
        qDebug() << "bye bye...";
        loginAgain(); //程序退出
      }


    });
    // stack窗口切换
    connect(ui->myfiles_page, &MyFileWg::gotoTransfer, [=](TransferStatus status)
    {
        ui->btn_group->slotButtonClick(Page::TRANSFER);
        if(status == TransferStatus::Uplaod)
        {
            ui->transfer_page->showUpload();
        }
        else if(status == TransferStatus::Download)
        {
            ui->transfer_page->showDownload();
        }
    });
    // 信号传递
    connect(ui->sharefile_page, &ShareList::gotoTransfer, ui->myfiles_page, &MyFileWg::gotoTransfer);

}

void MainWindow::loginAgain()
{
    // 发送信号，告诉登陆窗口，切换用户
    emit changeUser();
    // 清空上一个用户的上传或下载任务
    //ui->myfiles_page->clearAllTask();

    // 清空上一个用户的一些文件显示信息
    //ui->myfiles_page->clearFileList();
    //ui->myfiles_page->clearItems();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap bk(":/images/title_bk3.jpg");
    painter.drawPixmap(0, 0, width(), height(), bk);
}
