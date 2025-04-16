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

bool Database::setValue(QString username, QString password,int currency, double value,bool transaction)
{
    if(!db.isOpen()) openDB();
    QSqlQuery query;
    QString cmd = "SELECT SavingAmount from `users` WHERE username=:username AND currencyType=:currency;";
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":currency", currency);

    bool ok = query.exec();

    if(ok)
    {
        if(query.first()){

            double amount=query.value(0).toDouble();
            qInfo()<<amount;
            qInfo()<<value;
            if(transaction)
            amount+=value;
            else
            amount-=value;
            qInfo()<<amount;
            QString cmd = "UPDATE `users` SET SavingAmount=:SavingAmount WHERE username=:username AND currencyType=:currency;";
            query.prepare(cmd);
            query.bindValue(":username", username);
            query.bindValue(":currency", currency);
            query.bindValue(":SavingAmount", QString::number(amount));

            bool ok = query.exec();

            if(ok){
                return true;
            }
            else{
                qInfo()<<query.lastError().text();
            }

        }
        else{
            QString cmd = "INSERT INTO `users` (`username`,`password`,`currencyType`,`SavingAmount`)VALUES(:username,:password,:currencyType,:SavingAmount);";
            query.prepare(cmd);
            query.bindValue(":username", username);
            query.bindValue(":password", password);
            query.bindValue(":currencyType", currency);
            query.bindValue(":SavingAmount", value);

            bool ok = query.exec();

            if(ok){
                return true;
            }
            else{
                qInfo()<<query.lastError().text();
            }
        }
    }
    else{
        qInfo()<<query.lastError().text();
    }


    return false;
}

QString Database::getValue(QString username,int currency,QString column)
{
    //if(!db.isOpen()) openDB();
    QString cmd = QString("SELECT %0 FROM `users` WHERE  username=:username AND currencyType=:currency;").arg(column);
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":currency", currency);


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



