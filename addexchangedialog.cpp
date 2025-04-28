#include "addexchangedialog.h"
#include "ui_addexchangedialog.h"

AddExchangeDialog::AddExchangeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddExchangeDialog)
{
    ui->setupUi(this);

}

AddExchangeDialog::~AddExchangeDialog()
{
    delete ui;
}

double AddExchangeDialog::getAmount() const
{
    return amount;
}

QString AddExchangeDialog::getComment() const
{
    return comment;
}

void AddExchangeDialog::setStocksAndprices(const QMap<QString, double> &newStocksAndprices)
{
    stocksAndprices = newStocksAndprices;
    init();
}

void AddExchangeDialog::init()
{
    qInfo()<<"gldi benikii\n"<<stocksAndprices;
    ui->comboBox->addItems(stocksAndprices.keys());
}

void AddExchangeDialog::save()
{
    stock=ui->comboBox->currentText();
    amount=ui->spinBox->value();
    comment=ui->lineEdit->text();
}

void AddExchangeDialog::on_buttonBox_accepted()
{
    save();
    accept();
}

QString AddExchangeDialog::getStock() const
{
    return stock;
}


void AddExchangeDialog::on_buttonBox_rejected()
{
    reject();
}

