#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>
#include  <QList>
#include <QMessageBox>
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    bool openDB();

public slots:
    bool createUser(QString username,QString password,int &errorCode);
    bool searchValue(QString column,QString value);
    bool setValue(QString username,QString password,int currency,double value);
    QString getValue(QString username,int currency,QString column);
    QList<int> getCurrencies(QString username);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
