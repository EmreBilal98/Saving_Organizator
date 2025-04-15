#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>

enum class CurrencyType {
    UNKNOWN=-1,
    AUD=0,
    BGN,
    BRL,
    CAD,
    CHF,
    CNY,
    CZK,
    DKK,
    EUR,
    GBP,
    HKD,
    HUF,
    IDR,
    ILS,
    INR,
    ISK,
    JPY,
    KRW,
    MXN,
    MYR,
    NOK,
    NZD,
    PHP,
    PLN,
    RON,
    SEK,
    SGD,
    THB,
    TRY,
    USD,
    ZAR,
    COUNT,
};

class Currency : public QObject
{
    Q_OBJECT
public:
    explicit Currency(QObject *parent = nullptr);
    void currencyRequest(const QString &base);
    static QString currencyToString(CurrencyType currency);
    static CurrencyType stringToCurrency(const QString &currencyStr);
    static QStringList currencyToStringList(QList<int> currencies);
signals:
    //void getValue(double value);
    void getValue(QMap<QString,double> currencies);

private slots:
    void currenyReply(QNetworkReply *reply);
private:

    QNetworkAccessManager manager;
    double m_value;
    QMap<QString,double> m_currencies;


};

#endif // CURRENCY_H
