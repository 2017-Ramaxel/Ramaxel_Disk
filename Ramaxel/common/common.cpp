#include <QFile>
#include <QMap>
#include <QDir>
#include <QTime>
#include <QFileInfo>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QApplication>
#include <QJsonDocument>
#include <QFileInfoList>
#include <QDesktopWidget>
#include <QCryptographicHash>
#include "des.h"
#include "common.h"

// 初始化变量
QString Common::m_typePath = FILETYPEDIR;
QStringList Common::m_typeList = QStringList();
QNetworkAccessManager* Common::m_netManager = new QNetworkAccessManager;


Common::Common(QObject *parent)
{
    //向编译器指示函数主体中未使用具有指定名称的参数。
    //这可用于禁止编译器警告，同时允许在函数签名中使用有意义的参数名称定义函数。
    Q_UNUSED(parent);
}

//屏幕中间显示
void Common::moveToCenter(QWidget *tmp)
{
    // 显示窗口
    tmp->show();
    // 屏幕中间显示
    // 使用qApp->desktop();也可以
    // QDesktopWidget *QApplication::desktop()
    // 返回桌面小部件（也称为根窗口）。
    QDesktopWidget* desktop = QApplication::desktop();
    // 移动窗口
    tmp->move((desktop->width() - tmp->width())/2, (desktop->height() - tmp->height())/2);
}

/*
 * brief           从配置文件中得到相对应的参数
 *
 * title     配置文件title名称[title]
 * key       key
 * path      配置文件路径
 *
 * returns
 *                  success: 得到的value
 *                  fail:    空串
 */

//读本地json配置文件
QString Common::getCfgValue(QString title, QString key, QString path)
{
    QFile file(path);

    //以只读方式打开
    if(file.open(QIODevice::ReadOnly) == false)
    {
        //打开失败
        perror("文件打开错误");
        return "";
    }

    QByteArray json = file.readAll();   //读取所有内容
    file.close();   //关闭文件

    //QString QJsonParseError :: errorString（）const
    //返回适合于所报告的JSON解析错误的人类可读消息。
    QJsonParseError error;

    //将源数据json转化为JsonDocument
    //由QByteArray对象构造一个QJsonDocument对象, 用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(json,&error);
    if(error.error == QJsonParseError::NoError) //没有出错
    {
        if(doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return "";
        }

        if(doc.isObject())  //如果对象不为空
        {
            /*
            {
                "login": {
                    "pwd": "wqq2b4Ild/w=",
                    "remember": "yes",
                    "user": "Mi/CvL0kLkQ="
                },
                "type_path": {
                    "path": "conf/fileType"
                },
                "web_server": {
                    "ip": "192.168.1.27",
                    "port": "80"
                }
            }
            */
            //QJsonObject QJsonDocument :: object（）const
            //返回文档中包含的QJsonObject。
            // QJsonObject json对象,描述json数据中{}括起来的部分
            QJsonObject obj = doc.object();//取最外层这个大对象

            QJsonObject tmp = obj.value(title).toObject();
            QStringList list = tmp.keys();  //取出key列表
            for(int i = 0; i< list.size(); ++i){
                if(list.at(i) == key){
                    return tmp.value(list.at(i)).toString();
                }
            }
        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }
    return "";
}

// 通过读取文件, 得到文件类型, 存放在typeList
void Common::getFileTypeList()
{
    // QDir类使用相对或者绝对文件路径来指向一个文件或目录
    QDir dir(m_typePath);

    /*bool QDir::exists(const QString &name) const
    如果名为name的文件存在，则返回true；否则，返回true。否则返回false。
    */
    /*bool QDir::mkpath(const QString &dirPath) const
        创建目录路径dirPath。
        该函数将创建创建目录所需的所有父目录。
        如果成功，则返回true；否则，返回true。 否则返回false。
        如果在调用此函数时路径已存在，则它将返回true。
    */
    if(!dir.exists()){
        dir.mkpath(m_typePath);
        cout << m_typePath << "创建成功!!!";
    }

    /*
        QDir::Dirs      列出目录；
        QDir::AllDirs   列出所有目录，不对目录名进行过滤；
        QDir::Files     列出文件；
        QDir::Drives    列出逻辑驱动器名称，该枚举变量在Linux/Unix中将被忽略；
        QDir::NoSymLinks        不列出符号链接；
        QDir::NoDotAndDotDot    不列出文件系统中的特殊文件.及..；
        QDir::NoDot             不列出.文件，即指向当前目录的软链接
        QDir::NoDotDot          不列出..文件；
        QDir::AllEntries        其值为Dirs | Files | Drives，列出目录、文件、驱动器及软链接等所有文件；
        QDir::Readable      列出当前应用有读权限的文件或目录；
        QDir::Writable      列出当前应用有写权限的文件或目录；
        QDir::Executable    列出当前应用有执行权限的文件或目录；
        Readable、Writable及Executable均需要和Dirs或Files枚举值联合使用；
        QDir::Modified      列出已被修改的文件，该值在Linux/Unix系统中将被忽略；
        QDir::Hidden        列出隐藏文件；
        QDir::System        列出系统文件；
        QDir::CaseSensitive 设定过滤器为大小写敏感。
    */
    dir.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot | QDir::NoSymLinks);   //过滤文件
    dir.setSorting(QDir::Size | QDir::Reversed);    //按照文件大小从小到大排序

    /* QFileInfo提供有关文件在文件系统中的名称和位置（路径），其访问权限以及它是目录链接还是符号链接等信息。
     * QFileInfoList QDir::entryInfoList(const QStringList &nameFilters, QDir::Filters filters = NoFilter, QDir::SortFlags sort = NoSort) const
     * 返回目录中所有文件和目录的QFileInfo对象的列表，
     * 根据先前使用setNameFilters（）和setFilter（）设置的名称和属性过滤器进行排序，
     * 并根据通过setSorting（）设置的标志进行排序。
     * 名称过滤器，文件属性过滤器和排序规范可以使用nameFilters，过滤器和排序参数来覆盖。
     * 如果目录不可读，不存在或没有符合规范的目录，则返回一个空列表。
     */
    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        /*QString QFileInfo::fileName() const
         * 返回文件名，不包括路径。
         */
        m_typeList.append( fileInfo.fileName() );
    }
}

