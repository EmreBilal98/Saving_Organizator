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
        ui->lineUsername->clear();
        ui->linePassword->clear();
        stockExchanges=stockExchangeCheck();


        setModel();
        setModel2();
        file=new File(m_username);

        //ui->actionAdd_Saving->setEnabled(true);


        ui->stackedWidget->setCurrentIndex(USER);
    }
    else
        QMessageBox::critical(this,"Log in error","Username or password wrong");
}

void MainWindow::signUp()
{

    ui->stackedWidget->setCurrentIndex(SIGNUP);

}

void MainWindow::init()
{
    //password lineEditlerine ggizli yazım modu verildi
    ui->linePassword->setEchoMode(QLineEdit::Password);
    ui->lineEdit_suPass->setEchoMode(QLineEdit::Password);
    ui->lineEdit_suPassVerify->setEchoMode(QLineEdit::Password);


    QPushButton *btn_login=new QPushButton("Log in",this);
    QPushButton *btn_signUp=new QPushButton("Sign up",this);

    connect(btn_login,&QPushButton::clicked,this,&MainWindow::login);
    connect(btn_signUp,&QPushButton::clicked,this,&MainWindow::signUp);

    ui->buttonBox->addButton(btn_login,QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton(btn_signUp,QDialogButtonBox::ButtonRole::ActionRole);

    model.setColumnCount(5);

    model.setHeaderData(0, Qt::Horizontal, "currency");
    model.setHeaderData(1, Qt::Horizontal, "amount");
    model.setHeaderData(2, Qt::Horizontal, "TL equivalent");
    model.setHeaderData(3, Qt::Horizontal, "TL cost");
    model.setHeaderData(4, Qt::Horizontal, "TL profit");

    ui->tableView->setModel(&model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    modelXAU.setColumnCount(5);

    modelXAU.setHeaderData(0, Qt::Horizontal, "currency");
    modelXAU.setHeaderData(1, Qt::Horizontal, "amount");
    modelXAU.setHeaderData(2, Qt::Horizontal, "TL equivalent");
    modelXAU.setHeaderData(3, Qt::Horizontal, "TL cost");
    modelXAU.setHeaderData(4, Qt::Horizontal, "TL profit");

    ui->tableView_xau->setModel(&modelXAU);

    ui->tableView_xau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    modelExchange.setColumnCount(5);

    modelExchange.setHeaderData(0, Qt::Horizontal, "currency");
    modelExchange.setHeaderData(1, Qt::Horizontal, "amount");
    modelExchange.setHeaderData(2, Qt::Horizontal, "TL equivalent");
    modelExchange.setHeaderData(3, Qt::Horizontal, "TL cost");
    modelExchange.setHeaderData(4, Qt::Horizontal, "TL profit");

    ui->tableView_exchange->setModel(&modelExchange);

    ui->tableView_exchange->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    m_username.clear();
    m_password.clear();

    ui->stackedWidget->setCurrentIndex(LOGIN);
    on_stackedWidget_currentChanged(LOGIN);
    //ui->actionAdd_Saving->setEnabled(false);




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
    prices=currencyCheck("TRY",Currency::currencyToStringList(db.getCurrencies(m_username)));
    qInfo()<<prices;
    foreach(QString key,prices.keys()){
        for(int column = 0; column < 5; ++column) {
            QStandardItem *item = new QStandardItem();
            if(column==0){
                item->setText(QString("%0").arg(key));
                qInfo()<<key<<":"<<prices.value(key);
            }
            else if(column==1)
                item->setText(QString("%0").arg(db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(key)),1,"SavingAmount")));
            else if(column==2){
                double TLBaseCurrency=1/prices.value(key);
                qInfo()<<key<<":"<<TLBaseCurrency<<" Carpan::"<<(db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(key)),1,"SavingAmount").toDouble());
                double val=(db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(key)),1,"SavingAmount").toDouble())*TLBaseCurrency;
                item->setText(QString("%0").arg(val));
            }
            else if(column==3){
                double  val=db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(key)),1,"cost").toDouble();
                qInfo()<<"cost:"<<val;
                item->setText(QString("%0").arg(val));
            }
            else if(column==4){
                double val=model.item(row,2)->text().toDouble()-model.item(row,3)->text().toDouble();
                item->setText(QString("%0").arg(val));
            }
            model.setItem(row,column,item);

        }
        row++;
    }
}

