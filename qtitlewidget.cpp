#include "qtitlewidget.h"
#include "ui_qtitlewidget.h"
#include "iconhelper.h"
#include "qtool.h"

QTitleWidget::QTitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTitleWidget)
{
    ui->setupUi(this);
    InitView();
}

QTitleWidget::~QTitleWidget()
{
    delete ui;
}
 
void QTitleWidget::InitView()
{
    //隐藏标题栏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    ui->lab_Title->installEventFilter(this);
    ui->widget_title->setAttribute(Qt::WA_TranslucentBackground);
    /*设置图标*/
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d));
    IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096));
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068));
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015));
    //信号
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(OnBtnMenuClose()));
    connect(ui->btnMenu_Min, SIGNAL(clicked()), this, SLOT(OnMinMenuMin()));

}

void QTitleWidget::OnBtnMenuClose()
{
    emit closesSignals();
}

void QTitleWidget::OnMinMenuMin()
{
    emit minSignals();
}


void QTitleWidget::SetShowStyle(int flag)
{
    ui->btnMenu_Close->setVisible(false);
    ui->btnMenu_Max->setVisible(false);
    ui->btnMenu_Min->setVisible(false);
    if (flag & STYLE_CLOSE)
    {
        ui->btnMenu_Close->setVisible(true);
    }
    if(flag & STYLE_MAX)
    {
        ui->btnMenu_Max->setVisible(true);
    }
    if(flag& STYLE_MIN)
    {
        ui->btnMenu_Min->setVisible(true);
    }


}

void QTitleWidget::SetTitle(QString str)
{
    ui->lab_Title->setText(str);
}
