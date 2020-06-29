#include "sharelist.h"
#include "ui_sharelist.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFileDialog>
#include "logininfoinstance.h"
#include "common/downloadtask.h"
#include "selfwidget/filepropertyinfo.h"

ShareList::ShareList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShareList)
{
    ui->setupUi(this);

    //初始化ListWidget属性
    initListWidget();
    addActionMenu();
    m_manager = Common::getNetManager();

    // 定时检查下载队列是否有任务需要下载
    connect(&m_downloadTimer, &QTimer::timeout, [=]()
    {
        // 上传文件处理，取出上传任务列表的队首任务，上传完后，再取下一个任务
        downloadFilesAction();
    });
    // 启动定时器，500毫秒间隔
    // 每个500毫秒，检测下载任务，每一次只能下载一个文件
    m_downloadTimer.start(500);
}

ShareList::~ShareList()
{
    //清空文件共享列表
    clearShareFileList();
    //清空所有item项目
    clearItems();
    delete ui;
}

// 初始化ListWidget属性
void ShareList::initListWidget()
{
    ui->listWidget->setViewMode(QListView::IconMode);   // 设置显示图标模式
    ui->listWidget->setIconSize(QSize(80, 80));         // 设置图标大小
    ui->listWidget->setGridSize(QSize(100, 120));       // 设置item大小

    // 设置QLisView大小改变时，图标的调整模式，默认是固定的，可以改成自动调整
    ui->listWidget->setResizeMode(QListView::Adjust);   // 自动适应布局

    // 设置列表可以拖动，如果想固定不能拖动，使用QListView::Static
    ui->listWidget->setMovement(QListView::Static);
    // 设置图标之间的间距, 当setGridSize()时，此选项无效
    ui->listWidget->setSpacing(30);
    ui->listWidget->setContextMenuPolicy( Qt::CustomContextMenu);

    connect(ui->listWidget, &QListWidget::customContextMenuRequested, [=](const QPoint& pos)
    {
        QListWidgetItem *item = ui->listWidget->itemAt( pos );

        if( item == NULL ) // 没有点图标
        {
            // QPoint QMouseEvent::pos()   这个只是返回相对这个widget(重载了QMouseEvent的widget)的位置。
            // QPoint QMouseEvent::globalPos()  窗口坐标，这个是返回鼠标的全局坐标
            // QPoint QCursor::pos() [static] 返回相对显示器的全局坐标
            // QWidget::pos() : QPoint 这个属性获得的是当前目前控件在父窗口中的位置
            m_menuEmpty->exec( QCursor::pos() ); // 在鼠标点击的地方弹出菜单
        }
        else // 点图标
        {
            ui->listWidget->setCurrentItem(item);
            m_menu->exec( QCursor::pos() );
        }
    });
}

void ShareList::addActionMenu()
{
    //菜单一，文件右键菜单
    m_menu = new MyMenu(this);

    m_downloadAction = new QAction("下载", this);
    m_propertyAction = new QAction("属性", this);
    m_cancelAction = new QAction("取消分享", this);
    m_saveAction = new QAction("转存文件", this);

    m_menu->addAction(m_downloadAction);
    m_menu->addAction(m_cancelAction);
    m_menu->addAction(m_saveAction);
    m_menu->addAction(m_propertyAction);

    //菜单二
    m_menuEmpty = new MyMenu(this);
    m_refreshAction = new QAction("刷新", this);
    m_menuEmpty->addAction(m_refreshAction);

    //信号与槽
    connect(m_downloadAction, &QAction::triggered, [=]()
    {
        cout << "下载文件";
        addDownloadFiles();
    });

    connect(m_cancelAction, &QAction::triggered, [=]()
    {
        cout << "取消分享";
        dealSelectedFile(Cancel);
    });

    connect(m_saveAction, &QAction::triggered, [=]()
    {
        cout << "转存文件";
        dealSelectedFile(Save);
    });

    connect(m_propertyAction, &QAction::triggered, [=]()
    {
        cout << "文件属性";
        dealSelectedFile(Property);
    });

    connect(m_refreshAction, &QAction::triggered, [=]()
    {
        cout << "刷新页面";
        //刷新共享列表的页面
        refreshFiles();
    });

}

