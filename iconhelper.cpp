#include "iconhelper.h"
#include "iconhelper.h"


IconHelper *IconHelper::_instance = 0;

IconHelper::IconHelper(QObject *) :QObject(qApp)
{
    QString strPath;// = QCoreApplication::applicationDirPath();
    strPath += ":/image/fontawesome-webfont.ttf";
	int fontId = QFontDatabase::addApplicationFont(strPath);
	QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
	iconFont = QFont(fontName);
}

void IconHelper::SetIcon(QLabel *lab, QChar c)
{
	iconFont.setPointSize(11);
	lab->setFont(iconFont);
	lab->setText(c);
}

void IconHelper::SetIcon(QPushButton *btn, QChar c)
{
	iconFont.setPointSize(11);
	btn->setFont(iconFont);
	btn->setText(c);
}
