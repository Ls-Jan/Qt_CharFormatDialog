


#include<QApplication>
#include<QDebug>
#include"XJ_CharFormatDialog.h"


class Obj:public QObject{
public:
    XJ_CharFormatDialog*__dlg;
    Obj(XJ_CharFormatDialog*dlg):QObject(dlg){
        this->__dlg=dlg;
        QObject::connect(dlg,&XJ_CharFormatDialog::signal_hide,this,&Obj::Print);
        QObject::connect(dlg,&XJ_CharFormatDialog::signal_change,this,&Obj::Print);
    }
    void Print(){
        QTextCharFormat*fmt=this->__dlg->Get_CharFormat();
        QFont font=fmt->font();
        qDebug()<<font
               <<fmt->foreground()
              <<fmt->background();
    }
};

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    XJ_CharFormatDialog dlg;
    new Obj(&dlg);
    dlg.show();

    return a.exec();
}


