#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QMap>
#include "database.h"
#include "adddialog.h"
#include "currency.h"


// enum CurrencyType {
//     USD,
//     EUR,
//     UNKNOWN
// };


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void login();
    void signUp();
    void on_btnSignUp_clicked();

    void on_actionAdd_Saving_triggered();

private:
    Ui::MainWindow *ui;
    Database db;
    QStandardItemModel model;
    QString m_username,m_password;

    void init();
    void errorExceptions(int &error);
    void setModel();
    QMap<QString,double> currencyCheck(const QString &base, const QStringList &target);
    // QString currencyToString(CurrencyType currency);
    // CurrencyType stringToCurrency(const QString &currencyStr);

    // QStringList currencyToStringList(QList<int> currencies);
};
#endif // MAINWINDOW_H
