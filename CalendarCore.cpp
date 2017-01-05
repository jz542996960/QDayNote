#include "CalendarCore.h"
#include "LunarData.h"

int const DayOrdinal[13]={0,31,59,90,120,151,181,212,243,273,304,334,365};//平年的每个月1日所对应的年内序数
int const DayOrdinalLeap[13]={0,31,60,91,121,152,182,213,244,274,305,335,366};//闰年的每个月1日对应的年内序数

CCalendarCore::CCalendarCore(void)
{
}

CCalendarCore::~CCalendarCore(void)
{
}

/*************************************************************************
* 函数名称： IsLeapYear
* 完整名称： CCalendarCore::IsLeapYear
* 功能描述： 是否为闰年
* 函数参数： WORD wYear		公历年份
* 函数参数： BOOL & bLeapYear		是否闰年
* 返回类型： BOOL		TRUE：成功，FALSE：失败
* 访问方式： public static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::IsLeapYear(WORD wYear,BOOL &bLeapYear)
{
    if (wYear<1600||wYear>=6400)//压缩算法规定了的年份区间
    {
        return FALSE;
    }
    if (wYear%4==0&&wYear%100!=0||wYear%400==0)//判断闰年的条件
    {
        bLeapYear=TRUE;
    }else
    {
        bLeapYear=FALSE;
    }
    return TRUE;
}

/*************************************************************************
* 函数名称： GetDayOrdinal
* 完整名称： CCalendarCore::GetDayOrdinal
* 功能描述： 获取年内序数，元旦为0
* 函数参数： WORD wYear
* 函数参数： WORD wMonth
* 函数参数： WORD wDay
* 函数参数： WORD & wOrdinal		年内序数
* 返回类型： BOOL
* 访问方式： public static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::GetDayOrdinal(WORD wYear, WORD wMonth, WORD wDay,WORD &wOrdinal)
{
    //从日期算出距离元旦的天数
    if (DateCheck(wYear,wMonth,wDay)==0)//对输入的日期进行检查
    {
        return FALSE;
    }
    BOOL bLeapYear=FALSE;
    if (!IsLeapYear(wYear,bLeapYear))
    {
        return FALSE;
    }
    if (bLeapYear==TRUE)
    {
        wOrdinal=DayOrdinalLeap[wMonth-1]+wDay-1;//元旦为序数0，因此减1
    }else
    {
        wOrdinal=DayOrdinal[wMonth-1]+wDay-1;
    }
    return TRUE;
}

/*************************************************************************
* 函数名称： GetDateFromOrdinal
* 完整名称： CCalendarCore::GetDateFromOrdinal
* 功能描述： 从年内序数计算月和日
* 函数参数： WORD wYear		公历年
* 函数参数： WORD wOrdinal		年内序数（元旦为0）
* 函数参数： WORD & wMonth		公历月
* 函数参数： WORD & wDay		公历日
* 返回类型： BOOL
* 访问方式： public static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::GetDateFromOrdinal(WORD wYear, WORD wOrdinal, WORD &wMonth, WORD &wDay)
{
    //从距离元旦的天数算出日期
    if (wOrdinal<0)
    {
        return FALSE;
    }
    BOOL bLeapYear=FALSE;
    if (!IsLeapYear(wYear,bLeapYear))
    {
        return FALSE;
    }
    if (bLeapYear==TRUE)
    {
        if (wOrdinal>=366)//超出了该年的总天数
        {
            return FALSE;
        }
    }else
    {
        if (wOrdinal>=365)
        {
            return FALSE;
        }
    }
    wMonth=0;
    int i=0;
    for (i=0;i<12;i++)
    {
        if (bLeapYear==TRUE)
        {
            if (wOrdinal>=DayOrdinalLeap[i]&&wOrdinal<DayOrdinalLeap[i+1])//找出月份
            {
                wMonth=i+1;
                wDay=wOrdinal-DayOrdinalLeap[i]+1;//计算出“日”
                break;
            }
        }else
        {
            if (wOrdinal>=DayOrdinal[i]&&wOrdinal<DayOrdinal[i+1])
            {
                wMonth=i+1;
                wDay=wOrdinal-DayOrdinal[i]+1;
                break;
            }
        }
    }
    return TRUE;
}

/*************************************************************************
* 函数名称： DateCheck
* 完整名称： CCalendarCore::DateCheck
* 功能描述： 日期合法性检查
* 函数参数： WORD wYear
* 函数参数： WORD wMonth
* 函数参数： WORD wDay
* 返回类型： BOOL
* 访问方式： private static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::DateCheck(WORD wYear,WORD wMonth,WORD wDay)
{
    if (wYear<START_YEAR||wYear>=END_YEAR||wMonth>12||wMonth<1||wDay<1||wDay>31)
    {
        return FALSE;
    }
    if (wMonth==4||wMonth==6||wMonth==9||wMonth==11)
    {
        if (wDay==31)
        {
            return FALSE;
        }
    }else if (wMonth==2)
    {
        BOOL bLeapYear=FALSE;
        IsLeapYear(wYear,bLeapYear);
        if (bLeapYear==FALSE)
        {
            if (wDay>28)
            {
                return FALSE;
            }
        }else
        {
            if (wDay>29)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/*************************************************************************
* 函数名称： LunarGetNewYearOrdinal
* 完整名称： CCalendarCore::LunarGetNewYearOrdinal
* 功能描述： 获取农历正月初一的年内序数
* 函数参数： WORD wLunarYear
* 返回类型： short
* 访问方式： public static
* 函数状态：
**************************************************************************/
short CCalendarCore::LunarGetNewYearOrdinal(WORD wLunarYear)
{
    UINT uData=0;
    if (GetMonthInfo(wLunarYear,uData)==FALSE)
    {
        return 0;
    }
    return (short)((uData>>17)&0x3F);//取出农历新年的年内序数
}

