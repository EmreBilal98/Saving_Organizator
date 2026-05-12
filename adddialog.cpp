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

QString AddDialog::getComment() const
{
    return comment;
}

double AddDialog::getAmount() const
{
    return amount;
}

int AddDialog::getCurrency() const
{
    return currency;
}

double AddDialog::getPrice() const
{
    return price;
}

void AddDialog::init()
{
    currency=0;
    amount=0;
    comment.clear();
    ui->comboBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox->view()->setMinimumHeight(100);
    ui->comboBox->view()->setMaximumHeight(550);
    ui->Price_spinbox->setEnabled(false);
    connect(ui->chk_activate, &QCheckBox::toggled, ui->Price_spinbox, &QDoubleSpinBox::setEnabled);
    for(int i=0;i<static_cast<int>(CurrencyType::COUNT)-1;i++){
        ui->comboBox->addItem(Currency::currencyToString(static_cast<CurrencyType>(i)));
    }

}

void AddDialog::save()
{
    currency=ui->comboBox->currentIndex();
    amount=ui->doubleSpinBox->value();
    comment=ui->cmntLine->text();
    ui->chk_activate->isChecked()?price=ui->Price_spinbox->value():price=-1;

}

