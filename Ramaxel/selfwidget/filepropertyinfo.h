#ifndef FILEPROPERTYINFO_H
#define FILEPROPERTYINFO_H

#include <QDialog>
#include "common/common.h" //FileInfo

namespace Ui {
class FilePropertyInfo;
}

class FilePropertyInfo : public QDialog
{
    Q_OBJECT

public:
    explicit FilePropertyInfo(QWidget *parent = nullptr);
    ~FilePropertyInfo();

    //设置内容
    void setInfo(FileInfo *info);

private:
    Ui::FilePropertyInfo *ui;
};

#endif // FILEPROPERTYINFO_H
