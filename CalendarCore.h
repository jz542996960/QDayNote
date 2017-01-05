#ifndef CALENDAR_CORE
#define CALENDAR_CORE
#include<QString>
#include<windows.h>

//typedef bool BOOL;
//typedef int  WORD;


static QString Xinqi[7]={QStringLiteral("星期日"),QStringLiteral("星期一"),QStringLiteral("星期二"),QStringLiteral("星期三"),QStringLiteral("星期四"),QStringLiteral("星期五"),QStringLiteral("星期六")};
static QString rName[30]={QStringLiteral("初一"),QStringLiteral("初二"),QStringLiteral("初三"),QStringLiteral("初四"),QStringLiteral("初五"),QStringLiteral("初六"),QStringLiteral("初七"),QStringLiteral("初八"),QStringLiteral("初九"),QStringLiteral("初十"),QStringLiteral("十一"),QStringLiteral("十二"),QStringLiteral("十三"),QStringLiteral("十四"),QStringLiteral("十五"),QStringLiteral("十六"),QStringLiteral("十七"),QStringLiteral("十八"),QStringLiteral("十九"),QStringLiteral("二十"),QStringLiteral("廿一"),QStringLiteral("廿二"),QStringLiteral("廿三"),QStringLiteral("廿四"),QStringLiteral("廿五"),QStringLiteral("廿六"),QStringLiteral("廿七"),QStringLiteral("廿八"),QStringLiteral("廿九"),QStringLiteral("三十")};
static QString yName[12]={QStringLiteral("正月"),QStringLiteral("二月"),QStringLiteral("三月"),QStringLiteral("四月"),QStringLiteral("五月"),QStringLiteral("六月"),QStringLiteral("七月"),QStringLiteral("八月"),QStringLiteral("九月"),QStringLiteral("十月"),QStringLiteral("十一月"),QStringLiteral("十二月")};
static QString Tiangan[10]={QStringLiteral("甲"),QStringLiteral("乙"),QStringLiteral("丙"),QStringLiteral("丁"),QStringLiteral("戊"),QStringLiteral("己"),QStringLiteral("庚"),QStringLiteral("辛"),QStringLiteral("壬"),QStringLiteral("癸")};
static QString Dizhi[12]={QStringLiteral("子"),QStringLiteral("丑"),QStringLiteral("寅"),QStringLiteral("卯"),QStringLiteral("辰"),QStringLiteral("巳"),QStringLiteral("午"),QStringLiteral("未"),QStringLiteral("申"),QStringLiteral("酉"),QStringLiteral("戌"),QStringLiteral("亥")};
static QString Shengxiao[12]={QStringLiteral("鼠"),QStringLiteral("牛"),QStringLiteral("虎"),QStringLiteral("兔"),QStringLiteral("龙"),QStringLiteral("蛇"),QStringLiteral("马"),QStringLiteral("羊"),QStringLiteral("猴"),QStringLiteral("鸡"),QStringLiteral("狗"),QStringLiteral("猪")};
static QString Xinzuo[12]={QStringLiteral("摩羯座"),QStringLiteral("水瓶座"),QStringLiteral("双鱼座"),QStringLiteral("白羊座"),QStringLiteral("金牛座"),QStringLiteral("双子座"),QStringLiteral("巨蟹座"),QStringLiteral("狮子座"),QStringLiteral("处女座"),QStringLiteral("天秤座"),QStringLiteral("天蝎座"),QStringLiteral("射手座")};
static QString Jieqi[24]={QStringLiteral("冬至"),QStringLiteral("小寒"),QStringLiteral("大寒"),QStringLiteral("立春"),QStringLiteral("雨水"),QStringLiteral("惊蛰"),QStringLiteral("春分"),QStringLiteral("清明"),QStringLiteral("谷雨"),QStringLiteral("立夏"),QStringLiteral("小满"),QStringLiteral("芒种"),QStringLiteral("夏至"),QStringLiteral("小暑"),QStringLiteral("大暑"),QStringLiteral("立秋"),QStringLiteral("处暑"),QStringLiteral("白露"),QStringLiteral("秋分"),QStringLiteral("寒露"),QStringLiteral("霜降"),QStringLiteral("立冬"),QStringLiteral("小雪"),QStringLiteral("大雪")};
static QString Shujiu[9]={QStringLiteral("一九"),QStringLiteral("二九"),QStringLiteral("三九"),QStringLiteral("四九"),QStringLiteral("五九"),QStringLiteral("六九"),QStringLiteral("七九"),QStringLiteral("八九"),QStringLiteral("九九")};
static QString Meiyu[2]={QStringLiteral("入梅"),QStringLiteral("出梅")};
static QString Sanfu[3]={QStringLiteral("初伏"),QStringLiteral("中伏"),QStringLiteral("末伏")};
static QString Month[12]={QStringLiteral("January"),QStringLiteral("February"),QStringLiteral("March"),QStringLiteral("April"),QStringLiteral("May"),QStringLiteral("June"),QStringLiteral("July"),QStringLiteral("August"),QStringLiteral("September"),QStringLiteral("October"),QStringLiteral("November"),QStringLiteral("December")};