/*************************************************************************
* 函数名称： LunarGetDaysofMonth
* 完整名称： CCalendarCore::LunarGetDaysofMonth
* 功能描述： 获取农历月的天数
* 函数参数： WORD wLunarYear
* 函数参数： WORD wLunarMonth
* 函数参数： BOOL bLeapMonth
* 返回类型： WORD
* 访问方式： public static
* 函数状态：
**************************************************************************/
WORD CCalendarCore::LunarGetDaysofMonth(WORD wLunarYear,WORD wLunarMonth,BOOL bLeapMonth)
{
    int i=0;//循环变量
    WORD DX_data=0;//该年大小月情况
    WORD Acc_LeapMonth=0;
    if (wLunarYear==START_YEAR-1)//农历还在起始年份的前一年
    {
        if (cPreLeapIndex==-1)//无闰月
        {
            if (bLeapMonth==TRUE)
            {
                return 0;
            }
            return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
        }else
        {
            Acc_LeapMonth=cPreLeapIndex+9;
            if (Acc_LeapMonth>wLunarMonth)
            {
                if (bLeapMonth==TRUE)
                {
                    return 0;
                }
                return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
            }else
            {
                if ((bLeapMonth==1&&wLunarMonth==Acc_LeapMonth)||wLunarMonth>Acc_LeapMonth)
                {
                    return cPreMonth[wLunarMonth-8]-cPreMonth[wLunarMonth-9];
                }else
                {
                    return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
                }
            }
        }
    }
    UINT uData=0;
    if (GetMonthInfo(wLunarYear,uData)==FALSE)
    {
        return 0;
    }
    DX_data=(WORD)(uData&0x1FFF);//整年大小月情况
    Acc_LeapMonth=LunarGetLeapMonth(wLunarYear);//获取真实闰月月份
    if (bLeapMonth)//指定查询的当前月是闰月
    {
        if (Acc_LeapMonth!=wLunarMonth)
        {
            return 0;//不存在的闰月
        }
        for (i=0;i<wLunarMonth;i++)
        {
            DX_data>>=1;//右移一位，即从末尾开始找该闰月月份所在的位
        }
    }else
    {
        if (Acc_LeapMonth>0)//存在闰月
        {
            if (wLunarMonth<=Acc_LeapMonth)//月份在闰月之前，倒找需要多找一位
            {
                for (i=0;i<wLunarMonth-1;i++)
                {
                    DX_data>>=1;
                }
            }else
            {
                for (i=0;i<wLunarMonth;i++)//月份在闰月之后
                {
                    DX_data>>=1;
                }
            }
        }else
        {
            for (i=0;i<wLunarMonth-1;i++)//无闰月
            {
                DX_data>>=1;
            }
        }
    }
    if (DX_data&0x01)
    {
        return 30;//大月
    }else
    {
        return 29;//小月
    }
}

