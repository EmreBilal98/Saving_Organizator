#include "addgolddialog.h"
#include "ui_addgolddialog.h"

AddGoldDialog::AddGoldDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGoldDialog)
{
    ui->setupUi(this);
    ui->price_spinBox->setEnabled(false);
    connect(ui->chk_activate, &QCheckBox::toggled, ui->price_spinBox, &QDoubleSpinBox::setEnabled);
}

AddGoldDialog::~AddGoldDialog()
{
    delete ui;
}

double AddGoldDialog::getAmount() const
{
    return amount;
}

QString AddGoldDialog::getComment() const
{
    return comment;
}

double AddGoldDialog::getPrice() const
{
    return price;
}


void AddGoldDialog::save()
{
    comment=ui->lineEdit->text();
    amount=ui->doubleSpinBox->value();
    ui->chk_activate->isChecked()?price=ui->price_spinBox->value():price=-1;

}

void AddGoldDialog::on_buttonBox_accepted()
{
    save();
    accept();
}


void AddGoldDialog::on_buttonBox_rejected()
{
    reject();
}





