#include "downloadtask.h"
#include "downloadlayout.h"


//静态数据成员，类中声明，类外必须定义
DownloadTask * DownloadTask::instance;

//static类的析构函数在main()退出后调用
DownloadTask::Garbo DownloadTask::temp; //静态数据成员，类中声明，类外定义

DownloadTask *DownloadTask::getInstance()
{
    //判断是否是第一次调用
    if(instance == nullptr)
    {
        instance = new DownloadTask();
    }
    return instance;
}

void DownloadTask::clearList()
{
    int n = list.size();
    for(int i = 0; i < n; ++i)
    {
        DownloadInfo *tmp = list.takeFirst();
        delete tmp;
    }
}

bool DownloadTask::isEmpty()
{
    return list.isEmpty();
}

bool DownloadTask::isDownload()
{
    for(int i = 0; i != list.size();++i)
    {
        if(list.at(i)->isDownload == true)
        {
            return true;
        }
    }
    return false;
}

bool DownloadTask::isShareTask()
{
    if(isEmpty())
    {
        return NULL;
    }
    return list.at(0)->isShare;
}

DownloadInfo *DownloadTask::takeTask()
{
    if(isEmpty())
    {
        return NULL;
    }
    list.at(0)->isDownload = true;
    return list.at(0);
}

//删除下载完成的任务
void DownloadTask::dealDownloadTask()
{
    //遍历队列
    for(int i = 0; i != list.size(); ++i)
    {
        if(list.at(i)->isDownload == true)
        {
            //移除文件
            DownloadInfo *tmp = list.takeAt(i);

            //布局
            DownloadLayout *downloadLayout = DownloadLayout::getInstance();
            QLayout *layout = downloadLayout->getDownloadLayout();

            //删除进度条
            //layout->removeWidget(tmp->dp);
            //delete tmp->dp;

            //关闭删除文件
            QFile *file = tmp->file;
            file->close();
            delete file;

            delete tmp;
            return;
        }
    }
}


//添加下载任务到队列
int DownloadTask::appendDownloadList(FileInfo *info, QString filePathName, bool isShare)
{
    for(int i = 0; i != list.size(); ++i)
    {
        if(list.at(i)->user == info->user && list.at(i)->filename==info->filename)
        {
            cout << info->filename << "已经在下载任务队列";
            return -1;
        }
    }

    QFile *file = new QFile(filePathName); //文件指针分配空间

    if(!file->open(QIODevice::WriteOnly))
    { //如果打开文件失败，则删除 file，并使 file 指针为 NULL，然后返回
        cout << "file open error";

        delete file;
        file = NULL;
        return -2;
    }
    //动态创建节点
    DownloadInfo *tmp = new DownloadInfo;
    tmp->user = info->user;   //用户
    tmp->file = file;         //文件指针
    tmp->filename = info->filename; //文件名字
    tmp->md5 = info->md5;           //文件md5
    tmp->url = info->url;           //下载网址
    tmp->isDownload = false;        //没有在下载
    tmp->isShare = isShare;         //是否为共享文件下载

    //DataProgress *p = new DataProgress; //创建进度条
    //p->setFileName(tmp->filename); //设置文件名字

    //获取布局
    DownloadLayout *downloadLayout = DownloadLayout::getInstance();
    QVBoxLayout *layout = (QVBoxLayout*)downloadLayout->getDownloadLayout();

    //tmp->dp = p;
    // 添加到布局, 最后一个是弹簧, 插入到弹簧上边
    //layout->insertWidget(layout->count()-1, p);

    cout << info->url << "已经添加到下载列表";

    //插入节点
    list.append(tmp);


    return 0;
}





