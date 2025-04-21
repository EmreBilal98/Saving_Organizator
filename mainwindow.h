#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QStringList>
#include <QList>
#include <QMap>
#include "database.h"
#include "adddialog.h"
#include "currency.h"
#include "removedialog.h"
#include "file.h"


enum StackedWidgetIdex{
    LOGIN,USER,ACTIVITIES,SIGNUP
};


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

    void on_actionRemove_Saving_triggered();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btnsuLogIn_clicked();

    void on_actionLog_Out_triggered();

    void on_actionAccount_Activities_triggered();

    void on_actionMain_Page_triggered();

private:
    Ui::MainWindow *ui;
    Database db;
    QMap<QString,double> prices;
    QStandardItemModel model;
    QStringList activities;
    QString m_username,m_password;
    File *file;

    void init();
    void errorExceptions(int &error);
    void setModel();
    QMap<QString,double> currencyCheck(const QString &base, const QStringList &target);
    void enableActions(StackedWidgetIdex widgetIndex);

};
#endif // MAINWINDOW_H