/*************************************************************************
* 函数名称： LunarExpandDX
* 完整名称： CCalendarCore::LunarExpandDX
* 功能描述： 展开大小月信息
* 函数参数： WORD wLunarYear
* 函数参数： WORD wDayOfMonth[15]
* 返回类型： BOOL
* 访问方式： private static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::LunarExpandDX(WORD wLunarYear,WORD wDayOfMonth[15])
{
    if (wLunarYear<START_YEAR||wLunarYear>=END_YEAR)
    {
        return FALSE;
    }
    int i=0;//循环变量
    WORD pos=0,iLeapMonth=0;//数组写入位置，闰月
    for (i=0;i<15;i++)
    {
        wDayOfMonth[i]=0;//对数组清零
    }
    if (wLunarYear==START_YEAR)
    {
        if (cPreLeapIndex==-1)//处理起始年份之前一年数据
        {
            wDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];//农历上一年十一月总天数
            pos++;
        }else
        {
            if (cPreLeapIndex==1)//闰十月
            {
                wDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
                pos++;
            }else
            {
                //闰十一月或闰十二月
                wDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];
                pos++;
                wDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
                pos++;
            }
        }
        wDayOfMonth[pos]=LunarGetNewYearOrdinal(wLunarYear)-cPreMonth[2];//（闰）十二月
        pos++;
    }else
    {
        iLeapMonth=LunarGetLeapMonth(wLunarYear-1);//取得前一农历年的闰月情况
        if (iLeapMonth<11)//一月至十月的闰月
        {
            wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear-1,11,0);//取上一年十一月天数
            pos++;
            wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear-1,12,0);//取上一年十二月天数
            pos++;
        }else
        {
            wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear-1,11,0);//取上一年十一月的天数
            pos++;
            if (iLeapMonth==11)//闰十一月
            {
                wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear-1,11,1);//取上一年闰十一月的天数
                pos++;
                wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear-1,12,0);//取上一年十二月天数
                pos++;
            }else if (iLeapMonth==12)
            {
                wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear-1,12,0);//取上一年十二月天数
                pos++;
                wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear-1,12,1);//取上一年闰十二月天数
                pos++;
            }
        }
    }
    iLeapMonth=LunarGetLeapMonth(wLunarYear);//获取当前农历年的闰月情况
    if (iLeapMonth==0)//无闰月
    {
        for (i=0;i<12;i++)
        {
            wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear,i+1,0);//取每个农历月天数
            pos++;
        }
    }else
    {
        for (i=0;i<12;i++)
        {
            if (i==iLeapMonth)
            {
                wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear,i,1);//取闰月的天数
                pos++;
            }
            wDayOfMonth[pos]=LunarGetDaysofMonth(wLunarYear,i+1,0);//取非闰月的天数
            pos++;
        }
    }
    return TRUE;
}

/*************************************************************************
* 函数名称： GetMonthInfo
* 完整名称： CCalendarCore::GetMonthInfo
* 功能描述： 获取农历月份信息（从提取cMonthInfo中提取）
* 形式参数： WORD wYear
* 形式参数： UINT & uData
* 访问方式： private static
* 返回类型： BOOL
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::GetMonthInfo(WORD wYear,UINT& uData)
{
    if (wYear<START_YEAR||wYear>=END_YEAR)
    {
        return FALSE;
    }
    int iStartPos=(wYear-START_YEAR)*3;
    uData=byMonthInfo[iStartPos];
    uData<<=8;
    uData|=byMonthInfo[iStartPos+1];
    uData<<=8;
    uData|=byMonthInfo[iStartPos+2];
    return TRUE;
}

/*************************************************************************
* 函数名称： LunarGetLeapMonth
* 完整名称： CCalendarCore::LunarGetLeapMonth
* 功能描述： 获取农历闰月月份
* 函数参数： WORD wLunarYear
* 返回类型： WORD
* 访问方式： public static
* 函数状态：
**************************************************************************/
WORD CCalendarCore::LunarGetLeapMonth(WORD wLunarYear)
{
    UINT data=0;
    if (GetMonthInfo(wLunarYear,data)==FALSE)
    {
        return 0;
    }
    WORD wLeapMonth=(WORD)((data>>13)&0x0F);
    return wLeapMonth;
}

