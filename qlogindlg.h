#ifndef QLOGINDLG_H
#define QLOGINDLG_H

#include <QDialog>
#include "qtitlewidget.h"
#include<QMouseEvent>
namespace Ui {
class QLoginDlg;
}

class QLoginDlg : public QDialog
{
    Q_OBJECT
public:
     QLoginDlg(QWidget *parent = 0);
    ~QLoginDlg();
private:
    Ui::QLoginDlg *ui;
private:
    void InitView();
    QTitleWidget *titleWidget;//标题栏
private:
    QPoint dragVector;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void OnLoginClick();
};

#endif // QLOGINDLG_H
