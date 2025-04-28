#include "database.h"

Database::Database(QObject *parent)
    : QObject{parent}
{}


bool Database::openDB()
{
    qInfo() << "Opening Database";
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("saving_organize");
    db.setUserName("qt6ca"); //Change the username
    db.setPassword("479-annem"); //Change the password



    bool ok =false;

    if(!db.isOpen())
       ok=db.open();
    else
        return true;

    if(ok)
    {
        qInfo() << "Opened database connection!";
        return true;
    }

    qInfo() << "Failed to open connection!";
    qInfo() << db.lastError().text();

    return false;
}

bool Database::createUser(QString username, QString password,int &errorCode)
{
    if(!db.isOpen()) openDB();
    QSqlQuery query;
    QString cmd = "SELECT * from `users` WHERE username=:username";
    query.prepare(cmd);
    query.bindValue(":username", username);


    bool ok = query.exec();


    if(ok)
    {
        if(!query.next()){

            qInfo() << "Inserting row";
            QSqlQuery query;
            QString cmd = "INSERT INTO `users` (`username`,`password`)VALUES(:username,:password);";
            query.prepare(cmd);
            query.bindValue(":username", username);
            query.bindValue(":password", password);

            bool ok = query.exec();

            if(ok)
            {
                qInfo() << "Inserted " << query.lastInsertId().toInt();
                return true;
            }
            else{
                qInfo()<<query.lastError().text();
            }
        }
        else{
            errorCode=1;
        }
    }
    else{
        qInfo()<<query.lastError().text();
    }


    return false;
 }

bool Database::searchValue(QString column, QString value)
{
    if(!db.isOpen()) openDB();
    QSqlQuery query;
    QString cmd=QString("SELECT %0 FROM users;").arg(column);
    query.prepare(cmd);

    bool ok = query.exec(cmd);

    if(ok)
    {
        qInfo()<<query.size();
        while(query.next()){
            qInfo()<<column<<":"<<query.value(0).toString();
            if(value.compare(query.value(0).toString(),Qt::CaseSensitive)==0){
                return true;
            }
        }
    }
    else{
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }


    return false;

}

bool Database::setValue(QString username, QString password,int currency, double value,bool transaction,double cost,int savingType,QString StockName)
{
    if(!db.isOpen()) openDB();


    QSqlQuery query;
    if(savingType!=3)
    {
    QString cmd = "SELECT SavingAmount,cost from `users` WHERE username=:username AND currencyType=:currency AND SavingType=:SavingType;";
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":currency", currency);
    query.bindValue(":SavingType", QString::number(savingType));
    }
    else{
        QString cmd = "SELECT SavingAmount,cost from `users` WHERE username=:username AND StockName=:StockName AND SavingType=:SavingType;";
        query.prepare(cmd);
        query.bindValue(":username", username);
        query.bindValue(":StockName", StockName);
        query.bindValue(":SavingType", QString::number(savingType));
    }

    bool ok = query.exec();

    if(ok)
    {
        if(query.first()){//  eğerki bu curencyType da ve bu  usernamede bi kayıt varsa o satıra ekleyecek ve bu  if e girecek
            qInfo()<<"gelmesi gereken";
            double amount=query.value(0).toDouble();
            double totalCost=query.value(1).toDouble();
            qInfo()<<amount;
            qInfo()<<totalCost;
            qInfo()<<value;
            if(transaction){
            amount+=value;
            totalCost+=cost;
            }
            else{
            totalCost=totalCost-(value*(totalCost/amount));
            amount-=value;
            }
            qInfo()<<amount;
            qInfo()<<totalCost;
            if(savingType!=3)
            {
                QString cmd = "UPDATE `users` SET SavingAmount=:SavingAmount,cost=:cost WHERE username=:username AND currencyType=:currency AND SavingType=:SavingType;";
                query.prepare(cmd);
                query.bindValue(":username", username);
                query.bindValue(":currency", currency);
                query.bindValue(":SavingAmount", QString::number(amount));
                query.bindValue(":cost", QString::number(totalCost));
                query.bindValue(":SavingType", QString::number(savingType));

                bool ok = query.exec();

                if(ok){
                    qInfo()<<"queery true";
                    return true;
                }
                else{
                    qInfo()<<"queery false";
                    qInfo()<<query.lastError().text();
                }
            }
            else{
                QString cmd = "UPDATE `users` SET SavingAmount=:SavingAmount,cost=:cost WHERE username=:username AND StockName=:StockName AND SavingType=:SavingType;";
                query.prepare(cmd);
                query.bindValue(":username", username);
                query.bindValue(":SavingAmount", QString::number(amount));
                query.bindValue(":cost", QString::number(totalCost));
                query.bindValue(":SavingType", QString::number(savingType));
                query.bindValue(":StockName", StockName);

                bool ok = query.exec();

                if(ok){
                    qInfo()<<"queery true";
                    return true;
                }
                else{
                    qInfo()<<"query false";
                    qInfo()<<query.lastError().text();
                }
            }

        }
        else{//  eğerki bu curencyType da ve bu  usernamede bi kayıt yoksa databaseye yeni bir satır ekleyecek ve bu  else  e girecek
            if(savingType!=3){
                QString cmd = "INSERT INTO `users` (`username`,`password`,`currencyType`,`SavingAmount`,`cost`,`SavingType`)VALUES(:username,:password,:currencyType,:SavingAmount,:cost,:SavingType);";
                query.prepare(cmd);
                query.bindValue(":username", username);
                query.bindValue(":password", password);
                query.bindValue(":currencyType", currency);
                query.bindValue(":SavingAmount", value);
                query.bindValue(":cost", QString::number(cost));
                query.bindValue(":SavingType", QString::number(savingType));
                qInfo()<<"gelmesi gerekmeyen";
                bool ok = query.exec();

                if(ok){
                    return true;
                }
                else{
                    qInfo()<<query.lastError().text();
                }
            }
            else{
                QString cmd = "INSERT INTO `users` (`username`,`password`,`currencyType`,`SavingAmount`,`cost`,`SavingType`,`StockName`)VALUES(:username,:password,:currencyType,:SavingAmount,:cost,:SavingType,:StockName);";
                query.prepare(cmd);
                query.bindValue(":username", username);
                query.bindValue(":password", password);
                query.bindValue(":currencyType", currency);
                query.bindValue(":SavingAmount", value);
                query.bindValue(":cost", QString::number(cost));
                query.bindValue(":SavingType", QString::number(savingType));
                query.bindValue(":StockName", StockName);
                qInfo()<<"gelmesi gerekmeyen";
                bool ok = query.exec();

                if(ok){
                    return true;
                }
                else{
                    qInfo()<<query.lastError().text();
                }
            }
        }
    }
    else{
        qInfo()<<query.lastError().text();
    }


    return false;
}