/*************************************************************************
* 函数名称： GetLunar
* 完整名称： CCalendarCore::GetLunar
* 功能描述： 获取农历
* 函数参数： WORD wYear
* 函数参数： WORD wMonth
* 函数参数： WORD wDay
* 函数参数： WORD & wLunarYear
* 函数参数： WORD & wLunarMonth
* 函数参数： WORD & wLunarDay
* 函数参数： BOOL & bLeapMonth
* 返回类型： BOOL
* 访问方式： public static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::GetLunar(WORD wYear,WORD wMonth,WORD wDay,WORD &wLunarYear,WORD &wLunarMonth,WORD &wLunarDay,BOOL &bLeapMonth)
{
    WORD DaysNum=0;//年内序数
    if (!GetDayOrdinal(wYear,wMonth,wDay,DaysNum))
    {
        return FALSE;//日期不正确
    }
    wLunarYear=wYear;
    short LunarNewYear=0,remain_days=0;//农历新年的公历年内序数，剩余天数
    WORD DaysOfLunarMonth[15]={0};//存放农历月份天数
    WORD iLeapMonthPre=0,iLeapMonth=0;//农历上一年闰月，今年闰月
    LunarNewYear=LunarGetNewYearOrdinal(wLunarYear);
    LunarExpandDX(wLunarYear,DaysOfLunarMonth);//获取月份天数，数组从上一年十一月开始到今年（闰）十二月，包含闰月
    iLeapMonthPre=LunarGetLeapMonth(wLunarYear-1);
    if (iLeapMonthPre==0)
    {
        iLeapMonth=LunarGetLeapMonth(wLunarYear);//上一年没有闰月，则查询今年闰月
    }
    bLeapMonth=FALSE;
    remain_days=DaysNum-LunarNewYear;//距离农历新年天数
    int i=0;
    if (iLeapMonthPre>10)
    {
        i=3;//今年正月在“DaysOfLunarMonth”中的索引，上一年十一月或十二月有闰月
    }else
    {
        i=2;//上一年十一月和十二月无闰月时，今年正月的索引
    }
    if (LunarNewYear>DaysNum)//早于农历新年
    {
        wLunarYear-=1;//农历年减1
        while(remain_days<0)
        {
            i--;//第一次先减去是因为当前i是正月，减1表示上一年十二月（或闰十二月）
            remain_days+=DaysOfLunarMonth[i];//加上上一年十二月、十一月的总天数（含闰月）直到日数大于0
        }
        if (iLeapMonthPre>10)//如果上一年十一月或十二月存在闰月
        {
            if (iLeapMonthPre==11)//闰十一月
            {
                if (i==0)//十一月（即在闰月之前）
                {
                    wLunarMonth=11+i;//转换到月份
                }else
                {
                    wLunarMonth=10+i;
                    if (wLunarMonth==iLeapMonthPre)
                    {
                        bLeapMonth=1;
                    }
                }
            }else if (iLeapMonthPre==12)//闰十二月
            {
                if (i<2)//在闰月之前
                {
                    wLunarMonth=11+i;
                }else
                {
                    wLunarMonth=10+i;
                    if (wLunarMonth==iLeapMonthPre)
                    {
                        bLeapMonth=TRUE;
                    }
                }
            }
        }else
        {
            wLunarMonth=11+i;
        }
        wLunarDay=remain_days;
    }else
    {
        while (remain_days>=DaysOfLunarMonth[i])
        {
            remain_days-=DaysOfLunarMonth[i];//寻找农历月
            i++;//移至下个月
        }
        if (iLeapMonthPre>10)
        {
            wLunarMonth=i-2;
        }else
        {
            if (iLeapMonth>0)
            {
                if (i-2<iLeapMonth)
                {
                    wLunarMonth=i-1;
                }else
                {
                    wLunarMonth=i-2;
                    if (wLunarMonth==iLeapMonth)
                    {
                        bLeapMonth=TRUE;
                    }
                }
            }else
            {
                wLunarMonth=i-1;
            }
        }
        wLunarDay=remain_days;
    }
    wLunarDay+=1;//索引转换到数量
    return TRUE;
}

/*************************************************************************
* 函数名称： GetGregorian
* 完整名称： CCalendarCore::GetGregorian
* 功能描述： 获取公历
* 函数参数： WORD wLunarYear
* 函数参数： WORD wLunarMonth
* 函数参数： WORD wLunarDay
* 函数参数： BOOL bLeapMonth
* 函数参数： WORD & wYear
* 函数参数： WORD & wMonth
* 函数参数： WORD & wDay
* 返回类型： BOOL
* 访问方式： public static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::GetGregorian(WORD wLunarYear,WORD wLunarMonth,WORD wLunarDay,BOOL bLeapMonth,WORD &wYear,WORD &wMonth,WORD &wDay)
{
    if (wLunarYear<START_YEAR||wLunarYear>=END_YEAR||wLunarMonth<1||wLunarMonth>12||wLunarDay<1||wLunarDay>30)
    {
        return FALSE;//年、月、日检查
    }
    if (bLeapMonth)
    {
        if (LunarGetLeapMonth(wLunarYear)!=wLunarMonth)
        {
            return FALSE;//闰月检查
        }
    }
    if (wLunarDay>LunarGetDaysofMonth(wLunarYear,wLunarMonth,bLeapMonth))
    {
        return FALSE;//大小月检查
    }
    WORD DaysOfLunarMonth[15]={0};//存放农历月份天数
    WORD iLeapMonthPre=0,iLeapMonth=0;//农历年闰月
    WORD LunarNewYear=0;//农历新年的公历年内序数
    WORD iDaysofYear=0;//一年总天数
    short remain_days=0;//剩余天数
    int i=0;//循环变量
    LunarExpandDX(wLunarYear,DaysOfLunarMonth);//大小月表（农历每月天数）
    LunarNewYear=LunarGetNewYearOrdinal(wLunarYear);//找到正月初一r公历年内序数
    iLeapMonth=LunarGetLeapMonth(wLunarYear);//找出农历年的闰月
    remain_days+=LunarNewYear;//加上正月初一的序数
    if (iLeapMonthPre>10)
    {
        i=3;//今年正月在“DaysOfLunarMonth”中的索引，上一年十一月或十二月有闰月
    }else
    {
        i=2;//上一年十一月和十二月无闰月时，今年正月的索引
    }
    if (iLeapMonth==0)
    {
        if (iLeapMonthPre>10)
        {
            for (;i<wLunarMonth+2;i++)
            {
                remain_days+=DaysOfLunarMonth[i];//年内序数累加
            }
        }else
        {
            for (;i<wLunarMonth+1;i++)
            {
                remain_days+=DaysOfLunarMonth[i];//年内序数累加
            }
        }
    }else
    {
        if (wLunarMonth<iLeapMonth||(bLeapMonth==FALSE&&wLunarMonth==iLeapMonth))//在闰月之前
        {
            for (;i<wLunarMonth+1;i++)
            {
                remain_days+=DaysOfLunarMonth[i];
            }
        }else
        {
            for (;i<wLunarMonth+2;i++)
            {
                remain_days+=DaysOfLunarMonth[i];
            }
        }
    }
    remain_days+=wLunarDay-1;//减1是因为日名转到序数
    GetDayOrdinal(wLunarYear,12,31,iDaysofYear);//获取公历年总天数
    iDaysofYear++;//由序数转为天数
    wYear=wLunarYear;
    if (remain_days>iDaysofYear)
    {
        remain_days-=iDaysofYear;
        wYear+=1;//下一年
    }
    GetDateFromOrdinal(wYear,remain_days,wMonth,wDay);
    return TRUE;
}

/*************************************************************************
* 函数名称： GetJieQi
* 完整名称： CCalendarCore::GetJieQi
* 功能描述： 获取指定公历月份内的两个节气
* 函数参数： WORD wYear
* 函数参数： WORD wMonth
* 函数参数： WORD wJieQi[2]
* 返回类型： BOOL
* 访问方式： public static
* 函数状态：
**************************************************************************/
BOOL CCalendarCore::GetJieQi(WORD wYear,WORD wMonth,WORD wJieQi[2])
{
    if (wYear<START_YEAR||wYear>=END_YEAR||wMonth>12||wMonth<1)
    {
        return FALSE;
    }
    int index=(wYear-START_YEAR)*3;//对应每公历年首个节气所在字节的索引
    WORD wJQData=wSTSource[bySTIndex[index]];
    WORD wXiaoHanOrder=(unsigned short)((wJQData>>14)+3);//加上3，转为小寒的年内序数
    WORD wCurJQData=(wJQData>>12)&0x03;//当前计算的节气与上一节气的天数差信息
    if (wMonth==1)
    {
        wJieQi[0]=wXiaoHanOrder+1;//加1转到日期
        wJieQi[1]=wCurJQData+14+wXiaoHanOrder+1;//大寒：小寒的年内序数加上距离小寒的天数
        return TRUE;
    }
    int iRem=0;
    WORD wDays=wCurJQData+14;//距离小寒的天数，当前为大寒距离小寒的天数
    wDays+=wXiaoHanOrder;//加上小寒，转为年内序数
    for (int i=1;i<wMonth;i++)
    {
        iRem=i%4;
        wCurJQData=(wJQData>>(18-((iRem+1)<<2)))&0x03;
        wDays+=wCurJQData+14;
        wCurJQData=(wJQData>>(16-((iRem+1)<<2)))&0x03;
        wDays+=wCurJQData+14;
        if (iRem==3)
        {
            wJQData=wSTSource[bySTIndex[index+(i+1)/4]];
        }
    }
    GetDateFromOrdinal(wYear,wDays,wMonth,wJieQi[1]);//wMonth中的第二个节气
    GetDateFromOrdinal(wYear,wDays-wCurJQData-14,wMonth,wJieQi[0]);//第一个节气
    return TRUE;
}