void ShareList::refreshFiles()
{
    m_userFilesCount = 0;

    //获取用户信息
    LoginInfoInstance *login = LoginInfoInstance::getInstance();

    // 获取共享文件数目
    QString url = QString("http:// %1:%2/sharefiles?cmd=count").arg(login->getIp()).arg(login->getPort());

    QNetworkReply *reply = m_manager->get(QNetworkRequest(QUrl(url)));
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    //获取请求的数据完成时，就会发送信号SIGNAL(finished())
    connect(reply, &QNetworkReply::finished,[=]()
    {
        if(reply->error() != QNetworkReply::NoError)
        {
            cout << reply->errorString();
            reply->deleteLater();
            return ;
        }

        //服务器返回文件个数
        QByteArray array = reply->readAll();
        cout << array;
        reply->deleteLater();

        //清空文件列表信息
        clearShareFileList();

        m_userFilesCount = array.toLong();
        cout << "userFilesCount = " << m_userFilesCount;
        if (m_userFilesCount > 0)
        {
            //获取文件列表
            m_start = 0;
            m_count = 10;

            getUserFilesList();
        }
        else
        {
            //更新文件item
            refreshFileItems();
        }
    });
}

void ShareList::clearShareFileList()
{
    int n = m_shareFileList.size();
    for (int i = 0; i < n; ++i)
    {
        FileInfo *tmp = m_shareFileList.takeFirst();
        delete tmp;
    }
}

// 获取共享文件列表
void ShareList::getUserFilesList()
{
    cout << m_userFilesCount;
    if(m_userFilesCount <= 0)
    {
        cout << "获取共享文件列表条件结束";
        refreshFileItems();
        return;
    }
    else if(m_count >m_userFilesCount)
    {
        m_count = m_userFilesCount;
    }

   QNetworkRequest request;
    //获取登录用户
   LoginInfoInstance *login = LoginInfoInstance::getInstance(); // 获取单例
   QString url = QString("http://%1:%2/sharefiles?cmd=normal").arg(login->getIp()).arg(login->getPort());
   request.setUrl(QUrl(url));

   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   QByteArray data = setFilesListJson(m_start, m_count);

//   //文件数量减少，开始位置更改
//   m_start = m_start + m_count;
//   m_userFilesCount = m_userFilesCount - m_count;
   // 改变文件起点位置
   m_start += m_count;
   m_userFilesCount -= m_count; // 文件数量递减

   QNetworkReply* reply = m_manager->post(request, data);
   if(reply == nullptr)
   {
       cout << "reply == Null";
       return;
   }

   //获取请求的数据完成时，就会发送信号SIGNAL(finished())
   connect(reply, &QNetworkReply::finished,[=]()
   {
       if(reply->error() != QNetworkReply::NoError)
       {
           cout << reply->errorString();
           reply->deleteLater();
           return ;
       }

       //服务器返回文件个数
       QByteArray array = reply->readAll();
       reply->deleteLater();

       //处理文件列表Json信息，015为错误码
       if("015" != m_cm.getCode(array))
       {
           //解析文件列表json，存放在文件列表中
            getFileJsonInfo(array);

            getUserFilesList();
       }
       else
       {
           cout << "015错误码";
       }
   });
}

//更新文件item
void ShareList::refreshFileItems()
{
    //清空所有item
    clearItems();

    int n = m_shareFileList.size();
    for (int i = 0; i < n; ++i)
    {
        FileInfo *tmp = m_shareFileList.at(i);
        QListWidgetItem *item = tmp->item;
        //listWidget添加item
        ui->listWidget->addItem(item);
    }
}

//文件列表的json
QByteArray ShareList::setFilesListJson(int start, int count)
{
    QMap<QString, QVariant> tmp;
    tmp.insert("start", start);
    tmp.insert("count", count);
    QJsonDocument doc = QJsonDocument::fromVariant(tmp);
    if(doc.isNull())
    {
        cout << "FileList's jsondocument is null";
        return "";
    }

    return doc.toJson();
}