// 得到文件后缀，参数为文件类型，函数内部判断是否有此类型，如果有，使用此类型，没有，使用other.png
QString Common::getFileType(QString type)
{
    /* bool QStringList::contains(const QString &str, Qt::CaseSensitivity cs = Qt::CaseSensitive) const
     * 如果列表中包含字符串str，则返回true;否则返回false。
     * 如果cs是Qt::CaseInsensitive;搜索不区分大小写;搜索默认是区分大小写的。
     */
    if(true == m_typeList.contains(type)){
        return m_typePath + "/" + type;
    } else {
        return m_typePath + "/other.png";
    }
}

//服务器设置的时候，将信息写入配置文件
void Common::writeWebInfo(QString ip, QString port, QString path)
{
    //web_server信息
    QMap<QString,QVariant> web_server;
    web_server.insert("ip",ip);
    web_server.insert("port",port);

    // type_path信息
    QMap<QString, QVariant> type_path;
    type_path.insert("path", m_typePath);

    // login信息
    QString user = getCfgValue("login", "user");
    QString pwd = getCfgValue("login", "pwd");
    QString remember = getCfgValue("login", "remember");

    QMap<QString, QVariant> login;
    login.insert("user", user);
    login.insert("pwd", pwd);
    login.insert("remember", remember);

    // QVariant类作为一个最为普遍的Qt数据类型的联合
    // QVariant为一个万能的数据类型--可以作为许多类型互相之间进行自动转换。
    QMap<QString, QVariant> json;
    json.insert("web_server", web_server);
    json.insert("type_path", type_path);
    //json.insert("login", login);

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(json);
    if ( jsonDoc.isNull() == true)
    {
        cout << " QJsonDocument::fromVariant(json) err";
        return;
    }

    QFile file(path);

    if(false ==file.open(QIODevice::WriteOnly))
    {
        cout<< "file open error";
        return;
    }

    file.write(jsonDoc.toJson());
    file.close();
}