/*************************************************************************
* 函数名称： GetDayOfWeek
* 完整名称： CCalendarCore::GetDayOfWeek
* 功能描述： 获取星期
* 函数参数： WORD wYear
* 函数参数： WORD wMonth
* 函数参数： WORD wDay
* 返回类型： short
* 访问方式： public static
* 函数状态：
**************************************************************************/
short CCalendarCore::GetDayOfWeek(WORD wYear,WORD wMonth,WORD wDay)
{
    WORD uDayOrd=0;
    if (GetDayOrdinal(wYear,wMonth,wDay,uDayOrd)==0)
    {
        return -1;
    }
    unsigned int DayofWeek=0;
    uDayOrd++;//一年中的第几天，因为GetDayOrdinal所得到的是索引，因此要加一
    wYear--;
    DayofWeek=(wYear+wYear/4-wYear/100+wYear/400+uDayOrd)%7;//这个只是算星期的通用公式
    return DayofWeek;
}

/*************************************************************************
* 函数名称： GetDaysOfMonth
* 完整名称： CCalendarCore::GetDaysOfMonth
* 功能描述： 取公历月份天数
* 函数参数： WORD wYear
* 函数参数： WORD wMonth
* 返回类型： WORD
* 访问方式： public static
* 函数状态：
**************************************************************************/
WORD CCalendarCore::GetDaysOfMonth(WORD wYear,WORD wMonth)
{
    if (wMonth==12)
    {
        return 31;//这里为了简便，判断12月就直接返回
    }
    WORD days1=0,days2=0;
    WORD ret=0;
    ret=GetDayOrdinal(wYear,wMonth,1,days1);//本月1日在年内的序数
    if (ret==0)
    {
        return ret;
    }
    wMonth++;
    ret=GetDayOrdinal(wYear,wMonth,1,days2);//下个月1日的年内序数
    if (ret==0)
    {
        return ret;
    }
    ret=days2-days1;//下个月1日的序数减本月1日的序数
    return ret;
}

