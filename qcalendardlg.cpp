#include "qcalendardlg.h"
#include "ui_qcalendardlg.h"
#include <QDate>
#include"CalendarCore.h"
int yearDays[12] = {31,30,31,30,31,30,31,31,30,31,30,31};//每月有几天


QString rq2[42]={QStringLiteral("")};//存放农历日期

QCalendarDlg::QCalendarDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCalendarDlg)
{
    ui->setupUi(this);
    InitView();
}

QCalendarDlg::~QCalendarDlg()
{
    delete ui;
}

void QCalendarDlg::InitView()
{
  QTool::setDlgNoTitle(this);
  QTool::addTitleWidget(this,QStringLiteral("日历"),STYLE_CLOSE|STYLE_MIN);
  //初始化界面
  QString strDate;
  for(int i=2016;i<2019;i++)
  {
      ui->comboBoxYear->addItem(strDate.setNum(i));
  }
  for(int i = 1;i<=12;i++)
  {
     ui->comboBoxMonth->addItem(strDate.setNum(i));
  }
  for(int i=1;i<=30;i++)
  {
      ui->comboBoxDay->addItem(strDate.setNum(i));
  }
  //初始设置为当月
   QDate date = QDate::currentDate();
   ui->comboBoxYear->setCurrentText(strDate.setNum(date.year()));
   ui->comboBoxMonth->setCurrentText(strDate.setNum(date.month()));
   ui->comboBoxDay->setCurrentText(strDate.setNum(date.day()));

  //取得所有单个日历表格
  QObjectList objList = ui->widget->children();

  int m_nObjIndex[42] = {8,9,10,14,11,
                         12,13,15,20,
                         19,16,18,17,
                         21,22,27,26,
                         23,25,24,28,
                         29,34,33,30,
                         32,31,35,36,
                         41,40,37,39,
                         38,42,43,48,
                         47,44,46,45,49};

    int j = 0;

  for(int i=0;i<objList.size();++i)
  {
    if(objList[i]->inherits("QDateCellWidget"))
    {

        int mIndex = m_nObjIndex[j];
        j++;
       dateWidgetVec.push_back((QDateCellWidget*)objList[mIndex]);
    }
  }
  if(dateWidgetVec.size()> 0)
  {
      InitWidgetDate();
  }
  //连接信号
  connect(ui->comboBoxMonth,SIGNAL(currentIndexChanged(int)),this,SLOT(OnMonthIndexChange(int)));
   connect(ui->comboBoxYear,SIGNAL(currentIndexChanged(int)),this,SLOT(OnYearIndexChange(int)));
}

