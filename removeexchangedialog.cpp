#include "removeexchangedialog.h"
#include "ui_removeexchangedialog.h"

RemoveExchangeDialog::RemoveExchangeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveExchangeDialog)
{
    ui->setupUi(this);

}

RemoveExchangeDialog::~RemoveExchangeDialog()
{
    delete ui;
}

void RemoveExchangeDialog::setUsername(const QString &newUsername)
{
    username = newUsername;
    init();
}

void RemoveExchangeDialog::init()
{
    QStringList stocks=db.getList(username,3,"StockName");
    qInfo()<<stocks;
    ui->comboBox->addItems(db.getList(username,3,"StockName"));

}

void RemoveExchangeDialog::save()
{
    stockandpice.first=ui->comboBox->currentText();;
    stockandpice.second=ui->spinBox->value();
}

void RemoveExchangeDialog::on_horizontalSlider_valueChanged(int value)
{
    int scrollMin = ui->horizontalSlider->minimum();
    int scrollMax = ui->horizontalSlider->maximum();
    int spinMin = ui->spinBox->minimum();
    int spinMax = ui->spinBox->maximum();

    // ScrollBar konumuna göre yüzde hesapla
    double ratio = static_cast<double>(value - scrollMin) / (scrollMax - scrollMin);
    int spinValue = spinMin + ratio * (spinMax - spinMin);

    ui->spinBox->setValue(spinValue);
}


void RemoveExchangeDialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->spinBox->setMaximum(db.getExchangeValue(username,ui->comboBox->currentText(),3,"SavingAmount").toInt());
}

QPair<QString, int> RemoveExchangeDialog::getStockandpice() const
{
    return stockandpice;
}


void RemoveExchangeDialog::on_buttonBox_accepted()
{
    save();
    accept();
}


void RemoveExchangeDialog::on_buttonBox_rejected()
{
    reject();
}

