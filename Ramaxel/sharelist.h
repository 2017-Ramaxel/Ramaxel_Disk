#ifndef SHARELIST_H
#define SHARELIST_H

#include <QWidget>
#include <QTimer>
#include "common/common.h"
#include "selfwidget/mymenu.h"

namespace Ui {
class ShareList;
}

class ShareList : public QWidget
{
    Q_OBJECT

public:
    explicit ShareList(QWidget *parent = nullptr);
    ~ShareList();

    //初始化
    void initListWidget();
    //添加右键菜单
    void addActionMenu();

//------------刷新action------------
    //刷新共享列表页面
    void refreshFiles();

    //删除当前文件列表
    void clearShareFileList();

    //获取新的文件列表
    void getUserFilesList();

    //获取文件item
    void refreshFileItems();

    //设置文件列表Json包
    QByteArray setFilesListJson(int start, int count);

    //解析json信息
    void getFileJsonInfo(QByteArray array);

    //清除所有item
    void clearItems();

//----------下载文件处理----------------
    // 取出下载任务列表的队首任务，下载完后，再取下一个任务
    void downloadFilesAction();


signals:
    void gotoTransfer(TransferStatus status);


private:
    Ui::ShareList *ui;
    Common m_cm;
    QTimer m_downloadTimer;
    enum CMD{Property, Cancel, Save};

    //文件右键菜单
    MyMenu *m_menufile;
    QAction *m_downloadAction;
    QAction *m_propertyAction;
    QAction *m_cancelAction;
    QAction *m_saveAction;
    //空白处右键菜单
    MyMenu *m_menu;
    QAction *m_refreshAction;

    QNetworkAccessManager *m_manager;

    QList<FileInfo *> m_shareFileList;      //共享文件列表
    long m_userFileCount;   //用户文件数目

    int m_start;            //文件位置起点
    int m_count;            //每次请求文件个数
};

#endif // SHARELIST_H
