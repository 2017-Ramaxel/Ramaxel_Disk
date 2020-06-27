#include "sharelist.h"
#include "ui_sharelist.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
//        downloadFilesAction();
    });
    // 启动定时器，500毫秒间隔
    // 每个500毫秒，检测下载任务，每一次只能下载一个文件
    m_downloadTimer.start(500);
}

ShareList::~ShareList()
{
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
            m_menu->exec( QCursor::pos() ); // 在鼠标点击的地方弹出菜单
        }
        else // 点图标
        {
            ui->listWidget->setCurrentItem(item);
            m_menufile->exec( QCursor::pos() );
        }
    });
}

void ShareList::addActionMenu()
{
    //菜单一，文件右键菜单
    m_menufile = new MyMenu(this);

    m_downloadAction = new QAction("下载", this);
    m_propertyAction = new QAction("属性", this);
    m_cancelAction = new QAction("取消分享", this);
    m_saveAction = new QAction("转存文件", this);

    m_menufile->addAction(m_downloadAction);
    m_menufile->addAction(m_cancelAction);
    m_menufile->addAction(m_saveAction);
    m_menufile->addAction(m_cancelAction);

    //菜单二
    m_menu = new MyMenu(this);
    m_refreshAction = new QAction("刷新", this);
    m_menu->addAction(m_refreshAction);

    //信号与槽
    connect(m_propertyAction, &QAction::triggered, [=]()
    {
         qDebug() << "文件item属性";
//         dealSelectedFile(Property);
    });
    connect(m_refreshAction, &QAction::triggered,[=]()
    {
        qDebug() << "刷新页面";

        //刷新共享列表的页面
        refreshFiles();
    });
}

void ShareList::refreshFiles()
{
    m_userFileCount = 0;

    //获取用户信息


    // 获取共享文件数目

    //获取请求的数据完成时，就会发送信号SIGNAL(finished())

    //服务器返回文件个数

    //清空文件列表信息
    clearShareFileList();


    refreshFileItems();

}

void ShareList::clearShareFileList()
{
    int n = m_shareFileList.size();
    for (int i = 0; i < n; i++) {
        FileInfo *tmp = m_shareFileList.takeFirst();
        delete tmp;
    }
}

// 获取共享文件列表
void ShareList::getUserFilesList()
{
    if(m_userFileCount < 0)
    {
        qDebug() << "获取文件列表失败";
        refreshFileItems();
        return;
    }
    else if(m_count >m_userFileCount)
    {
        m_count = m_userFileCount;
    }

}

//更新文件item
void ShareList::refreshFileItems()
{
    //清空所有item
    clearItems();

    int n = m_shareFileList.size();
    for (int i = 0; i < n; i++) {
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
        qDebug() << "FileList's jsondocument is null";
        return "";
    }

    return doc.toJson();
}

void ShareList::getFileJsonInfo(QByteArray array)
{
    //将来源数据json转化为jsondocument
    QJsonParseError error;

    // 由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (doc.isNull() || doc.isEmpty())
        {
            qDebug() << "doc.isNull() || doc.isEmpty()";
            return;
        }

        if(doc.isObject())
        {
            //取得最外层这个大对象
            QJsonObject obj = doc.object();
            qDebug() << "服务器返回的数据" << obj;

            //获得对象里面的内容
            QJsonArray data = obj.value("files").toArray();

            int size = array.size();    //数组个数
            qDebug() << "文件的个数 size = " << size;
            for (int i = 0; i < size; i++) {
                QJsonObject tmp = data[i].toObject();
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
        qDebug() << "err = " << error.errorString();
    }

}

void ShareList::clearItems()
{
    //使用QListWidget::count()来统计ListWidget中总共的item数目
    int n = ui->listWidget->count();
    for (int i = 0; i<n; i++) {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        delete item;
    }
}