//登录的时候，将登录信息写入配置文件
void Common::writeLoginInfo(QString user, QString pwd, bool isRemeber, QString path)
{
    //读取服务器设置的ip地址和端口
    QString ip = getCfgValue("web_server", "ip");
    QString port = getCfgValue("web_server", "port");

    QMap<QString, QVariant> web_server;
    web_server.insert("ip",ip);
    web_server.insert("port", port);

    //type_path信息
    QMap<QString, QVariant> type_path;
    type_path.insert("path", m_typePath);

    //login信息
    QMap<QString, QVariant> login;

    // 登陆信息加密
    int ret = 0;

    //用户名加密
    unsigned char encUser[1024] = {0};
    int encUserLen;
    // toLocal8Bit(), 转换为本地字符集，如果windows则为gbk编码，如果linux则为utf-8编码
    ret = DesEnc((unsigned char *)user.toUtf8().data(), user.toUtf8().size(),encUser,&encUserLen);
    if(ret != 0){   //加密失败
        cout<<"DesEnc err";
        return;
    }

    //用户密码加密
    unsigned char encPwd[512] = {0};
    int encPwdLen;
    ret = DesEnc((unsigned char *)pwd.toUtf8().data(),pwd.toUtf8().size(),encPwd,&encPwdLen);
    if(ret != 0){
        cout<<"DesEnc error";
        return;
    }

    // 再次加密
    // base64转码加密，目的将加密后的二进制转换为base64字符串
    login.insert("user", QByteArray((char* )encUser,encUserLen).toBase64());   //用户名
    login.insert("pwd", QByteArray((char* )encPwd,encPwdLen).toBase64());   //用户密码

    //是否记住密码
    if(isRemeber == true)
    {
        login.insert("remember", "yes");
    }
    else
    {
        login.insert("remember", "no");
    }

    // QVariant类作为一个最为普遍的Qt数据类型的联合
    // QVariant为一个万能的数据类型--可以作为许多类型互相之间进行自动转换。
    //准备将web_server、type_path、login写入配置文件
    QMap<QString, QVariant> json;
    json.insert("web_server",web_server);
    json.insert("type_path", type_path);
    json.insert("login",login);

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(json);
    if(jsonDoc.isNull() == true)
    {
        cout<< "QjsonDocument:: fromVariant()error!!!";
        return;
    }

    QFile file(path);

    if( false == file.open(QIODevice::WriteOnly) )
    {
        cout << "file open err";
        return;
    }

    //json内容写入文件
    file.write(jsonDoc.toJson());
    file.close();

}

// 获取某个文件的md5码
QString Common::getFileMd5(QString filePath)
{
    QFile localFile(filePath);

    if(!localFile.open(QFile::ReadOnly)){
        qDebug() << "file open error.";
        return 0;
    }

    QCryptographicHash ch(QCryptographicHash::Md5);

    quint64 totalBytes = 0;
    quint64 bytesWritten = 0;
    quint64 bytesToWrite = 0;
    quint64 loadSize = 1024 * 4;
    QByteArray buf;

    totalBytes = localFile.size();
    bytesToWrite = totalBytes;

    while(1){
        if(bytesToWrite > 0){
            /* template <typename T> const T &qMin(const T &a, const T &b)
             * 返回a和b的最小值。
             */
            /* QByteArray QIODevice::read(qint64 maxSize)
             * 从设备读取最多maxSize字节，
             * 并返回作为QByteArray读取的数据。
             */
            buf = localFile.read(qMin(bytesToWrite, loadSize));
            ch.addData(buf);
            bytesWritten += buf.length();
            bytesToWrite -= buf.length();
            buf.resize(0);
        } else {
            break;
        }
        if(bytesWritten == totalBytes){
            break;
        }
    }

    localFile.close();
    QByteArray md5 = ch.result();
    return md5.toHex();

}

