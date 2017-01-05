#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T18:13:56
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDayNote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qjzsq.cpp \
    qlogindlg.cpp \
    qtitlewidget.cpp \
    iconhelper.cpp \
    shwmsgdlg.cpp \
    qtool.cpp \
    qdatecellwidget.cpp \
    qcalendardlg.cpp \
    CalendarCore.cpp

HEADERS  += mainwindow.h \
    qjzsq.h \
    qlogindlg.h \
    qtitlewidget.h \
    iconhelper.h \
    shwmsgdlg.h \
    qtool.h \
    qdatecellwidget.h \
    qcalendardlg.h \
    CalendarCore.h \
    LunarData.h

FORMS    += mainwindow.ui \
    qlogindlg.ui \
    qtitlewidget.ui \
    shwmsgdlg.ui \
    qdatecellwidget.ui \
    qcalendardlg.ui

RESOURCES += \
    other/rc.qrc
