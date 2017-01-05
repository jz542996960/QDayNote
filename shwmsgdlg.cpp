#include "shwmsgdlg.h"
#include "ui_shwmsgdlg.h"
#include"qtool.h"

ShwMsgDlg::ShwMsgDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShwMsgDlg)
{
    ui->setupUi(this);
    titleWidget = NULL;
    InitView();
}

ShwMsgDlg::~ShwMsgDlg()
{
    delete ui;
}

void ShwMsgDlg::setShowText(QString strMsg)
{
    ui->labelMsg->setText(strMsg);
}

void ShwMsgDlg::InitView()
{
   QTool::setDlgNoTitle(this);
   //创建自定义的标题栏
   titleWidget = new QTitleWidget(this);
   titleWidget->setFixedWidth(this->width());
   titleWidget->move(QPoint(0,0));
   titleWidget->SetShowStyle(0);//只显示关闭按钮
   //信号与槽函数
   connect(titleWidget,SIGNAL(closesSignals()),this,SLOT(accept()));
}

