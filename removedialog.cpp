#include "removedialog.h"
#include "ui_removedialog.h"

RemoveDialog::RemoveDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveDialog)
{
    ui->setupUi(this);
    comment.clear();
    price.first="";
    price.second=0;

    ui->comboBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox->view()->setMinimumHeight(100);
    ui->comboBox->view()->setMaximumHeight(550);
}

RemoveDialog::~RemoveDialog()
{
    delete ui;
}

void RemoveDialog::setPrices(const QMap<QString, double> &newPrices)
{
    prices = newPrices;

    // Sinyal tetiklenmesin diye geçici olarak engelle
    ui->comboBox->blockSignals(true);
    ui->comboBox->clear();
    ui->comboBox->addItems(prices.keys());
    ui->comboBox->blockSignals(false);

    // İlk item'i manuel olarak tetikle
    if (!prices.isEmpty())
        on_comboBox_currentTextChanged(ui->comboBox->currentText());
}

void RemoveDialog::setUsername(const QString &newUsername)
{
    m_username = newUsername;
}


void RemoveDialog::save()
{
    price.first=ui->comboBox->currentText();
    price.second=ui->doubleSpinBox->value();
    comment=ui->cmntLine->text();
}

void RemoveDialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->doubleSpinBox->setMaximum(db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(arg1)),"SavingAmount").toDouble());
}


void RemoveDialog::on_horizontalSlider_valueChanged(int value)
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


void RemoveDialog::on_buttonBox_accepted()
{
    save();
    accept();
}


void RemoveDialog::on_buttonBox_rejected()
{
    reject();
}

QString RemoveDialog::getComment() const
{
    return comment;
}

QPair<QString, double> RemoveDialog::getPrice() const
{
    return price;
}

