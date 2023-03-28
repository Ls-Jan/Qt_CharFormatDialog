#ifndef XJ_LISTWIDGET_H
#define XJ_LISTWIDGET_H


#include<QListWidget>

class XJ_ListWidget:public QListWidget{//简单继承QListWidget，可以选择性地屏蔽单击双击事件
private:
    bool __singleClick=true;
    bool __doubleClick=true;
public:
    using QListWidget::QListWidget;//继承基类的构造函数：https://blog.csdn.net/K346K346/article/details/81703914
    void Opt_AllowSingleClick(bool flag);
    void Opt_AllowDoubleClick(bool flag);
public:
    void mousePressEvent(QMouseEvent*)override;
    void mouseDoubleClickEvent(QMouseEvent*)override;
};



#endif // XJ_LISTWIDGET_H
