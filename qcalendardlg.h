#ifndef QCALENDARDLG_H
#define QCALENDARDLG_H

#include <QDialog>
#include"qtool.h"
#include"qdatecellwidget.h"
#include"vector"
namespace Ui {
class QCalendarDlg;
}

class QCalendarDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCalendarDlg(QWidget *parent = 0);
    ~QCalendarDlg();
private:
    Ui::QCalendarDlg *ui;
    void InitView();
    std::vector<QDateCellWidget*> dateWidgetVec;
    void InitWidgetDate();
private slots:
    void OnMonthIndexChange(int index);
    void OnYearIndexChange(int index);
};

#endif // QCALENDARDLG_H
