#include "myfilewg.h"
#include "ui_myfilewg.h"

MyFileWg::MyFileWg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyFileWg)
{
    ui->setupUi(this);
    // 初始化listWidget文件列表
    initListWidget();
    // 添加右键菜单
    addActionMenu();
}

MyFileWg::~MyFileWg()
{
    delete ui;
}

// 初始化listWidget文件列表
void MyFileWg::initListWidget()
{
    ui->listWidget->setViewMode(QListView::IconMode);   //设置显示图标模式
    ui->listWidget->setIconSize(QSize(80, 80));         //设置图标大小
    ui->listWidget->setGridSize(QSize(100, 120));       //设置item大小

    // 设置QLisView大小改变时，图标的调整模式，默认是固定的，可以改成自动调整
    ui->listWidget->setResizeMode(QListView::Adjust);   //自动适应布局

    // 设置列表可以拖动，如果想固定不能拖动，使用QListView::Static
    ui->listWidget->setMovement(QListView::Static);
    // 设置图标之间的间距, 当setGridSize()时，此选项无效
    ui->listWidget->setSpacing(30);

    // listWidget 右键菜单
    // 发出 customContextMenuRequested 信号
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, &MyFileWg::rightMenu);
    // 点中列表中的上传文件图标
    connect(ui->listWidget, &QListWidget::itemPressed, this, [=](QListWidgetItem* item)
    {
        QString str = item->text();
        if(str == "上传文件")
        {
            //添加需要上传的文件到上传任务列表
            addDownloadFiles();
        }
    });
}

void MyFileWg::addActionMenu()
{
    //===================菜单1==================
    m_menu = new MyMenu( this );

    // 初始化菜单项
    m_downloadAction = new QAction("下载", this);
    m_shareAction = new QAction("分享", this);
    m_delAction = new QAction("删除", this);
    m_propertyAction = new QAction("属性", this);

    // 动作1添加到菜单1
    m_menu->addAction(m_downloadAction);
    m_menu->addAction(m_shareAction);
    m_menu->addAction(m_delAction);
    m_menu->addAction(m_propertyAction);

    //===================菜单2===================
    m_menuEmpty = new MyMenu( this );
    // 动作2
    m_pvAscendingAction = new QAction("按下载量升序", this);
    m_pvDescendingAction = new QAction("按下载量降序", this);
    m_refreshAction = new QAction("刷新", this);
    m_uploadAction = new QAction("上传", this);

    // 动作2添加到菜单2
    m_menuEmpty->addAction(m_pvAscendingAction);
    m_menuEmpty->addAction(m_pvDescendingAction);
    m_menuEmpty->addAction(m_refreshAction);
    m_menuEmpty->addAction(m_uploadAction);

    //信号与槽
    // 下载
    connect(m_downloadAction, &QAction::triggered, [=]()
    {
        cout << "下载动作";
        //添加需要下载的文件到下载任务列表
        addDownloadFiles();
    });

    // 分享
    connect(m_shareAction, &QAction::triggered, [=]()
    {
        cout << "分享动作";
        dealSelectdFile("分享"); //处理选中的文件
    });

    // 删除
    connect(m_delAction, &QAction::triggered, [=]()
    {
        cout << "删除动作";
        dealSelectdFile("删除"); //处理选中的文件
    });

    // 属性
    connect(m_propertyAction, &QAction::triggered, [=]()
    {
        cout << "属性动作";
        dealSelectdFile("属性"); //处理选中的文件
    });

    // 按下载量升序
    connect(m_pvAscendingAction, &QAction::triggered, [=]()
    {
        cout << "按下载量升序";
        refreshFiles(PvAsc);
    });

    // 按下载量降序
    connect(m_pvDescendingAction, &QAction::triggered, [=]()
    {
        cout << "按下载量降序";
        refreshFiles(PvDesc);
    });

    //刷新
    connect(m_refreshAction, &QAction::triggered, [=]()
    {
        cout << "刷新动作";
        //显示用户的文件列表
        refreshFiles();
    });

    //上传
    connect(m_uploadAction, &QAction::triggered, [=]()
    {
        cout << "上传动作";
        //添加需要上传的文件到上传任务列表
        addUploadFiles();
    });
}


// 显示右键菜单
void MyFileWg::rightMenu(const QPoint &pos)
{
    QListWidgetItem *item = ui->listWidget->itemAt( pos );

    if( item == nullptr ) //没有点图标
    {
        m_menuEmpty->exec( QCursor::pos() ); //在鼠标点击的地方弹出菜单
    }
    else //点图标
    {
        ui->listWidget->setCurrentItem(item);

        if(item->text() == "上传文件") //如果是上传文件，没有右击菜单
        {
            return;
        }

        m_menu->exec( QCursor::pos() );
    }
}


// 处理选中的文件
void MyFileWg::dealSelectdFile(QString cmd)
{
    //获取当前选中的item
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item == nullptr)
    {
        return;
    }

    //查找文件列表匹配的元素
    for(int i = 0; i < m_fileList.size(); ++i)
    {
        if(m_fileList.at(i)->item == item)
        {
            if(cmd == "分享")
            {
                cout << "分享文件...";
                shareFile( m_fileList.at(i) ); //分享某个文件
            }
            else if(cmd == "删除")
            {
                cout << "删除文件...";
                delFile( m_fileList.at(i) ); //删除某个文件
            }
            else if(cmd == "属性")
            {
                cout << "获取文件属性...";
                getFileProperty( m_fileList.at(i) ); //获取属性信息
            }
            break; //跳出循环
        }
    }
}


// 分享文件
void MyFileWg::shareFile(FileInfo *info)
{
    cout << "分享成功...";
}

// 删除文件
void MyFileWg::delFile(FileInfo *info)
{

        cout << "删除成功...";
}

// 获取文件属性
void MyFileWg::getFileProperty(FileInfo *info)
{
        cout << "获取属性成功...";
}

// 显示用户文件列表
// cmd取值，Normal：普通用户列表，PvAsc：按下载量升序， PvDesc：按下载量降序
void MyFileWg::refreshFiles(MyFileWg::Display cmd)
{
    cout << "刷新并显示文件列表";
}

// 添加需要上传的文件
void MyFileWg::addUploadFiles()
{
    cout << "上传文件...";
}

// 添加需要下载的文件
void MyFileWg::addDownloadFiles()
{
    cout << "下载文件...";

}

