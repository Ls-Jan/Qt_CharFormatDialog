

#include "XJ_NumInput.h"
#include<QKeyEvent>
#include<string>
using namespace std;

XJ_NumInput::XJ_NumInput(QWidget *parent, int curr, int min, int max, int step):QLineEdit(parent){
    this->__curr=curr;
    this->Set_Step(step);
    this->Set_MinMax(min,max);
    this->setReadOnly(true);

    this->setAlignment(Qt::AlignCenter);//设置居中对齐
    this->setFont(QFont("宋体",13));//改字号
    this->setCursor(Qt::PointingHandCursor);//手型光标：https://blog.csdn.net/chenyijun/article/details/52452880
}

void XJ_NumInput::Set_MinMax(int min, int max){
    if(min>max){
        min^=max;
        max^=min;
        min^=max;
    }
    this->__min=min;
    this->__max=max;
    this->Opt_UpdateValue(this->__curr);
}

void XJ_NumInput::Set_Value(int value){
    this->Opt_UpdateValue(value);
}

void XJ_NumInput::Set_Step(int num){
    if(num<1)
        num=1;
    this->__step=num;
}

int XJ_NumInput::Get_Value(){
    return this->__curr;
}

void XJ_NumInput::mouseDoubleClickEvent(QMouseEvent *){
    this->setReadOnly(false);
}

void XJ_NumInput::keyPressEvent(QKeyEvent *event){
    this->setAlignment(Qt::AlignCenter);//设置居中对齐
    if(event->key()==Qt::Key_Return or event->key()==Qt::Key_Enter){//按下回车键
        int value=this->text().toInt();
        if(to_string(value)!=this->text().toStdString())//防止无效输入
            return;
        this->Opt_UpdateValue(value);
        this->setReadOnly(true);
    }
    else
        QLineEdit::keyPressEvent(event);
}

void XJ_NumInput::wheelEvent(QWheelEvent *event){
    QPoint delta=event->angleDelta();
    this->Set_Value(this->__curr+(delta.y()>0?1:-1));//滚轮向上滚动，增加
}

void XJ_NumInput::Opt_UpdateValue(int value){
    int curr=value;
    if(curr<this->__min)
        curr=this->__min;
    else if(curr>this->__max)
        curr=this->__max;
    if(this->__curr!=curr){
        this->__curr=curr;
        this->valueChanged(curr);
        this->setText(to_string(curr).data());
        this->update();
    }
}
