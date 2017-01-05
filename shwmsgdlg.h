#ifndef SHWMSGDLG_H
#define SHWMSGDLG_H

#include <QDialog>
#include"qtitlewidget.h"

namespace Ui {
class ShwMsgDlg;
}

class ShwMsgDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ShwMsgDlg(QWidget *parent = 0);
    ~ShwMsgDlg();
    void setShowText(QString strMsg);
private:
    Ui::ShwMsgDlg *ui;
private:
    void InitView();
    QTitleWidget *titleWidget;

};

#endif // SHWMSGDLG_H
