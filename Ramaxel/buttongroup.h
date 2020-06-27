#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QSignalMapper>
#include <QMap>
#include <QPainter>
#include <QMouseEvent>


enum Page{MYFILE, SHARE, TRANKING, TRANSFER, SWITCHUSR};
namespace Ui {
class ButtonGroup;
}

class QToolButton;

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

public slots:
    // 按钮处理函数
    void slotButtonClick(Page cur);
    void slotButtonClick(QString text);

signals:
    void sigMyFile();
    void sigShareList();
    void sigDownload();
    void sigTransform();
    void sigSwitchUser();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPoint m_pos;
    QSignalMapper* m_mapper;
    QToolButton* m_curBtn;
    QMap<QString, QToolButton*> m_btns;
    Ui::ButtonGroup *ui;
    QMap<Page, QString> m_pages;
};

#endif // BUTTONGROUP_H
