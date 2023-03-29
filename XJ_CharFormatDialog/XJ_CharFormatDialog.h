#ifndef XJ_CHARFORMATDIALOG_H
#define XJ_CHARFORMATDIALOG_H



#include"XJ_NumInput.h"
#include"XJ_ColorChoose.h"

#include<QMap>
#include<QFont>
#include<QTextCharFormat>
#include<QLabel>
#include<QPushButton>
#include<QTextEdit>
#include<QListWidget>
#include<QGroupBox>
#include<QVBoxLayout>
#include<QHBoxLayout>



class XJ_CharFormatDialog:public QWidget{//字体样式对话框【为了减少资源浪费，该对话框可以通过Set_CharFormat函数循环利用
    Q_OBJECT;
signals://槽信号
    void signal_change();//字体样式发生改变
    void signal_hide();//窗口隐藏
public:
    XJ_CharFormatDialog(QWidget*parent=nullptr);
    ~XJ_CharFormatDialog();
    void Set_DisplayText(QString displayText);//设置展示的文本内容
    void Set_CharFormat(QTextCharFormat* format);//设置字体样式。当传入空指针时将使用其自带的字体样式
    QTextCharFormat*Get_CharFormat();//获取字体样式
public:
    void hideEvent(QHideEvent *event) override;
    void update();

private:
    QTextCharFormat __charFormat;//自带的字体样式(通过避免执行delete __charFormat_new 的方式来规避逻辑上的混乱/漏洞。
    QTextCharFormat *__charFormat_new;//字体样式(新)
    QTextCharFormat *__charFormat_old;//字体样式(旧)
    struct Widgets{//一份组件
        QListWidget *fontLst;//字体列表
        QListWidget *styleLst;//字体风格列表(斜体、粗体等
        XJ_NumInput *size;//大小
        XJ_ColorChoose *foreColor;//前景色
        XJ_ColorChoose *backColor;//背景色
        QTextEdit*display;//文本展示
        QPushButton*ok;//确认
        QPushButton*cancel;//取消
    }__wids;
    const QMap<QString,bool(QFont::*)()const>__styleToGet{//用于简化代码。(类成员函数指针+字典初始化
        {"斜体",&QFont::italic},
        {"粗体",&QFont::bold},
        {"上划线",&QFont::overline},
        {"删除线",&QFont::strikeOut},
        {"下划线",&QFont::underline}
    };
    const QMap<QString,void(QFont::*)(bool)>__styleToSet{//用于简化代码。(类成员函数指针+字典初始化
        {"斜体",&QFont::setItalic},
        {"粗体",&QFont::setBold},
        {"上划线",&QFont::setOverline},
        {"删除线",&QFont::setStrikeOut},
        {"下划线",&QFont::setUnderline}
    };
private:
    Widgets __CreateWidgets();//生成一份组件
    QGroupBox* __CreateGroupBox(QString title,QList<QWidget*> wids);//创建GroupBox以装载目标控件(纵布局QVBoxLayout
    void __Init_Layout();//设置布局
    void __Init_Other();//其他初始化
    void __UpdateWidgetsValue(Widgets wids);//更新组件值，值以字体样式(新)为准
    void __Opt_Cancel();//按钮点击撤销
    void __Opt_OK();//按钮点击确认
    void __Set_Style(QListWidgetItem*item);//设置字体风格(斜体粗体等)
    void __Set_Font(QListWidgetItem*item);//设置字体
    void __Set_Size(int size);//设置大小
    void __Set_ForeColor(QColor color);//设置前景色
    void __Set_BackColor(QColor color);//设置背景色
};

#endif // XJ_CHARFORMATDIALOG_H
