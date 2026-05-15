#include "currency.h"

Currency::Currency(QObject *parent)
    : QObject{parent}
{
    connect(&manager, &QNetworkAccessManager::finished, this, &Currency::currenyReply);
    connect(&managerGold, &QNetworkAccessManager::finished, this, &Currency::XAUReply);
    connect(&managerExchange, &QNetworkAccessManager::finished, this, &Currency::ExchangeReply);
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

void Currency::XAUReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    // Sayfa içeriğini al
    QString pageContent = reply->readAll();

    QRegularExpression reSatis("<li class=\"midrow satis\"[^>]*>([0-9.]+)</li>");
    QRegularExpression reAlis("<li class=\"midrow alis\"[^>]*>([0-9.]+)</li>");
    QRegularExpressionMatch matchSatis = reSatis.match(pageContent);
    QRegularExpressionMatch matchAlis = reAlis.match(pageContent);

    if (matchSatis.hasMatch()) {
        QString satisFiyati = matchSatis.captured(1);
        qDebug() << "Gram Altın Satış Fiyatı:" << satisFiyati;
        emit getSellXAUPrice(satisFiyati.toDouble());
    } else {
        qDebug() << "Fiyat bulunamadı.";
    }

    if (matchAlis.hasMatch()) {
        QString alisFiyati = matchAlis.captured(1);
        qDebug() << "Gram Altın Satış Fiyatı:" << alisFiyati;
        emit getBuyXAUPrice(alisFiyati.toDouble());
    } else {
        qDebug() << "Fiyat bulunamadı.";
    }
}

void Currency::ExchangeReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    QString pageContent = QString::fromUtf8(reply->readAll());
    QMap<QString, double> exchanges;

    // --- YENİ TABLO YAPISI İÇİN (180 KB'lık versiyon) ---
    // Bu RegEx <tr data-symbol-id="AEFES"> yapısını yakalar
    QRegularExpression tableRe("<tr[^>]*data-symbol-id=\"([^\"]+)\"");
    QRegularExpressionMatchIterator iTable = tableRe.globalMatch(pageContent);

    while (iTable.hasNext()) {
        QRegularExpressionMatch match = iTable.next();
        QString symbol = match.captured(1);

        // Bu sembolün satırı içindeki fiyatı bul (data-column="c" olan td)
        // Örn: <td data-column="c" ...>19,8700</td>
        QRegularExpression priceRe("<td[^>]*data-column=\"c\"[^>]*>([^<]+)</td>");

        // Sadece o satırın devamındaki ilk fiyatı almak için sembolden sonraki kısmı tara
        QRegularExpressionMatch priceMatch = priceRe.match(pageContent, match.capturedEnd());

        if (priceMatch.hasMatch()) {
            QString fiyat = priceMatch.captured(1).trimmed();
            exchanges.insert(symbol, fiyat.replace(",", ".").toDouble());
        }
    }

    // --- EĞER TABLO YAPISI BOŞSA ESKİ LİSTE YAPISINI DENE (337 KB'lık versiyon) ---
    if (exchanges.isEmpty()) {
        QRegularExpression listRe("data-symbol=\"([^\"]+)\"");
        QRegularExpressionMatchIterator iList = listRe.globalMatch(pageContent);

        while (iList.hasNext()) {
            QRegularExpressionMatch match = iList.next();
            QString symbol = match.captured(1);
            QRegularExpression priceRe("id=\"h_td_fiyat_id_" + symbol + "\"[^>]*>([^<]+)</li>");
            QRegularExpressionMatch priceMatch = priceRe.match(pageContent);

            if (priceMatch.hasMatch()) {
                QString fiyat = priceMatch.captured(1).trimmed();
                exchanges.insert(symbol, fiyat.replace(",", ".").toDouble());
            }
        }
    }

    qInfo() << "Çekilen toplam veri adedi:" << exchanges.size();
    emit getStocks(exchanges);
}

QString Currency::currencyToString(CurrencyType currency) {
    switch (currency) {
    case CurrencyType::AUD: return "AUD";
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

QString Currency::XAUToString(XAUtype XAU)
{
    switch (XAU) {
    case XAUtype::GrXAU: return "GrXAU";
    default: return "UNKNOWN";
    }
}

XAUtype Currency::stringToXAU(const QString &XAUStr)
{
    static const QMap<QString, XAUtype> XAUMap = {
        {"GrXAU", XAUtype::GrXAU}
    };

    return XAUMap.value(XAUStr.toUpper(), XAUtype::UNKNOWN);
}

QStringList Currency::XAUToStringList(QList<int> XAUs)
{
    QStringList result;
    for (int XAUInt : XAUs) {
        XAUtype xau = static_cast<XAUtype>(XAUInt);
        result.append(XAUToString(xau));
    }
    return result;
}

void Currency::getXAUData()
{
    QUrl url("https://altin.in/fiyat/gram-altin");
    QNetworkRequest request(url);
    managerGold.get(request);
}

void Currency::getExchangesData()
{
    QUrl url("https://bigpara.hurriyet.com.tr/borsa/canli-borsa/");
    QNetworkRequest request(url);

    // Tarayıcı taklidi yapıyoruz
    //request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36");

    managerExchange.get(request);
}


