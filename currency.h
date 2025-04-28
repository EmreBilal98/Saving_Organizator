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

enum XAUtype{
    UNKNOWN=-1,
    GrXAU=0,
    COUNT
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
    static QString XAUToString(XAUtype XAU);
    static XAUtype stringToXAU(const QString &XAUStr);
    static QStringList XAUToStringList(QList<int> XAUs);
    //altin
    void getXAUData();
    //borsa
    void getExchangesData();
signals:
    //void getValue(double value);
    void getValue(QMap<QString,double> currencies);
    void getBuyXAUPrice(double XAUbuyPrice);//altin alis fiyati
    void getSellXAUPrice(double XAUSellPrice);//altin satis fiyati
    void getStocks(QMap<QString,double> exchanges);//bist100  fiyatları

private slots:
    void currenyReply(QNetworkReply *reply);
    //altin
    void XAUReply(QNetworkReply* reply);
    //borsa
    void ExchangeReply(QNetworkReply* reply);
private:

    QNetworkAccessManager manager,managerGold,managerExchange;
    double m_value;
    QMap<QString,double> m_currencies;


};

#endif // CURRENCY_H
