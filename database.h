#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>
#include  <QList>
#include <QMessageBox>

#define ADD true
#define SUB false


class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    bool openDB();

public slots:
    bool createUser(QString username,QString password,int &errorCode);
    bool searchValue(QString column,QString value);
    bool setValue(QString username,QString password,int currency,double value,bool transaction,double cost=0,int savingType=1,QString StockName=nullptr);
    QString getValue(QString username,int currency,int savingType,QString column);
    QList<int> getCurrencies(QString username);
    QList<QString> getList(QString username,int SavingType,QString column);
    QString getExchangeValue(QString username,QString StockName,int savingType,QString column);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
