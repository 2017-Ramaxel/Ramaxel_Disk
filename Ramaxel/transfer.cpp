#include "transfer.h"
#include "ui_transfer.h"

Transfer::Transfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transfer)
{
    ui->setupUi(this);
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
