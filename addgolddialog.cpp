#include "addgolddialog.h"
#include "ui_addgolddialog.h"

AddGoldDialog::AddGoldDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGoldDialog)
{
    ui->setupUi(this);
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

void AddGoldDialog::save()
{
    comment=ui->lineEdit->text();
    amount=ui->doubleSpinBox->value();;
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

