#include "downloadlayout.h"

//静态数据成员，类中声明，类外必须定义
DownloadLayout* DownloadLayout::instance = new DownloadLayout;

//static类的析构函数在min（）退出后调用
DownloadLayout::Garbo DownloadLayout::temp;

DownloadLayout *DownloadLayout::getInstance()
{
    return instance;
}

void DownloadLayout::setDownloadLayout(QWidget *p)
{
    m_wg = new QWidget(p);
    QLayout* layout = p->layout();
    layout->addWidget(m_wg);
    layout->setContentsMargins(0,0,0,0);
    QVBoxLayout* vlayout = new QVBoxLayout;

    //布局设置
    m_wg->setLayout(vlayout);
    vlayout->setContentsMargins(0,0,0,0);
    m_layout = vlayout;

    vlayout->addStretch();
}

QLayout *DownloadLayout::getDownloadLayout()
{
    return m_layout;

}
