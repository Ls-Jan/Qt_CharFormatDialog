#ifndef XJ_COLORCHOOSE_H
#define XJ_COLORCHOOSE_H



#include<QPushButton>
#include<QColor>
#include<Qt>
class XJ_ColorChoose:public QPushButton{//小控件，点击弹出换色窗口
    Q_OBJECT;
signals://槽信号
    void valueChanged(QColor col);//值修改时发送信号
public:
    XJ_ColorChoose(QWidget*parent=nullptr);
    void Set_Color(QColor col);
    QColor Get_Color();
protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    QColor __col;
};


#endif // XJ_COLORCHOOSE_H
