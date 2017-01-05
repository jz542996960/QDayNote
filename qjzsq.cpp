#include "qjzsq.h"

QJZSq* QJZSq::m_JzSq = nullptr;

QJZSq::QJZSq()
{

}

QJZSq::QJZSq(const QJZSq& JQ)
{

}

QJZSq::~QJZSq()
{

}

QJZSq* QJZSq::getInstance()
{
  if(m_JzSq==nullptr)
  {
      m_JzSq = new QJZSq;
      if(!m_JzSq->Init())
      {
          delete m_JzSq;
          m_JzSq = NULL;
      }
  }
  return m_JzSq;
}

bool QJZSq::Init()
{
  database =  QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName("DayNote.db");
  if(!database.open())
  {
    return false;
  }
  return true;
}

bool QJZSq::CreateTable(QString str)
{
   QSqlQuery sql_query;
   sql_query.prepare(str);
   if(!sql_query.exec())
   {
       qDebug()<<QObject::tr("Table Create failed");
       qDebug()<<sql_query.lastError();
       return false;
   }
   return true;
}

bool QJZSq::Login(QString strUserName, QString strPwd)
{
   QString str;
  // str = "select * from users where USERNAME=? and PASSWORD=?";
   str = QString("select * from users where USERNAME= \"%1\" and PASSWORD=\"%2\" ").arg(strUserName).arg(strPwd);
   QSqlQuery sql_query;
   sql_query.prepare(str);
 //  sql_query.addBindValue(strUserName);
  // sql_query.addBindValue(strPwd);
   if(!sql_query.exec())
   {
       qDebug()<<QObject::tr("login failed");
       qDebug()<<sql_query.lastError();
       return false;
   }
   while(sql_query.next())
   {
     return true;
   }
   return false;
}