class CCalendarCore
{
public:
    CCalendarCore(void);
    ~CCalendarCore(void);
public:
    //判断闰年，参数：年份，闰年，返回值：FALSE-失败，TRUE-成功
    static BOOL IsLeapYear(WORD wYear,BOOL &bLeapYear);
    //计算日期在年内的序数，参数：年，月，日，年内序数，返回值：FALSE-失败，TRUE-成功
    static BOOL GetDayOrdinal(WORD wYear, WORD wMonth, WORD wDay,WORD &wOrdinal);
    //从年内序数计算月、日，参数：年，年内序数，月，日，返回值：FALSE-失败，TRUE-成功
    static BOOL GetDateFromOrdinal(WORD wYear, WORD wOrdinal, WORD &wMonth, WORD &wDay);
    //获取农历新年的公历年内序数，参数：农历年，返回值：农历新年的公历年内序数
    static short LunarGetNewYearOrdinal(WORD wLunarYear);
    //获取农历月的天数，参数：农历年，农历月，是否为闰月，返回值：该农历月的天数，为0代表参数无效
    static WORD LunarGetDaysofMonth(WORD wLunarYear,WORD wLunarMonth,BOOL bLeapMonth);
    //获取农历某一年的闰月情况，参数：农历年，返回值，该年的闰月月份，0表示无闰月
    static WORD LunarGetLeapMonth(WORD wLunarYear);
    //公历转农历，参数：公历年、月、日，农历年、月、日，是否为闰月，返回值：FALSE-失败，TRUE-成功
    static BOOL GetLunar(WORD wYear,WORD wMonth,WORD wDay,WORD &wLunarYear,WORD &wLunarMonth,WORD &wLunarDay,BOOL &bLeapMonth);
    //农历转公历，参数：家历年、月、日，是否为闰月，公历年、月、日，返回值：FALSE-失败，TRUE-成功
    static BOOL GetGregorian(WORD wLunarYear,WORD wLunarMonth,WORD wLunarDay,BOOL bLeapMonth,WORD &wYear,WORD &wMonth,WORD &wDay);
    //得到指定年份的节气信息，首个是小寒
    static BOOL GetJieQi(WORD wYear,WORD wMonth,WORD wJieQi[2]);
    //计算星期，返回-1表示输入的年月日不正确或者超出年份范围
    static short GetDayOfWeek(WORD wYear,WORD wMonth,WORD wDay);
    //计算某个月的天数，返回天数，如果返回0表示年或月有误
    static WORD GetDaysOfMonth(WORD wYear,WORD wMonth);
    //获取数九、三伏
    static BOOL GetExtremeSeason(WORD wYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu);
    //获取入梅、出梅
    static BOOL GetMeiYu(WORD wYear,unsigned short* wRuMeiOrd,unsigned short* wChuMeiOrd);
    //获取某天的节日、节气
    static BYTE G_HolidayShow(WORD wYear,WORD wMonth,WORD wDay,QString &Buf);
    //获取某天的农历节日
    static BYTE L_HolidayShow(WORD wLYear,WORD wLMonth,WORD wLDay,BOOL bLeapMonth,QString &Buf);
private:
    //检验年、月、日的合法性，参数：年，月，日，返回值：FALSE-失败，TRUE-成功
    static BOOL DateCheck(WORD wYear,WORD wMonth,WORD wDay);
    //展开大小月数据表（某一年的），参数：农历年，从上一年十一月开始到当前年份（闰）十二月的每月天数，返回值：FALSE-失败，TRUE-成功
    static BOOL LunarExpandDX(WORD wLunarYear,WORD wDayOfMonth[15]);
    //获取农历月份信息
    static BOOL GetMonthInfo(WORD wYear,UINT& uData);
};
#endif
