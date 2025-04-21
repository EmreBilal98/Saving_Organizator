#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include  <QStringList>
#include  "currency.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

    int getCurrency() const;

    double getAmount() const;

    QString getComment() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddDialog *ui;
    int currency;
    double amount;
    QString comment;

    void init();
    void save();
};

#endif // ADDDIALOG_H
