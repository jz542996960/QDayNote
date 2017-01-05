#include "qlogindlg.h"
#include "ui_qlogindlg.h"
#include"qjzsq.h"
#include<QGraphicsOpacityEffect>
#include"qtool.h"
#include"qcalendardlg.h"
#include"memory"

QLoginDlg::QLoginDlg(QWidget *parent):QDialog(parent),
    ui(new Ui::QLoginDlg)
{
    ui->setupUi(this);
    InitView();
}

QLoginDlg::~QLoginDlg()
{
    delete ui;
}

void QLoginDlg::InitView()
{
   //隐藏标题栏
   this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

   // QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    //effect->setOpacity(0.5);
    //ui->btn_login->setGraphicsEffect(effect);

   //创建自定义的标题栏
   titleWidget = new QTitleWidget(this);
   titleWidget->setFixedWidth(this->width());
   titleWidget->move(QPoint(0,0));
   titleWidget->SetShowStyle(STYLE_CLOSE);//只显示关闭按钮
   //信号与槽函数
   connect(titleWidget,SIGNAL(closesSignals()),this,SLOT(accept()));
   connect(ui->btn_login,SIGNAL(clicked()),this,SLOT(OnLoginClick()));

}

void QLoginDlg::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragVector = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void QLoginDlg::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton)
    {
        move(event->globalPos() - dragVector);
        event->accept();
    }
}


void QLoginDlg::OnLoginClick()
{
  QString strUserName = "";
  QString strPwd = "";
  strUserName = ui->lineEdit_UserName->text();
  strPwd = ui->lineEdit_Pwd->text();
  if(strUserName.length() <= 0 || strPwd.length() <= 0)
  {
     QTool::showMsg(QStringLiteral("用户名,密码不能为空"));
     return;
  }
  if(QJZSq::getInstance())
  {
    if(QJZSq::getInstance()->Login(strUserName,strPwd))
    {
       std::unique_ptr<QCalendarDlg> dlg  = std::make_unique<QCalendarDlg>(nullptr);
       dlg->exec();
       this->close();
    }
    else
    {
      QTool::showMsg(QStringLiteral("用户名密码错误"));
    }
  }
  else
  {
       QTool::showMsg(QStringLiteral("数据库连接失败"));
  }
}