void QCalendarDlg::InitWidgetDate()//根据年份月份显示日历
{
  int m_nMonth = ui->comboBoxMonth->currentText().toInt(); //月
  int m_nYear = ui->comboBoxYear->currentText().toInt();//年
  int m_nDay = ui->comboBoxDay->currentText().toInt();//日

  short wDayofWeek_1=CCalendarCore::GetDayOfWeek(m_nYear,m_nMonth,1);//获取这个月1日的星期
  short m_nMonthDays = CCalendarCore::GetDaysOfMonth(m_nYear,m_nMonth);//得到这个月一共有几天
  WORD wLunarYear,wLunarMonth,wLunarDay = 0;//农历的年月日
  BOOL bLeapMonth = false;//是否闰月

  CCalendarCore::GetLunar(m_nYear,m_nMonth,1,wLunarYear,wLunarMonth,wLunarDay,bLeapMonth);//计算这个月1日的农历
  int wLunarDaysofMonth = CCalendarCore::LunarGetDaysofMonth(wLunarYear,wLunarMonth,bLeapMonth);//获取农历总天数\


  if (wDayofWeek_1==-1)
  {
      return;//输入年月有误
  }

  /*计算公立*/
  for(int i = 0;i<wDayofWeek_1;i++)
  {
      dateWidgetVec[i]->setDays("","");
  }


  for(int i=1;i<=m_nMonthDays;i++)
  {

     dateWidgetVec[wDayofWeek_1]->setGongLiDay(QTool::IntToQString(i));
     wDayofWeek_1++;
  }


  for(int i=wDayofWeek_1;i<42;i++)
  {
     dateWidgetVec[i]->setDays("","");
  }

  /*计算农历*/
  int tmp = 0;
  for(;tmp<42;tmp++)
  {
    rq2[tmp] = QStringLiteral("");//清空
  }

  int wCurGDayIndex = 0;
  int wCurLunarDayIndex = wLunarDay - 1;
  wDayofWeek_1=CCalendarCore::GetDayOfWeek(m_nYear,m_nMonth,1);//获取这个月1日的星期
  while( wCurGDayIndex < m_nMonthDays)
  {
    tmp = 0;
    if(wCurLunarDayIndex >= wLunarDaysofMonth)
    {
        CCalendarCore::GetLunar(m_nYear,m_nMonth,wCurGDayIndex+1,wLunarYear,wLunarMonth,wLunarDay,bLeapMonth);//计算此时的农历
        wLunarDaysofMonth=CCalendarCore::LunarGetDaysofMonth(wLunarYear,wLunarMonth,bLeapMonth);//获取农历总天数
        wCurLunarDayIndex=0;//重新回到初一
        rq2[wCurGDayIndex+wDayofWeek_1]=("");
        if (bLeapMonth)
        {
           rq2[wCurGDayIndex+wDayofWeek_1] = QStringLiteral(" 闰");
        }
        rq2[wCurGDayIndex+wDayofWeek_1]+=yName[wLunarMonth-1];
        if (wLunarDaysofMonth==30)
        {
            rq2[wCurGDayIndex+wDayofWeek_1] += QStringLiteral("（大）");
        }
        else
         {
             rq2[wCurGDayIndex+wDayofWeek_1] += QStringLiteral("（小）");
         }
         tmp=5;
    }
    else
    {
      QString str = rName[wCurLunarDayIndex];
      rq2[wCurGDayIndex + wDayofWeek_1] = rName[wCurLunarDayIndex];
    }
    if(tmp == 0)
    {
      tmp = CCalendarCore::L_HolidayShow(wLunarYear,wLunarMonth,wCurLunarDayIndex+1,bLeapMonth,rq2[wCurGDayIndex+wDayofWeek_1]);//农历节日
      int tmp2=0;
      QString str_tmp;
      tmp2 = CCalendarCore::G_HolidayShow(m_nYear,m_nMonth,wCurGDayIndex+1,str_tmp);//公历节日及节气
      if(tmp != 0)
      {
         if(tmp2 != 0) //如果公立和农历都有节日
         {
             QString str = " ";
             str += str_tmp;
             rq2[wCurGDayIndex+wDayofWeek_1]+=str;
         }
      }
      else
      {
          if (tmp2!=0)//只有公历节日
          {
              rq2[wCurGDayIndex+wDayofWeek_1]=str_tmp;
              tmp=tmp2;
          }
      }
    }
    wCurLunarDayIndex++;
    wCurGDayIndex++;
  }


  for(int i=0;i<42;i++)
  {
    dateWidgetVec[i]->setNongLiDay(rq2[i]);
  }



}

void QCalendarDlg::OnMonthIndexChange(int index)
{
   int m_nMonth = ui->comboBoxMonth->currentText().toInt();
   int m_nYear = ui->comboBoxYear->currentText().toInt();
   int days = CCalendarCore::GetDaysOfMonth(m_nYear,m_nMonth);//得到这个月一共有几天

   ui->comboBoxDay->clear();
   for(int i=1;i<=days;i++)
   {
      ui->comboBoxDay->addItem( QTool::IntToQString(i));
   }
   InitWidgetDate();

}

void QCalendarDlg::OnYearIndexChange(int index)
{
    int m_nYear = ui->comboBoxYear->itemText(index).toInt();
    int m_nMonth  = ui->comboBoxMonth->currentText().toInt();
    int days = CCalendarCore::GetDaysOfMonth(m_nYear,m_nMonth);//得到这个月一共有几天
    ui->comboBoxDay->clear();
    for(int i=1;i<=days;i++)
    {
       ui->comboBoxDay->addItem(QTool::IntToQString(i));
    }
    InitWidgetDate();
}
