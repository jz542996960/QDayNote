#ifndef QJZSQ_H
#define QJZSQ_H

#include <QObject>
#include<QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QVariantList>

class QJZSq : public QObject
{
public:
    static QJZSq* getInstance();
    bool CreateTable(QString str);
    bool Login(QString strUserName,QString strPwd);
private:
    QJZSq();
    QJZSq(const QJZSq& jzsq);
    ~QJZSq();
private:
    static QJZSq*  m_JzSq;
    QSqlDatabase database;
    bool Init();
};

#endif // QJZSQ_H
