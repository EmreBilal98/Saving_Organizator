#ifndef ADDEXCHANGEDIALOG_H
#define ADDEXCHANGEDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class AddExchangeDialog;
}

class AddExchangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExchangeDialog(QWidget *parent = nullptr);
    ~AddExchangeDialog();

    double getAmount() const;

    QString getComment() const;

    void setStocksAndprices(const QMap<QString, double> &newStocksAndprices);

    QString getStock() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddExchangeDialog *ui;
    QMap<QString,double> stocksAndprices;
    double amount;
    QString stock,comment;

    void init();
    void save();
};

#endif // ADDEXCHANGEDIALOG_H