void MainWindow::setModel2()
{
    QStringList exchanges,XAUs;
    exchanges=db.getList(m_username,3,"StockName");
    XAUs=db.getList(m_username,2,"currencyType");
    qInfo()<<"exchange:"<<exchanges;
    qInfo()<<"XAUs:"<<XAUs;
    int row=0;
    foreach (QString stock, exchanges) {
        for(int column = 0; column < 5; ++column) {
            QStandardItem *item = new QStandardItem();
            if(column==0){
                item->setText(stock);
            }
            else if(column==1){
                item->setText(db.getExchangeValue(m_username,stock,3,"SavingAmount"));
            }
            else if(column==2){
                qInfo()<<"amoount:"<<db.getExchangeValue(m_username,stock,3,"SavingAmount").toDouble()<<"value:"<<stockExchanges.value(stock);
                item->setText(QString::number((db.getExchangeValue(m_username,stock,3,"SavingAmount").toDouble())*stockExchanges.value(stock)));
            }
            else if(column==3){
                item->setText(db.getExchangeValue(m_username,stock,3,"cost"));
            }
            else if(column==4){
                double val=modelExchange.item(row,2)->text().toDouble()-modelExchange.item(row,3)->text().toDouble();
                item->setText(QString::number(val));
            }
            modelExchange.setItem(row,column,item);

        }
        row++;
    }
    row=0;
    foreach (QString xau, XAUs) {
        for(int column = 0; column < 5; ++column) {
            QStandardItem *item = new QStandardItem();
            if(column==0){
                item->setText(Currency::XAUToString(static_cast<XAUtype>(xau.toInt())));
            }
            else if(column==1){
                item->setText(db.getValue(m_username,xau.toInt(),2,"SavingAmount"));
            }
            else if(column==2){
                item->setText(QString::number((modelXAU.item(row,1)->text().toDouble())*XAUSellCheck()));
            }
            else if(column==3){
                item->setText(db.getValue(m_username,xau.toInt(),2,"cost"));
            }
            else if(column==4){
                double val=modelXAU.item(row,2)->text().toDouble()-modelXAU.item(row,3)->text().toDouble();
                item->setText(QString::number(val));
            }
            modelXAU.setItem(row,column,item);

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

double MainWindow::XAUBuyCheck()
{
    double price;
    Currency *api=new Currency(this);
    QEventLoop loop;
    connect(api,&Currency::getBuyXAUPrice,api,[&price,&loop](double XAUbuyPrice){

        price=XAUbuyPrice;
        loop.quit();
    });
    api->getXAUData();
    loop.exec();

    return price;
}

double MainWindow::XAUSellCheck()
{
    double price;
    Currency *api=new Currency(this);
    QEventLoop loop;
    connect(api,&Currency::getSellXAUPrice,api,[&price,&loop](double XAUsellPrice){

        price=XAUsellPrice;
        loop.quit();
    });
    api->getXAUData();
    loop.exec();
    qInfo()<<"altin satis:"<<price;
    return price;
}

QMap <QString,double> MainWindow::stockExchangeCheck()
{
    QMap <QString,double> myExchanges;
    Currency *api=new Currency(this);
    QEventLoop loop;
    QObject::connect(api,&Currency::getStocks,api,[&myExchanges,&loop](QMap <QString,double> exchanges){
        //qInfo()<<"get ici:"<<exchanges;
        myExchanges=exchanges;
        loop.quit();
    });
    api->getExchangesData();
    loop.exec();
    //qInfo()<<"get dışı:"<<myExchanges;
    return myExchanges;
}

void MainWindow::enableActions(StackedWidgetIdex widgetIndex)
{
    if(widgetIndex==StackedWidgetIdex::USER || widgetIndex==StackedWidgetIdex::ACTIVITIES){
        ui->actionAccount_Activities->setEnabled((widgetIndex==StackedWidgetIdex::ACTIVITIES)?false:true);
        ui->actionMain_Page->setEnabled((widgetIndex==StackedWidgetIdex::USER)?false:true);
        ui->actionAdd_Saving->setEnabled(true);
        ui->actionRemove_Saving->setEnabled(true);
        ui->actionLog_Out->setEnabled(true);
        ui->actionAdd_Gold->setEnabled(true);
        ui->actionadd_Exchange->setEnabled(true);
        return;
    }
    ui->actionAccount_Activities->setEnabled(false);
    ui->actionMain_Page->setEnabled(false);
    ui->actionAdd_Saving->setEnabled(false);
    ui->actionRemove_Saving->setEnabled(false);
    ui->actionLog_Out->setEnabled(false);
    ui->actionAdd_Gold->setEnabled(false);
    ui->actionadd_Exchange->setEnabled(false);
}

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

    ui->lineEdit_suUsername->clear();
    ui->lineEdit_suPass->clear();
    ui->lineEdit_suPassVerify->clear();

    ui->stackedWidget->setCurrentIndex(LOGIN);
}


void MainWindow::on_actionAdd_Saving_triggered()
{
    AddDialog *dlg=new AddDialog(this);
    dlg->exec();

    qInfo()<<dlg->getAmount();
    qInfo()<<dlg->getCurrency();
    QStringList getCurValue;
    getCurValue.append(Currency::currencyToString(static_cast<CurrencyType>(dlg->getCurrency())));
    double cost=(1/currencyCheck("TRY",getCurValue).value(getCurValue.first()))*dlg->getAmount();
    qInfo()<<db.setValue(m_username,m_password,dlg->getCurrency(),dlg->getAmount(),ADD,cost);

    file->addLineToFile(Currency::currencyToString(static_cast<CurrencyType>(dlg->getCurrency())),dlg->getAmount(),dlg->getComment(),db.getValue(m_username,dlg->getCurrency(),1,"SavingAmount").toDouble(),ADD);


    setModel();

}


void MainWindow::on_actionRemove_Saving_triggered()
{
    RemoveDialog  *dlg=new RemoveDialog(this);
    dlg->setUsername(m_username);
    dlg->setPrices(prices);


    int  result=dlg->exec();

    if(result==RemoveDialog::Accepted){

        db.setValue(m_username,m_password,static_cast<int>(Currency::stringToCurrency(dlg->getPrice().first)),dlg->getPrice().second,SUB);

        file->addLineToFile(dlg->getPrice().first,dlg->getPrice().second,dlg->getComment(),db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(dlg->getPrice().first)),1,"SavingAmount").toDouble(),SUB);
        setModel();
    }



}