QString Database::getValue(QString username,int currency,int savingType,QString column)
{
    if(!db.isOpen()) openDB();
    QString cmd = QString("SELECT %0 FROM `users` WHERE  username=:username AND currencyType=:currency AND SavingType=:SavingType;").arg(column);
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":currency", currency);
    query.bindValue(":SavingType",savingType);


    bool ok = query.exec();

    if(ok){
        if(query.next())
        return query.value(0).toString();
        else{
            return QString();
        }
    }
    else{
        qInfo()<<query.lastError().text();
    }

    return QString();
}

QList<int> Database::getCurrencies(QString username)
{
    if(!db.isOpen()) openDB();
    QString cmd = "SELECT currencyType FROM `users` WHERE  username=:username;";
    QSqlQuery query;
    QList<int> currencies;
    query.prepare(cmd);
    query.bindValue(":username", username);


    bool ok = query.exec();

    if(ok){
        while(query.next()){
            currencies<<query.value(0).toInt();
        }
    }
    else{
        qInfo()<<query.lastError().text();
    }

    return currencies;
}

QList<QString> Database::getList(QString username,int SavingType, QString column)
{
    if(!db.isOpen()) openDB();
    QString cmd = QString("SELECT %0 FROM `users` WHERE  username=:username  AND SavingType=:SavingType;").arg(column);
    QSqlQuery query;
    QList<QString> list;
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":SavingType", SavingType);


    bool ok = query.exec();

    if(ok){
        while(query.next()){
            list<<query.value(0).toString();
        }
    }
    else{
        qInfo()<<query.lastError().text();
    }

    return list;
}

QString Database::getExchangeValue(QString username, QString StockName, int savingType, QString column)
{
    if(!db.isOpen()) openDB();
    QString cmd = QString("SELECT %0 FROM `users` WHERE  username=:username AND StockName=:StockName AND SavingType=:SavingType;").arg(column);
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":StockName", StockName);
    query.bindValue(":SavingType",savingType);


    bool ok = query.exec();

    if(ok){
        if(query.next())
            return query.value(0).toString();
        else{
            return QString();
        }
    }
    else{
        qInfo()<<query.lastError().text();
    }

    return QString();
}





