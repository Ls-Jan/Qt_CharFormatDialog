#include "XJ_ListWidget.h"


void XJ_ListWidget::Opt_AllowSingleClick(bool flag){
    this->__singleClick=flag;
}

void XJ_ListWidget::Opt_AllowDoubleClick(bool flag){
    this->__doubleClick=flag;
}

void XJ_ListWidget::mousePressEvent(QMouseEvent *event){
    if(this->__singleClick)
        QListWidget::mousePressEvent(event);
}

void XJ_ListWidget::mouseDoubleClickEvent(QMouseEvent *event){
    if(this->__doubleClick){
        QListWidget::mousePressEvent(event);
        QListWidget::mouseDoubleClickEvent(event);
    }
}