void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    enableActions(static_cast<StackedWidgetIdex>(arg1));
}


void MainWindow::on_btnsuLogIn_clicked()
{
    QMessageBox::StandardButton  reply;
    reply=QMessageBox::question(this,"Are you sure?","The button will send you to  Log in sccreen",QMessageBox::Yes|QMessageBox::No);

    if(reply==QMessageBox::Yes)
    ui->stackedWidget->setCurrentIndex(LOGIN);
}


void MainWindow::on_actionLog_Out_triggered()
{
    m_username.clear();
    m_password.clear();
    QMessageBox::StandardButton  reply;
    reply=QMessageBox::question(this,"Are you sure?","The button will log out you",QMessageBox::Yes|QMessageBox::No);

    if(reply==QMessageBox::Yes)
        ui->stackedWidget->setCurrentIndex(LOGIN);
}


void MainWindow::on_actionAccount_Activities_triggered()
{
    if(file->open(QIODevice::ReadOnly)){

        ui->textEdit->setHtml(file->readAll());

        file->close();
    }
    ui->stackedWidget->setCurrentIndex(ACTIVITIES);
}


void MainWindow::on_actionMain_Page_triggered()
{
    ui->stackedWidget->setCurrentIndex(USER);
}


void MainWindow::on_actionAdd_Gold_triggered()
{
    XAUprice=XAUBuyCheck();
    qInfo()<<"XAUprice:"<<XAUprice<<"\n\n\n";
    AddGoldDialog *dlg=new  AddGoldDialog(this);;
    dlg->exec();
    qInfo()<<dlg->getAmount();
    db.setValue(m_username,m_password,0,dlg->getAmount(),ADD,dlg->getAmount()*XAUprice,2);
    setModel2();
}


void MainWindow::on_actionadd_Exchange_triggered()
{
    stockExchanges=stockExchangeCheck();
    AddExchangeDialog *dlg=new AddExchangeDialog(this);
    dlg->setStocksAndprices(stockExchanges);

    dlg->exec();
    db.setValue(m_username,m_password,0,dlg->getAmount(),ADD,dlg->getAmount()*stockExchanges.value(dlg->getStock()),3,dlg->getStock());
    setModel2();

}


void MainWindow::on_actionRemove_Gold_triggered()
{
    RemoveGoldDialog *dlg=new RemoveGoldDialog(this);
    dlg->setTotalAmount(db.getValue(m_username,0,2,"SavingAmount").toDouble());
    int  result=dlg->exec();

    if(result==RemoveDialog::Accepted){

        db.setValue(m_username,m_password,0,dlg->getRemovedAmount(),SUB,0,2);

        //file->addLineToFile(dlg->getPrice().first,dlg->getPrice().second,dlg->getComment(),db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(dlg->getPrice().first)),1,"SavingAmount").toDouble(),SUB);
        setModel2();
    }

}


void MainWindow::on_actionRemove_exchange_triggered()
{
    RemoveExchangeDialog *dlg=new RemoveExchangeDialog(this);
    dlg->setUsername(m_username);
    int  result=dlg->exec();


    if(result==RemoveDialog::Accepted){

        db.setValue(m_username,m_password,0,dlg->getStockandpice().second,SUB,0,3,dlg->getStockandpice().first);

        //file->addLineToFile(dlg->getPrice().first,dlg->getPrice().second,dlg->getComment(),db.getValue(m_username,static_cast<int>(Currency::stringToCurrency(dlg->getPrice().first)),1,"SavingAmount").toDouble(),SUB);
        setModel2();
    }
}