//获取文件信息的json包
void ShareList::getFileJsonInfo(QByteArray data)
{
    /*
        {
            "user": "yoyo",     -- user	文件所属用户
            "md5": "e8ea6031b779ac26c319ddf949ad9d8d",      -- md5 文件md5
            "time": "2017-02-26 21:35:25",      -- createtime 文件创建时间
            "filename": "test.mp4",      -- filename 文件名字
            "share_status": 0,      -- shared_status 共享状态, 0为没有共享， 1为共享
            "pv": 0,        -- pv 文件下载量，默认值为0，下载一次加1
            "url": "http://192.168.31.109:80/group1/M00/00/00/wKgfbViy2Z2AJ-FTAaM3As-g3Z0782.mp4",   -- url 文件url
            "size": 27473666,       -- size 文件大小, 以字节为单位
            "type": "mp4"        -- type 文件类型： png, zip, mp4……
        }
    */

    //将来源数据json转化为jsondocument
    QJsonParseError error;

    // 由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return;
        }

        if(doc.isObject())
        {
            //取得最外层这个大对象
            QJsonObject obj = doc.object();
            cout << "服务器返回的数据" << obj;

            //获得对象里面的内容
            QJsonArray array = obj.value("files").toArray();
            cout << array;
            int size = array.size();    //数组个数
            cout << "文件的个数 size = " << size;
            for (int i = 0; i < size; ++i) {
                QJsonObject tmp = array[i].toObject();

                FileInfo* info = new FileInfo;
                info->user = tmp.value("user").toString();
                info->md5 = tmp.value("md5").toString();
                info->time = tmp.value("time").toString();
                info->filename = tmp.value("filename").toString();
                info->shareStatus = tmp.value("share_status").toInt();
                info->pv = tmp.value("pv").toInt();
                info->url = tmp.value("url").toString();
                info->size = tmp.value("size").toInt();
                info->type = tmp.value("type").toString();
                QString type = info->type + ".png";
                info->item = new QListWidgetItem(QIcon(m_cm.getFileType(type)),info->filename);

                //list添加节点
                m_shareFileList.append(info);
            }
        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }

}

//清除文件item
void ShareList::clearItems()
{
    //使用QListWidget::count()来统计ListWidget中总共的item数目
    int n = ui->listWidget->count();
    for (int i = 0; i<n; ++i) {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        delete item;
    }
}

//下载文件action实现
void ShareList::downloadFilesAction()
{
    DownloadTask *p = DownloadTask::getInstance();
    if(p == nullptr)
    {
        cout << "DownloadTask::getInstance() == null";
        return;
    }
    //下载队列为空，说明无任务
    if(p->isEmpty())
    {
        return;
    }
    //当前时间无任务在下载，才能单任务下载
    if(p->isDownload())
    {
        return;
    }

    //是否为共享文件的下载任务，是才能执行，否则中断程序
    if(p->isShareTask() == false)
    {
        return;
    }

    DownloadInfo *tmp = p->takeTask();
    QUrl url = tmp->url;
    QFile *file = tmp->file;
    QString md5 = tmp->md5;
    QString filename = tmp->filename;
    DataProgress *dp = tmp->dp;

    //发送get请求
    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));
    if(reply == nullptr)
    {
        //删除文件
        p->dealDownloadTask();
        cout << "get err";
        return;
    }

    //获取请求的数据完成时，就会发送信号SIGNAL(finished))
    connect(reply, &QNetworkReply::finished, [=]()
    {
        cout << "下载完成";
        reply->deleteLater();
        p->dealDownloadTask();

        LoginInfoInstance *login = LoginInfoInstance::getInstance();
        m_cm.writeRecord(login->getUser(), filename, "010");

        dealFilePv(md5, filename);
    });

    //readyRead信号，可将数据保存下来
    connect(reply, &QNetworkReply::readyRead, [=]()
    {
       //文件存在
        if(file!=nullptr)
        {
            file->write(reply->readAll());
        }
    });

    connect(reply, &QNetworkReply::downloadProgress, [=](qint64 bytesRead, qint64 totalBytes)
    {
        //设置进度
        dp->setProgress(bytesRead, totalBytes);
    });
}

