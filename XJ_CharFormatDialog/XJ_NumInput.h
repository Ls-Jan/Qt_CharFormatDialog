#ifndef XJ_NUMINPUT_H
#define XJ_NUMINPUT_H


#include<QLineEdit>

class XJ_NumInput:public QLineEdit{
    Q_OBJECT;
signals://槽信号
    void valueChanged(int col);//值修改时发送信号
public:
    XJ_NumInput(QWidget*parent=nullptr,int curr=0,int min=INT_MIN,int max=INT_MAX,int step=1);
public:
    void Set_MinMax(int min,int max);//设置最小最大值
    void Set_Value(int value);//设置当前值
    void Set_Step(int num);//设置步长
    int Get_Value();//获取当前值
protected:
    void mouseDoubleClickEvent(QMouseEvent *) override;//双击进入编辑
    void keyPressEvent(QKeyEvent *) override;//进入编辑后回车退出
    void wheelEvent(QWheelEvent*) override;//滚轮修改值
private:
    void Opt_UpdateValue(int value);//更新curr值
private:
    int __curr;
    int __min;
    int __max;
    int __step;
};



#endif // XJ_NUMINPUT_H
