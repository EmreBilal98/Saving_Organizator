#ifndef REMOVEEXCHANGEDIALOG_H
#define REMOVEEXCHANGEDIALOG_H

#include <QDialog>
#include <QPair>
#include "database.h"

namespace Ui {
class RemoveExchangeDialog;
}

class RemoveExchangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveExchangeDialog(QWidget *parent = nullptr);
    ~RemoveExchangeDialog();

    void setUsername(const QString &newUsername);

    QPair<QString, int> getStockandpice() const;

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RemoveExchangeDialog *ui;
    Database db;
    QString username;
    QPair<QString,int> stockandpice;

    void init();
    void save();
};

#endif // REMOVEEXCHANGEDIALOG_H