//处理被选择的文件，主要是右键菜单
void ShareList::dealSelectedFile(ShareList::CMD cmd)
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item == nullptr)
    {
        cout << "没有item可选择";
        return;
    }

    //查找文件列表中item
    for (int i = 0; i< m_shareFileList.size(); ++i)
    {
        if(m_shareFileList.at(i)->item == item)
        {
            if(cmd == Property)
            {
                //获取属性信息
                getFileProperty(m_shareFileList.at(i));
            }
            else if(cmd == Cancel)
            {
                //取消分享
                cancelShareFile(m_shareFileList.at(i));
            }
            else if(cmd == Save)
            {
                //转存文件
                saveFileToMyList(m_shareFileList.at(i));
            }
            break;
        }
    }
}

//获取文件属性信息
void ShareList::getFileProperty(FileInfo *info)
{
    //创建一个文件属性的对话框
    FilePropertyInfo dlg;
    dlg.setInfo(info);
    //显示
    dlg.exec();
}

//取消分享文件
void ShareList::cancelShareFile(FileInfo *info)
{
    //获取登录用户
    LoginInfoInstance *login = LoginInfoInstance::getInstance();

    //如果该文件不是该用户的分享文件，则无权限取消分享
    if(login->getUser() != info->user)
    {
        QMessageBox::warning(this, "操作失败", "此文件不是当前登录的用户，无法执行取消文件分享");
        return;
    }

    //取消分享
    QNetworkRequest request;
    QString url = QString("http://%1:%2/dealsharefile?cmd=cancel").arg(login->getIp()).arg(login->getPort());
    request.setUrl(QUrl(url));
    cout << "url = " << url;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = setShareFileJson(login->getUser(), info->md5, info->filename);
    QNetworkReply *reply = m_manager->post(request, data);
    if(reply == nullptr)
    {
        cout << "reply == NULL";
        return;
    }
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if(reply->error()!=QNetworkReply::NoError)
        {
            cout << reply->errorString();
            reply->deleteLater();
            return ;
        }
        QByteArray array = reply->readAll();
        reply->deleteLater();

        /*
            取消分享：
                成功：{"code":"018"}
                失败：{"code":"019"}
        */
        if("018" == m_cm.getCode(array))
        {
            //从文件列表中移除该文件item
            for (int i = 0; i< m_shareFileList.size(); ++i)
            {
                if(m_shareFileList.at(i) == info)
                {
                    QListWidgetItem *item = info->item;
                    //从列表视图移除该item
                    ui->listWidget->removeItemWidget(item);
                    delete item;

                    m_shareFileList.removeAt(i);
                    delete info;
                    break;
                }
            }

            QMessageBox::information(this, "操作成功", "该文件已经被取消分享！");
        }
        else
        {
            QMessageBox::warning(this, "操作失败", "该文件取消分享失败！");
        }
    });
}

//保存为文件到mylist中
void ShareList::saveFileToMyList(FileInfo *info)
{
    //获取登录用户
    LoginInfoInstance *login = LoginInfoInstance::getInstance();

    //如果该文件已经存在于用户的列表中，则无权限转存文件
    if(login->getUser()!=info->user)
    {
        QMessageBox::warning(this,"操作失败", "此文件不是当前登录的用户，无法执行取消文件分享");
        return;
    }

    //转存文件
    QNetworkRequest request;
    QString url = QString("http://%1:%2/dealsharefile?cmd=cancel").arg(login->getIp()).arg(login->getPort());
    request.setUrl(QUrl(url));
    cout << "url = " << url;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = setShareFileJson(login->getUser(), info->md5, info->filename);
    QNetworkReply *reply = m_manager->post(request, data);
    if(reply == nullptr)
    {
        cout << "reply == NULL";
        return;
    }
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if(reply->error()!=QNetworkReply::NoError)
        {
            cout << reply->errorString();
            reply->deleteLater();
            return ;
        }
        QByteArray array = reply->readAll();
        reply->deleteLater();

        /*
           转存文件：
               成功：{"code":"020"}
               文件已存在：{"code":"021"}
               失败：{"code":"022"}
        */
        if("020" == m_cm.getCode(array))
        {
            QMessageBox::information(this, "操作成功", "该文件已保存到该用户列表!");
        }
        else if("021" == m_cm.getCode(array))
        {
            QMessageBox::warning(this, "操作失败", "该文件已存在，无需转存！");
        }
        else if("022" == m_cm.getCode(array))
        {
            QMessageBox::warning(this, "操作失败", "文件转存失败！");
        }
    });
}

