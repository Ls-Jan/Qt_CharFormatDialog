#include "XJ_CharFormatDialog.h"
#include<QFontDatabase>

XJ_CharFormatDialog::XJ_CharFormatDialog(QWidget *parent):QWidget(parent){
    this->__charFormat.setBackground(QColor(255,255,255,255));//就，挺，莫名其妙的，初始化的QTextCharFormat，它的背景颜色是黑的，但画出来的字是正常的，但是如果重新调用该函数的话又黑了，好离谱。
    this->__charFormat.setFontFamily("黑体");//随便设个字体
    this->__charFormat_new=&this->__charFormat;
    this->__charFormat_old=new QTextCharFormat(*this->__charFormat_new);

    this->__wids=this->__CreateWidgets();
    this->__UpdateWidgetsValue(this->__wids);
    this->__Init_Layout();
    this->__Init_Other();
    this->update();

    this->setWindowModality(Qt::ApplicationModal);//阻挡其他窗口
    this->setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);//对话框，并只保留关闭按钮
    this->setWindowTitle("选择字体样式");
}

XJ_CharFormatDialog::~XJ_CharFormatDialog(){
    delete this->__charFormat_old;
}

void XJ_CharFormatDialog::Set_DisplayText(QString displayText){
    this->__wids.display->setText(displayText);
}

void XJ_CharFormatDialog::Set_CharFormat(QTextCharFormat* format){
    if(format==nullptr)
        format=&this->__charFormat;
    delete this->__charFormat_old;
    this->__charFormat_new=format;
    this->__charFormat_old=new QTextCharFormat(*format);
    this->__UpdateWidgetsValue(this->__wids);
    this->update();
}

QTextCharFormat *XJ_CharFormatDialog::Get_CharFormat(){
    return this->__charFormat_new;
}

void XJ_CharFormatDialog::hideEvent(QHideEvent *event){
    this->signal_hide();
    QWidget::hideEvent(event);
}

void XJ_CharFormatDialog::update(){
    QTextCursor cursor=this->__wids.display->textCursor();
    cursor.movePosition(cursor.Start,cursor.MoveAnchor);
    cursor.movePosition(cursor.End,cursor.KeepAnchor);
    cursor.setCharFormat(*this->__charFormat_new);
    QWidget::update();
}

XJ_CharFormatDialog::Widgets XJ_CharFormatDialog::__CreateWidgets(){
    QListWidget *fontLst=new QListWidget(this);//字体列表
    QListWidget *styleLst=new QListWidget(this);//字体风格列表(斜体、粗体等
    XJ_NumInput *size=new XJ_NumInput(this,10,1,999);//大小
    XJ_ColorChoose *foreColor=new XJ_ColorChoose(this);//前景色
    XJ_ColorChoose *backColor=new XJ_ColorChoose(this);//背景色
    QPushButton*ok=new QPushButton("确认",this);//确认
    QPushButton*cancel=new QPushButton("取消",this);//取消
    QTextEdit*display=new QTextEdit(this);//文本展示

    {//创建字体下拉列表(但这里不需要，只需要字体列表)：https://blog.csdn.net/qq_41673920/article/details/118336875
        QListWidget*pListWidget=fontLst;
        QFontDatabase fontData;
        foreach(QString strFont,fontData.families(QFontDatabase::Any)){
            QListWidgetItem *pItem = new QListWidgetItem(strFont,pListWidget);
            pItem->setFont(QFont(strFont,12));
            pListWidget->addItem(pItem);
        }
    }
    {//创建字体风格列表，操作同上
        QListWidget*pListWidget=styleLst;
        QStringList lst{"斜体","粗体","上划线","删除线","下划线"};//对应函数依次是：setItalic setBold setUnderline setStrikeOut setOverline
        foreach(QString type,lst){
            QListWidgetItem *pItem = new QListWidgetItem(type,pListWidget);
            pItem->setCheckState(Qt::CheckState::Unchecked);
            pItem->setFont(QFont("宋体",12));
            pListWidget->addItem(pItem);
        }
    }

    return Widgets{
        fontLst,//字体列表
        styleLst,//字体风格列表(斜体、粗体等
        size,//大小
        foreColor,//前景色
        backColor,//背景色
        display,//文本展示
        ok,//确认
        cancel,//取消
    };
}

QGroupBox *XJ_CharFormatDialog::__CreateGroupBox(QString title, QList<QWidget*> wids){
    QGroupBox*gBox=new QGroupBox(title,this);
    QVBoxLayout*box=new QVBoxLayout(gBox);
    foreach(QWidget* wid,wids)
        box->addWidget(wid);
//    gBox->setAlignment(Qt::AlignVCenter);
    gBox->setStyleSheet("QGroupBox{border:3px solid rgb(96,192,255); border-radius:5px;margin-top:5px} QGroupBox::title{subcontrol-origin:margin;left:20px;}");
    return gBox;
}

