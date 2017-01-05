#include "qdatecellwidget.h"
#include "ui_qdatecellwidget.h"
#include<QPainter>
#include <QPen>
#include"qtitlewidget.h"
#include"qtool.h"
QDateCellWidget::QDateCellWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDateCellWidget)
{
    ui->setupUi(this);
    InitView();

}

QDateCellWidget::~QDateCellWidget()
{
    delete ui;
}

void QDateCellWidget::setGongLiDay(const QString &strDay)
{
   ui->label_g->setText(strDay);
}

void QDateCellWidget::setNongLiDay(const QString &strDay)
{
   ui->label_n->setText(strDay);
}

void QDateCellWidget::setDays(const QString &strGlDay, const QString &strNlDay)
{
   ui->label_g->setText(strGlDay);
   ui->label_n->setText(strNlDay);
}

void QDateCellWidget::InitView()
{
  // QTool::setDlgNoTitle(this);
    m_index = 0;
}

void QDateCellWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   int m_width = this->width();
   int m_height = this->height();



   QPen penDot(Qt::black);
   penDot.setStyle(Qt::DotLine);

  painter.setPen(penDot);
  painter.drawLine(QPointF(m_width,0),QPointF(m_width-1,m_height-1));
  painter.drawLine(QPointF(m_width-1,m_height-1),QPointF(0,m_height));

}

void QDateCellWidget::SetIndex(const int &index)
{
   m_index = index;
}

