#include "mainwindow.h"
#include "qlogindlg.h"
#include <QApplication>
#include<QFile>
#include"qdatecellwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 1
    QString strFile =":/qss/darkgray.css";
    QFile file(strFile);
    if (file.open(QFile::ReadOnly))
    {
       QString qss = QLatin1String(file.readAll());
       qApp->setStyleSheet(qss);
       QString PaletteColor = qss.mid(20, 7);
       qApp->setPalette(QPalette(QColor(PaletteColor)));
       file.close();
    }
#endif
    //登录
   QLoginDlg m_dlg;
   m_dlg.show();

    return a.exec();
}
