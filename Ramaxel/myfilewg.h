#ifndef MYFILEWG_H
#define MYFILEWG_H

#include <QWidget>
#include "common/common.h"
#include "selfwidget/mymenu.h"

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
    // 初始化listWidget文件列表
    void initListWidget();
    // 添加右键菜单
    void addActionMenu();

private:
    //点击右键菜单信号的槽函数
    void rightMenu(const QPoint &pos);

private:
    Ui::MyFileWg *ui;

    MyMenu *m_menu; //菜单1
    QAction *m_downloadAction; // 下载
    QAction *m_shareAction;    // 分享
    QAction *m_delAction;      // 删除
    QAction *m_propertyAction; // 属性

    MyMenu   *m_menuEmpty;          // 菜单2
    QAction *m_pvAscendingAction;  // 按下载量升序
    QAction *m_pvDescendingAction; // 按下载量降序
    QAction *m_refreshAction;      // 刷新
    QAction *m_uploadAction;       // 上传

signals:
    void loginAgainSignal();
    void gotoTransfer(TransferStatus status);
};

#endif // MYFILEWG_H
