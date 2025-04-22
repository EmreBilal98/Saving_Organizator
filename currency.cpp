#include "currency.h"

Currency::Currency(QObject *parent)
    : QObject{parent}
{
    connect(&manager, &QNetworkAccessManager::finished, this, &Currency::currenyReply);
}

void Currency::currencyRequest(const QString &base)
{
    QString url = QString("https://api.frankfurter.app/latest?from=%0").arg(base);
    qInfo()<<url;
    QNetworkRequest request((QUrl(url)));
    manager.get(request);
}

void Currency::currenyReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);

        if (error.error != QJsonParseError::NoError) {
            qWarning() << "JSON parse hatası:" << error.errorString();
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("rates")) {
            qWarning() << "JSON not include 'quotes";
            return;
        }

        QJsonObject rates = jsonObj["rates"].toObject();
        for (auto it = rates.begin(); it != rates.end(); ++it) {
            QString key = it.key();
            double value = it.value().toDouble();
            m_currencies.insert(key, value);
        }
        if(!m_currencies.isEmpty()){
            emit getValue(m_currencies);
        }
        else{
            qWarning() << "'TRY' base currencies not found!";
        }

    } else {
        qWarning() << "Hata:" << reply->errorString();
    }
    reply->deleteLater();
}

QString Currency::currencyToString(CurrencyType currency) {
    switch (currency) {
    case CurrencyType::AUD: return "AUD";
    case CurrencyType::BGN: return "BGN";
    case CurrencyType::BRL: return "BRL";
    case CurrencyType::CAD: return "CAD";
    case CurrencyType::CHF: return "CHF";
    case CurrencyType::CNY: return "CNY";
    case CurrencyType::CZK: return "CZK";
    case CurrencyType::DKK: return "DKK";
    case CurrencyType::EUR: return "EUR";
    case CurrencyType::GBP: return "GBP";
    case CurrencyType::HKD: return "HKD";
    case CurrencyType::HUF: return "HUF";
    case CurrencyType::IDR: return "IDR";
    case CurrencyType::ILS: return "ILS";
    case CurrencyType::INR: return "INR";
    case CurrencyType::ISK: return "ISK";
    case CurrencyType::JPY: return "JPY";
    case CurrencyType::KRW: return "KRW";
    case CurrencyType::MXN: return "MXN";
    case CurrencyType::MYR: return "MYR";
    case CurrencyType::NOK: return "NOK";
    case CurrencyType::NZD: return "NZD";
    case CurrencyType::PHP: return "PHP";
    case CurrencyType::PLN: return "PLN";
    case CurrencyType::RON: return "RON";
    case CurrencyType::SEK: return "SEK";
    case CurrencyType::SGD: return "SGD";
    case CurrencyType::THB: return "THB";
    case CurrencyType::TRY: return "TRY";
    case CurrencyType::USD: return "USD";
    case CurrencyType::ZAR: return "ZAR";
    default: return "UNKNOWN";
    }
}

CurrencyType Currency::stringToCurrency(const QString &currencyStr) {
    static const QMap<QString, CurrencyType> currencyMap = {
        {"AUD", CurrencyType::AUD},
        {"BGN", CurrencyType::BGN},
        {"BRL", CurrencyType::BRL},
        {"CAD", CurrencyType::CAD},
        {"CHF", CurrencyType::CHF},
        {"CNY", CurrencyType::CNY},
        {"CZK", CurrencyType::CZK},
        {"DKK", CurrencyType::DKK},
        {"EUR", CurrencyType::EUR},
        {"GBP", CurrencyType::GBP},
        {"HKD", CurrencyType::HKD},
        {"HUF", CurrencyType::HUF},
        {"IDR", CurrencyType::IDR},
        {"ILS", CurrencyType::ILS},
        {"INR", CurrencyType::INR},
        {"ISK", CurrencyType::ISK},
        {"JPY", CurrencyType::JPY},
        {"KRW", CurrencyType::KRW},
        {"MXN", CurrencyType::MXN},
        {"MYR", CurrencyType::MYR},
        {"NOK", CurrencyType::NOK},
        {"NZD", CurrencyType::NZD},
        {"PHP", CurrencyType::PHP},
        {"PLN", CurrencyType::PLN},
        {"RON", CurrencyType::RON},
        {"SEK", CurrencyType::SEK},
        {"SGD", CurrencyType::SGD},
        {"THB", CurrencyType::THB},
        {"TRY", CurrencyType::TRY},
        {"USD", CurrencyType::USD},
        {"ZAR", CurrencyType::ZAR}
    };

    return currencyMap.value(currencyStr.toUpper(), CurrencyType::UNKNOWN);
}

QStringList Currency::currencyToStringList(QList<int> currencies) {
    QStringList result;
    for (int curInt : currencies) {
        CurrencyType currency = static_cast<CurrencyType>(curInt);
        result.append(currencyToString(currency));
    }
    return result;
}


