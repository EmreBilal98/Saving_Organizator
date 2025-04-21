#include "file.h"

File::File(const QString& username):QFile(username+QString(".html"))
{
    // bir html dosyası olacağı için burada dosya ilk oluşturulurkenki configurationlar yapılıyor
    if(!this->exists()){

        if(!this->open(QIODevice::WriteOnly)) return;

        QTextStream  stream(this);
        QByteArray data;
        data.append("<html><body>");//dosya başına ekleniyor
        stream<<data;

        this->close();

    }
}

bool File::addLineToFile(QString currencyType, double currencyAmount, QString comment,double currencyBalance,bool transaction)
{
    if(!this->open(QIODevice::ReadOnly)) return false;

    QByteArray availableConntents=this->readAll();//her yeni satır en başa yazılsın diye dosya içeriği
    //alınıyor.Yeni içerik dosyaya yazıılacak sonra bu tekrar attılacak

    this->close();

    if(!this->open(QIODevice::WriteOnly)) return false;

    QTextStream  stream(this);
    QByteArray data;
    //ekleme ise yeşil silme ise kırmızı label içinde nnottumuz yazılıyor
    data.append(QString("<p><span style='color: %0;'>").arg(transaction?"green":"red").toLatin1());
    data.append(currencyType.toLatin1());
    data.append(QByteArray("\t"));
    data.append((transaction?QString("+").toLatin1():QString("-").toLatin1())+QString::number(currencyAmount).toLatin1());
    data.append(QByteArray("\t"));
    data.append(comment .toUtf8());//açıklamada türkçe karakter kullanabilmek için utf8 e çevrildi
    data.append(QByteArray("\t"));
    data.append(QString::number(currencyBalance).toLatin1());
    data.append(QByteArray("\t"));
    QString dateTime=QDateTime::currentDateTime().toString();
    data.append(dateTime.toLatin1());
    data.append(QByteArray("\r\n"));
    data.append("</span></p>");
    stream<<data;
    stream<<availableConntents;
    stream<<"</body></html>";
    this->close();

    return true;


}

