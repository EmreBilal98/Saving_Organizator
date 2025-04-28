#ifndef REMOVEGOLDDIALOG_H
#define REMOVEGOLDDIALOG_H

#include <QDialog>

namespace Ui {
class RemoveGoldDialog;
}

class RemoveGoldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveGoldDialog(QWidget *parent = nullptr);
    ~RemoveGoldDialog();



    double getRemovedAmount() const;

    void setTotalAmount(double newTotalAmount);

    QString getComment() const;

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RemoveGoldDialog *ui;
    double RemovedAmount,totalAmount;
    QString comment;

    void save();
};

#endif // REMOVEGOLDDIALOG_H
