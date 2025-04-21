#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    init();
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_buttonBox_accepted()
{
    save();
    accept();
}


void AddDialog::on_buttonBox_rejected()
{
    reject();
}

double AddDialog::getAmount() const
{
    return amount;
}

int AddDialog::getCurrency() const
{
    return currency;
}

void AddDialog::init()
{
    currency=0;
    amount=0;
    QStringList currencies;
    for(int i=0;i<static_cast<int>(CurrencyType::COUNT)-1;i++){
        ui->comboBox->addItem(Currency::currencyToString(static_cast<CurrencyType>(i)));
    }
    // currencies<<"Dolar"<<"Euro";
    // foreach (QString item, currencies) {
    //     ui->comboBox->addItem(item);
    // }
}

void AddDialog::save()
{
    currency=ui->comboBox->currentIndex();
    amount=ui->doubleSpinBox->value();
    // File file("erqut");
    // file.addLineToFile(ui->comboBox->currentText(),amount,"fddbhdjkfbsdjfld");

}