//*************************************************************************
// 函数名称： GetExtremeSeason
// 完整名称： CCalendarCore::GetExtremeSeason
// 功能描述： 获取数九、伏日信息
// 形式参数： WORD wYear
// 形式参数： short * sYijiu
// 形式参数： unsigned short * wChuFu
// 形式参数： unsigned short * wMoFu
// 访问方式： public static
// 返回类型： BOOL
// 函数状态：
//*************************************************************************
BOOL CCalendarCore::GetExtremeSeason(WORD wYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu)
{
    if (wYear<START_YEAR||wYear>=END_YEAR)
    {
        return FALSE;
    }
    WORD wjq[2]={0};
    int ET_index=wYear-START_YEAR;//数九、梅雨及三伏的年份索引
    if (wYear==START_YEAR)
    {
        *sYijiu=cPreDongzhiOrder;
    }else
    {
        GetJieQi(wYear-1,12,wjq);
        *sYijiu=wjq[1]-32;
    }
    *wChuFu=((wExtermSeason[ET_index]&0x3E)>>1)+180;
    *wMoFu=(*wChuFu)+((wExtermSeason[ET_index]&0x01)==1?30:20);
    return TRUE;
}

//*************************************************************************
// 函数名称： GetMeiYu
// 完整名称： CCalendarCore::GetMeiYu
// 功能描述： 获取入梅、出梅日期
// 形式参数： WORD wYear
// 形式参数： unsigned short * wRuMeiOrd
// 形式参数： unsigned short * wChuMeiOrd
// 访问方式： public static
// 返回类型： BOOL
// 函数状态：
//*************************************************************************
BOOL CCalendarCore::GetMeiYu(WORD wYear,unsigned short* wRuMeiOrd,unsigned short* wChuMeiOrd)
{
    if (wYear<START_YEAR||wYear>=END_YEAR)
    {
        return FALSE;
    }
    int ET_index=wYear-START_YEAR;//数九、梅雨及三伏的年份索引
    *wRuMeiOrd=((wExtermSeason[ET_index]&0xF800)>>11)+150;
    *wChuMeiOrd=((wExtermSeason[ET_index]&0x07C0)>>6)+180;
    return TRUE;
}