//将某个字符串加密成md5码
QString Common::getStrMd5(QString str)
{
    //md5加密
    QByteArray array = QCryptographicHash::hash(str.toLocal8Bit(),QCryptographicHash::Md5);

    return array.toHex();
}

// 产生分隔线
QString Common::getBoundary()
{
    // 随机种子
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QString tmp;

    // 48~122, '0'~'A'~'z'
    for(int i = 0; i < 16; i++)
    {
        tmp[i] = rand() % (122-48) + 48;
    }

    return QString("------WebKitFormBoundary%1").arg(tmp);
}

// 得到服务器回复的状态码， 返回值为 "000", 或 "001"
QString Common::getCode(QByteArray json)
{
    QJsonParseError error;

    QJsonDocument doc = QJsonDocument::fromJson(json,&error);
    if(error.error == QJsonParseError::NoError){
        if(doc.isNull() || doc.isEmpty()){
            cout<< "doc.isNull() || doc.isEmpty()";
            return "";
        }
        if(doc.isObject()){
            // 取得最外层这个大对象
            QJsonObject obj = doc.object();
            return obj.value("code").toString();
        }
    } else {
        cout<< "err = " << error.errorString();
    }
    return "";
}

//获取唯一的netwokermanager对象
QNetworkAccessManager *Common::getNetManager()
{
    // 该对象一般一个应用程序中有一个就够了，无需new多个
    return  m_netManager;
}

// 传输数据记录到本地文件，
// user：操作用户，name：操作的文件, code: 操作码， path: 文件保存的路径
void Common::writeRecord(QString user, QString name, QString code, QString path)
{
    //文件名字,登录用户名则为文件名
    QString fileName = path + user;
    //检查目录是否存在, 如果不存在, 则创建目录
    QDir dir(path);
    if(!dir.exists()){
        //目录不存在,创建
        if(dir.mkpath(path)){
            cout << path << "目录创建成功...";
        } else {
            cout << path << "目录创建失败...";
        }
    }
    cout << "fileName = " << fileName.toUtf8().data();

    QFile file(fileName);
    QByteArray array;

    //如果文件存在, 先读取文件原来的内容
    if(file.exists() == true ){
        if(file.open(QIODevice::ReadOnly) == false ){
            cout << "file.open(QIODevice::ReadOnly) err";
            return;
        }

        //读取文件原来的内容
        array = file.readAll();
        file.close();
    }

    if(file.open(QIODevice::WriteOnly) == false){
        cout << "file.open(QIODevice::WriteOnly) err";
        return;
    }

    QDateTime time = QDateTime::currentDateTime();  //获取系统现在的时间
    QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    /* 秒传文件：
     * 文件已存在：{"code":"005"}
     * 秒传成功：  {"code":"006"}
     * 秒传失败：  {"code":"007"}
     *
     * 上传文件：
     * 成功：{"code":"008"}
     * 失败：{"code":"009"}
     *
     * 下载文件：
     * 成功：{"code":"010"}
     * 失败：{"code":"011"}
     */
     QString actionStr;
     if(code == "005"){
         actionStr = "上传失败,文件已存在";
     } else if(code == "006") {
         actionStr = "秒传成功";
     } else if(code == "008") {
         actionStr = "上传成功";
     } else if(code == "009") {
         actionStr = "上传失败";
     } else if(code == "010") {
         actionStr = "下载成功";
     } else if(code == "011") {
         actionStr = "下载失败";
     }

     QString str = QString("[%1]\t%2\t[%3]\r\n").arg(name).arg(timeStr).arg(actionStr);
     cout << str.toUtf8().data();

     //toLocal8Bit(), 转换为本地字符集
     //先写新内容
     file.write(str.toLocal8Bit());

     if(array.isEmpty() == false){
         //再写原来的内容
         file.write(array);
     }

     file.close();
}









