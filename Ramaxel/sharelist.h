#ifndef SHARELIST_H
#define SHARELIST_H

#include <QWidget>
#include "common/common.h"
namespace Ui {
class ShareList;
}

class ShareList : public QWidget
{
    Q_OBJECT

public:
    explicit ShareList(QWidget *parent = nullptr);
    ~ShareList();

private:
    Ui::ShareList *ui;

signals:
    void gotoTransfer(TransferStatus status);
};

#endif // SHARELIST_H
