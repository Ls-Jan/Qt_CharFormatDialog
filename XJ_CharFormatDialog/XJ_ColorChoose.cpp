

#include "XJ_ColorChoose.h"
#include<string>
#include<QMouseEvent>
#include<QColorDialog>
using namespace std;

XJ_ColorChoose::XJ_ColorChoose(QWidget*parent):QPushButton(parent){
    this->setCursor(Qt::PointingHandCursor);//手型光标：https://blog.csdn.net/chenyijun/article/details/52452880
}

void XJ_ColorChoose::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){//左键点击
        QColor col=QColorDialog::getColor(this->__col,nullptr,"",QColorDialog::ShowAlphaChannel);//运行时疯狂提示警告，属实王八蛋，懒得管，眼不见心不烦（管的话还得手动设置位置使其正好处于屏幕中央，想想都烦
        if(col.isValid())
            this->Set_Color(col);
    }
}

void XJ_ColorChoose::Set_Color(QColor col){
    this->__col=col;
    int r,g,b,a;
    col.getRgb(&r,&g,&b,&a);
    if(a==1)//Qt日常犯病，透明度1就给我视作255搞个不透明出来，什么傻逼
        a=0;
    string color=to_string(r)+","+to_string(g)+","+to_string(b)+","+to_string(a);
    string style="QPushButton{background-color:rgba(%);};";
    style.replace(style.find('%'),1,color);
    this->setStyleSheet(style.data());//设置颜色
    this->update();
    this->valueChanged(col);//值修改时发送信号
}

QColor XJ_ColorChoose::Get_Color(){
    return this->__col;
}