void XJ_CharFormatDialog::__Init_Layout(){
    QWidget *wid_other=new QWidget(this);//先把大小、前景色、背景色这仨控件装起来
    {
        QLabel*lb_size=new QLabel("  大小：",this);
        QLabel*lb_foreColor=new QLabel("前景色：",this);
        QLabel*lb_backColor=new QLabel("背景色：",this);

        QGridLayout *grid=new QGridLayout(wid_other);
        grid->addWidget(lb_size,0,0);
        grid->addWidget(lb_foreColor,1,0);
        grid->addWidget(lb_backColor,2,0);
        grid->addWidget(this->__wids.size,0,1);
        grid->addWidget(this->__wids.foreColor,1,1);
        grid->addWidget(this->__wids.backColor,2,1);
//        QVBoxLayout* vbox=(QVBoxLayout*)other->layout();//盒布局不好控制缩进，废弃不用
//        QHBoxLayout* hbox1=new QHBoxLayout();
//        QHBoxLayout* hbox2=new QHBoxLayout();
//        QHBoxLayout* hbox3=new QHBoxLayout();
//        hbox1->addWidget(lb_size);
//        hbox1->addWidget(this->__wids.size);
//        hbox2->addWidget(lb_foreColor);
//        hbox2->addWidget(this->__wids.foreColor);
//        hbox3->addWidget(lb_backColor);
//        hbox3->addWidget(this->__wids.backColor);
//        vbox->addLayout(hbox1);
//        vbox->addLayout(hbox2);
//        vbox->addLayout(hbox3);
    }

    QGroupBox*font=this->__CreateGroupBox("字体",{this->__wids.fontLst});
    QGroupBox*styleLst=this->__CreateGroupBox("样式",{this->__wids.styleLst});
    QGroupBox*other=this->__CreateGroupBox("其他",{wid_other});
    QGroupBox*display=this->__CreateGroupBox("样例展示",{this->__wids.display});

    QVBoxLayout *vbox=new QVBoxLayout(this);
    QVBoxLayout *vbox1=new QVBoxLayout();
    QVBoxLayout *vbox2=new QVBoxLayout();
    QHBoxLayout *hbox1=new QHBoxLayout();
    QHBoxLayout *hbox2=new QHBoxLayout();
    vbox1->addWidget(font,6);//装“字体”和“样例展示”
    vbox1->addWidget(display,4);
    vbox2->addWidget(styleLst);//装“样式”和“其他”
    vbox2->addWidget(other);
    hbox1->addLayout(vbox1,7);//装入俩盒布局
    hbox1->addLayout(vbox2,3);
    hbox2->addStretch(10);//装入“确认”和“撤销”按钮
    hbox2->addWidget(this->__wids.ok);
    hbox2->addWidget(this->__wids.cancel);
    vbox->addLayout(hbox1);//装入俩盒布局，布局设置完毕
    vbox->addLayout(hbox2);
}

void XJ_CharFormatDialog::__Init_Other(){
    this->__wids.display->setText("abcdefg\nABCDEFG\n1234567\n一二三四五六七");
    QObject::connect(this->__wids.size,&XJ_NumInput::valueChanged,this,&XJ_CharFormatDialog::__Set_Size);
    QObject::connect(this->__wids.styleLst,&QListWidget::itemClicked,this,&XJ_CharFormatDialog::__Set_Style);
    QObject::connect(this->__wids.fontLst,&QListWidget::itemClicked,this,&XJ_CharFormatDialog::__Set_Font);
    QObject::connect(this->__wids.foreColor,&XJ_ColorChoose::valueChanged,this,&XJ_CharFormatDialog::__Set_ForeColor);
    QObject::connect(this->__wids.backColor,&XJ_ColorChoose::valueChanged,this,&XJ_CharFormatDialog::__Set_BackColor);
    QObject::connect(this->__wids.ok,&QPushButton::clicked,this,&XJ_CharFormatDialog::__Opt_OK);
    QObject::connect(this->__wids.cancel,&QPushButton::clicked,this,&XJ_CharFormatDialog::__Opt_Cancel);

}



void XJ_CharFormatDialog::__UpdateWidgetsValue(XJ_CharFormatDialog::Widgets wids){
    QTextCharFormat* charFormat=this->__charFormat_new;

    wids.size->Set_Value(charFormat->font().pointSize());
    wids.foreColor->Set_Color(charFormat->foreground().color());
    wids.backColor->Set_Color(charFormat->background().color());
    {
        QListWidget*pListWidget=wids.fontLst;
        QString family=charFormat->fontFamily();
        for(int pst=0;pst<pListWidget->count();++pst){
            if(family==pListWidget->item(pst)->text()){
                pListWidget->setCurrentRow(pst);
                break;
            }
        }
    }
    {
        QListWidget*pListWidget=wids.styleLst;
        QFont font=charFormat->font();
        for(int pst=0;pst<pListWidget->count();++pst){
            QListWidgetItem* item=pListWidget->item(pst);
            auto t=item->text();
            auto func=this->__styleToGet[item->text()];
            item->setCheckState((font.*func)()?Qt::Checked:Qt::Unchecked);//使用类成员函数指针的一个运算符：.*
        }
    }
}

void XJ_CharFormatDialog::__Opt_Cancel(){
    *this->__charFormat_new=*this->__charFormat_old;
    this->close();//这比hide好使
}

void XJ_CharFormatDialog::__Opt_OK(){
    *this->__charFormat_old=*this->__charFormat_new;
    this->close();
}

void XJ_CharFormatDialog::__Set_Style(QListWidgetItem*item){
    QFont font=this->__charFormat_new->font();
    auto func=(this->__styleToSet)[item->text()];
    (font.*func)(item->checkState());//使用类成员函数指针的一个运算符：.*
    this->__charFormat_new->setFont(font);
    this->update();
    this->signal_change();
}

void XJ_CharFormatDialog::__Set_Font(QListWidgetItem*item){
    this->__charFormat_new->setFontFamily(item->text());
    this->update();
    this->signal_change();
}

void XJ_CharFormatDialog::__Set_Size(int size){
    this->__charFormat_new->setFontPointSize(size);
    this->update();
    this->signal_change();
}

void XJ_CharFormatDialog::__Set_ForeColor(QColor color){
    this->__charFormat_new->setForeground(color);
    this->update();
    this->signal_change();
}

void XJ_CharFormatDialog::__Set_BackColor(QColor color){
    this->__charFormat_new->setBackground(color);
    this->update();
    this->signal_change();
}




