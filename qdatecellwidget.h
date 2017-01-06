#ifndef QDATECELLWIDGET_H
#define QDATECELLWIDGET_H

#include <QWidget>
#include<QPaintEvent>

namespace Ui {
class QDateCellWidget;
}

class QDateCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QDateCellWidget(QWidget *parent = 0);
    ~QDateCellWidget();
public:
    void setGongLiDay(const QString& strDay);
    void setNongLiDay(const QString& strDay);

    void setNongLiDay(const QColor& color,const QString& strDay);

    void setDays(const QString& strGlDay,const QString & strNlDay);
    void SetIndex(const int& index);
private:
    Ui::QDateCellWidget *ui;
    void InitView();
    int m_index;
protected:
   void  paintEvent(QPaintEvent *event);

};

#endif // QDATECELLWIDGET_H