//设置分享文件json包
QByteArray ShareList::setShareFileJson(QString user, QString md5, QString filename)
{
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("md5", md5);
    tmp.insert("filename", filename);

    QJsonDocument json = QJsonDocument::fromVariant(tmp);
    if(json.isNull())
    {
        cout << "jsonDocument.isNull()";
        return "";
    }
    return json.toJson();
}

//添加下载文件
void ShareList::addDownloadFiles()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item == nullptr)
    {
        cout << "item == null";
        return;
    }

    //跳转到下载页面
    emit gotoTransfer(TransferStatus::Download);

    //获取下载列表实例
    DownloadTask *p = DownloadTask::getInstance();
    if(p == nullptr)
    {
        cout << "DownloadTask::getInstance() == null";
        return;
    }

    for (int i=0;i<m_shareFileList.size(); ++i)
    {
        if(m_shareFileList.at(i)->item == item)
        {
            QString filePathName = QFileDialog::getSaveFileName(this, "选择保存文件路径", m_shareFileList.at(i)->filename);
            if(filePathName.isEmpty())
            {
                cout << "filePathName is empty.";
                return;
            }

            /*
               下载文件：
                    成功：{"code":"009"}
                    失败：{"code":"010"}

                追加任务到下载队列
                参数：info：下载文件信息， filePathName：文件保存路径
                成功：0
                失败：
                  -1: 下载的文件是否已经在下载队列中
                  -2: 打开文件失败
            */
            //追加到下载列表
            int res = p->appendDownloadList(m_shareFileList.at(i), filePathName, true);
            if(res == -1)
            {
                QMessageBox::warning(this, "任务已完成", "任务已在下载队列中！");
            }
            //打开文件失败
            else if(res == -2)
            {
                LoginInfoInstance *login = LoginInfoInstance::getInstance();
                //下载文件失败
                m_cm.writeRecord(login->getUser(), m_shareFileList.at(i)->filename, "010");
            }
            break;
        }
    }
}

// 下载文件 pv 字段处理
void ShareList::dealFilePv(QString md5, QString filename)
{
    QNetworkRequest request;

    LoginInfoInstance *login = LoginInfoInstance::getInstance();

    QString url = QString("http://%1:%2/dealsharefile?cmd=pv").arg(login->getIp()).arg(login->getPort());
    request.setUrl(QUrl(url));
    cout << "url = " << url;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray data = setShareFileJson(login->getUser(), md5, filename);

    QNetworkReply* reply = m_manager->post(request, data);
    if(reply == nullptr)
    {
        cout << "reply == null";
        return;
    }

    connect(reply, &QNetworkReply::finished, [=]()
    {
        if(reply->error() != QNetworkReply::NoError)
        {
            cout << reply->errorString();
            reply->deleteLater();
            return ;
        }

        QByteArray array = reply->readAll();
        cout <<array;

        reply->deleteLater();

        if("016" == m_cm.getCode(array))
        {
            for (int i = 0; i< m_shareFileList.size(); ++i)
            {
                FileInfo *info = m_shareFileList.at(i);
                if(info->md5 == md5 && info->filename == filename)
                {
                    int pv = info->pv;
                    info->pv = pv+1;
                    break;
                }
            }
        }
        else
        {
            cout << "下载文件pv字段处理失败！";
        }
    });
}
