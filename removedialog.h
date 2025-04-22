#ifndef REMOVEDIALOG_H
#define REMOVEDIALOG_H

#include <QDialog>
#include <QThread>
#include "database.h"
#include "currency.h"

namespace Ui {
class RemoveDialog;
}

class RemoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveDialog(QWidget *parent = nullptr);
    ~RemoveDialog();

    void setPrices(const QMap<QString, double> &newPrices);

    void setUsername(const QString &newUsername);

    QPair<QString, double> getPrice() const;

    QString getComment() const;

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RemoveDialog *ui;
    QMap<QString,double> prices;
    QString m_username;
    Database db;
    QPair<QString, double> price;
    QString comment;

    void save();
};

#endif // REMOVEDIALOG_H
