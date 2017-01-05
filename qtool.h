#ifndef QTOOL_H
#define QTOOL_H
#include"shwmsgdlg.h"
#include<QDialog>

#define STYLE_CLOSE 00000001  //关闭
#define STYLE_MIN   00000010  //最小化
#define STYLE_MAX   00000100  //最大化

class QTool: public QObject
{

public:
    QTool();
    static int showMsg(const QString& strMsg);
    static void setDlgNoTitle(QDialog *dlg);
    static void addTitleWidget(QDialog *dlg,const QString& strTitle,int type);
    static QString IntToQString(int value);
};

#endif // QTOOL_H
