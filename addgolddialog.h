#ifndef ADDGOLDDIALOG_H
#define ADDGOLDDIALOG_H

#include <QDialog>

namespace Ui {
class AddGoldDialog;
}

class AddGoldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGoldDialog(QWidget *parent = nullptr);
    ~AddGoldDialog();

    double getAmount() const;

    QString getComment() const;
    void save();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddGoldDialog *ui;
    double amount;
    QString comment;
};

#endif // ADDGOLDDIALOG_H
