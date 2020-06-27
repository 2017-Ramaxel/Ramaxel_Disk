#ifndef MYFILEWG_H
#define MYFILEWG_H

#include <QWidget>
#include "common/common.h"

namespace Ui {
class MyFileWg;
}

class MyFileWg : public QWidget
{
    Q_OBJECT

public:
    explicit MyFileWg(QWidget *parent = nullptr);
    ~MyFileWg();


    // Normal：普通用户列表，PvAsc：按下载量升序， PvDesc：按下载量降序
    enum Display{Normal, PvAsc, PvDesc};
    // 显示用户的文件列表
    void refreshFiles(Display cmd=Normal);

private:
    Ui::MyFileWg *ui;

signals:
    void loginAgainSignal();
    void gotoTransfer(TransferStatus status);
};

#endif // MYFILEWG_H
