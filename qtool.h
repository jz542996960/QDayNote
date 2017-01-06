#ifndef QTOOL_H
#define QTOOL_H
#include"shwmsgdlg.h"
#include<QDialog>

#define STYLE_CLOSE 00000001  //关闭
#define STYLE_MIN   00000010  //最小化
#define STYLE_MAX   00000100  //最大化

const QString Color_DayDefault   = "rgb(160,118,18)";//日期默认颜色
const QString Color_SolarTerms   = "rgb(200,70,230)";//节气颜色
const QString Color_ShuJiu       = "rgb(20,120,255)";//数九颜色
const QString Color_MeiYu        = "rgb(30,190,35)";//入梅、出梅颜色
const QString Color_SanFu        = "rgb(255,100,25)";//三伏颜色
const QString Color_MonthHeader  = "rgb(0,0,255)";//月首
const QString Color_Holiday      = "rgb(255,0,0)";//节日
const QString Color_Holiday_2    = "rgb(255,30,160)";//其它节日
const QString Color_Weekend      = "rgb(255,0,0)";//周末
const QString Color_Weekday      = "rgb(0,0,0)";//工作日



class QTool: public QObject
{

public:
    QTool();
    static int showMsg(const QString& strMsg);
    static void setDlgNoTitle(QDialog *dlg);
    static void addTitleWidget(QDialog *dlg,const QString& strTitle,int type);
    static QString IntToQString(int value);
    static QColor  getColor(int temp);
};

#endif // QTOOL_H
