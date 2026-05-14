#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/saving_organizer_icons/main.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
