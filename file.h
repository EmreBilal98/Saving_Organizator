#ifndef FILE_H
#define FILE_H
#include <QFile>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QColor>
#include "currency.h"


class File:public QFile
{
public:
    File(const QString& username);
    bool addLineToFile(QString currencyType,double currencyAmount,QString comment,double currencyBalance,bool transaction);


};

#endif // FILE_H
