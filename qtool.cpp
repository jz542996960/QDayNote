#include "qtool.h"
#include"qtitlewidget.h"
QTool::QTool()
{

}

int QTool::showMsg(const QString& strMsg)
{
    QString str(strMsg);
    ShwMsgDlg *msgDlg = new ShwMsgDlg();
    msgDlg->setShowText(str);
    int ret = msgDlg->exec();
    delete msgDlg;
    msgDlg = NULL;
    return ret;
}

void QTool::setDlgNoTitle(QDialog *dlg)
{
    if(dlg == NULL) return;
    dlg->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
}

void QTool::addTitleWidget(QDialog *dlg,const QString& strTitle,int type)
{
    if(dlg==NULL) return;
    QTitleWidget *titleWidget = new QTitleWidget(dlg);
    titleWidget->setFixedWidth(dlg->width());
    titleWidget->move(0,0);
    titleWidget->SetTitle(strTitle);
    titleWidget->SetShowStyle(type);
    connect(titleWidget,SIGNAL(closesSignals()),dlg,SLOT(close()));
    connect(titleWidget,SIGNAL(minSignals()),dlg,SLOT(showMinimized()));
}

QString QTool::IntToQString(int value)
{
    QString strRet,strValuse;
    strRet = strValuse.setNum(value);
    return strRet;
}