//*************************************************************************
// 函数名称： G_HolidayShow
// 完整名称： CCalendarCore::G_HolidayShow
// 功能描述： 公历节日
// 形式参数： WORD wYear
// 形式参数： WORD wMonth
// 形式参数： WORD wDay
// 形式参数： CString & Buf
// 访问方式： public static
// 返回类型： BYTE
// 函数状态：
//*************************************************************************
BYTE CCalendarCore::G_HolidayShow(WORD wYear,WORD wMonth,WORD wDay,QString &Buf)
{
    WORD iJQ_date[2]={0};//节气编号
    WORD iDayOrdial=0;//日期的年内序数
    int ET_index=(wYear-START_YEAR)*5;//数九、梅雨及三伏的年份索引，对应表中的三九第一天（每年6个数值）
    WORD iDayofweek_1st=0;//月首星期
    if (CCalendarCore::GetJieQi(wYear,wMonth,iJQ_date)==1)
    {
        if (iJQ_date[0]==wDay)
        {
            Buf=Jieqi[((wMonth<<1)-1)%24];//该月第一个节气
            return 1;
        }else if (iJQ_date[1]==wDay)
        {
            Buf=Jieqi[(wMonth<<1)%24];//该月第二个节气
            return 1;
        }
    }
    if (CCalendarCore::GetDayOrdinal(wYear,wMonth,wDay,iDayOrdial))
    {
        int i=0;
        WORD wJQ[2]={0};
        GetJieQi(wYear,12,wJQ);//取12月两个节气
        WORD wDongzhi=0;//冬至
        unsigned short wrumei=0,wchumei=0,wchufu=0,wmofu=0;
        short sshujiu=0;
        GetDayOrdinal(wYear,12,wJQ[1],wDongzhi);//转换到年内序数
        GetExtremeSeason(wYear,&sshujiu,&wchufu,&wmofu);
        GetMeiYu(wYear,&wrumei,&wchumei);
        /*if (iDayOrdial==cExtermSeason[wDongzhi)
        {
            Buf=Shujiu[0];//一九（即冬至，不需要判断了，上面冬至已经优先输出了）
            return 1;
        }else */if (iDayOrdial==wDongzhi+9)
        {
            Buf=QStringLiteral("[")+Shujiu[1]+QStringLiteral("]");//二九
            return 1;
        }
        if (iDayOrdial>=(sshujiu+9)&&iDayOrdial<sshujiu+81)
        {
            for (i=0;i<8;i++)
            {
                if (iDayOrdial==sshujiu+(i+1)*9)
                {
                    Buf=QStringLiteral("[")+Shujiu[i+1]+QStringLiteral("]");//三九至九九
                    return 2;
                }
            }
        }else if (iDayOrdial==wrumei)
        {
            Buf=Meiyu[0];//入梅
            return 3;
        }else if (iDayOrdial==wchumei)
        {
            Buf=Meiyu[1];//出梅
            return 3;
        }else if (iDayOrdial==wchufu)
        {
            Buf=Sanfu[0];//初伏
            return 4;
        }else if (iDayOrdial==wchufu+10)
        {
            Buf=Sanfu[1];//中伏
            return 4;
        }else if (iDayOrdial==wmofu)
        {
            Buf=Sanfu[2];//末伏
            return 4;
        }
    }
    if (wMonth==1)
    {
        if (wDay==1)
        {
            Buf=QStringLiteral("元旦");
            return 6;
        }
    }else if (wMonth==2)
    {
        if (wDay==14)
        {
            Buf=QStringLiteral("情人节");
            return 6;
        }
    }else if (wMonth==3)
    {
        switch (wDay)
        {
        case 5:
            if (wYear>=1963)
            {
                Buf=QStringLiteral("学雷锋日");
                return 6;
            }
            break;
        case 8:
            if (wYear>=1900)
            {
                Buf=QStringLiteral("妇女节");
                return 6;
            }
            break;
        case 12:
            if (wYear>=1928)
            {
                Buf=QStringLiteral("植树节");
                return 6;
            }
            break;
        case 15:
            if (wYear>=1983)
            {
                Buf=QStringLiteral("消权日");
                return 6;
            }
            break;
        default:
            break;
        }
    }else if (wMonth==4)
    {
        if (wDay==1)
        {
            Buf=QStringLiteral("愚人节");
            return 6;
        }
    }else if (wMonth==5)
    {
        if (wYear>=1872)
        {
            iDayofweek_1st=CCalendarCore::GetDayOfWeek(wYear,wMonth,1);//取月首星期
            if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==2)//5月第二个周日母亲节
            {
                Buf=QStringLiteral("母亲节");
                return 6;
            }
        }
        switch (wDay)
        {
        case 1:
            if (wYear>=1890)
            {
                Buf=QStringLiteral("劳动节");
                return 6;
            }
            break;
        case 4:
            if (wYear>=1919)
            {
                Buf=QStringLiteral("青年节");
                return 6;
            }
            break;
        case 12:
            if (wYear>=1912)
            {
                Buf=QStringLiteral("护士节");
                return 6;
            }
            break;
        case 31:
            if (wYear>=1989)
            {
                Buf=QStringLiteral("无烟日");
                return 6;
            }
            break;
        default:
            break;
        }
    }else if (wMonth==6)
    {
        if (wYear>=1910)
        {
            iDayofweek_1st=CCalendarCore::GetDayOfWeek(wYear,wMonth,1);//取月首星期
            if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==3)//6月第三个周日父亲节
            {
                Buf=QStringLiteral("父亲节");
                return 6;
            }
        }
        switch (wDay)
        {
        case 1:
            if (wYear>1949)
            {
                Buf=QStringLiteral("儿童节");
                return 6;
            }
            break;
        case 5:
            if (wYear>=1972)
            {
                Buf=QStringLiteral("环境日");
                return 6;
            }
            break;
        case 26:
            if (wYear>=1987)
            {
                Buf=QStringLiteral("禁毒日");
                return 6;
            }
            break;
        default:
            break;
        }
    }else if (wMonth==7)
    {
        switch (wDay)
        {
        case 1:
            if (wYear>=1921)
            {
                Buf=QStringLiteral("中共诞辰");
                return 6;
            }
            break;
        case 7:
            if (wYear>=1937)
            {
                Buf=QStringLiteral("抗战纪念");
                return 6;
            }
            break;
        default:
            break;
        }
    }else if (wMonth==8)
    {
        if (wDay==1)
        {
            if (wYear>=1933)
            {
                Buf=QStringLiteral("建军节");
                return 6;
            }
        }
    }else if (wMonth==9)
    {
        switch (wDay)
        {
        case 3:
            if (wYear>=1945)
            {
                Buf=QStringLiteral("抗战胜利");
                return 6;
            }
            break;
        case 10:
            if (wYear>=1985)
            {
                Buf=QStringLiteral("教师节");
                return 6;
            }
            break;
        default:
            break;
        }
    }else if (wMonth==10)
    {
        if (wDay==1)
        {
            if (wYear>=1949)
            {
                Buf=QStringLiteral("国庆");
                return 6;
            }
        }
    }else if (wMonth==11)
    {
        if (wYear>=1941)
        {
            iDayofweek_1st=CCalendarCore::GetDayOfWeek(wYear,wMonth,1);//取月首星期
            if ((wDay+iDayofweek_1st-1)%7==4&&((wDay+iDayofweek_1st-1+(iDayofweek_1st<=4?7:0))/7)==4)//11月第四个周四感恩节
            {
                Buf=QStringLiteral("感恩节");
                return 6;
            }
        }
        if (wDay==1)
        {
            Buf=QStringLiteral("万圣节");
            return 6;
        }
    }else if (wMonth==12)
    {
        switch (wDay)
        {
        case 10:
            if (wYear>=1948)
            {
                Buf=QStringLiteral("人权日");
                return 6;
            }
            break;
        case 12:
            if (wYear>=1936)
            {
                Buf=QStringLiteral("西安事变");
                return 6;
            }
            break;
        case 24:
            Buf=QStringLiteral("平安夜");
            return 6;
        case 25:
            Buf=QStringLiteral("圣诞节");
            return 6;
        default:
            break;
        }
    }
    return FALSE;
}

