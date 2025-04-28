#include "removegolddialog.h"
#include "ui_removegolddialog.h"

RemoveGoldDialog::RemoveGoldDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveGoldDialog)
{
    ui->setupUi(this);
    comment.clear();
}

RemoveGoldDialog::~RemoveGoldDialog()
{
    delete ui;
}

double RemoveGoldDialog::getRemovedAmount() const
{
    return RemovedAmount;
}

void RemoveGoldDialog::setTotalAmount(double newTotalAmount)
{
    totalAmount = newTotalAmount;
    ui->doubleSpinBox->setMaximum(totalAmount);
}

void RemoveGoldDialog::on_horizontalSlider_valueChanged(int value)
{
    int scrollMin = ui->horizontalSlider->minimum();
    int scrollMax = ui->horizontalSlider->maximum();
    int spinMin = ui->doubleSpinBox->minimum();
    int spinMax = ui->doubleSpinBox->maximum();

    // ScrollBar konumuna göre yüzde hesapla
    double ratio = static_cast<double>(value - scrollMin) / (scrollMax - scrollMin);
    int spinValue = spinMin + ratio * (spinMax - spinMin);

    ui->doubleSpinBox->setValue(spinValue);
}

void RemoveGoldDialog::save()
{
    comment=ui->lineEdit->text();
    RemovedAmount=ui->doubleSpinBox->value();;
}

QString RemoveGoldDialog::getComment() const
{
    return comment;
}


void RemoveGoldDialog::on_buttonBox_accepted()
{
    save();
    accept();
}


void RemoveGoldDialog::on_buttonBox_rejected()
{
    reject();
}

