#ifndef QTITLEWIDGET_H
#define QTITLEWIDGET_H

#include <QWidget>

namespace Ui {
class QTitleWidget;
}

class QTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QTitleWidget(QWidget *parent = 0);
    ~QTitleWidget();
public:
    void SetTitle(QString str);
    void SetShowStyle(int flag);
private:
    Ui::QTitleWidget *ui;
private:
    void InitView();
signals://信号 不用实现
    void closesSignals();//关闭信号
    void minSignals();//最小化信号
private slots:
    void OnBtnMenuClose();
    void OnMinMenuMin();

};

#endif // QTITLEWIDGET_H