//*************************************************************************
// 函数名称： L_HolidayShow
// 完整名称： CCalendarCore::L_HolidayShow
// 功能描述： 农历节日
// 形式参数： WORD wLYear
// 形式参数： WORD wLMonth
// 形式参数： WORD wLDay
// 形式参数： BOOL bLeapMonth
// 形式参数： CString & Buf
// 访问方式： public static
// 返回类型： BYTE
// 函数状态：
//*************************************************************************
BYTE CCalendarCore::L_HolidayShow(WORD wLYear,WORD wLMonth,WORD wLDay,BOOL bLeapMonth,QString &Buf)
{
    WORD LeapMonth=CCalendarCore::LunarGetLeapMonth(wLYear);//取该年农历闰月
    WORD DayofLM=LunarGetDaysofMonth(wLYear,wLMonth,bLeapMonth);//农历月的总天数
    if (bLeapMonth==0)
    {
        if (wLMonth==1)
        {
            if (wLDay==DayofLM)
            {
                Buf=QStringLiteral("正月晦");
                return 6;
            }
            switch (wLDay)
            {
            case 1:
                Buf=QStringLiteral("春节");
                return 6;
            case 15:
                Buf=QStringLiteral("元宵节");
                return 6;
            case 25:
                Buf=QStringLiteral("填仓节");
                return 6;
            default:
                break;
            }
        }else if (wLMonth==2)
        {
            if (wLDay==2)
            {
                Buf=QStringLiteral("春龙节");
                return 6;
            }
        }else if (wLMonth==3)
        {
            if (wLDay==3)
            {
                Buf=QStringLiteral("上巳节");
                return 6;
            }
        }else if (wLMonth==5)
        {
            if (wLDay==5)
            {
                Buf=QStringLiteral("端午节");
                return 6;
            }
        }else if (wLMonth==6)
        {
            if (wLDay==6)
            {
                Buf=QStringLiteral("天贶节");
                return 6;
            }else if (wLDay==24)
            {
                Buf=QStringLiteral("观莲节");
                return 6;
            }
        }else if (wLMonth==7)
        {
            if (wLDay==7)
            {
                Buf=QStringLiteral("七夕");
                return 6;
            }else if (wLDay==15)
            {
                Buf=QStringLiteral("中元节");
                return 6;
            }else if (wLDay==DayofLM)
            {
                Buf=QStringLiteral("地藏节");
                return 6;
            }
        }else if (wLMonth==8)
        {
            if (wLDay==1)
            {
                Buf=QStringLiteral("天医节");
                return 6;
            }else if (wLDay==15)
            {
                Buf=QStringLiteral("中秋节");
                return 6;
            }
        }else if (wLMonth==9)
        {
            if (wLDay==9)
            {
                Buf=QStringLiteral("重阳节");
                return 6;
            }
        }else if (wLMonth==10)
        {
            if (wLDay==1)
            {
                Buf=QStringLiteral("祭祖节");
                return 6;
            }else if (wLDay==15)
            {
                Buf=QStringLiteral("下元节");
                return 6;
            }
        }else if (wLMonth==12)
        {
            if (LeapMonth!=12)
            {
                DayofLM=CCalendarCore::LunarGetDaysofMonth(wLYear,12,0);//非闰十二月
                if (wLDay==8)
                {
                    Buf=QStringLiteral("腊八节");
                    return 6;
                }else if (wLDay==16)
                {
                    Buf=QStringLiteral("尾牙节");
                    return 6;
                }else if (wLDay==23)
                {
                    Buf=QStringLiteral("小年");
                    return 6;
                }else if (wLDay==DayofLM)//农历十二月的最后一天是除夕
                {
                    Buf=QStringLiteral("除夕");
                    return 6;
                }
            }
        }
    }else
    {
        if (bLeapMonth==LeapMonth)
        {
            if (bLeapMonth==12)
            {
                DayofLM=CCalendarCore::LunarGetDaysofMonth(wLYear,12,1);//闰十二月
                if (wLDay==8)
                {
                    Buf=QStringLiteral("腊八节");
                    return 6;
                }else if (wLDay==16)
                {
                    Buf=QStringLiteral("尾牙节");
                    return 6;
                }else if (wLDay==23)
                {
                    Buf=QStringLiteral("小年");
                    return 6;
                }else if (wLDay==DayofLM)//农历十二月的最后一天是除夕
                {
                    Buf=QStringLiteral("除夕");
                    return 6;
                }
            }
        }
    }
    return FALSE;//没有节日等
}
