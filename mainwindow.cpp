#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{
    if(db.searchValue("username",ui->lineUsername->text()) && db.searchValue("password",ui->linePassword->text())){
        m_username=ui->lineUsername->text();
        m_password=ui->linePassword->text();
        setModel();

        ui->actionAdd_Saving->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
        QMessageBox::critical(this,"Log in error","Username or password wrong");
}

void MainWindow::signUp()
{

    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::init()
{
    QPushButton *btn_login=new QPushButton("Log in",this);
    QPushButton *btn_signUp=new QPushButton("Sign up",this);

    connect(btn_login,&QPushButton::clicked,this,&MainWindow::login);
    connect(btn_signUp,&QPushButton::clicked,this,&MainWindow::signUp);

    ui->buttonBox->addButton(btn_login,QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton(btn_signUp,QDialogButtonBox::ButtonRole::ActionRole);

    model.setColumnCount(3);

    model.setHeaderData(0, Qt::Horizontal, "currency");
    model.setHeaderData(1, Qt::Horizontal, "amount");
    model.setHeaderData(2, Qt::Horizontal, "TL base");

    ui->tableView->setModel(&model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    m_username.clear();
    m_password.clear();
    ui->actionAdd_Saving->setEnabled(false);




}

void MainWindow::errorExceptions(int &error)
{
    if(error==1){
        QMessageBox::critical(this,"username is duplicate","Your username using by other our user!!!");
    }
}

void MainWindow::setModel()
{
    int row=0;
    qInfo()<<db.getCurrencies(m_username);
    if(db.getCurrencies(m_username).isEmpty()) return;
    QMap<QString,double> values=currencyCheck("TRY",Currency::currencyToStringList(db.getCurrencies(m_username)));
    qInfo()<<values;
    foreach(QString key,values.keys()){
        for(int column = 0; column < 3; ++column) {
            QStandardItem *item = new QStandardItem();
            if(!column){
                item->setText(QString("%0").arg(key));
                //curVal=currencyCheck("TRY",currencyToString(static_cast<CurrencyType>(currency)));
                qInfo()<<key<<":"<<values.value(key);
            }
            else if(column==1)
                item->setText(QString("%0").arg(db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(key)),"SavingAmount")));
            else{
                double TLBaseCurrency=1/values.value(key);
                qInfo()<<key<<":"<<TLBaseCurrency<<" Carpan::"<<(db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(key)),"SavingAmount").toDouble());
                double val=(db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(key)),"SavingAmount").toDouble())*TLBaseCurrency;
                item->setText(QString("%0").arg(val));
            }
            model.setItem(row,column,item);

        }
        row++;
    }
}

QMap<QString,double> MainWindow::currencyCheck(const QString &base, const QStringList &target)
{
    Currency *api=new Currency(this);
    api->currencyRequest(base);
    QStringList srcCur;
    foreach (QString item, target) {
        srcCur.append(base+item);
    }
    qInfo()<<target;
    //qInfo()<<srcCur;
    QMap<QString,double> val;
    QEventLoop loop;
    connect(api,&Currency::getValue,api,[&target,&val,&loop](QMap<QString,double> currencies){

        foreach(QString item,target){
        if(currencies.contains(item))
        val.insert(item.remove("TRY"),currencies[item]);
        }
        loop.quit();
    });

    loop.exec();

    return val;
}

// QString MainWindow::currencyToString(CurrencyType currency) {
//     switch (currency) {
//     case CurrencyType::USD: return "USD";
//     case CurrencyType::EUR: return "EUR";
//     default: return "Unknown";
//     }
// }

// CurrencyType MainWindow::stringToCurrency(const QString &currencyStr) {
//     if (currencyStr == "USD") return CurrencyType::USD;
//     else if (currencyStr == "EUR") return CurrencyType::EUR;
//     else return CurrencyType::UNKNOWN; // veya default bir değer
// }

// QStringList MainWindow::currencyToStringList(QList<int> currencies) {
//     qInfo()<<currencies;
//     QStringList result;
//     foreach (int curInt, currencies) {
//         CurrencyType currency=static_cast<CurrencyType>(curInt);
//         switch (currency) {
//         case CurrencyType::USD:
//             result.append("USD");
//             break;
//         case CurrencyType::EUR:
//             result.append("EUR");
//             break;
//         default: result.append("Unknown");
//         }
//     }
//     return  result;

// }

void MainWindow::on_btnSignUp_clicked()
{
    if(ui->lineEdit_suPass->text().compare(ui->lineEdit_suPassVerify->text())!=0){
        QMessageBox::critical(this,"password verification error","Your passwords different from each  other!!!");
        return;
    }
    int error;
    if(!db.createUser(ui->lineEdit_suUsername->text(),ui->lineEdit_suPass->text(),error))
    {
        errorExceptions(error);
        return;
    }

    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_actionAdd_Saving_triggered()
{
    AddDialog *dlg=new AddDialog(this);
    dlg->exec();

    qInfo()<<dlg->getAmount();
    qInfo()<<dlg->getCurrency();


    qInfo()<<db.setValue(m_username,m_password,dlg->getCurrency(),dlg->getAmount());

    setModel();

}

